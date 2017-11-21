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
    char s[100];
    read(status1[READ], s, sizeof(s)); //READ USING FIRST PIPE
    int n;
    sscanf(s, "%d", &n);
    printf("[child] quick mathing on %d\n", n);
    n = n * n / 4;
    sprintf(s, "%d", n);
    close(status2[READ]);
    write(status2[WRITE], s, sizeof(s));
    printf("[child] sending %s\n", s);
  } else {
    close(status1[READ]); //FIRST PIPE NO READING => writing
    char s[100]= "124";
    printf("[parent] sending %s\n", s);
    write(status1[WRITE], &s, sizeof(s)); //WRITE USING FIRST PIPE
    close(status2[WRITE]);
    read(status2[READ], s, sizeof(s));
    printf("[parent] received %s\n", s);
  }
  return 0;
}
