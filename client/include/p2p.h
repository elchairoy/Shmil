#ifndef __P2P_H__
#define __P2P_H__

#include <netinet/in.h>

/**
 * @brief Gets from server the address of the other peer.
 * 
 * @param peer_addr A pointer to an address object.
 * @return int 0 on success, -1 on error.
 */
int get_other_peer_addr(struct sockaddr_in *peer_addr);

#endif