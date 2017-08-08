#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

int main(int argc, char *argv[]) {

    int port;
    if (argc != 2 || sscanf(argv[1], "%i", &port) == 0) {
        printf("Usage: %s PORT\n", argv[0]);
        return 1;
    }

    int fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (fd == -1) {
        perror("socket");
        return 1;
    }

    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(fd, (struct sockaddr *) &addr, sizeof(addr)) == -1) {
        perror("bind");
        return 1;
    }

    while (1) {
        struct sockaddr_storage addr_client;
        socklen_t addr_client_len = sizeof(addr_client);
        char buffer[256];
        int len = recvfrom(fd, buffer, 256, 0, (struct sockaddr *) &addr_client, &addr_client_len);
        if (len < 0) {
            perror("recvfrom");
            return 1;
        }
        printf("%.*s\n", len, buffer);
        // Reply.
        if (addr_client.ss_family == AF_INET) 
            sendto(fd, "reply!", strlen("reply!"), 0, (struct sockaddr *) &addr_client, sizeof(struct sockaddr_in));
        else if (addr_client.ss_family == AF_INET6)
            sendto(fd, "reply!", strlen("reply!"), 0, (struct sockaddr *) &addr_client, sizeof(struct sockaddr_in6));
    }

    close(fd);

    return 0;
}
