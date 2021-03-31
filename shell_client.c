#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

#include "archivo.h"
#include "leercadena.h"
#include "tcp.h"

#define MAX_LENGTH_STRING 20

int main(int argc, char* argv[]){

     int socket, puerto;
     char *host;
     char comando [BUFSIZ];

     
     	
	if (argc != 4){
	fprintf(stderr,"Uso: %s <host> <puerto> <filename>\n",argv[0]);
	return 1;
	}
  
	host = argv[1];
	puerto = atoi(argv[2]);
	printf("Looking to connect at <%s,%d>\n",host,puerto);
	socket = TCP_Open(Get_IP(host),puerto);
	printf(" connected\n");
     

     while(1){
   
   
     char *filename;

     pid_t pid, pid_temp;
     //leer cadena
     printf("> ");
     bzero(comando, BUFSIZ);
     leer_de_teclado(BUFSIZ,comando);
     //si comando == exit salir del ciclo
     if (!strcmp("exit",comando)){
     printf("Disconnected \n");
     break;
     }                
     
     // De lo contrario continua con el proceso fork
     
	pid = fork();
     
	if(pid < 0){
	fprintf(stderr, "Error creating Child process \n");
	exit (1);
	}
     
	if (pid == 0){
	char *filename;
	
	
	//Envio del comando
	TCP_Write_String(socket, comando);
	//Recv_ACK(socket);
     
	// Envio de archivo
	//filename = (char*)malloc(sizeof(char)*BUFSIZ);
	filename = (char*)calloc(BUFSIZ,sizeof(char));
	assert(filename != NULL);
	TCP_Read_String(socket,filename,BUFSIZ); Send_ACK(socket);
	printf("Archivo a recibir [%s]\n",filename);
	free(filename);
	filename = argv[3];
	TCP_Recv_File(socket, filename);
	printf("Archivo recibido en archivo [%s]\n",filename);
	
	TCP_Read_String(socket, filename, BUFSIZ);
	//Send_ACK(socket);

     
	//Muestra por pantalla el archivo
	//cat_archivo(filename);

	char cadena[MAX_LENGTH_STRING];
	cat_archivo("archivo.c");
	borrar_archivo("demo.c");
	generar_nombre_archivo(MAX_LENGTH_STRING,cadena); 
	printf("%s\n",cadena);
	
     
	break;
	}
     
	// proceso padre espera por la terminacion y continua
	// en el ciclo esperando por otro comando
     
	pid_temp = wait(NULL); 
	assert(pid == pid_temp);   
     
	}
     
	return 0;
}


