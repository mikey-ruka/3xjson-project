/**
 * Ruka Raposa Project by Ruka Raposa Team & Contribuitors.
 * Project is under GPL3-license, read LICENSE.md on the root.
 */

#include "3xJson/Decoder/Tokenizer/Rewind.h"

#include "3xJson/Decoder/Tokenizer.h"
#include "3xJson/Redirects.h"

void
XJ_DecoderTokenizerRewind(
    XJ_DecoderTokenizer* tokenizer,
    const XJ_U8 amount
)
{
    XJ_Size cp = NK_ReaderGetPosition(tokenizer->source);
    NK_ReaderSetPosition(
        tokenizer->source,
        (
            amount > cp
            ? 0
            : cp - amount
        )
    );
}