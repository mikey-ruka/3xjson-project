/**
 * Ruka Raposa Project by Ruka Raposa Team & Contribuitors.
 * Project is under GPL3-license, read LICENSE.md on the root.
 */
#ifndef XJDecoderTokenizerEatString_h
#define XJDecoderTokenizerEatString_h

#include "3xJson/Decoder/Tokenizer.h"

/**
 * @brief This function will run on the whole buffer and eat the string token.
 */
const XJ_Result
XJ_DecoderTokenizerEatString(
    XJ_DecoderTokenizer* tokenizer,
    const NK_S32 entrypoint
);

#endif