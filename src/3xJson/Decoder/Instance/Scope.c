/**
 * Ruka Raposa Project by Ruka Raposa Team & Contribuitors.
 * Project is under GPL3-license, read LICENSE.md on the root.
 */

#include "3xJson/Decoder/Instance/Scope.h"

void
XJ_DecoderInstancePushCurrentScope(
    XJ_DecoderInstance* instance
)
{
    /** NOTE: We save on the stack the current scope: */
    NK_VectorPush(
        &instance->scope_stack,
        (void*)(&instance->current_scope)
    );
}

void
XJ_DecoderInstancePopCurrentScope(
    XJ_DecoderInstance* instance
)
{
    /** 
     * NOTE: When removing from the stack, we need to carry for the orphaned
     * `XJ_Value`, since you are destroying the current `XJ_Value` we were 
     * actually constructing.
     */
    
}