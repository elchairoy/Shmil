#include "p2p.h"

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>

#define LISTEN_PORT 3910
#define MAX_CLIENTS 100

int main(void)
{
    int our_socket = 0, client1 = 0, client2 = 0;
    struct sockaddr_in our_address; /* What address (network card) and port to listen on */

    /* Create an IP socket, using stream method, using TCP. */
    our_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    printf("socket retrieve success\n");

    our_address.sin_family = AF_INET;                /* Use IPv4 addresses */
    our_address.sin_addr.s_addr = htonl(INADDR_ANY); /* Listen on any network card */
    our_address.sin_port = htons(LISTEN_PORT);       /* Specify port */

    bind(our_socket, (struct sockaddr *)&our_address, sizeof(our_address));
    listen(our_socket, MAX_CLIENTS);

    while (1)
    {
        struct sockaddr_in peer1_addr, peer2_addr;
        socklen_t peer1_addr_len = sizeof(peer1_addr);
        socklen_t peer2_addr_len = sizeof(peer2_addr);

        client1 = accept(our_socket, (struct sockaddr*) &peer1_addr, &peer1_addr_len); /* accept awaiting request */
        printf("Got my first client!\n");
        client2 = accept(our_socket, (struct sockaddr*) &peer2_addr, &peer2_addr_len); /* accept awaiting request */
        printf("Got my second client!\n");

        establish_p2p(client1, peer1_addr, client2, peer2_addr);
        
        close(client1);
        close(client2);
    }

    return 0;
}