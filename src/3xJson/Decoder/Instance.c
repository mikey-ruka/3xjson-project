/**
 * Ruka Raposa Project by Ruka Raposa Team & Contribuitors.
 * Project is under GPL3-license, read LICENSE.md on the root.
 */

#include "3xJson/Decoder/Instance.h"
#include "3xJson/Decoder/Tokenizer.h"
#include "3xJson/Redirects.h"
#include "3xJson/Enums.h"

XJ_DecoderInstance*
XJ_DecoderInstanceNew()
{
    XJ_DecoderInstance* new_instance = 
        (XJ_DecoderInstance*)(
            NK_AllocatorGet(sizeof(XJ_DecoderInstance))
        );
    return new_instance;
}

void
XJ_DecoderInstanceFree(
    XJ_DecoderInstance* instance
)
{
    NK_AllocatorFree(instance);
}

void
XJ_DecoderInstanceConstruct(
    XJ_DecoderInstance* instance,
    NK_Reader* reader
)
{
    XJ_DecoderTokenizerConstruct(&instance->tokenizer, reader);

    /** Construct the stack: */
    NK_VectorConstruct(
        &instance->scope_stack,
        sizeof(XJ_DecoderInstanceScope)
    );
    
    /** We say the machine is on this state: */
    instance->current_scope.action = 0;
    instance->current_scope.inside = XJ_ENUMS_INSTANCE_SCOPE_INSIDE_ROOT;
    instance->state = XJ_ENUMS_INSTANCE_STATE_RUNNING;
}

void
XJ_DecoderInstanceDestruct(
    XJ_DecoderInstance* instance
)
{
    XJ_DecoderTokenizerDestruct(&instance->tokenizer);
    NK_VectorDestruct(&instance->scope_stack);
}
