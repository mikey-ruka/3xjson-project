/**
 * Ruka Raposa Project by Ruka Raposa Team & Contribuitors.
 * Project is under GPL3-license, read LICENSE.md on the root.
 */

#include "3xJson/Decoder/Instance.h"
#include "3xJson/Decoder/Instance/InsideRoot.h"
#include "3xJson/Decoder/Instance/InsideList.h"
#include "3xJson/Decoder/Instance/InsideTable.h"
#include "3xJson/Enums.h"

NK_U8
XJ_DecoderInstanceStep(
    XJ_DecoderInstance* instance
)
{
    switch(instance->current_scope.inside)
    {
        case XJ_ENUMS_INSTANCE_SCOPE_INSIDE_ROOT:
            {
                XJ_DecoderInstanceInsideRoot(instance);
            };
            break;
        case XJ_ENUMS_INSTANCE_SCOPE_INSIDE_LIST:
            {
                XJ_DecoderInstanceInsideList(instance);
            };
            break;
        case XJ_ENUMS_INSTANCE_SCOPE_INSIDE_TABLE:
            {
                XJ_DecoderInstanceInsideTable(instance);
            };
            break;
        default:
            /**
             * In case we are in the wrong state of mind, then something bad
             * happened on the copying from stack to the memory itself.
             */
            {
                NK_Panic(
                    "%s: invalid inside scope = %d",
                    NK_CURRENT_WHERE,
                    (int)(instance->current_scope.inside)
                );
            };
            break;
    };
}