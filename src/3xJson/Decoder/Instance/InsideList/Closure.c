/**
 * Ruka Raposa Project by Ruka Raposa Team & Contribuitors.
 * Project is under GPL3-license, read LICENSE.md on the root.
 */

#include "3xJson/Decoder/Instance/InsideList/Closure.h"
#include "3xJson/Decoder/Instance/Scope.h"
#include "3xJson/Enums.h"

void
XJ_DecoderInstanceInsideListClosure(
    XJ_DecoderInstance* instance
)
{
    XJ_DecoderTokenizerStep(&instance->tokenizer);
    if(
        instance->tokenizer.state_register_bits.special_token
    )
    {
        switch(instance->tokenizer.special_token_handler)
        {
            case ',':
                instance->current_scope.action =
                    XJ_ENUMS_INSTANCE_SCOPE_ACTION_LIST_GET_DATA;
                break;
            case ']':
                XJ_DecoderInstancePopCurrentScope(instance);
                break;
            default:
                {
                    NK_Panic(
                        "%s: Untreated error [EXPECTED , or ], got %c]",
                        NK_CURRENT_WHERE,
                        instance->tokenizer.special_token_handler
                    );
                };
                break;
        };
    }
    else
    {
        NK_Panic(
            "%s: Untreated error [EXPECTED ', 'or ']', got %s]",
            NK_CURRENT_WHERE,
            NK_DynamicStringGetBuffer(&instance->tokenizer.token)
        );
    }
}
