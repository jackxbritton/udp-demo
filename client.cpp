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
    addr.sin_addr.s_addr = htonl(0x7f000001);

    if (sendto(fd, "test", strlen("test"), 0, (struct sockaddr *) &addr, sizeof(addr)) == -1) {
        perror("sendto");
        return 1;
    }

    return 0;
}
