
#ifndef _MT_RING_H__
#define _MT_RING_H__

#include "sci_types.h"
#include "mmiaudio.h"
#include "mmi_module.h"

#ifdef __cplusplus
extern   "C" {
#endif

//ring_id

#define MACRO_RES_PRJ_TYPE      MACRO_RES_PRJ_RING
#include "macro_res_prj_def.h"

#undef RES_ADD_STRING
#define RES_ADD_STRING(TXT_ID, DEFAULT_STRING) 

typedef enum _ANGRYMONKEY_RING_ID_E
{
	MT_RING_NULL = (MMI_MODULE_MT << 16) | MMI_SYS_RES_FLAG,
#include "magic_tower_mdu_def.h"
	MT_RING_MAX_ID
} MT_RING_ID_E;

#undef RES_ADD_RING              
#define RES_ADD_RING(RING_ID,ring_path)             

#undef MACRO_RES_PRJ_TYPE

#ifdef __cplusplus
}
#endif

#endif // _ANGRYMONKEY_RING_H__

