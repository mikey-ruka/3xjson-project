/**
 * Ruka Raposa Project by Ruka Raposa Team & Contribuitors.
 * Project is under GPL3-license, read LICENSE.md on the root.
 */
#include "3xJson/Decoder/Tokenizer.h"
#include "3xJson/Redirects.h"

XJ_DecoderTokenizer*
XJ_DecoderTokenizerNew()
{
    XJ_DecoderTokenizer* new_tokenizer =
        (XJ_DecoderTokenizer*)(
            NK_AllocatorGet(sizeof(XJ_DecoderTokenizer))
        );
    return new_tokenizer;
}

void
XJ_DecoderTokenizerFree(
    XJ_DecoderTokenizer* tokenizer
)
{
    NK_AllocatorFree(tokenizer);
}

void
XJ_DecoderTokenizerConstruct(
    XJ_DecoderTokenizer* tokenizer,
    NK_Reader* source
)
{
    NK_DynamicStringConstruct(&tokenizer->token);
    tokenizer->source = source;

    /** The line must start on the 1 (there is no '0' line) */
    tokenizer->line_counter = 1;
    tokenizer->max_buffer_position = 0;

    /** Set the others to null. */
    tokenizer->number_handler = 0;
    tokenizer->special_token_handler = 0;
    tokenizer->state_register = 0;
}

void
XJ_DecoderTokenizerDestruct(
    XJ_DecoderTokenizer* tokenizer
)
{
    NK_DynamicStringDestruct(&tokenizer->token);
    /** Zero everything. */
    NK_RedirectMemset(
        tokenizer,
        0,
        sizeof(XJ_DecoderTokenizer)
    );
}

