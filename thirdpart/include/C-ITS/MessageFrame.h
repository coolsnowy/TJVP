/*
 * Generated by asn1c-0.9.24 (http://lionet.info/asn1c)
 * From ASN.1 module "DSRC"
 * 	found in "C-ITS.ASN"
 */

#ifndef	_MessageFrame_H_
#define	_MessageFrame_H_


#include <asn_application.h>

/* Including external dependencies */
#include "DSRCmsgID.h"
#include <ANY.h>
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* MessageFrame */
typedef struct MessageFrame {
	DSRCmsgID_t	 messageId;
	ANY_t	 value;
	/*
	 * This type is extensible,
	 * possible extensions are below.
	 */
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} MessageFrame_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_MessageFrame;

#ifdef __cplusplus
}
#endif

#endif	/* _MessageFrame_H_ */
#include <asn_internal.h>