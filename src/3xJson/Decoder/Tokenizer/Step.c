/**
 * Ruka Raposa Project by Ruka Raposa Team & Contribuitors.
 * Project is under GPL3-license, read LICENSE.md on the root.
 */
#include "3xJson/Decoder/Tokenizer.h"
#include "3xJson/Decoder/Tokenizer/ResetState.h"
#include "3xJson/Decoder/Tokenizer/GetCharacter.h"
#include "3xJson/Decoder/Tokenizer/EatString.h"
#include "3xJson/Decoder/Tokenizer/EatToken.h"

#include "3xJson/Redirects.h"

XJ_Result
XJ_DecoderTokenizerStep(
    XJ_DecoderTokenizer* tokenizer
)
{
    /** Reset the machine: */
    XJ_DecoderTokenizerResetState(tokenizer);
    
    /** Clean the buffer: */
    NK_DynamicStringClear(&tokenizer->token);

    /** CC = Current Character; */
    XJ_S32 cc = 0;
    XJ_Result good = true;

    cc = XJ_DecoderTokenizerGetCharacter(tokenizer);
    while(
        (cc == ' ')     ||
        (cc == '\t')    ||
        (cc == '\r')    ||
        (cc == '\n')
    )
    {
        cc = XJ_DecoderTokenizerGetCharacter(tokenizer);
    }

    switch(cc)
    {
        /** EOF (or buffer ending): */
        case -1:
            /** In this case, there is nothing to parse anymore. */
            good = false;
            break;
        /** String: */
        case '\'':
        case '"':
            good = XJ_DecoderTokenizerEatString(tokenizer, cc);
            break;
        /** Special Tokens: */
        case ':':
        case '{':
        case '}':
        case '[':
        case ']':
            tokenizer->special_token_handler = (NK_U8)(cc);
            tokenizer->state_register_bits.special_token = true;
            break;
        /** Anything else: */
        default:
            good = XJ_DecoderTokenizerEatToken(tokenizer, cc);
            break;
    };

    return good;
}
