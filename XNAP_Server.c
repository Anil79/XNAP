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

#include "XNAP_18.5_Stack.h"

void XNAP_ReceiveMessage( uint8_t procedureCode, uint8_t messageType, void * msg, SI_XNAPNode * ngNode)
{
	printf("received message procedureCode=%d Type=%d\n", procedureCode, messageType);
}

int main( int argc, char* argv[])
{
	printf( "XNAP Server\n");
	XNAP__InitStack( "./xnap_s_logs/");
	XNAP__SetHost( "192.160.1.3", NULL, 38422);
	XNAP__SetOnMessageRecv( XNAP_ReceiveMessage);
	XNAP__StartStack();

	// cat /proc/net/sctp/eps 
	// lsof -R | grep 
		
	__si_core_wait();
}

