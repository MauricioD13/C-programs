#include <stdio.h>
#include <stdlib.h>
#include <WinSock2.h>

int main(){
    WSADATA wsa;
    SOCKET client_socket;
    struct sockaddr_in server; // Server to connect
    char *message;

    printf("\n Initialising Winsock...");
    if(WSAStartup(MAKEWORD(2,2),&wsa)!=0){
        printf("Failed, Error code: %d",WSAGetLastError());
        return 1;
    }
    printf("Initialised. \n");

    //Create a SOCKET
    client_socket=socket(AF_INET,SOCK_STREAM,0);
    if(client_socket==INVALID_SOCKET){
        printf("Failed creating socket: %d",WSAGetLastError());
    }
    printf("Socket created. \n");

    //Configuring conection to server
    server.sin_addr.s_addr= inet_addr("127.0.0.1");
    server.sin_family= AF_INET;
    server.sin_port= htons(8000);

    //Connect to remote server
    int connection_status;
    connection_status=connect(client_socket,(struct sockaddr *) &server,sizeof(server));
    if(connection_status<0){
        printf("Connect error: %d",WSAGetLastError());
        return 1;
    }
    puts("Connected");

    //Send some data
    int send_status;
    message="FUNCIONE!!!";
    send_status=send(client_socket,message,strlen(message),0);
    if(send_status<0){
        puts("Send failed");
        return 1;
    }
    puts("Data send\n");
    return 0;
}