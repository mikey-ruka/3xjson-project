/**
 * Ruka Raposa Project by Ruka Raposa Team & Contribuitors.
 * Project is under GPL3-license, read LICENSE.md on the root.
 */

#include "3xJson/Decoder/Instance/InsideTable/Opening.h"
#include "3xJson/Decoder/Instance/Scope.h"
#include "3xJson/Enums.h"

/**
 * @brief This steps the inside table options.
 */
void
XJ_DecoderInstanceInsideTableOpening(
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
            case '}':
                /** Early closure! */
                printf("%s: Got an early closure?\n", NK_CURRENT_WHERE);
                XJ_DecoderInstancePopCurrentScope(instance);
                break;
            default:
                /** Invalid: */
                {
                    NK_Panic(
                        "%s: Invalid token  = %c",
                        NK_CURRENT_WHERE,
                        instance->tokenizer.special_token_handler
                    );
                };
                break;
        };
    }
    else if(
        instance->tokenizer.state_register_bits.string
    )
    {
        /** MOVE: */
        NK_SubmergedStringSetImmediate(
            &instance->current_scope.current_key,
            NK_DynamicStringGetBuffer(&instance->tokenizer.token)
        );
        instance->current_scope.action = 
            XJ_ENUMS_INSTANCE_SCOPE_ACTION_TABLE_CONFIRM_ASSIGNMENT;
    }
    else
    {
        NK_Panic(
            "%s: Invalid token = %s\n",
            NK_CURRENT_WHERE,
            NK_DynamicStringGetBuffer(&instance->tokenizer.token)
        );
    }
}