#ifndef _MT_IMAGE_H_
#define _MT_IMAGE_H_

#ifdef __cplusplus
extern   "C" {
#endif

///////////////////////////////////////////////////////////////////////////////
// Text Resource ID
///////////////////////////////////////////////////////////////////////////////

#define MACRO_MDU_TYPE  MACRO_MDU_IMAGE
#undef RES_ADD_RING
#define RES_ADD_RING(RING_ID,ring_path)
#include "macro_mdu_def.h"
#include "mmi_module.h"
#include "sci_types.h"

typedef enum MT_MMI_IMG_ID_E
{
	MT_IMG_NULL = MMI_MODULE_MT << 16 | MMI_SYS_RES_FLAG,
#include "magic_tower_mdu_def.h"
	MT_IMG_MAX
} MT_MMI_IMG_ID_E;

#undef RES_ADD_RING
#undef MACRO_MDU_TYPE

#ifdef __cplusplus
}
#endif

#endif
