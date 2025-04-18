#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <semaphore.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdarg.h>
#include <unistd.h>
#include <signal.h>
#include <limits.h>
#include <poll.h>
#include <sys/epoll.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <error.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <net/if.h> 
#include <resolv.h>


#ifndef SI_XNAP_18_5__H
#define SI_XNAP_18_5__H

#include "sirik_socket.h"
#include "XNAP_18.5.h"
#include "XNAP_18.5_Facade.h"

typedef int (*XNAP__FPointer_OnConnect)( SI_Socket * siSocket);

void XNAP__InitStack( char * logsPath);
void XNAP__SetHost( char * ipv4_1, char * ipv4_2, int port);
void XNAP__SetOnMessageRecv( fp_xnap_on_message handler );
void XNAP__SetOnConnect( XNAP__FPointer_OnConnect fp);
void XNAP__AddServer( char * ipv4_1, char * ipv4_2, int port);
void XNAP__StartStack();


#endif




