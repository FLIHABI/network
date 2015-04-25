#ifndef F_BROADCASTER
# define F_BROADCASTER

# define BROADCAST_ADD "255.255.255.255"
# define BROADCAST_MSG "Flihabi"
# define BROADCAST_PORT 4545

int broadcastLoop();
int broadcast(const char *ip, const char *msg, int port);

# include "broadcaster.cc"

#endif
