# Shell

Hasta el momento he fusionado los archivos de file_cliente, file_server,
basic_cliente, basic_server, archivo_main.

para compilarlos archivos, uso los siguientes comandos:

Servidor --> gcc -c archivo.c leercadena.c
         --> gcc shell_server.c tcp.c leercadena.o archivo.o -o shell_server
         --> ./shell_server tcp.c 

cliente --> gcc -c archivo.c leercadena.c
        --> gcc shell_client.c tcp.c leercadena.o archivo.o -o shell_client
        --> ./shell_client localhost 12358 demo.c






