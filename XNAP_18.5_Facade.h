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

#include "sirik_core.h"
#include "libAsn.h"
#include "XNAP_18.5.h"
//#include "lib_node.h"

#ifndef SIRIK_XNAP_H
#define SIRIK_XNAP_H


typedef struct __si_xnap_node
{
	SI_Socket * siSocket;
	//SI_RAN_Client * RANClient;
	int NodeType;
	uint8_t * transportEng;
	
} SI_XNAPNode;

typedef void (*fp_xnap_on_message)( uint8_t procedureCode, uint8_t messageType, void * msg, SI_XNAPNode * ngNode);

void __si_xnap_set_app_messahe_handler( fp_xnap_on_message handler);
void __si_xnap_handle_message( SI_XNAPNode * s1apNode, SI_SocketSCTPBuffer * sctpBuffer);

int __si_xnap_sendmsg( uint8_t * buffer, uint32_t len, SI_XNAPNode * ngNode);
void __si_xnap_app_message_handler( uint8_t procedureCode, uint8_t messageType, void * msg, SI_XNAPNode * ngNode);






int __si_xnap_send_HandoverRequest( SI_XNAP_DT_PDU_HandoverRequest * objHandoverRequest, SI_XNAPNode * xnapNode);
int __si_xnap_send_HandoverRequestAcknowledge( SI_XNAP_DT_PDU_HandoverRequestAcknowledge * objHandoverRequestAcknowledge, SI_XNAPNode * xnapNode);
int __si_xnap_send_HandoverPreparationFailure( SI_XNAP_DT_PDU_HandoverPreparationFailure * objHandoverPreparationFailure, SI_XNAPNode * xnapNode);
int __si_xnap_send_SNStatusTransfer( SI_XNAP_DT_PDU_SNStatusTransfer * objSNStatusTransfer, SI_XNAPNode * xnapNode);
int __si_xnap_send_HandoverCancel( SI_XNAP_DT_PDU_HandoverCancel * objHandoverCancel, SI_XNAPNode * xnapNode);
int __si_xnap_send_RetrieveUEContextRequest( SI_XNAP_DT_PDU_RetrieveUEContextRequest * objRetrieveUEContextRequest, SI_XNAPNode * xnapNode);
int __si_xnap_send_RetrieveUEContextResponse( SI_XNAP_DT_PDU_RetrieveUEContextResponse * objRetrieveUEContextResponse, SI_XNAPNode * xnapNode);
int __si_xnap_send_RetrieveUEContextFailure( SI_XNAP_DT_PDU_RetrieveUEContextFailure * objRetrieveUEContextFailure, SI_XNAPNode * xnapNode);
int __si_xnap_send_RANPaging( SI_XNAP_DT_PDU_RANPaging * objRANPaging, SI_XNAPNode * xnapNode);
int __si_xnap_send_XnUAddressIndication( SI_XNAP_DT_PDU_XnUAddressIndication * objXnUAddressIndication, SI_XNAPNode * xnapNode);
int __si_xnap_send_UEContextRelease( SI_XNAP_DT_PDU_UEContextRelease * objUEContextRelease, SI_XNAPNode * xnapNode);
int __si_xnap_send_SNodeAdditionRequest( SI_XNAP_DT_PDU_SNodeAdditionRequest * objSNodeAdditionRequest, SI_XNAPNode * xnapNode);
int __si_xnap_send_SNodeAdditionRequestAcknowledge( SI_XNAP_DT_PDU_SNodeAdditionRequestAcknowledge * objSNodeAdditionRequestAcknowledge, SI_XNAPNode * xnapNode);
int __si_xnap_send_SNodeAdditionRequestReject( SI_XNAP_DT_PDU_SNodeAdditionRequestReject * objSNodeAdditionRequestReject, SI_XNAPNode * xnapNode);
int __si_xnap_send_SNodeReconfigurationComplete( SI_XNAP_DT_PDU_SNodeReconfigurationComplete * objSNodeReconfigurationComplete, SI_XNAPNode * xnapNode);
int __si_xnap_send_SNodeModificationRequest( SI_XNAP_DT_PDU_SNodeModificationRequest * objSNodeModificationRequest, SI_XNAPNode * xnapNode);
int __si_xnap_send_SNodeModificationRequestAcknowledge( SI_XNAP_DT_PDU_SNodeModificationRequestAcknowledge * objSNodeModificationRequestAcknowledge, SI_XNAPNode * xnapNode);
int __si_xnap_send_SNodeModificationRequestReject( SI_XNAP_DT_PDU_SNodeModificationRequestReject * objSNodeModificationRequestReject, SI_XNAPNode * xnapNode);
int __si_xnap_send_SNodeModificationRequired( SI_XNAP_DT_PDU_SNodeModificationRequired * objSNodeModificationRequired, SI_XNAPNode * xnapNode);
int __si_xnap_send_SNodeModificationConfirm( SI_XNAP_DT_PDU_SNodeModificationConfirm * objSNodeModificationConfirm, SI_XNAPNode * xnapNode);
int __si_xnap_send_SNodeModificationRefuse( SI_XNAP_DT_PDU_SNodeModificationRefuse * objSNodeModificationRefuse, SI_XNAPNode * xnapNode);
int __si_xnap_send_SNodeReleaseRequest( SI_XNAP_DT_PDU_SNodeReleaseRequest * objSNodeReleaseRequest, SI_XNAPNode * xnapNode);
int __si_xnap_send_SNodeReleaseRequestAcknowledge( SI_XNAP_DT_PDU_SNodeReleaseRequestAcknowledge * objSNodeReleaseRequestAcknowledge, SI_XNAPNode * xnapNode);
int __si_xnap_send_SNodeReleaseReject( SI_XNAP_DT_PDU_SNodeReleaseReject * objSNodeReleaseReject, SI_XNAPNode * xnapNode);
int __si_xnap_send_SNodeReleaseRequired( SI_XNAP_DT_PDU_SNodeReleaseRequired * objSNodeReleaseRequired, SI_XNAPNode * xnapNode);
int __si_xnap_send_SNodeReleaseConfirm( SI_XNAP_DT_PDU_SNodeReleaseConfirm * objSNodeReleaseConfirm, SI_XNAPNode * xnapNode);
int __si_xnap_send_SNodeCounterCheckRequest( SI_XNAP_DT_PDU_SNodeCounterCheckRequest * objSNodeCounterCheckRequest, SI_XNAPNode * xnapNode);
int __si_xnap_send_SNodeChangeRequired( SI_XNAP_DT_PDU_SNodeChangeRequired * objSNodeChangeRequired, SI_XNAPNode * xnapNode);
int __si_xnap_send_SNodeChangeConfirm( SI_XNAP_DT_PDU_SNodeChangeConfirm * objSNodeChangeConfirm, SI_XNAPNode * xnapNode);
int __si_xnap_send_SNodeChangeRefuse( SI_XNAP_DT_PDU_SNodeChangeRefuse * objSNodeChangeRefuse, SI_XNAPNode * xnapNode);
int __si_xnap_send_RRCTransfer( SI_XNAP_DT_PDU_RRCTransfer * objRRCTransfer, SI_XNAPNode * xnapNode);
int __si_xnap_send_XnRemovalRequest( SI_XNAP_DT_PDU_XnRemovalRequest * objXnRemovalRequest, SI_XNAPNode * xnapNode);
int __si_xnap_send_XnRemovalResponse( SI_XNAP_DT_PDU_XnRemovalResponse * objXnRemovalResponse, SI_XNAPNode * xnapNode);
int __si_xnap_send_XnRemovalFailure( SI_XNAP_DT_PDU_XnRemovalFailure * objXnRemovalFailure, SI_XNAPNode * xnapNode);
int __si_xnap_send_XnSetupRequest( SI_XNAP_DT_PDU_XnSetupRequest * objXnSetupRequest, SI_XNAPNode * xnapNode);
int __si_xnap_send_XnSetupResponse( SI_XNAP_DT_PDU_XnSetupResponse * objXnSetupResponse, SI_XNAPNode * xnapNode);
int __si_xnap_send_XnSetupFailure( SI_XNAP_DT_PDU_XnSetupFailure * objXnSetupFailure, SI_XNAPNode * xnapNode);
int __si_xnap_send_NGRANNodeConfigurationUpdate( SI_XNAP_DT_PDU_NGRANNodeConfigurationUpdate * objNGRANNodeConfigurationUpdate, SI_XNAPNode * xnapNode);
int __si_xnap_send_NGRANNodeConfigurationUpdateAcknowledge( SI_XNAP_DT_PDU_NGRANNodeConfigurationUpdateAcknowledge * objNGRANNodeConfigurationUpdateAcknowledge, SI_XNAPNode * xnapNode);
int __si_xnap_send_NGRANNodeConfigurationUpdateFailure( SI_XNAP_DT_PDU_NGRANNodeConfigurationUpdateFailure * objNGRANNodeConfigurationUpdateFailure, SI_XNAPNode * xnapNode);
int __si_xnap_send_PartialUEContextTransfer( SI_XNAP_DT_PDU_PartialUEContextTransfer * objPartialUEContextTransfer, SI_XNAPNode * xnapNode);
int __si_xnap_send_PartialUEContextTransferAcknowledge( SI_XNAP_DT_PDU_PartialUEContextTransferAcknowledge * objPartialUEContextTransferAcknowledge, SI_XNAPNode * xnapNode);
int __si_xnap_send_PartialUEContextTransferFailure( SI_XNAP_DT_PDU_PartialUEContextTransferFailure * objPartialUEContextTransferFailure, SI_XNAPNode * xnapNode);
int __si_xnap_send_E_UTRA_NR_CellResourceCoordinationRequest( SI_XNAP_DT_PDU_E_UTRA_NR_CellResourceCoordinationRequest * objE_UTRA_NR_CellResourceCoordinationRequest, SI_XNAPNode * xnapNode);
int __si_xnap_send_E_UTRA_NR_CellResourceCoordinationResponse( SI_XNAP_DT_PDU_E_UTRA_NR_CellResourceCoordinationResponse * objE_UTRA_NR_CellResourceCoordinationResponse, SI_XNAPNode * xnapNode);
int __si_xnap_send_CellActivationRequest( SI_XNAP_DT_PDU_CellActivationRequest * objCellActivationRequest, SI_XNAPNode * xnapNode);
int __si_xnap_send_CellActivationResponse( SI_XNAP_DT_PDU_CellActivationResponse * objCellActivationResponse, SI_XNAPNode * xnapNode);
int __si_xnap_send_CellActivationFailure( SI_XNAP_DT_PDU_CellActivationFailure * objCellActivationFailure, SI_XNAPNode * xnapNode);
int __si_xnap_send_ResetRequest( SI_XNAP_DT_PDU_ResetRequest * objResetRequest, SI_XNAPNode * xnapNode);
int __si_xnap_send_ResetResponse( SI_XNAP_DT_PDU_ResetResponse * objResetResponse, SI_XNAPNode * xnapNode);
int __si_xnap_send_ErrorIndication( SI_XNAP_DT_PDU_ErrorIndication * objErrorIndication, SI_XNAPNode * xnapNode);
int __si_xnap_send_NotificationControlIndication( SI_XNAP_DT_PDU_NotificationControlIndication * objNotificationControlIndication, SI_XNAPNode * xnapNode);
int __si_xnap_send_ActivityNotification( SI_XNAP_DT_PDU_ActivityNotification * objActivityNotification, SI_XNAPNode * xnapNode);
int __si_xnap_send_PrivateMessage( SI_XNAP_DT_PDU_PrivateMessage * objPrivateMessage, SI_XNAPNode * xnapNode);
int __si_xnap_send_SecondaryRATDataUsageReport( SI_XNAP_DT_PDU_SecondaryRATDataUsageReport * objSecondaryRATDataUsageReport, SI_XNAPNode * xnapNode);
int __si_xnap_send_DeactivateTrace( SI_XNAP_DT_PDU_DeactivateTrace * objDeactivateTrace, SI_XNAPNode * xnapNode);
int __si_xnap_send_TraceStart( SI_XNAP_DT_PDU_TraceStart * objTraceStart, SI_XNAPNode * xnapNode);
int __si_xnap_send_HandoverSuccess( SI_XNAP_DT_PDU_HandoverSuccess * objHandoverSuccess, SI_XNAPNode * xnapNode);
int __si_xnap_send_ConditionalHandoverCancel( SI_XNAP_DT_PDU_ConditionalHandoverCancel * objConditionalHandoverCancel, SI_XNAPNode * xnapNode);
int __si_xnap_send_EarlyStatusTransfer( SI_XNAP_DT_PDU_EarlyStatusTransfer * objEarlyStatusTransfer, SI_XNAPNode * xnapNode);
int __si_xnap_send_FailureIndication( SI_XNAP_DT_PDU_FailureIndication * objFailureIndication, SI_XNAPNode * xnapNode);
int __si_xnap_send_HandoverReport( SI_XNAP_DT_PDU_HandoverReport * objHandoverReport, SI_XNAPNode * xnapNode);
int __si_xnap_send_ResourceStatusRequest( SI_XNAP_DT_PDU_ResourceStatusRequest * objResourceStatusRequest, SI_XNAPNode * xnapNode);
int __si_xnap_send_ResourceStatusResponse( SI_XNAP_DT_PDU_ResourceStatusResponse * objResourceStatusResponse, SI_XNAPNode * xnapNode);
int __si_xnap_send_ResourceStatusFailure( SI_XNAP_DT_PDU_ResourceStatusFailure * objResourceStatusFailure, SI_XNAPNode * xnapNode);
int __si_xnap_send_ResourceStatusUpdate( SI_XNAP_DT_PDU_ResourceStatusUpdate * objResourceStatusUpdate, SI_XNAPNode * xnapNode);
int __si_xnap_send_MobilityChangeRequest( SI_XNAP_DT_PDU_MobilityChangeRequest * objMobilityChangeRequest, SI_XNAPNode * xnapNode);
int __si_xnap_send_MobilityChangeAcknowledge( SI_XNAP_DT_PDU_MobilityChangeAcknowledge * objMobilityChangeAcknowledge, SI_XNAPNode * xnapNode);
int __si_xnap_send_MobilityChangeFailure( SI_XNAP_DT_PDU_MobilityChangeFailure * objMobilityChangeFailure, SI_XNAPNode * xnapNode);
int __si_xnap_send_AccessAndMobilityIndication( SI_XNAP_DT_PDU_AccessAndMobilityIndication * objAccessAndMobilityIndication, SI_XNAPNode * xnapNode);
int __si_xnap_send_CellTrafficTrace( SI_XNAP_DT_PDU_CellTrafficTrace * objCellTrafficTrace, SI_XNAPNode * xnapNode);
int __si_xnap_send_RANMulticastGroupPaging( SI_XNAP_DT_PDU_RANMulticastGroupPaging * objRANMulticastGroupPaging, SI_XNAPNode * xnapNode);
int __si_xnap_send_ScgFailureInformationReport( SI_XNAP_DT_PDU_ScgFailureInformationReport * objScgFailureInformationReport, SI_XNAPNode * xnapNode);
int __si_xnap_send_ScgFailureTransfer( SI_XNAP_DT_PDU_ScgFailureTransfer * objScgFailureTransfer, SI_XNAPNode * xnapNode);
int __si_xnap_send_F1CTrafficTransfer( SI_XNAP_DT_PDU_F1CTrafficTransfer * objF1CTrafficTransfer, SI_XNAPNode * xnapNode);
int __si_xnap_send_IABTransportMigrationManagementRequest( SI_XNAP_DT_PDU_IABTransportMigrationManagementRequest * objIABTransportMigrationManagementRequest, SI_XNAPNode * xnapNode);
int __si_xnap_send_IABTransportMigrationManagementResponse( SI_XNAP_DT_PDU_IABTransportMigrationManagementResponse * objIABTransportMigrationManagementResponse, SI_XNAPNode * xnapNode);
int __si_xnap_send_IABTransportMigrationManagementReject( SI_XNAP_DT_PDU_IABTransportMigrationManagementReject * objIABTransportMigrationManagementReject, SI_XNAPNode * xnapNode);
int __si_xnap_send_IABTransportMigrationModificationRequest( SI_XNAP_DT_PDU_IABTransportMigrationModificationRequest * objIABTransportMigrationModificationRequest, SI_XNAPNode * xnapNode);
int __si_xnap_send_IABTransportMigrationModificationResponse( SI_XNAP_DT_PDU_IABTransportMigrationModificationResponse * objIABTransportMigrationModificationResponse, SI_XNAPNode * xnapNode);
int __si_xnap_send_IABResourceCoordinationRequest( SI_XNAP_DT_PDU_IABResourceCoordinationRequest * objIABResourceCoordinationRequest, SI_XNAPNode * xnapNode);
int __si_xnap_send_IABResourceCoordinationResponse( SI_XNAP_DT_PDU_IABResourceCoordinationResponse * objIABResourceCoordinationResponse, SI_XNAPNode * xnapNode);
int __si_xnap_send_RetrieveUEContextConfirm( SI_XNAP_DT_PDU_RetrieveUEContextConfirm * objRetrieveUEContextConfirm, SI_XNAPNode * xnapNode);
int __si_xnap_send_CPCCancel( SI_XNAP_DT_PDU_CPCCancel * objCPCCancel, SI_XNAPNode * xnapNode);
int __si_xnap_send_RachIndication( SI_XNAP_DT_PDU_RachIndication * objRachIndication, SI_XNAPNode * xnapNode);
int __si_xnap_send_DataCollectionRequest( SI_XNAP_DT_PDU_DataCollectionRequest * objDataCollectionRequest, SI_XNAPNode * xnapNode);
int __si_xnap_send_DataCollectionResponse( SI_XNAP_DT_PDU_DataCollectionResponse * objDataCollectionResponse, SI_XNAPNode * xnapNode);
int __si_xnap_send_DataCollectionFailure( SI_XNAP_DT_PDU_DataCollectionFailure * objDataCollectionFailure, SI_XNAPNode * xnapNode);
int __si_xnap_send_DataCollectionUpdate( SI_XNAP_DT_PDU_DataCollectionUpdate * objDataCollectionUpdate, SI_XNAPNode * xnapNode);





#endif
