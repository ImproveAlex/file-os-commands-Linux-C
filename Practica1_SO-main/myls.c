#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <limits.h>
#include <errno.h>
#include <unistd.h>
#include <linux/limits.h>

int main(int argc, char *argv[]) {
    DIR *dir;
    struct dirent *entry;

    char dir_path[PATH_MAX]; // Buffer para almacenar la ruta del directorio

    if (argc == 1) {
        // No se proporcionó ningún argumento, abrimos el directorio actual
        if (getcwd(dir_path, sizeof(dir_path)) == NULL) {
            fprintf(stderr, "No se pudo obtener el directorio actual");
            exit(-1);
        }
        dir = opendir(dir_path);
    } else if (argc == 2) {
        // Se proporcionó un argumento, intentamos abrir el directorio especificado
        dir = opendir(argv[1]);
        if (dir == NULL) {
            fprintf(stderr, "No se ha podido abrir el directorio indicado\n");
            exit(-1);
        }
    } else {
        // Número de argumentos incorrecto
        fprintf(stderr, "Número de argumentos incorrecto\n");
        exit(-1);
    }

    // Recorremos todas las entradas del directorio hasta llegar al final
    while ((entry = readdir(dir)) != NULL) {
        printf("%s\n", entry->d_name);
    }

    // Cerramos el directorio
    closedir(dir);
    return 0;
}