#include <stdio.h>
#include <sys/types.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


int main(int argc, char **argv){
/*
  //We are trying to open a file that does not exist
  FILE* input = fopen("NoFile.txt", "r");

  //Note the value in errno
  printf("\nError Code: %d\n", errno);

  //Print associated error message
  perror("Error Message");
*/
	/* create the child */
   int  pid;
   int status=0;
   if ((pid = fork()) < 0)
     {
       printf("fork failed\n");
       return 2;
     }
 
   if (pid != 0)
     {
		// wait(&status);
       printf("parent, argv[0] : %s\n", argv[0]);
     }
   else
     {
        printf("child, argv[1] : %s\n", argv[1]);
     }
  return (0);
}