/**
 * Ruka Raposa Project by Ruka Raposa Team & Contribuitors.
 * Project is under GPL3-license, read LICENSE.md on the root.
 */

#include "3xJson/Decoder/Instance/InsideList.h"
#include "3xJson/Decoder/Instance/InsideList/Opening.h"
#include "3xJson/Decoder/Instance/InsideList/GetData.h"
#include "3xJson/Decoder/Instance/InsideList/Closure.h"
#include "3xJson/Enums.h"

void
XJ_DecoderInstanceInsideList(
    XJ_DecoderInstance* instance
)
{
    switch(instance->current_scope.action)
    {
        case XJ_ENUMS_INSTANCE_SCOPE_ACTION_LIST_OPENING:
            XJ_DecoderInstanceInsideListOpening(instance);
            break;
        case XJ_ENUMS_INSTANCE_SCOPE_ACTION_LIST_GET_DATA:
            XJ_DecoderInstanceInsideListGetData(instance);
            break;
        case XJ_ENUMS_INSTANCE_SCOPE_ACTION_LIST_CLOSURE:
            XJ_DecoderInstanceInsideListClosure(instance);
            break;
        default:
            {
                NK_Panic(
                    "%s: Invalid action = %d",
                    NK_CURRENT_WHERE,
                    instance->current_scope.action
                );
            };
            break;
    };
}