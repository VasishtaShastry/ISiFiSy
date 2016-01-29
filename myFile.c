#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <utime.h>
#include <dirent.h>
#define BUFFERSIZE 1024
#define COPYMORE 0644

void myCopy (char source[20], char destination[20]){

	int in_fd, out_fd, n_chars;
 	char buf[BUFFERSIZE];

 	/* open files */
	if ( (in_fd=fs_open(source, O_RDONLY)) == -1 )
 	{
    	oops("Cannot open ", source);
    }


  	if ( (out_fd=fs_creat(destination, COPYMORE)) == -1 )
  	{
    	oops("Cannot creat ", destination);
  	}


  	/* copy files */
  	while( (n_chars = fs_read(in_fd, buf, BUFFERSIZE)) > 0 )
  	{
    	if( fs_write(out_fd, buf, n_chars) != n_chars )
    	{
      		oops("Write error to ", destination);
    	}


    if( n_chars == -1 )
    {
      oops("Read error from ", source);
    }
   } 


    /* close files */
    if( fs_close(in_fd) == -1 || fs_close(out_fd) == -1 )
    {
      oops("Error closing files", "");
    }



}

void myWrite (char content[50], char destination[20]){

	int  out_fd, n_chars;
 	

 	/* open files */
	
  	if ( (out_fd=fs_creat(destination, COPYMORE)) == -1 )
  	{
    	oops("Cannot creat ", destination);
  	}


	n_chars = fs_write(out_fd, content, strlen(content));
   
    if( n_chars == -1 )
    {
      oops("Read error from ", destination);
    }
   

	/* close files */
    if(fs_close(out_fd) == -1 )
    {
      oops("Error closing files", "");
    }

}

void myInfo (char topic[20]){

}

void myTouch(char filename[20]){

  int flag;

  if((access (filename, F_OK)) !=0){

    fs_creat(filename, 0644);
    return;
  }

  flag = utime (filename, NULL);
	if (flag != 0){
    oops ("Error", "");
  } 
}

void myLs (){

  DIR *dp;
  struct dirent *dir;
  struct stat fdetails;
  char name [5] = ".";

  if( NULL == (dp = opendir( name )))
      return ;

  while ( dir = readdir(dp) )
  {
    if( !strcmp(dir->d_name,".") || !strcmp(dir->d_name, ".."))
    {
        continue;
    }
    printf("%s\t",dir->d_name);
  }
  printf( "\n" );
}

void myCAT (char filename[20]){
  
  int fd, chars;
  char buf[100];
  if ((access(filename, F_OK)) !=0 ) {

      oops("file doesn't exist", "");
      return;
  }
  
  fd = fs_open(filename, O_RDONLY);
  if (fd == -1){
    oops("File doesn't have read permission","");
  }
  while ( (chars = fs_read(fd, buf, 100)) >0)
                fs_write(1, buf, chars);

  fs_close(fd);
//  free(buf);
}