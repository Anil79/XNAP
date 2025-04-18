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

#include "sirik_socket.h"
#include "XNAP_18.5.h"
#include "XNAP_18.5_Stack.h"


int xnap_server_onconnect( SI_Socket * siSocket)
{
	printf("Connected\n");

	SI_XNAPNode * f1Node = (SI_XNAPNode *) siSocket->transportEng;

	if(!f1Node)
	{
		__si_malloc2( sizeof( SI_XNAPNode), (uint8_t **)&f1Node);
		siSocket->transportEng 	= (uint8_t *) f1Node;
		f1Node->transportEng 	= (uint8_t *) siSocket;
	}
	f1Node->siSocket = siSocket;
	

	// SI_XNAP_DT_PDU_XnSetupRequest * oXnSetupRequest = (SI_XNAP_DT_PDU_XnSetupRequest*)malloc(sizeof(SI_XNAP_DT_PDU_XnSetupRequest));
	// memset( oXnSetupRequest, 0, sizeof(SI_XNAP_DT_PDU_XnSetupRequest));
	
	
	// // ID = id-GlobalNG-RAN-node-ID, PRESENCE = mandatory L:9858
	// SI_XNAP_DT_GlobalNG_RANNode_ID * globalNGRANnodeID;
	// oXnSetupRequest->globalNGRANnodeID_isset = 1;

	// // ID = id-TAISupport-list, PRESENCE = mandatory L:9858
	// SI_XNAP_DT_TAISupport_List * tAISupportlist;
	// oXnSetupRequest->tAISupportlist_isset = 1;

	// // ID = id-AMF-Region-Information, PRESENCE = mandatory L:9858
	// // SI_XNAP_DT_AMF_Region_Information * aMFRegionInformation;
	// __si_xnap_init_AMF_Region_Information( &oXnSetupRequest->aMFRegionInformation);
	
	// SI_XNAP_DT_GlobalAMF_Region_Information * oGlobalAMF_Region_Information = (SI_XNAP_DT_GlobalAMF_Region_Information*)malloc(sizeof(SI_XNAP_DT_GlobalAMF_Region_Information));
	// memset( oGlobalAMF_Region_Information, 0, sizeof(SI_XNAP_DT_GlobalAMF_Region_Information));
	
	// // SI_XNAP_DT_PLMN_Identity * plmn_ID;
	// __si_xnap_init_PLMN_Identity2( &oGlobalAMF_Region_Information->plmn_ID, "/x21/x22/x23", 3);

	// // SI_XNAP_DT_GlobalAMFRegionInformation_amf_region_id * amf_region_id;
	
	// __si_linked_list_add( oXnSetupRequest->aMFRegionInformation->GlobalAMF_Region_Information, (uint8_t*)SI_XNAP_DT_GlobalAMF_Region_Information);
	// oXnSetupRequest->aMFRegionInformation_isset = 1;
	 
	SI_XNAP_DT_PDU_UEContextRelease * oUEContextRelease = (SI_XNAP_DT_PDU_UEContextRelease*)__si_allocM(sizeof(SI_XNAP_DT_PDU_UEContextRelease));
	memset( oUEContextRelease, 0, sizeof(SI_XNAP_DT_PDU_UEContextRelease));
	

	oUEContextRelease->sourceNGRANnodeUEXnAPID = 2;
	oUEContextRelease->sourceNGRANnodeUEXnAPID_isset = 1;

	oUEContextRelease->targetNGRANnodeUEXnAPID = 3;
	oUEContextRelease->targetNGRANnodeUEXnAPID_isset = 1;
	
	__si_xnap_send_UEContextRelease( oUEContextRelease, f1Node);
	__si_xnap_memfree_pdu_UEContextRelease( oUEContextRelease);

	return 0;
}	

void XNAP_ReceiveMessage( uint8_t procedureCode, uint8_t messageType, void * msg, SI_XNAPNode * ngNode)
{
	printf("Received Message With procedureCode=%u\n", procedureCode);
}

int main( int argc, char* argv[])
{
	printf( "XNAP Server\n");
	XNAP__InitStack( "./xnap_c_logs/");
	XNAP__SetHost( "192.160.1.4", NULL, 0);
	XNAP__AddServer( "192.160.1.3", NULL, 38422);
	XNAP__SetOnConnect( xnap_server_onconnect);
	XNAP__SetOnMessageRecv( XNAP_ReceiveMessage);
	XNAP__StartStack();

	// cat /proc/net/sctp/eps 
	// lsof -R | grep 
		
	__si_core_wait();
}

