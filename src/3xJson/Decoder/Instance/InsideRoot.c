/**
 * Ruka Raposa Project by Ruka Raposa Team & Contribuitors.
 * Project is under GPL3-license, read LICENSE.md on the root.
 */

#include "3xJson/Decoder/Instance/InsideRoot.h"
#include "3xJson/Enums.h"

#include "3xJson/Decoder/Instance/InsideRoot/Bootstrap.h"
#include "3xJson/Decoder/Instance/InsideRoot/Ending.h"

void
XJ_DecoderInstanceInsideRoot(
    XJ_DecoderInstance* instance
)
{
    switch(instance->current_scope.action)
    {
        case XJ_ENUMS_INSTANCE_SCOPE_ACTION_ROOT_BOOTSTRAP:
            {
                XJ_DecoderInstanceInsideRootBootstrap(instance);     
            };
            break;
        case XJ_ENUMS_INSTANCE_SCOPE_ACTION_ROOT_CLOSURE:
            {
                XJ_DecoderInstanceInsideRootEnding(instance);
            }    
            break;
        default:
            /**
             * In this case, we might have lost the alignment and now we are
             * running rogue, this probably means an severe bug.
             */
            {
                NK_Panic(
                    "%s: invalid action = %d",
                    NK_CURRENT_WHERE,
                    (int)(instance->current_scope.action)
                );
            };
            break;
    }
}