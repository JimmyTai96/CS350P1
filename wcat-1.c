#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>

int main(int argc, char** argv)
{
  //case for no arguments provided, printing nothing
  //argc should be 1 if just "wcat" or ./a.out is provided so...
  if (argc == 1)
  {
    exit(0);
  }

  //maximum number of characters we'll be reading for any given file 
  //(at least for this test)
  //will be 10,000.
  char buf[10000];

  //^ this isn't a very clean way to do this


  //in the case that multiple arguments are given, print out the contents of
  //all files given as arguments
  int i;
  for(i = 1; i < argc; i++)
  {
    //printf("%s:\n", argv[i]);

    //open file and exit error in case of issues with opening
    int fd;
    while ((fd = open(argv[i], O_RDONLY)) == -1 && errno == EINTR)
      ;
    if (fd == -1)
    {
      fprintf(stderr, "Failed to open file '%s'\n", argv[i]);
      perror(NULL);
      exit(EXIT_FAILURE);
    }

    //read bytes into buffer
    int bytesread;
    while((bytesread = read(fd, buf, 10000)) == -1 && errno == EINTR)
      ;
    if (bytesread == -1)
    {
      perror("Problem reading from file");
      //free(buf);
      exit(EXIT_FAILURE);
    }

    //write contents of buffer to standard output
    //need to do this line by line?
    int byteswritten;
    while ((byteswritten = write(STDOUT_FILENO, buf, bytesread)) == -1 && errno == EINTR)
      ;
    if(byteswritten == -1)
    {
      perror("Failed to write to stdout");
      //free(buf);
      exit(EXIT_FAILURE);
    }

    //free allocated memory
    //free(buf);

    //close current file before moving on
    int closeresult;
    while ((closeresult = close(fd)) == -1 && errno == EINTR)
      ;
    if (closeresult == -1)
    {
      fprintf(stderr, "Failed to close file '%s'\n", argv[1]);
      perror(NULL);
      exit(EXIT_FAILURE);
    }
    
  }
  //include

  return 0;
}
