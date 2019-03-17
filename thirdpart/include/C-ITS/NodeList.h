/*
 * Generated by asn1c-0.9.24 (http://lionet.info/asn1c)
 * From ASN.1 module "DSRC"
 * 	found in "C-ITS.ASN"
 */

#ifndef	_NodeList_H_
#define	_NodeList_H_


#include <asn_application.h>

/* Including external dependencies */
#include <asn_SEQUENCE_OF.h>
#include <constr_SEQUENCE_OF.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Forward declarations */
struct Node;

/* NodeList */
typedef struct NodeList {
	A_SEQUENCE_OF(struct Node) list;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} NodeList_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_NodeList;

#ifdef __cplusplus
}
#endif

/* Referred external types */
#include "Node.h"

#endif	/* _NodeList_H_ */
#include <asn_internal.h>
