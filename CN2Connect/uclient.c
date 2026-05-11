#include<stdio.h>
#include<winsock2.h>
#include<string.h>

int main() {

    WSADATA wsa;
    SOCKET s;

    struct sockaddr_in server;

    int server_len = sizeof(server);

    char msg[1000], reply[1000];

    WSAStartup(MAKEWORD(2,2), &wsa);

    // socket created
    s = socket(AF_INET, SOCK_DGRAM, 0);

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_port = htons(8888);

    while(1) {

        printf("Client: ");
        gets(msg);

        sendto(s, msg, strlen(msg), 0,
              (struct sockaddr*)&server, server_len);

        if(strcmp(msg, "exit") == 0)
            break;

        int n = recvfrom(s, reply, 1000, 0,
                        NULL, NULL);

        reply[n] = '\0';

        printf("Server: %s\n", reply);

        if(strcmp(reply, "exit") == 0)
            break;
    }

    closesocket(s);
    WSACleanup();

    return 0;
}
