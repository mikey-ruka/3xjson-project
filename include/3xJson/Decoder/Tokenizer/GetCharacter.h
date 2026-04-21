/**
 * Ruka Raposa Project by Ruka Raposa Team & Contribuitors.
 * Project is under GPL3-license, read LICENSE.md on the root.
 */
#ifndef XJDecoderTokenizerGetCharacter_h
#define XJDecoderTokenizerGetCharacter_h

#include "3xJson/Decoder/Tokenizer.h"

/**
 * @brief This returns an character (and automatically should increment the
 * line counter in case it has reached the max).
 */
const XJ_S32
XJ_DecoderTokenizerGetCharacter(
    XJ_DecoderTokenizer* tokenizer
);

#endif