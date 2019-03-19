
#ifndef _MT_TEXT_H_
#define _MT_TEXT_H_

#ifdef __cplusplus
extern   "C" {
#endif

///////////////////////////////////////////////////////////////////////////////
// Text Resource ID
///////////////////////////////////////////////////////////////////////////////

#define MACRO_MDU_TYPE  MACRO_MDU_TEXT
#define RES_ADD_RING(RING_ID,ring_path)
#include "macro_mdu_def.h"
#include "mmi_module.h"
typedef enum MT_MMI_TEXT_ID_E
{
	MT_TXT_NULL = MMI_MODULE_MT << 16 | MMI_SYS_RES_FLAG,
#include "magic_tower_mdu_def.h"
	MT_TXT_MAX
} MT_MMI_TEXT_ID_E;

#undef RES_ADD_RING
#undef MACRO_MDU_TYPE

#ifdef __cplusplus
}
#endif

#endif
