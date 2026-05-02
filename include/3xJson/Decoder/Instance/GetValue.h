/**
 * Ruka Raposa Project by Ruka Raposa Team & Contribuitors.
 * Project is under GPL3-license, read LICENSE.md on the root.
 */
#ifndef XJDecoderInstanceGetValue_h
#define XJDecoderInstanceGetValue_h

#include "3xJson/Decoder/Instance.h"

/**
 * @brief This will return the value to be adquired.
 * 
 * @warning You need to call `XJ_DecoderTokenizerStep()` to get the next token
 * because `GetValue` will use whatever is present on the `instance->tokenizer`
 * this is done to avoid unalignment problems.
 */
XJ_Value
XJ_DecoderInstanceGetValue(
    XJ_DecoderInstance* instance,
    XJ_U8 next_action
);

#endif