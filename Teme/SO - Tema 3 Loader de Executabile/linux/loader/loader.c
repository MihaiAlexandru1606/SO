#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>

#include "exec_parser.h"

/**
 * calculeaza calculeaza minimul, il folosesc ca dimensiune alocat sa fie
 * de cel mult pageSize
 */

#define MAX_MEM_SIZE(a, b) ((a) <= (b) ? (a) : (b))
#define NULL_INDEX		-1
#define NULL_FILE_DESCRIPTOR	-1

static so_exec_t *exec;
static struct sigaction old_action;
static int file_descriptor;

/**
 * functia verifica daca o adresa la care s-a produs respectivul page fault se
 * afla intr-un unul dintre segmente
 * @param addr adresa unde s-a produs page fault
 * @param exe retine informati despre executabil
 * @return index-ul segmentului in care se gaseste acea adresa
 */
static int index_segment(uintptr_t addr, so_exec_t *exe)
{

	for (int i = 0; i < exe->segments_no; ++i)
		if (exe->segments[i].vaddr <= addr &&
		    addr <= exe->segments[i].vaddr + exe->segments[i].mem_size)
			return i;


	return NULL_INDEX;
}

static void seg_fault_handler(int signum, siginfo_t *siginfo, void *context)
{
	/**
	 * se verifica ca segnalul sa provina de la un seg fault pentru cazul
	 * in care memoria nu este mapata
	 */
	if (signum != SIGSEGV || siginfo->si_code != SEGV_MAPERR)
		goto OLD_ACTION;

	int page_size = getpagesize();

	/** adressa de inceput a pagini */
	/** se aligiaza adresa unde s-a produs eroare la pageSize */
	char *addr_page_fault = (char *) ALIGN_DOWN((int) siginfo->si_addr,
						   page_size);
	int index_seg = index_segment((uintptr_t) addr_page_fault, exec);

	/** daca nu apartine vre unui segment */
	if (index_seg == NULL_INDEX)
		goto OLD_ACTION;

	so_seg_t seg = exec->segments[index_seg];
	/**
	 * offsetul pagini unde s-a produs eroarea, pana la
	 * inceputul segmentului
	 */
	int offset_page = (int) (addr_page_fault - seg.vaddr);
	/**
	 * diminesiunea totala a datelor ce trebui scrise pentru respentiva
	 * pagina
	 */
	int mem_size = MAX_MEM_SIZE(page_size,
				    (int) seg.mem_size - offset_page);
	/**
	 * dimensiua datelor ce vor fi citite din memorie
	 */
	int size_read_file = MAX_MEM_SIZE(page_size,
					  (int) seg.file_size - offset_page);
	/**
	 * offset-ul in fiserul de unde se citeste exectabilul
	 */
	int offset_file = offset_page + seg.offset;

	/** daca trebui sa citim date din fiser */
	if (size_read_file > 0) {
		/**
		 * mapare informatilor din respectiva pagina din segmault
		 * in memorie
		 */
		void *map_addres = mmap(addr_page_fault, mem_size, seg.perm,
					MAP_PRIVATE | MAP_FIXED,
					file_descriptor,
					offset_file);
		assert(map_addres != MAP_FAILED);

		/** cazul in care pagina respectiva contine atat date din
		 * fisier si restul pana la dimesiuana mem_size sunt 0-uri
		 */
		if (size_read_file < mem_size) {
			/** restul datelor sunt modificate la 0 */
			int size_zero = mem_size - size_read_file;

			memset((char *) map_addres + size_read_file, 0,
			       size_zero);
		}

	} else {
		/** datele sunt initializate cu zero */
		void *map_addres = mmap(addr_page_fault, mem_size, seg.perm,
					MAP_PRIVATE | MAP_ANONYMOUS,
					NULL_FILE_DESCRIPTOR, 0);
		assert(map_addres != MAP_FAILED);
	}


	return;

OLD_ACTION:
	old_action.sa_sigaction(signum, siginfo, context);
}

int so_init_loader(void)
{
	/**
	 * initializare handler-ului care trateaza daca o pagina
	 * nu este alocata
	 */
	struct sigaction seg_fault_action;

	seg_fault_action.sa_sigaction = seg_fault_handler;
	sigemptyset(&seg_fault_action.sa_mask);
	sigaddset(&seg_fault_action.sa_mask, SIGSEGV);
	seg_fault_action.sa_flags = SA_SIGINFO;
	assert(sigaction(SIGSEGV, &seg_fault_action, &old_action) != -1);

	return -1;
}

int so_execute(char *path, char *argv[])
{
	file_descriptor = open(path, O_RDONLY);
	assert(file_descriptor > -1);

	exec = so_parse_exec(path);
	if (!exec)
		return -1;

	so_start_exec(exec, argv);

	assert(close(file_descriptor) != 0);
	return -1;
}
