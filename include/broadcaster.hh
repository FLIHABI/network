#ifndef F_BROADCASTER
# define F_BROADCASTER

# define BROADCAST_ADD "255.255.255.255"

int broadcastLoop();
int broadcast(const char *ip, const char *msg, int port);

#endif
