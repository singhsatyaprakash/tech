#include<stdio.h>
#include<winsock2.h>
#include<string.h>

int main() {

    WSADATA wsa;
    SOCKET s;
    struct sockaddr_in server;
    char msg[1000], reply[1000];
    //winsock initalized...
    WSAStartup(MAKEWORD(2,2), &wsa);

    s = socket(AF_INET, SOCK_STREAM, 0); //socket created

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_port = htons(8888);

    connect(s, (struct sockaddr*)&server, sizeof(server)); //connection to server

    while(1) {
        
        printf("Client: ");
        gets(msg);

        send(s, msg, strlen(msg), 0); //socket, buffer, size, flags...flag=0 normal sending

        if(strcmp(msg, "exit") == 0)
            break;

        int n = recv(s, reply, 1000, 0);
        reply[n] = '\0';

        printf("Server: %s\n", reply);

        if(strcmp(reply, "exit") == 0)
            break;
    }

    closesocket(s);
    WSACleanup();

    return 0;
}