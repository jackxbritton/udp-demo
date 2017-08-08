#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

int main(int argc, char *argv[]) {

    int ip_ints[4];
    int port;
    if (argc != 3 || sscanf(argv[1], "%i.%i.%i.%i:%i", &ip_ints[0], &ip_ints[1], &ip_ints[2], &ip_ints[3], &port) != 5) {
        printf("Usage: %s IP:PORT MSG\n", argv[0]);
        return 1;
    }

    uint32_t ip = ((ip_ints[3] <<  0) & 0x000000FF)
                | ((ip_ints[2] <<  8) & 0x0000FF00)
                | ((ip_ints[1] << 16) & 0x00FF0000)
                | ((ip_ints[0] << 24) & 0xFF000000);

    int fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (fd == -1) {
        perror("socket");
        return 1;
    }

    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = htonl(ip);

    if (sendto(fd, argv[2], strlen(argv[2]), 0, (struct sockaddr *) &addr, sizeof(addr)) == -1) {
        perror("sendto");
        return 1;
    }
    // Receive response.
    char buffer[256];
    int len = recvfrom(fd, buffer, 256, 0, NULL, NULL);
    if (len < 0) {
        perror("recvfrom");
        return 1;
    }
    printf("%.*s\n", len, buffer);

    return 0;
}
