/**
 * Ruka Raposa Project by Ruka Raposa Team & Contribuitors.
 * Project is under GPL3-license, read LICENSE.md on the root.
 */
#ifndef XJDecoderTokenizerEatToken_h
#define XJDecoderTokenizerEatToken_h

#include "3xJson/Decoder/Tokenizer.h"

/**
 * @brief Consume the token until it is good.
 */
const XJ_Result
XJ_DecoderTokenizerEatToken(
    XJ_DecoderTokenizer* tokenizer,
    const XJ_S32 entrypoint
);

#endif