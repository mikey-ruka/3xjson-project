/**
 * Ruka Raposa Project by Ruka Raposa Team & Contribuitors.
 * Project is under GPL3-license, read LICENSE.md on the root.
 */
#include "3xJson/Decoder/Tokenizer/EatToken.h"

#include "3xJson/Decoder/Tokenizer.h"
#include "3xJson/Decoder/Tokenizer/GetCharacter.h"
#include "3xJson/Decoder/Tokenizer/Rewind.h"
#include "3xJson/Redirects.h"

/**
 * TODO: Implement e+, e- notation.
 */

const XJ_Result
XJ_DecoderTokenizerEatToken(
    XJ_DecoderTokenizer* tokenizer,
    const XJ_S32 entrypoint
)
{
    XJ_Result good = true;
    XJ_S32 cc = entrypoint;
    XJ_Size cc_counter = 0;
    XJ_S8 number_handler_multiply = 1;

    NK_DynamicStringPush(&tokenizer->token, (XJ_C8)(entrypoint));
    
    /** Set the registers ready. */
    tokenizer->state_register_bits.number = true;
    tokenizer->number_handler = 0;

    /**
     * NOTE: This is a block of code, we use labels because it is more
     * obvious to see what is going on if we do so.
     */
top_position:

    switch(cc)
    {
        case -1:
        case ' ':
        case '\t':
        case '\n':
        case '\r':
            /** Don't jump anywhere. */
            goto useless_token_ending;
        /**
         * TODO: On the the future, implement token dropping on the state of the
         * tokenizer, this will rewind the buffer for the next
         * `XJ_DecoderTokenizerStep` and it might cost additional time of
         * processing (we need to be rewinding all the time), once the v.1 is
         * released, this can be easily optimized by cached parameters.
         */
        case '\'':
        case '"':
        case '{':
        case '}':
        case '[':
        case ']':
        case ':':
            XJ_DecoderTokenizerRewind(tokenizer, 1);
            goto highlight_token_ending;
        default:
            break;
    };

    /** Did we get an token that is not an string? */
    if(
        (! ((cc >= '0') && (cc <= '9')))
    )
    {
        if(
            (cc == '-') &&
            (cc_counter <= 0)
        )
        {
            number_handler_multiply = -1;
        }
        else if(
            (cc == '.') && 
            (!tokenizer->state_register_bits.decimal)
        )
        {
            tokenizer->state_register_bits.number = false;
            /**
             * TODO: The decimal can be reconstructed by real part and
             * quotient part (but this requires an bit of code), maybe
             * on the future implement an decimal_handler.
             */
            tokenizer->state_register_bits.decimal = true;
        }
        else
        {
            /** If any of them are alive yet: */
            if(
                (tokenizer->state_register_bits.number) |
                (tokenizer->state_register_bits.decimal)
            )
            {
                tokenizer->state_register_bits.number = false;
                tokenizer->state_register_bits.decimal = false;
            }
        }
    }
    else
    {
        /** 
         * `3xJson` is good at numbers, we don't need to transform them later
         * but anything else ...
         */
        if(
            (tokenizer->state_register_bits.number)
        )
        {
            tokenizer->number_handler = 
                (tokenizer->number_handler * 10) +
                (cc - '0');
            printf("GOT: %c\n", cc);
        }
    }

    /**
     * In any of the cases, we push back on the tokenizer.
     */
    NK_DynamicStringPush(&tokenizer->token, cc);

    /**
     * We need to return to the top, we could use a `while`, but that is
     * infering on more nests, using goto here is just like an loop.
     */
    cc = XJ_DecoderTokenizerGetCharacter(tokenizer);
    goto top_position;

useless_token_ending:
highlight_token_ending:

    /**
     * @brief We multiply the handler (even if the code has failed).
     */
    tokenizer->number_handler =
        tokenizer->number_handler * number_handler_multiply;

    return good;
}