/* 
 * File:   VUE32_Impl.h
 * Author: bedm2308
 *
 * Created on 24 septembre 2012, 14:34
 */

#ifndef VUE32_IMPL_H
#define	VUE32_IMPL_H

#include "NETV32_Common.h"

// Number of existing VUE32
#define NB_VUE32 7

// Typedefs for the ID-specific function pointers
typedef void (*FUNC_INIT)();
typedef void (*FUNC_IMPL)();
typedef void (*FUNC_ONMSG)(NETV_MESSAGE*);

// Arrays of function pointers for each implementation
extern FUNC_INIT gInitFunc[NB_VUE32+1];
extern FUNC_IMPL gImplFunc[NB_VUE32+1];
extern FUNC_ONMSG gOnMsgFunc[NB_VUE32+1];

#endif	/* VUE32_IMPL_H */

