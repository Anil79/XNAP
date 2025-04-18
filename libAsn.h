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

#ifndef SIRIK_MME_DEFAULTS_H
#define SIRIK_MME_DEFAULTS_H

#pragma pack(4)

#define INITIATING_MESSAGE_PDU_CHOICE											0x00
#define SUCCESSFUL_OUTCOME_PDU_CHOICE											0x20
#define UN_SUCCESSFUL_OUTCOME_PDU_CHOICE										0x40

#define INITIATING_MESSAGE_PDU_CHOICE__EXT										0x00
#define SUCCESSFUL_OUTCOME_PDU_CHOICE__EXT										0x40
#define UN_SUCCESSFUL_OUTCOME_PDU_CHOICE__EXT									0x80


#define SI_ASN_DECODE_ERROR_OCTET_STRING										1001
#define SI_ASN_DECODE_ERROR_PRINTABLE_STRING									1002
#define SI_ASN_DECODE_ERROR_BIT_STRING											1003
#define SI_ASN_DECODE_ERROR_INTEGER												1004	
#define SI_ASN_DECODE_ERROR_ENUMERATOR											1005
#define SI_ASN_DECODE_ERROR_CHOICE												1006
#define SI_ASN_DECODE_ERROR_SEQUENCE											1007
#define SI_ASN_DECODE_ERROR_SEQUENCE_OF											1008

#define SI_ASN_DECODE_ERROR_INSUFFICENT_BUFFER									2010

uint16_t __si_asn_getTAC( u_char * data);
uint32_t __si_asn_getTAC3( u_char * data);
void __si_asn_getPlmn( u_char * data, uint16_t * mcc, uint16_t * mnc);
uint32_t __si_asn_cellId( u_char * data);

typedef struct __si_asn_coding_context
{
	uint8_t header[40];
	uint16_t headerlen;
	
	uint8_t buffer[1024];
	uint16_t pos;
	uint16_t len;
	uint8_t usedBits;
	uint16_t ieStartPos;
	uint16_t ieLastLen;
	uint32_t iError;
	
	int16_t ieMaxReadBytes;
	int16_t ieCurrPos;
} SI_ASN_CodingContext;

void __si_asn_memset( SI_ASN_CodingContext * context);
void __si_asn_init_CodingContext( SI_ASN_CodingContext * context);
void __si_asn_set_max_read_bytes_for_ie( uint16_t datalen, SI_ASN_CodingContext * context);
int __si_asn_has_decode_error( SI_ASN_CodingContext * context);
int __si_asn_copy_buffer( SI_ASN_CodingContext * context, unsigned char ** data, int * len);

void __si_asn_pad_bits( SI_ASN_CodingContext * context);
void __si_asn_pad_readbits( SI_ASN_CodingContext * context);
void __si_asn_add_bit( SI_ASN_CodingContext * context, uint8_t bitval);
void __si_asn_add_bits( SI_ASN_CodingContext * context, uint8_t * srcData, int srcMsbBitPos, uint16_t count, uint8_t padIfPendingBits);
void __si_asn_add_bytes( SI_ASN_CodingContext * context, uint8_t * srcData, uint16_t count, uint8_t padIfPendingBits);
void __si_asn_add_byte( SI_ASN_CodingContext * context, uint8_t srcData);
uint8_t __si_asn_get_bit_val_uint8( SI_ASN_CodingContext * context, uint8_t iReadBits);
uint8_t __si_asn_get_byte( SI_ASN_CodingContext * context);
void __si_asn_copy_nbits( SI_ASN_CodingContext * context, uint8_t * dstData, uint16_t count, uint8_t padIfPendingBits);
void __si_asn_copy_bytes( SI_ASN_CodingContext * context, uint8_t * dstData, uint16_t count, uint8_t padIfPendingBits);
uint16_t __si_asn_get_bit_val_uint16( SI_ASN_CodingContext * context, uint8_t iReadBits);
uint16_t __si_asn_get_range_val_length( SI_ASN_CodingContext * context);
uint16_t __si_asn_get_uint16val( SI_ASN_CodingContext * context);
uint16_t __si_asn_get_total_used_length( uint16_t datalen, SI_ASN_CodingContext * context);
uint16_t __si_asn_move_unknown_field_length( SI_ASN_CodingContext * context);
unsigned long long int __si_asn_get_uintmax( SI_ASN_CodingContext * context, int iNoOfbytes);
int __si_asn_get_listitem_count( uint16_t minItems, uint32_t maxItems, int lvl, SI_ASN_CodingContext * codingContext);


void __si_asn_reserve_byte_for_length( SI_ASN_CodingContext * context);
void __si_asn_set_length_at_reserved( SI_ASN_CodingContext * context);
void __si_asn_set_length_at_pos( int ieStartPos, SI_ASN_CodingContext * context);
void __si_asn_set_bit_at_index( SI_ASN_CodingContext * context, uint16_t index, uint8_t value);
void __si_asn_set_buffer_length( SI_ASN_CodingContext * context);
void __si_asn_add_length8( SI_ASN_CodingContext * context, uint8_t length);
void __si_asn_add_length16( SI_ASN_CodingContext * context, uint16_t length);
void __si_asn_print_bit_info( SI_ASN_CodingContext * context);
void __si_asn_print_bit_info2( char * key, SI_ASN_CodingContext * context);
void __si_asn_log_bits( char * key, SI_ASN_CodingContext * codingContext, int iVal, int startBufPos, int bitStartPos, int count);
int __si_asn_getRequiredBitCount( int value);

void __si_asn_dump_integer( char * name, uint8_t * buffer, int len, unsigned long long int lb, unsigned long long int ub, unsigned long long int data);
void __si_asn_dump_string( char * name, uint8_t * buffer, int len, unsigned long lb, unsigned long ub );
void __si_asn_dump_bitstring( char * name, uint8_t * buffer, int len, unsigned long lb, unsigned long ub );
void __si_asn_dump_choice( char * name, uint8_t * buffer, int len);
void __si_asn_dump_item( char * name, uint8_t * buffer, int len);

void __si_asn_log_buffer_range( SI_ASN_CodingContext * context, int bpos, int epos);


void __si_setBit( uint8_t * u8, uint8_t bitIndex);
void __si_clearBit( uint8_t * u8, uint8_t bitIndex);
uint8_t __si_isSet( uint8_t u8, uint8_t bitIndex);

int __si_asn_set_value_length( unsigned short n, uint8_t * buffer, int * len, int bitPos, SI_ASN_CodingContext * codingContext);
int __si_asn_get_value_length( unsigned short * n, uint8_t * buffer, int * len, int bitPos);
int __si_asn_set_value_range( unsigned long long int valueRange, unsigned long long int value, uint8_t * buffer, int * len, int bitPos, int addBits, SI_ASN_CodingContext * codingContext);
int __si_asn_set_range_bits_and_value( unsigned long long int valueRange, unsigned long long int value, SI_ASN_CodingContext * codingContext);
int __si_asn_get_range_bits_and_value( unsigned long long int valueRange, unsigned long long int * value, SI_ASN_CodingContext * codingContext);
int __si_asn_get_value_range( unsigned long long int valueRange, unsigned long long int * value, uint8_t * buffer, int * len, int bitPos);

void __si_asn_log_buffer( char *key , uint8_t * buffer, int len, const char * function, int line);
void __si_asn_print_buffer_bits( uint8_t * buffer, int len, int lineBreakPerByte);
void __si_asn_print_buffer_bits2( char * key, uint8_t * data, int len, int bufferIndex, const char * function, int line);
void __si_asn_log_buffer_bits( char * key, uint8_t * data, int len, int bufferIndex, const char * function, int line);

void __si_asn_convert_uint16_to_buffer( uint16_t length, uint8_t * outdata);

uint8_t __si_asn_get_pduMessageChoice( uint8_t u8);

/*
typedef enum criticality_enum
{
	criticality_enum__reject,
	criticality_enum__ignore, 
	criticality_enum__notify 	
} criticality_enum_t;
*/

#define 		criticality_enum__reject			0x00;
#define 		criticality_enum__ignore			0x40;
#define 		criticality_enum__notify			0x64;


typedef struct __si_OctetString 
{
	unsigned char * data;
	unsigned int length;	
} SI_OctetString;

typedef struct __si_BitString 
{
	unsigned char * data;
	unsigned int length;	
} SI_BitString;



void __getTestBITSTRING( SI_BitString * octetString, unsigned long min, unsigned long max);
void __getTestOCTETSTRING( SI_OctetString * octetString, unsigned long min, unsigned long max);
unsigned long __getTestINTEGER( unsigned long  min , unsigned long long int max);


int __si_asn_add_id_criticality( uint16_t id, uint8_t criticality, uint8_t * buffer, int * len);
int __si_asn_add_id_and_criticality( uint16_t id, uint8_t criticality, SI_ASN_CodingContext * codingContext);

void __si_mme_add_ProtocolIEsID( unsigned short id, uint8_t * buffer, int * len);

/*
	lengthType = 0 - no length
				 1 - fixed
				 2 - range
				 
	min = 0 if no length specified
			value of fixed if lengthType=1
			value of min if lengthType=2
			
	max = 0 if no length specified	
		  0 if lengthType=1
			value of man if lengthType=3	
*/

int __si_asn_AddOctetString( unsigned char * data, unsigned int datalen, int lengthType, int min, int max, int hasExt, uint8_t * buffer, int * len, SI_ASN_CodingContext * codingContext);
int __si_asn_AddOctetString2( unsigned char * data, unsigned int datalen, int lengthType, int min, int max, int hasExt, SI_ASN_CodingContext * codingContext, uint8_t isDerived);
int __si_asn_GetOctetString2( unsigned char ** data, unsigned int * datalen, int lengthType, int min, int max, int hasExt, SI_ASN_CodingContext * codingContext, uint8_t isDerived);

int __si_asn_AddBitString( unsigned char * data, unsigned int datalen, int bitslen, int lengthType, int min, int max, int hasExt, uint8_t * buffer, int * len, SI_ASN_CodingContext * codingContext);
int __si_asn_GetBitString( unsigned char ** data, unsigned int * datalen, int * bitslen, int lengthType, int min, int max, int hasExt, uint8_t isExtSet, SI_ASN_CodingContext * codingContext);

int __si_asn_AddPrintableString( unsigned char * data, unsigned int datalen, int lengthType, int min, int max, int hasExt, uint8_t * buffer, int * len, SI_ASN_CodingContext * codingContext);
int __si_asn_GetPrintableString( unsigned char ** data, unsigned int * datalen, int lengthType, int min, int max, int hasExt, SI_ASN_CodingContext * codingContext);

int __si_asn_AddChoice( int hasExt, uint8_t selectedChoice, int nonExtElemCount, int extElemCount, int isExtensionSelected, uint8_t * buffer, int * len, SI_ASN_CodingContext * codingContext);
int __si_asn_GetChoice( int hasExt, uint8_t * selectedChoice, int nonExtElemCount, int isExtensionSelected, int * isSet, SI_ASN_CodingContext * codingContext);

int __si_asn_AddEnum( uint8_t enumVal, uint8_t hasExt, uint8_t isExtSelected, uint8_t nonExtEnumCount, uint8_t extEnumCount, uint8_t * buffer, int * len, SI_ASN_CodingContext * codingContext);
int __si_asn_GetEnum( uint8_t * enumVal, uint8_t hasExt, uint8_t isExtSet, uint8_t nonExtEnumCount, int * isSet, SI_ASN_CodingContext * codingContext);

int __si_asn_AddConstrainedInteger( unsigned long long int data, int isExt, unsigned long long int lb, unsigned long long int ub, int hasExt, uint8_t * buffer, int * len, SI_ASN_CodingContext * codingContext);

int __si_asn_GetConstrainedInteger( unsigned long long int * data, int * isSet, unsigned long long int lb, unsigned long long int ub, int hasExt, SI_ASN_CodingContext * codingContext);

int __si_asn_GetSIListCount( SI_LinkedList * siList);

void * __si_asn_GetItemFromSIList( SI_LinkedList * siList, int index);

void __si_asn_set_encoded_length( uint8_t * buffer, uint16_t len, uint16_t pos, int * enclen);

int __si_asn_listitem_count( int itemCount, int maxItems, uint8_t * buffer, int * len, int lvl, SI_ASN_CodingContext * codingContext);
int __si_asn_listitem_count2( int itemCount, int minItems, int maxItems, int lvl, SI_ASN_CodingContext * codingContext);

void __si_asn_debug_enum( char * key, char * ieName, uint8_t data, int lvl, char * file, const char * function, int lineNo);
void __si_asn_debug_choice( char * key, char * ieName, uint8_t data, int lvl, char * file, const char * function, int lineNo);
void __si_asn_debug_string( char * key, char * ieName, uint8_t * data, unsigned int len, int lvl, char * file, const char * function, int lineNo);
void __si_asn_debug_printablestring( char * key, char * ieName, uint8_t * data, unsigned int len, int lvl, char * file, const char * function, int lineNo);
void __si_asn_debug_bitstring( char * key, char * ieName, uint8_t * data, unsigned int len, int bitslen, int lvl, char * file, const char * function, int lineNo);
void __si_asn_debug_integer( char * key, char * ieName, unsigned long long int data, int lvl, char * file, const char * function, int lineNo);

void __si_asn_alloc_n_copy( unsigned char ** data, char * srcData, int length);
void __si_asn_dump_string2( char * name, uint8_t * buffer, int len, unsigned long lb, unsigned long ub );

#endif