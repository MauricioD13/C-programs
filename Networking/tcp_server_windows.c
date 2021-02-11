#include <stdio.h>
#include <stdlib.h>
#include <WinSock2.h>

int main(){
    WSADATA wsa;
    SOCKET server_socket, new_socket;
    struct sockaddr_in server,client;
    char *message;
    printf("\n Initialising Winsock...");
    if(WSAStartup(MAKEWORD(2,2),&wsa)!=0){
        printf("Failed, Error code: %d",WSAGetLastError());
        return 1;
    }
    printf("Initialised. \n");

    //Create a SOCKET
    server_socket=socket(AF_INET,SOCK_STREAM,0);
    if(server_socket==INVALID_SOCKET){
        printf("Failed creating socket: %d\n",WSAGetLastError());
    }
    printf("Socket created. \n");
    
    //Prepare the sockaddr_in structure
    server.sin_family=PF_INET;
    server.sin_addr.s_addr=inet_addr("127.0.0.1");
    server.sin_port= htons(8000);

    //Bind

    if(bind(server_socket,(struct sockaddr *)&server,sizeof(server))==SOCKET_ERROR){
        printf("Bind failed with error code: %d\n",WSAGetLastError());
        exit(EXIT_FAILURE);
    }
    puts("Bind done");

    //Listen to incoming connections
    listen(server_socket,3);

    //Accept and incoming connections
    puts("Waiting for incoming connections...\n");
    int x=sizeof(struct sockaddr_in);
    while((new_socket= accept(server_socket,(struct sockaddr *)&client,&x))!=INVALID_SOCKET){
        puts("Connection accepted\n");
         //Reply to client
        message="Hola bebe, ha habido conexion pero me tengo que ir\n";
        send(new_socket,message,strlen(message),0);

    }
    if(new_socket== INVALID_SOCKET){
        printf("Accepted failed with error code: %d \n",WSAGetLastError());
        return 1;
    }
    
   
    closesocket(server_socket);
    WSACleanup();
    return 0;






}