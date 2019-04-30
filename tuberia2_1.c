/* Este archivo contiene el programa que ejecuta el hijo del programa que se
   encuentra en al archivo tuberia2.c.
   Lo Ãºnico que hace este programa es abrir una tuberÃ­a (pipe) establecida por
   el programa padre y enviarle un mensaje.

   Autor: Alberto Oliart Ros
*/

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int main() {

  int tubo;  // Variable para tener el descriptor del tubo

  tubo = open("/tmp/tubo1", O_WRONLY);
 
  write(tubo, "Hola hola", 9);

  exit(0);
}