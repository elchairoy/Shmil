#include "p2p.h"

#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/udp.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>

#define LISTEN_PORT 3910
#define MAX_CLIENTS 100
#define MAX_MESSAGE_LEN 1024

int main(void)
{
	int our_socket = 0;
	char buffer[MAX_MESSAGE_LEN];

	struct sockaddr_in our_address; /* What address (network card) and port to listen on */

	/* Create an IP socket, using stream method, using UDP. */
	our_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	printf("socket retrieve success\n");

	our_address.sin_family = AF_INET;				 /* Use IPv4 addresses */
	our_address.sin_addr.s_addr = htonl(INADDR_ANY); /* Listen on any network card */
	our_address.sin_port = htons(LISTEN_PORT);		 /* Specify port */

	bind(our_socket, (struct sockaddr *)&our_address, sizeof(our_address));

	while (1)
	{
		struct sockaddr_in peer1_addr, peer2_addr;
		unsigned int len1, len2; /* The lengths of the addresses (needed for recvfrom) */
		len1 = sizeof(peer1_addr);
		len2 = sizeof(peer2_addr);

		if (recvfrom(our_socket, (char *)buffer, MAX_MESSAGE_LEN,
					 MSG_WAITALL, (struct sockaddr *)&peer1_addr,
					 &len1) /* Get a massage from peer1 and insert his address into peer1_addr */
			< 0)
		{
			printf("Error occured getting first client");
			return -1;
		}
		printf("Got first peer: %s:%d\n", inet_ntoa(peer1_addr.sin_addr), ntohs(peer1_addr.sin_port));
		if (recvfrom(our_socket, (char *)buffer, MAX_MESSAGE_LEN,
					 MSG_WAITALL, (struct sockaddr *)&peer2_addr,
					 &len2) /* Get a massage from peer1 and insert his address into peer1_addr */
			< 0)
		{
			printf("Error occured getting first client");
			return -1;
		}
		printf("Got second peer: %s:%d\n", inet_ntoa(peer2_addr.sin_addr), ntohs(peer2_addr.sin_port));

		if (establish_p2p(our_socket, peer1_addr, peer2_addr) /* Send the addresses of each peer to the second peer */ < 0)
		{
			printf("Error occured sending the peers addresses.");
			return -1;
		}
	}

	return 0;
}