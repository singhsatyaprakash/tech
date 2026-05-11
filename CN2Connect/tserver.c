#include<stdio.h>
#include<winsock2.h>
#include<string.h>

int main() {

    WSADATA wsa;
    SOCKET server_socket, client_socket;
    struct sockaddr_in server, client;
    int c;
    char msg[1000], reply[1000];

    WSAStartup(MAKEWORD(2,2), &wsa);

    server_socket = socket(AF_INET, SOCK_STREAM, 0);

    //socket created...

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(8888);

    bind(server_socket, (struct sockaddr*)&server, sizeof(server));

    listen(server_socket, 3); // waiting for incoming single..

    c = sizeof(struct sockaddr_in);

    client_socket = accept(server_socket, (struct sockaddr*)&client, &c);

    while(1) {

        int n = recv(client_socket, msg, 1000, 0);
        msg[n] = '\0';

        printf("Client: %s\n", msg);

        if(strcmp(msg, "exit") == 0)
            break;

        printf("Server: ");
        gets(reply);

        send(client_socket, reply, strlen(reply), 0);

        if(strcmp(reply, "exit") == 0)
            break;
    }

    closesocket(client_socket);
    closesocket(server_socket);
    WSACleanup();

    return 0;
}