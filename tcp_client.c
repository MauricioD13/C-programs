#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
// For windows
//#include <WinSock2.h>
// For linux BSD
#include <sys/socket.h>
#include <netinet/in.h> //-> Manipulacion de headers, tiene la informacion de los headers para la ip y el puerto del otro socket

int main(){
    //Create a socket
    int network_socket;
    network_socket=socket(AF_INET,SOCK_STREAM,0);//AF_NET specify ipv4 and SOCK_STREAM specify TCP protocol
    
    //Specify an address for the socket and connect to another socket 
    struct sockaddr_in server_address;
    server_address.sin_family=  AF_INET; // Familia de la direccion, tipo de direccion con la que se va a trabajar   
    server_address.sin_port=    htons(8080); // El numero que se pasa como parametro a la funcion htons es el puerto que se va a trabajar
    // La funcion htons traduce el entero a el formato que requiere la funcion 
    server_address.sin_addr.s_addr=INADDR_ANY; // Aqui se define la direccion IP a la que se va a conectar, INADDR_ANY es la direccion local
    

    // La funcion connect necesita el entero del socket, el apuntador a server_address y el tamaño de la estructura
    int connection_status=connect(network_socket,(struct sockaddr *) &server_address,sizeof(server_address)); // Esta funcion devuelve un entero, si es 0 todo fue bien, si devuelve -1 entonces hubo un problema
    
    //Mirar si hay error en la conexion
    if(connection_status==-1){
        printf("Failed stablishing a connection\n\n");
    }
    else{
        printf("Connected\n");
    }
    //Recibir datos del servidor
    char *server_response=malloc(256*sizeof(char)); // Aqui se almacenara la informacion recibida por la funcion
    recv(network_socket,server_response, sizeof(server_response),0); //Parametros: socket, direccion donde se almacenará la informacion, tamaño del buffer, flags
    

    //Imprimir datos 

    printf("Server send %s \n",server_response);
    connection_status=connect(network_socket,(struct sockaddr *) &server_address,sizeof(server_address));
    if(connection_status){
        printf("Connection Accepted %d \n",connection_status);
    }
    char *response="Here is the client";
    if(server_response){
        send(server_address,response,sizeof(response),0);
    }
    //Cerrar el socket

    shutdown(network_socket,2);

    return 0;

}