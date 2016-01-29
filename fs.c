#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>


int fs_open(const char *pathname, int flags){
	return	open(pathname, flags);
}

int fs_read (int fd, void *buf, size_t count){

	return read(fd, buf, count);
}

int fs_write(int fd, const void *buf, size_t count){

	return write(fd, buf, count);
}

int fs_creat(const char *pathname, mode_t mode){

	return creat(pathname, mode); 
}

int fs_close(int fd){

	return close(fd);
}
