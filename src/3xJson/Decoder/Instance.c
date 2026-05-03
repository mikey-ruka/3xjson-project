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

static
void
P_XJ_DecoderInstanceDestructPostMortemCleanup(
    XJ_DecoderInstance* instance
)
{
    /**
     * TODO: What we do is go on the stack and clean it, and then clean the
     * residual trash `XJ_Value` that we got inside.
     */
    NK_Panic("Not implemented yet ;-)");
}

void
XJ_DecoderInstanceDestruct(
    XJ_DecoderInstance* instance
)
{
    /**
     * NOTE: We need to clean any mess the builder might have left.
     */
    if(instance->state == XJ_ENUMS_INSTANCE_STATE_DIED)
    {
        /** 
         * TODO: Maybe the compiler will assume this is a INLINE by itself
         * I hope we don't need any hinting here, but on the future, add
         * to `P_XJ_DecoderInstanceDestructPostMortemCleanup` an hint to 
         * inline, maybe: `NK_FUNCTION_HINT_INLINE` ? Who knows.
         */
        P_XJ_DecoderInstanceDestructPostMortemCleanup(
            instance
        );
    }

    /** Continue with the normal destruction: */
    XJ_DecoderTokenizerDestruct(&instance->tokenizer);
    NK_VectorDestruct(&instance->scope_stack);
}

XJ_Value
XJ_DecoderInstanceExtractResult(
    XJ_DecoderInstance* instance
)
{
    /** 
     * TODO: Cause panic when the `->value` was adquired from an inconsistent
     * state, this avoids having invalid readings.
     */

    /**
     * NOTE: We can do this, there is no problem since:
     *  +   The root value is not passed as pointer, but it itself (copy) with
     *      an pointer inside to the next layer.
     */
    return instance->result;
}

NK_U8
XJ_DecoderInstanceGetState(
    XJ_DecoderInstance* instance
)
{
    return instance->state;
}