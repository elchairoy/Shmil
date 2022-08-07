#include "p2p.h"

#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <unistd.h>

int establish_p2p(int our_socket, struct sockaddr_in peer1_addr, struct sockaddr_in peer2_addr)
{
    /* Print the addresses. */
    printf("peer1: %s:%d\n", inet_ntoa(peer1_addr.sin_addr), ntohs(peer1_addr.sin_port)); 
    printf("peer2: %s:%d\n", inet_ntoa(peer2_addr.sin_addr), ntohs(peer2_addr.sin_port));

    if (sendto(our_socket, &peer2_addr, sizeof(&peer1_addr),  
        MSG_CONFIRM, (const struct sockaddr *) &peer1_addr, 
            sizeof(peer1_addr)) /* Sends peer2 address to the peer1 */ < 0 ||
            
        sendto(our_socket, &peer1_addr, sizeof(&peer1_addr),  
        MSG_CONFIRM, (const struct sockaddr *) &peer2_addr, 
            sizeof(peer2_addr)) < 0 /* Sends peer1 address to the peer2 */
    ) return -1;

    return 0;
}
