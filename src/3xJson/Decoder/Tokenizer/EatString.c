/**
 * Ruka Raposa Project by Ruka Raposa Team & Contribuitors.
 * Project is under GPL3-license, read LICENSE.md on the root.
 */
#include "3xJson/Decoder/Tokenizer/EatString.h"

#include "3xJson/Decoder/Tokenizer.h"
#include "3xJson/Decoder/Tokenizer/GetCharacter.h"
#include "3xJson/Redirects.h"

const XJ_Result
XJ_DecoderTokenizerEatString(
    XJ_DecoderTokenizer* tokenizer,
    const NK_S32 entrypoint
)
{
    XJ_Result good = true;
    XJ_S32 cc;
    NK_DynamicStringPush(&tokenizer->token, (NK_C8)(entrypoint));
    
    /** We need to update the register: */
    tokenizer->state_register_bits.string = true;
top_position:
    cc = XJ_DecoderTokenizerGetCharacter(tokenizer);
    if(cc != -1)
    {
        NK_DynamicStringPush(&tokenizer->token, (NK_C8)(cc));
        if(cc != entrypoint)
        {
            goto top_position;
        }
    }
    else
    { 
        /**
         * NOTE: We don't allow strings to end up with EOF, it means the string
         * has not been closed during the whole execution of the tokenizer.
         */
        good = false;
    }
    return good;
}