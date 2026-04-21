/**
 * Ruka Raposa Project by Ruka Raposa Team & Contribuitors.
 * Project is under GPL3-license, read LICENSE.md on the root.
 */
#ifndef XJDecoderTokenizerRewind_h
#define XJDecoderTokenizerRewind_h

#include "3xJson/Decoder/Tokenizer.h"

/**
 * @brief Consume the token until it is good.
 */
void
XJ_DecoderTokenizerRewind(
    XJ_DecoderTokenizer* tokenizer,
    const XJ_U8 amount
);

#endif