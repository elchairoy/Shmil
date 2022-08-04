#include "p2p.h"

#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <unistd.h>

int establish_p2p(int peer1, struct sockaddr_in peer1_addr, int peer2, struct sockaddr_in peer2_addr)
{
    printf("peer1: %s:%d\n", inet_ntoa(peer1_addr.sin_addr), ntohs(peer1_addr.sin_port));
    printf("peer2: %s:%d\n", inet_ntoa(peer2_addr.sin_addr), ntohs(peer2_addr.sin_port));

    if (
        write(peer1, &peer2_addr, sizeof(peer2_addr)) < 0 ||
        write(peer2, &peer1_addr, sizeof(peer1_addr)) < 0
    ) return -1;

    return 0;
}
