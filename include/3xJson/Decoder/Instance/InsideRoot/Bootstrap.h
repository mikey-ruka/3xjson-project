/**
 * Ruka Raposa Project by Ruka Raposa Team & Contribuitors.
 * Project is under GPL3-license, read LICENSE.md on the root.
 */
#ifndef XJDecoderInstanceInsideRootBootstrap_h
#define XJDecoderInstanceInsideRootBootstrap_h

#include "3xJson/Decoder/Instance.h"

/**
 * @brief This sets the `bootstrap` for the `XJ_DecoderInstanceInsideRoot` mode
 * process. The `bootstrap` should check what exactly we are returning because:
 *  > 0 -> valid, we just have an XJ_Value(integer: 0)
 *  > {} -> valid, we just have an XJ_Value(table: {})
 */
void
XJ_DecoderInstanceInsideRootBootstrap(
    XJ_DecoderInstance* instance
);

#endif