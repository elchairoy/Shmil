#ifndef P2P_H
#define P2P_H

#include <netinet/in.h>

/**
 * @brief Establishes a P2P connection between peer1 and peer2
 * 
 * @param  peer1      A connected socket to peer1
 * @param  peer1_addr Peer1's address and port
 * @param  peer2      A connected socket to peer2
 * @param  peer1_addr Peer2's address and port
 * @return int        0 on success, -1 on error
 */
int establish_p2p(int peer1, struct sockaddr_in peer1_addr, int peer2, struct sockaddr_in peer2_addr);

#endif