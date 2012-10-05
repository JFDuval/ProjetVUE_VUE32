#include "VUE32_Utils.h"



LP_PARAMS g_sLpParams[MAX_NBR_LG_PLG];
unsigned int g_unLpSize = 0;


void ActiveLongPolling(LP_PARAMS &sParams)
{
    if ( g_unLpSize == MAX_NBR_LG_PLG)
        return;
    //TODO Make the ressource id doesn't exist already in the static array
    g_sLpParams[g_unLpSize++] = sParams;
}