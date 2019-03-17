/*
 * Generated by asn1c-0.9.24 (http://lionet.info/asn1c)
 * From ASN.1 module "DSRC"
 * 	found in "C-ITS.ASN"
 */

#ifndef	_Link_H_
#define	_Link_H_


#include <asn_application.h>

/* Including external dependencies */
#include "DescriptiveName.h"
#include "NodeReferenceID.h"
#include "LaneWidth.h"
#include "LaneList.h"
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Forward declarations */
struct PositionOffsetLLV;
struct SpeedLimitList;

/* Link */
typedef struct Link {
	DescriptiveName_t	*name	/* OPTIONAL */;
	NodeReferenceID_t	 upstreamNodeId;
	struct PositionOffsetLLV	*entryLine	/* OPTIONAL */;
	struct PositionOffsetLLV	*stopLine	/* OPTIONAL */;
	struct SpeedLimitList	*speedLimits	/* OPTIONAL */;
	LaneWidth_t	*laneWidth	/* OPTIONAL */;
	LaneList_t	 lanes;
	/*
	 * This type is extensible,
	 * possible extensions are below.
	 */
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} Link_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_Link;

#ifdef __cplusplus
}
#endif

/* Referred external types */
#include "PositionOffsetLLV.h"
#include "SpeedLimitList.h"

#endif	/* _Link_H_ */
#include <asn_internal.h>
