#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char** argv)
{

  int fd;
  char buf[1000];
  char one[1];
  //error for no arguments
  if (argc == 1)
  {
    fprintf(stderr, "Usage: %s searchterm [filename ...]\n", argv[0]);
    exit(EXIT_FAILURE);
  }
  
  //in the case there is one argument, grep is interactive
  if (argc == 2)
  {
    fd = STDIN_FILENO;
  }

  //in case there are two arguments, second should be filename and grep should search for matched in there
  if (argc == 3)
  {
    //open file and check for errors
    while ((fd = open(argv[2], O_RDONLY)) == -1 && errno == EINTR)
      ;
    if (fd == -1)
    {
      fprintf(stderr, "Failed to open file '%s'\n", argv[2]);
      perror(NULL);
      exit(EXIT_FAILURE);
    }
  }


  char* matchString = argv[1];
  int i;
  int bytesread;

  //printf("%d\n", fd);

  while (1)
  {
    
    for (i = 0; i < 1000; i++)
    {
      bytesread = read(fd, one, 1);

      //printf("%s\n", buf);
      //  printf("%s", one);
      // if (one[0] == '\n')
      // {
      //   printf("newline");
      //}
      // printf("  %d", i);
      // printf("  %d\n", bytesread);
      if (bytesread == -1)
      {
        perror("Failed to read line");
        exit(EXIT_FAILURE);
      }
      else if (bytesread == 0)
      {
        if (strstr(buf, matchString) != NULL)
        {
          // printf("It went here");
          printf("%s\n", buf);
        }
        //close file in case one has been opened and is being read
        if (argc == 3)
        {
          int closeresult;
          while ((closeresult = close(fd)) == -1 && errno == EINTR)
            ;
          if (closeresult == -1)
          {
            fprintf(stderr, "Failed to close file '%s'\n", argv[2]);
            perror(NULL);
            exit(EXIT_FAILURE);
          }
        }
        exit(0);
      }
      else if (one[0] == '\n')
      {
        if (strstr(buf, matchString) != NULL)
        {
          printf("%s\n", buf);
          i = -1;
          //printf("It went there");
          // printf("%d\n", i);
        }
        int j;
        i = -1;
        for (j = 0; j < 1000; j++)
        {
          buf[j] = '\0';
        }
        j = 0;
      }
      else
      {
        buf[i] = one[0];
      }
    }


  }


}
