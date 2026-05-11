#include<stdio.h>
#include<winsock2.h>
#include<string.h>

int main() {

    WSADATA wsa;
    SOCKET server_socket;

    struct sockaddr_in server, client;

    int c = sizeof(client);

    char msg[1000], reply[1000];

    WSAStartup(MAKEWORD(2,2), &wsa);

    // socket created
    server_socket = socket(AF_INET, SOCK_DGRAM, 0);

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(8888);

    bind(server_socket, (struct sockaddr*)&server, sizeof(server));

    while(1) {

        int n = recvfrom(server_socket, msg, 1000, 0,
                        (struct sockaddr*)&client, &c);

        msg[n] = '\0';

        printf("Client: %s\n", msg);

        if(strcmp(msg, "exit") == 0)
            break;

        printf("Server: ");
        gets(reply);

        sendto(server_socket, reply, strlen(reply), 0,
              (struct sockaddr*)&client, c);

        if(strcmp(reply, "exit") == 0)
            break;
    }

    closesocket(server_socket);
    WSACleanup();

    return 0;
}