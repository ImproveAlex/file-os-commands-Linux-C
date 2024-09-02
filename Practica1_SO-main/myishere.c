#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>


int main(int argc, char *argv[]){
	/*Se declaran las variables que usaremos a lo largo del código*/
	DIR *dir;
	struct dirent *entry;
	int fichero_encontrado = 0; 
	/*ERROR en el nº de argumentos*/
	if(argc != 3 ){
		fprintf(stderr, "ERROR. Número de argumentos inválido\n");
		exit(-1);
	}
	/*Se abre el directorio pasado como parámetro*/
	dir = opendir(argv[1]);
	/*ERROR al abrir el directorio*/
	if (dir == NULL){
		fprintf(stderr, "ERROR. No se ha podido abrir el directorio indicado\n");
		exit(-1);
	}
	/*Recorremos todas las entradas del directorio hasta llegar al final*/
	while((entry = readdir(dir))!= NULL){
		/*Utilizamos strcmp para ver si el segundo parámetro coincide con alguna de las entradas del directorio*/
		if((strcmp(entry->d_name, argv[2]) == 0)){
			/*Si se encuentra una entrada que coincida con el segundo parámetro, cambiamos el valor de la variable fichero_encontrado a 1 e imprimimos el resultado*/
			fichero_encontrado = 1;
			printf("File %s is in directory %s\n", argv[2], argv[1]);
		}
		/* Verificar si ocurrió un error al leer el directorio */
		if (entry == NULL && !fichero_encontrado) {
			perror("ERROR. No se ha podido leer los ficheros del directorio");
			closedir(dir);
			exit(-1);
    }
	}
	/*Si no se ha encontrado una entrada que coincida con el segundo parámetro, el valor de fichero_encontrado será 0*/
	if (fichero_encontrado == 0){
		printf("File %s is not in directory %s\n", argv[2], argv[1]);
	}
	/*Cerramos el directorio*/
	closedir(dir);
	return 0;
}