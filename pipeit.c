#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

int main() {
  int READ = 0;
  int WRITE = 1;

  int status1[2];
  int status2[2];
  int f;

  pipe(status1);
  pipe(status2);
  f = fork();

  if(!f) {
    close(status1[WRITE]); //FIRST PIPE NO WRITING => reading
    close(status2[READ]); //SECOND PIPE NO READING => writing
    char s[]= "from child";
    write(status2[WRITE], s, sizeof(s)); //WRITE USING SECOND PIPE
    read(status1[READ], s, sizeof(s)); //READ USING FIRST PIPE
    printf("Message received by child: %s\n", s);
  } else {
    close(status1[READ]); //FIRST PIPE NO READING => writing
    close(status2[WRITE]); //SECOND PIPE NO WRITING => reading
    char s[]= "from father";
    write(status1[WRITE], s, sizeof(s)); //WRITE USING FIRST PIPE
    read(status2[READ], s, sizeof(s)); //READ USING SECOND PIPE
    printf("Message received by parent: %s\n", s);
  }
  return 0;
}
