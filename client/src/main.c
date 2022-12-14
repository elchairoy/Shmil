#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>
#include <errno.h>
#include <stdio.h>
#include <netinet/in.h>

#include "p2p.h"

int main(void)
{
    int our_socket = 0;
    char buffer[1000];
    socklen_t size;
    struct sockaddr_in peer_addr;

    if ((our_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0) /* Creates the socket */
        return -1;

    if (get_other_peer_addr(our_socket, &peer_addr) < 0)
    {
        printf("Network error when trying to get other's peer address");
	printf("Errno: %d\n", errno);
        return -1;
    }
    printf("peer: %s:%d\n", inet_ntoa(peer_addr.sin_addr), ntohs(peer_addr.sin_port));

    if (udp_hole_punching(our_socket, peer_addr) < 0)
    {
        printf("Network error when trying to hole punch");
        return -1;
    }
    while (1)
    {
	/* Send */
	printf("Enter a message to send:\n");
	fgets(buffer, 1000, stdin);                  /* -1 to exclude the '\n' */
    	if (sendto(our_socket, (const char *)buffer, strlen(buffer) - 1,
        	MSG_CONFIRM, (const struct sockaddr *)&peer_addr,
	       	sizeof(peer_addr)) /* Sends the massage to the server */
		< 0)
			return -1;

	/* Get */
    	size = sizeof(peer_addr);
	memset(buffer, 0, 1000); /* Reset the buffer */
    	if (recvfrom(our_socket, buffer, 1000, MSG_WAITALL, (struct sockaddr *)&peer_addr,
         	&size) /* Gets the other peer's address from the server */
		< 0)
			return -1;
			
        printf("Got from peer: %s\n", buffer);
    }
    
    close(our_socket);

    return 0;
}
