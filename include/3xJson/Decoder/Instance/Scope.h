/**
 * Ruka Raposa Project by Ruka Raposa Team & Contribuitors.
 * Project is under GPL3-license, read LICENSE.md on the root.
 */

#ifndef XJDecoderInstanceScope_h
#define XJDecoderInstanceScope_h

#include "3xJson/Decoder/Instance.h"

void
XJ_DecoderInstancePushCurrentScope(
    XJ_DecoderInstance* instance
);

void
XJ_DecoderInstancePopCurrentScope(
    XJ_DecoderInstance* instance
);

#endif