#include <stdlib.h>
#include <stdio.h>

#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>    

enum
{
    BACKLOG = 10
};

int
main (int argc, char *argv[])
{
    int socket_desc = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_desc == -1) {
        return 1;
    }

    int port;
    sscanf(argv[1], "%d", &port);

    struct sockaddr_in server, client;
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = htonl(INADDR_ANY);
    server.sin_port = htons(port);

    if ( bind(socket_desc, (struct sockaddr *)&server, sizeof(server)) < 0) {
        return 2;
    }

    listen(socket_desc, BACKLOG);

    int c = sizeof(struct sockaddr_in);

    long long sum = 0;

    while (1) {

        int client_sock = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c);
        if (client_sock < 0) {
            return 3;
        }

        int32_t msg = 0;
        read(client_sock, &msg, sizeof(msg));
        msg = ntohl(msg);
        sum += msg;

        close(client_sock);

        if (!msg) {
            break;
        }
    }

    close(socket_desc);
    printf("%lld\n", sum);
    
    return 0;
}