/**
 * Ruka Raposa Project by Ruka Raposa Team & Contribuitors.
 * Project is under GPL3-license, read LICENSE.md on the root.
 */
#include "3xJson/Decoder/Tokenizer/ResetState.h"
#include "3xJson/Redirects.h"

void
XJ_DecoderTokenizerResetState(
    XJ_DecoderTokenizer* tokenizer
)
{
    /** NOTE: This sets everything to the default state for every parsing. */
    tokenizer->state_register = 0;
}