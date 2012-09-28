

#include "VUE32_Impl.h"

// Prototypes
void InitVUE32_0(void);
void InitVUE32_1(void);
void InitVUE32_2(void);
void InitVUE32_3(void);
void InitVUE32_4(void);
void InitVUE32_5(void);
void InitVUE32_6(void);
void InitVUE32_7(void);
void ImplVUE32_0(void);
void ImplVUE32_1(void);
void ImplVUE32_2(void);
void ImplVUE32_3(void);
void ImplVUE32_4(void);
void ImplVUE32_5(void);
void ImplVUE32_6(void);
void ImplVUE32_7(void);
void OnMsgVUE32_0(NETV_MESSAGE *msg);
void OnMsgVUE32_1(NETV_MESSAGE *msg);
void OnMsgVUE32_2(NETV_MESSAGE *msg);
void OnMsgVUE32_3(NETV_MESSAGE *msg);
void OnMsgVUE32_4(NETV_MESSAGE *msg);
void OnMsgVUE32_5(NETV_MESSAGE *msg);
void OnMsgVUE32_6(NETV_MESSAGE *msg);
void OnMsgVUE32_7(NETV_MESSAGE *msg);

// Arrays of function pointers for each implementation
FUNC_INIT gInitFunc[NB_VUE32+1] = {
    ImplVUE32_0,
    InitVUE32_1,
    InitVUE32_2,
    InitVUE32_3,
    InitVUE32_4,
    InitVUE32_5,
    InitVUE32_6,
    InitVUE32_7,
};

FUNC_IMPL gImplFunc[NB_VUE32+1] = {
    ImplVUE32_0,
    ImplVUE32_1,
    ImplVUE32_2,
    ImplVUE32_3,
    ImplVUE32_4,
    ImplVUE32_5,
    ImplVUE32_6,
    ImplVUE32_7,
};

FUNC_ONMSG gOnMsgFunc[NB_VUE32+1] = {
    OnMsgVUE32_0,
    OnMsgVUE32_1,
    OnMsgVUE32_2,
    OnMsgVUE32_3,
    OnMsgVUE32_4,
    OnMsgVUE32_5,
    OnMsgVUE32_6,
    OnMsgVUE32_7,
};
