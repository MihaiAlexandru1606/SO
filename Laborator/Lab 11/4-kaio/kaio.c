/**
 * SO, 2016
 * Lab #11, Advanced IO Linux
 *
 * Task #4, Linux
 *
 * KAIO
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>

#include <sys/eventfd.h>
#include <linux/types.h>
#include <sys/syscall.h>
#include <libaio.h>

#include "utils.h"

#ifndef BUFSIZ
#define BUFSIZ		4096
#endif

/* file names */
static char *files[] = {
	"/tmp/slo.txt",
	"/tmp/oer.txt",
	"/tmp/rse.txt",
	"/tmp/ufver.txt"
};


/* TODO 2 - Uncomment this to use eventfd */
/* #define USE_EVENTFD	1 */

/* eventfd file descriptor */
int efd;


/* file descriptors */
static int *fds;
static char g_buffer[BUFSIZ];

static void open_files(void)
{
	size_t n_files = sizeof(files) / sizeof(files[0]);
	size_t i;

	fds = malloc(n_files * sizeof(int));
	DIE(fds == NULL, "malloc");

	for (i = 0; i < n_files; i++) {
		fds[i] = open(files[i], O_CREAT | O_WRONLY | O_TRUNC, 0666);
		DIE(fds[i] < 0, "open");
	}
}

static void close_files(void)
{
	size_t n_files = sizeof(files) / sizeof(files[0]);
	size_t i;
	int rc;

	for (i = 0; i < n_files; i++) {
		rc = close(fds[i]);
		DIE(rc < 0, "close");
	}

	free(fds);
}

/*
 * init buffer with random data
 */
static void init_buffer(void)
{
	size_t i;

	srand(time(NULL));

	for (i = 0; i < BUFSIZ; i++)
		g_buffer[i] = (char) rand();
}


/*
 * wait for asynchronous I/O operations
 * (eventfd or io_getevents)
 */
static void wait_aio(io_context_t ctx, int nops)
{
	struct io_event *events;
	u_int64_t efd_ops = 0;
	int rc, i;

	/* TODO 1 - alloc structure */
	events = malloc(sizeof(struct io_event));
	DIE(events != NULL, "malloc");

#ifndef USE_EVENTFD
	/*
	 * TODO 1 - wait for async operations to finish
	 *	Use only io_getevents()
	 */
	io_getevents(ctx,
		     nops, /* min_nr */
		     nops, /* max_nr */
		     events,      /* vector to store completed events */
		     NULL);        /* no timeout */

#else
	/* TODO 2 - wait for async operations to finish
	 *
	 *	Use eventfd for completion notify
	 */

#endif

}

/*
 * write data asynchronously (using io_setup(2), io_sumbit(2),
 *	io_getevents(2), io_destroy(2))
 */

static void do_io_async(void)
{
	size_t n_files = sizeof(files) / sizeof(files[0]);
	size_t i;
	io_context_t ctx = 0;
	struct iocb *iocb;
	struct iocb **piocb;
	int n_aio_ops, rc;

	/* TODO 1 - allocate iocb and piocb */
	iocb = malloc(sizeof(struct iocb) * n_files);
	//piocb = malloc(sizeof(struct iocb));
	piocb = malloc(sizeof(void *));

	for (i = 0; i < n_files; i++) {
		piocb[i] = &iocb[i];
		/* TODO 1 - initialiaze iocb and piocb */
		memset(piocb[i], 0, sizeof(struct iocb));
		io_prep_pwrite(piocb[i], fds[i], g_buffer, BUFSIZ, 0);

//		memset(piocb, 0, sizeof(struct iocb));
//		io_prep_pwrite(piocb[i], fds[i], g_buffer, BUFSIZ, 0);


#ifdef USE_EVENTFD
		/* TODO 2 - set up eventfd notification */

#endif
	}

	/* TODO 1 - setup aio context */
	io_setup(n_files, &ctx);

	/* TODO 1 - submit aio */
	io_submit(ctx, n_files, piocb[i]);

	/* wait for completion*/
	wait_aio(ctx, n_files);


	/* TODO 1 - destroy aio context */
	io_destroy(ctx);
}

int main(void)
{
	open_files();
	init_buffer();

#ifdef USE_EVENTFD
	/* TODO 2 - init eventfd */

#endif

	do_io_async();

#ifdef USE_EVENTFD
	/* TODO 2 - close eventfd */

#endif
	close_files();

	return 0;
}
