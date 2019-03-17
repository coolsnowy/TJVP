/*
 * Generated by asn1c-0.9.24 (http://lionet.info/asn1c)
 * From ASN.1 module "DSRC"
 * 	found in "C-ITS.ASN"
 */

#ifndef	_PointList_H_
#define	_PointList_H_


#include <asn_application.h>

/* Including external dependencies */
#include <asn_SEQUENCE_OF.h>
#include <constr_SEQUENCE_OF.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Forward declarations */
struct RoadPoint;

/* PointList */
typedef struct PointList {
	A_SEQUENCE_OF(struct RoadPoint) list;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} PointList_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_PointList;

#ifdef __cplusplus
}
#endif

/* Referred external types */
#include "RoadPoint.h"

#endif	/* _PointList_H_ */
#include <asn_internal.h>
