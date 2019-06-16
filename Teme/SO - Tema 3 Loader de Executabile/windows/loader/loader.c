#include <stdio.h>
#include <Windows.h>

#define DLL_EXPORTS

#define MAX_MEM_SIZE(a , b) ((a) <= (b) ? (a) : (b))

#define PAGE_SIZE        0x10000
#define NULL_INDEX        -1

#include "loader.h"
#include "exec_parser.h"
#include "utils.h"

static so_exec_t *exec;
static LPVOID page_fault_handler;
static HANDLE hFIle;
static LPVOID mapFile;

/**
 * functia care realizeeza translatia valorilor pt flag-urile de
 * protectie/permisiune pt windows, pe linux coinideau,
 * valoruile sunt suprascrise ce cele de pe windows
 * @param exe retine informati despre executabil
 */
static void set_permission_segment_windows(so_exec_t *exe)
{
	int i;

	for (i = 0; i < exe->segments_no; ++i) {

		if (exe->segments[i].perm & PERM_R &&
		    exe->segments[i].perm & PERM_W &&
		    exe->segments[i].perm & PERM_X) {
			exe->segments[i].perm = PAGE_EXECUTE_READWRITE;
			continue;
		}

		if (exe->segments[i].perm & PERM_R &&
		    exe->segments[i].perm & PERM_X) {
			exe->segments[i].perm = PAGE_EXECUTE_READ;
			continue;
		}

		if (exe->segments[i].perm & PERM_R &&
		    exe->segments[i].perm & PERM_W) {
			exe->segments[i].perm = PAGE_READWRITE;
			continue;
		}

	
		if (exe->segments[i].perm & PERM_R)
			exe->segments[i].perm = PAGE_READONLY;
	}

}

/**
 * functia verifica daca o adresa la care s-a produs respectivul page fault se
 * afla intr-un unul dintre segmente
 * @param addr adresa unde s-a produs page fault
 * @param exe retine informati despre executabil
 * @return index-ul segmentului in care se gaseste acea adresa
 */
static int index_segment(uintptr_t addr , so_exec_t *exe)
{
	int i;

	for (i = 0; i < exe->segments_no; ++i)
		if (exe->segments[i].vaddr <= addr &&
		    addr <= exe->segments[i].vaddr + exe->segments[i].mem_size)
			return i;


	return NULL_INDEX;
}


static LONG CALLBACK page_fault(PEXCEPTION_POINTERS ExceptionInfo)
{
	ULONG_PTR addrFaultPage;
	int index_seg;
	so_seg_t seg;
	int size_read_file;
	int offset_page;
	int offset_file;
	LPVOID map;
	DWORD oldPrem;
	void *read_addr;
	BOOL bRet;

	/**
	 * se verifica ca segnalul sa provina de la un seg fault pentru cazul
	 * in care memoria nu este mapata
	 */
	if (ExceptionInfo->ExceptionRecord->ExceptionCode !=
	    EXCEPTION_ACCESS_VIOLATION)
		goto OLD_ACTION;

	addrFaultPage = ExceptionInfo->ExceptionRecord->ExceptionInformation[1];

	/** adrrssa de inceput a pagini */
	addrFaultPage = ALIGN_DOWN ((int) addrFaultPage , (int) PAGE_SIZE);


	index_seg = index_segment (addrFaultPage , exec);
	if (index_seg == NULL_INDEX)
		goto OLD_ACTION;

	seg = exec->segments[index_seg];

	/**
 	* offsetul pagini unde s-a produs eroarea, pana la
 	* inceputul segmentului
 	*/
	offset_page = (int) (addrFaultPage - seg.vaddr);

	/**
	* dimensiua datelor ce vor fi citite din memorie
	*/
	size_read_file = MAX_MEM_SIZE(PAGE_SIZE ,
				      (int) seg.file_size - offset_page);

	/**
	 * offset-ul in fiserul de unde se citeste exectabilul
	 */
	offset_file = offset_page + seg.offset;

	map = VirtualAlloc (
		(LPVOID) addrFaultPage ,
		PAGE_SIZE ,
		MEM_RESERVE | MEM_COMMIT ,
		PAGE_READWRITE
	);

	/**
	 * daca este cazul in care permisiunele nu sunt corecte trebui sa rulam
	 * hander-ul implicit, de aceia in caz de eroare se ruleaza hander-ul
	 * implicit pt cazurile in care nu a fostt un page fault pt memorie
	 * nempata
	 */
	if (map == NULL)
		goto OLD_ACTION;

	/** daca trebui sa citim date din fiser */
	/** copierea datelor */
	if (size_read_file > 0) {
		read_addr = (char *) mapFile + offset_file;
		memcpy (map , read_addr , size_read_file);
	}

	/** setarea protectie indicate */
	bRet = VirtualProtect (map , PAGE_SIZE , seg.perm , &oldPrem);
	DIE (bRet == FALSE , "VirtualProtect");

	return EXCEPTION_CONTINUE_EXECUTION;

OLD_ACTION:
	return EXCEPTION_CONTINUE_SEARCH;
}


int so_init_loader(void)
{
	page_fault_handler = AddVectoredExceptionHandler (1 , page_fault);
	DIE (page_fault_handler == NULL , "AddVectoredExceptionHandler");

	return -1;
}

int so_execute(char *path , char *argv[])
{
	DWORD rc;
	HANDLE hFileMapping;
	WIN32_FILE_ATTRIBUTE_DATA fileAttr;

	exec = so_parse_exec (path);
	if (!exec)
		return -1;

	set_permission_segment_windows (exec);

	hFIle = CreateFile (
		path ,
		GENERIC_READ ,
		FILE_SHARE_READ ,
		NULL ,
		OPEN_EXISTING ,
		FILE_ATTRIBUTE_READONLY ,
		NULL
	);

	DIE (hFIle == INVALID_HANDLE_VALUE , "CreateFile");

	rc = GetFileAttributesEx (path , GetFileExInfoStandard , &fileAttr);
	DIE (rc == FALSE , "GetFileAttributesEx");

	/** maparea fisierului in memorie */
	hFileMapping = CreateFileMapping (
		hFIle ,
		NULL ,
		PAGE_READONLY ,
		fileAttr.nFileSizeHigh ,
		fileAttr.nFileSizeLow ,
		path
	);
	DIE (hFileMapping == NULL , "CreateFileMapping");

	/** maparea fisierului in memorie */
	mapFile = MapViewOfFile (hFileMapping ,
				 FILE_MAP_READ ,
				 0 ,
				 0 ,
				 0
	);
	DIE(mapFile == NULL , "MapViewOfFile");

	so_start_exec (exec , argv);

	rc = RemoveVectoredExceptionHandler (page_fault_handler);
	DIE(rc == FALSE , "RemoveVectoredExceptionHandler");

	rc = CloseHandle (hFileMapping);
	DIE(rc == FALSE , "CloseHandel : hFileMapping");

	rc = CloseHandle (hFIle);
	DIE(rc == FALSE , "CloseHandel : hFIle");

	/** demaparea fisierului in memorie */
	rc = UnmapViewOfFile (mapFile);
	DIE(rc == FALSE , "UnmapViewOfFile");

	return -1;
}
