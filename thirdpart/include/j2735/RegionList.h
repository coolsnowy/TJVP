/*
 * Generated by asn1c-0.9.23 (http://lionet.info/asn1c)
 * From ASN.1 module "DSRC"
 * 	found in "DSRC_R36_Source.ASN"
 * 	`asn1c -S ../../../../tools/asn1c/skeletons -pdu=BasicSafetyMessage -fcompound-names`
 */

#ifndef	_RegionList_H_
#define	_RegionList_H_


#include <asn_application.h>

/* Including external dependencies */
#include <asn_SEQUENCE_OF.h>
#include <constr_SEQUENCE_OF.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Forward declarations */
struct RegionOffsets;

/* RegionList */
typedef struct RegionList {
	A_SEQUENCE_OF(struct RegionOffsets) list;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} RegionList_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_RegionList;

#ifdef __cplusplus
}
#endif

/* Referred external types */
#include "RegionOffsets.h"

#endif	/* _RegionList_H_ */
#include <asn_internal.h>
