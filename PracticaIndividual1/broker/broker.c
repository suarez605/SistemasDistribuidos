#include <stdio.h>
#include <stdlib.h>
#include "comun.h"
#include "diccionario.h"
#include "cola.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>

#define TAM 1024

struct mensaje {
	int tipoOperacion;
    char cola[100];
    char cuerpo[100];
};


int insertarCola(struct diccionario *d, char *nombreCola[]){
	struct cola *cola;
	cola = cola_create();
    if (dic_put(d, nombreCola, cola) < 0){
        fprintf(stderr, "Error, ya existe una cola con ese nombre.\n");
		return -1;
	}
	return 0;
}


int borraCola(){
	return 0;
}

int insertarMensaje(struct diccionario *d, char *nombreCola , char *mensaje){
    struct cola *c;
	int error;
	c=dic_get(d, nombreCola, &error);
	if(cola_push_back(c, mensaje) != 0){
		fprintf(stderr, "Error, no se ha podido almacenar el mensaje en la cola\n");
		return -1;
	}
	return 0;
}

int devolverMensaje(){
	return 0;
}


void imprime_int(void *v) {
    printf("%ld\n", (long)v);
}


void imprime_string(void *v) {
    printf("%s\n", v);
}

void imprime_cola(char *clave, void *valor) {
    printf("{\n", clave);
	cola_visit(valor, imprime_string);
	printf("}\n", clave);
}


int main(int argc, char *argv[]){
	struct diccionario *dic;
    dic = dic_create();

	char nombrecola1[100] = "COLA1";
	char mensaje[100] = "HOLA A TODOS LOS DE LA COLA1";
	insertarCola(dic, *nombrecola1);
	insertarMensaje(dic, *nombrecola1 , *mensaje);
	printf("Contenido del diccionario:\n");
    dic_visit(dic, imprime_cola);


	return 0;


	/*
 	int s, s_conec, leido;
	unsigned int tam_dir;
	struct sockaddr_in dir, dir_cliente;
	char buf[TAM];
	int opcion=1;

	if (argc!=2) {
		fprintf(stderr, "Uso: %s puerto\n", argv[0]);
		return 1;
	}
	if ((s=socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
		perror("error creando socket");
		return 1;
	}
	 // Para reutilizar puerto inmediatamente
        if (setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &opcion, sizeof(opcion))<0){
                perror("error en setsockopt");
                return 1;
        }
	dir.sin_addr.s_addr=INADDR_ANY;
	dir.sin_port=htons(atoi(argv[1]));
	dir.sin_family=PF_INET;
	if (bind(s, (struct sockaddr *)&dir, sizeof(dir)) < 0) {
		perror("error en bind");
		close(s);
		return 1;
	}
	if (listen(s, 5) < 0) {
		perror("error en listen");
		close(s);
		return 1;
	}
	while (1) {

		tam_dir=sizeof(dir_cliente);

		if ((s_conec=accept(s, (struct sockaddr *)&dir_cliente, &tam_dir))<0){
			perror("error en accept");
			close(s);
			return 1;
		}

		while ((leido=read(s_conec, buf, TAM))>0) {
			write(1, buf, leido);
			if (write(s_conec, buf, leido)<0) {
				perror("error en write");
				close(s);
				close(s_conec);
				return 1;
			}
		}

		if (leido<0) {
			perror("error en read");
			close(s);
			close(s_conec);
			return 1;
		}
		close(s_conec);
	}
	close(s);
	return 0;*/

}
