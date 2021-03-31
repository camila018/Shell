# Shell

Hasta el momento he fusionado los archivos de file_cliente, file_server,
basic_cliente, basic_server.

para compilarlos archivos, uso los siguientes comandos:

Servidor --> gcc shell_server.c tcp.c leercadena.c archivo.c -o shell_server
         --> ./shell_server tcp.c 

cliente --> gcc shell_client.c tcp.c leercadena.c archivo.c -o shell_client
        --> ./shell_client localhost 12358 demo.c


se presenta un fallo despues de enviar cualquier comando en la consola del cliente



