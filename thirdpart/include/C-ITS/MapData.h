/*
 * Generated by asn1c-0.9.24 (http://lionet.info/asn1c)
 * From ASN.1 module "DSRC"
 * 	found in "C-ITS.ASN"
 */

#ifndef	_MapData_H_
#define	_MapData_H_


#include <asn_application.h>

/* Including external dependencies */
#include "MinuteOfTheYear.h"
#include "MsgCount.h"
#include "NodeList.h"
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* MapData */
typedef struct MapData {
	MinuteOfTheYear_t	*timeStamp	/* OPTIONAL */;
	MsgCount_t	 msgIssueRevision;
	NodeList_t	 nodes;
	/*
	 * This type is extensible,
	 * possible extensions are below.
	 */
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} MapData_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_MapData;

#ifdef __cplusplus
}
#endif

#endif	/* _MapData_H_ */
#include <asn_internal.h>
