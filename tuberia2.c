/* Programa que implementa la comunicaciÃ³n entre dos procesos a travÃ©s de una
   tuberÃ­a con nombre (FIFO). En este archivo estÃ¡ el programa del primer
   proceso. En el archivo tuberia2_1.c estÃ¡ el cÃ³digo que corresponde al
   proceso que serÃ¡ hijo de Ã©ste

   Autor: Alberto Oliart Ros
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define MAXLINE 256

int main() {

  int tubo;  // Aquí estará el descriptor del archivo que corresponde a la tubería­a con nombre
  char linea[MAXLINE];  // Aquí se leerá la lía­nea de texto enviada por el proceso hijo.

  pid_t pid;  // Una variable para guardar el identificador de procesos
  int n;  // Para obtener el número de caracteres leí­dos en la tubería.

  // Ahora creamos una tubería con nombre.

  tubo = mkfifo("/tmp/tubo1", 0666);

  if (tubo < 0) { // Si hubo algÃºn error en la creaci+on del tubo, termina el programa
    printf("Error al crear la tuberÃ­a\n");
    exit(1);
  }

  // Se crea el proceso hijo y se le hace correr el programa que está en el
  // archivo tuberia2_1.

  pid = fork();

  if(pid == 0) {  // Este es el código del proceso hijo

    execvp("./tuberia2_1.c", NULL);  // Se ejecuta el programa
    exit(0); // En caso de fallo, se termina el proceso hijo.

  }
  else {  // Este es el código del proceso padre.

    // Primero se abre la tubería para lectura

    tubo = open("/tmp/tubo1", O_RDONLY);
    
    // Lee de la tubería el mensaje enviado por el proceso hijo.
    
    n = read(tubo, linea, MAXLINE);
    write(STDOUT_FILENO, linea, n);
    write(STDOUT_FILENO, "\n", 1);
    //printf("n = %d, %s\n",n, linea);

  }
  exit(0);  // Aquí termina el programa.
}