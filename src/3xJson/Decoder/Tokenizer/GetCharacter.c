/**
 * Ruka Raposa Project by Ruka Raposa Team & Contribuitors.
 * Project is under GPL3-license, read LICENSE.md on the root.
 */
#include "3xJson/Decoder/Tokenizer/GetCharacter.h"

#include "3xJson/Decoder/Tokenizer.h"
#include "3xJson/Redirects.h"

const XJ_S32
XJ_DecoderTokenizerGetCharacter(
    XJ_DecoderTokenizer* tokenizer
)
{
    XJ_S32 cc = NK_ReaderGetCharacter(tokenizer->source);
    XJ_U64 cp = NK_ReaderGetPosition(tokenizer->source);
    if((cc == '\n') && (tokenizer->max_buffer_position > cp))
    {
        tokenizer->line_counter++;
        tokenizer->max_buffer_position = cp;
    }
    return (const XJ_S32)(cc);
}