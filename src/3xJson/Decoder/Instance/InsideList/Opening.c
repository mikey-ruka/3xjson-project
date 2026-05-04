/**
 * Ruka Raposa Project by Ruka Raposa Team & Contribuitors.
 * Project is under GPL3-license, read LICENSE.md on the root.
 */

#include "3xJson/Decoder/Instance/InsideList/Opening.h"
#include "3xJson/Decoder/Instance/Scope.h"
#include "3xJson/Decoder/Instance/GetValue.h"
#include "3xJson/Enums.h"

void
XJ_DecoderInstanceInsideListOpening(
    XJ_DecoderInstance* instance
)
{
    XJ_Value maybe_value;
    /**
     * NOTE: Here we handle the [] case.
     */
    XJ_DecoderTokenizerStep(&instance->tokenizer);
    if(
        (instance->tokenizer.state_register_bits.special_token) &&
        (instance->tokenizer.special_token_handler == ']')
    )
    {
        printf("%s: Early closure!\n", NK_CURRENT_WHERE);
        XJ_DecoderInstancePopCurrentScope(instance);
    }
    else
    {
        /** NOTE: Here we get data: */
        maybe_value = XJ_DecoderInstanceGetValue(
            instance,
            XJ_ENUMS_INSTANCE_SCOPE_ACTION_LIST_CLOSURE
        );
        switch(maybe_value.type)
        {
            case XJ_ENUMS_VALUE_TYPE_NOTHING:
            case XJ_ENUMS_VALUE_TYPE_INTEGER:
            case XJ_ENUMS_VALUE_TYPE_DECIMAL:
            case XJ_ENUMS_VALUE_TYPE_BOOLEAN:
            case XJ_ENUMS_VALUE_TYPE_STRING:
                {
                    NK_VectorPush(
                        instance->current_scope.value.data.list,
                        (const void*)(&maybe_value)
                    );
                };
                break;
            default:
                /** Anything else, we don't touch. */
                break;
        }
    }
}