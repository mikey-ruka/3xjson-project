/**
 * Ruka Raposa Project by Ruka Raposa Team & Contribuitors.
 * Project is under GPL3-license, read LICENSE.md on the root.
 */

#include "3xJson/Decoder/Instance/InsideTable/ConfirmAssignment.h"
#include "3xJson/Decoder/Instance/Scope.h"
#include "3xJson/Enums.h"

/**
 * @brief This steps the inside table options.
 */
void
XJ_DecoderInstanceInsideTableConfirmAssignment(
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
            case ':':
                instance->current_scope.action =
                    XJ_ENUMS_INSTANCE_SCOPE_ACTION_TABLE_GET_DATA;
                break;
            default:
                {
                    NK_Panic(
                        "%s: Invalid token = %c\n",
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
            "%s: Invalid token = %s\n",
            NK_CURRENT_WHERE,
            NK_DynamicStringGetBuffer(&instance->tokenizer.token)
        );
    }
}