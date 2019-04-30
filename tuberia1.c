/* Un pequeñoo ejemplo del uso de una tubería en Unix */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


#define MAXLINE 256

int main(void)
{
  int     n;
  int     fd[2];  // El arreglo para la tuberÃ­a.
  pid_t   pid;
  char    line[MAXLINE];
  if (pipe(fd) < 0) {  // Se crea la tuberÃ­a. En caso de que haya error, Ã©ste
    // se reporta
    printf("Error al crear la tuberÃ­a\n");
    exit(1);
  }
  if ((pid = fork()) < 0) {  // Se crea un nuevo proceso.
    printf("Error al crear el nuevo proceso\n");
    exit(1);
  } else if (pid > 0) {       // Proceso padre
    close(fd[0]);             // Cierra la tuberÃ­a para lectura
    // sleep(2);
    write(fd[1], "hello world\n", 12); // Escribe algo a la tuberÃ­a
    wait(NULL);
    } else {                // Proceso hijo
    close(fd[1]);         // Cierra la tuberÃ­a para escritura
    sleep(1);
    n = read(fd[0], line, MAXLINE); // Lee algo de la tuberÃ­a
    write(STDOUT_FILENO, line, n);  // Escribe el mensaje a la pantalla
  }
  exit(0); // AquÃ­ se terminan los procesos
}