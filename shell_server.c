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

#define MAX 80


void func(int sockfd) 
{ 
	char buff[MAX]; 
	bzero(buff,MAX);
	TCP_Read_String(sockfd, buff, MAX); 
	printf("[CLIENT] %s\n",buff);
}




int main(int argc, char* argv[]){

	int socket, connfd;  
	int puerto;
	char *filename;
	char ack[MAX_TCP_ACK] = {0};
	

        if (argc != 3) {
	printf("Uso: %s <puerto> <archivo>\n",argv[0]);
	return 1;
 
        }
        
        puerto = atoi(argv[1]);
        filename = argv[2];
        printf("Connecting %d \n",puerto);
	socket = TCP_Server_Open(puerto);
	printf(" connected\n");
	connfd = TCP_Accept(socket);
	
	while(1){
	
	pid_t pid, pid_temp;
	int sockfd;
        char* buff;

                      
        
        if (!strcmp("exit",buff)){
        close(sockfd);
        break;
        }
        pid = fork();
        
	if(pid < 0){
	fprintf(stderr, "Error creating Child process \n");
	exit (1);
	}
        
        if (pid == 0){
	func(connfd);
	//Send_ACK(socket);
	
	//Envio del archivo
	TCP_Write_String(connfd, filename); 
//	Recv_ACK(connfd);
	TCP_Send_File(connfd,filename);
	
	
        break;
        }
        
        
	// proceso padre espera por la terminacion y continua
	// en el ciclo esperando por otro comando
	    
	pid_temp = wait(NULL); 
	assert(pid == pid_temp);   
     
        
        }
      


}
