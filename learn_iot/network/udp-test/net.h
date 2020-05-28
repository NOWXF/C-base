#ifndef __NET_H__
#define __NET_H__

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <strings.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <sys/wait.h>

#define SOCK_PORT 5001
#define SOCK_ADDR "127.0.0.1"

#endif
