#include <stdio.h>
#include "comun.h"
#include "diccionario.h"
#include "cola.h"
#include <unistd.h>
#include <sys/socket.h> 
#include <netinet/in.h> 
#include <string.h>
int main(int argc, char *argv[]){
    if(argc!=2) {
        fprintf(stderr, "Uso: %s puerto\n", argv[0]);
        return 1;
    }

    if(strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0  ){
        fprintf(stdout, "Mandato para lanzar e broker de mensajeria en el puerto especificado.\nCreado por ALvaro Suarez en 2021 para SSDD UPM.\nUso: %S  [puerto]", argv[0]);
    }


    int port = argv[1];
    int server_fd, new_socket, valread; 
    struct sockaddr_in address; 
    int opt = 1; 
    int addrlen = sizeof(address); 
    char buffer[1024] = {0}; 
    char *hello = "Hello from server"; 

    // Creating socket file descriptor 
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) 
    { 
        perror("socket failed"); 
        exit(-1); 
    } 
    
    // Forcefully attaching socket to the port 8080 
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))){ 
        perror("setsockopt"); 
        exit(-1); 
    } 

    address.sin_family = AF_INET; 
    address.sin_addr.s_addr = INADDR_ANY; 
    address.sin_port = htons( port ); 
     

    // Forcefully attaching socket to the port 8080 
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0){ 
        perror("bind failed"); 
        exit(-1); 
    } 
    return 0;
}
