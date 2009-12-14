#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <pm.h>

#define STDIN_FILENO 0 /* standard input file descriptor */
#define STDOUT_FILENO 1 /* standard output file descriptor */
#define STDERR_FILENO 2 /* standard error file descriptor */

void 
_exit(int n)
{
	while(1)
	{
		n = n;
	}
}

int
_stat(char *file, struct stat *st) {
	return 0;
}

int
_fstat(int fd, struct stat * st)
{
	if(fd == STDOUT_FILENO)
	{
		memset(st, 0, sizeof (* st));
		st->st_mode = S_IFCHR;
		st->st_blksize = 1024;
		return 0;
	}
	else
	{
		return(-1);
	}
}

register char *stack_ptr asm ("sp");

caddr_t
_sbrk_r(void *reent, size_t incr)
{
	extern char end asm ("end"); // Defined by the linker
	static char *heap_end;
	char *prev_heap_end;

	if( heap_end == NULL )
		heap_end = &end;
	prev_heap_end = heap_end;

	if(( heap_end + incr ) > stack_ptr )
	{
		/* Some of the libstdc++-v3 tests rely upon detecting */
		/* out of memory errors, so do not abort here. */
		exit(1);
		return (caddr_t) -1;
	}

	heap_end += incr;
	return (caddr_t) prev_heap_end;
}

int
_isatty(int fd)
{
	return 1;
}

int
_lseek(int fd, int ptr,int dir)
{
	return -1;
}

int
_open(const char *name, int mode)
{
	return -1;
}

int
_close(int fd)
{
    return -1;
}

int
_write(int fd, const void *data, unsigned int count)
{
    count = -1;
    return(count);
}

int _write_r(void *reent, int fd, char *ptr, size_t len)
{
	size_t i;

	for (i=0; i<len; i++)
	{
        plat_putByte(ptr[i]);
	}
	return len;
}


int
_read(int fd, void *buffer, unsigned int count)
{
    return -1;
}
