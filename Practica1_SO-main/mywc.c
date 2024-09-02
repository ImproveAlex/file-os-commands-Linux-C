#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define MAX_BUFFER 512

int main(int argc, char *argv[]) {
    /* Se declaran las variables que usaremos a lo largo del código */
    int n_lineas = 0, n_palabras = 0, en_palabra = 0, n_bytes = 0;
    char buffer;

    /* Verificar el número de argumentos */
    if (argc < 2) {
		fprintf(stderr, "ERROR. Número de argumentos inválido\n");
        exit(-1);
    }

    /* Abrir el fichero */
    int file = open(argv[1], O_RDONLY);
    /* Verificar si hay errores al abrir el fichero */
    if (file < 0) {
		fprintf(stderr, "ERROR. al abrir el fichero\n");
        exit(-1);
    }

    /* Leer el fichero hasta llegar al final o hasta que haya un error de lectura */
    while (read(file, &buffer, 1) > 0) {
        n_bytes++;
        /* Si se detecta un salto de línea */
        if (buffer == '\n') {
            n_lineas++;
        }

        if (buffer == ' ' || buffer == '\n' || buffer == '\t' || buffer == '\r' || buffer == '\f' || buffer == '\v') {
            en_palabra = 0;
        }
        /* Si se detecta un tab o un espacio en blanco */
        else if (!en_palabra) {
            n_palabras++;
            en_palabra = 1;
        }
    }

    /* Imprimir el número de líneas, palabras y bytes junto con el nombre del archivo */
    printf("%i %i %i %s\n", n_lineas, n_palabras, n_bytes, argv[1]);
    /* Cerrar el fichero abierto */
    close(file);
    return 0;
}