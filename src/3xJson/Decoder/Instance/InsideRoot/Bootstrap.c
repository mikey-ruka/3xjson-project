/**
 * Ruka Raposa Project by Ruka Raposa Team & Contribuitors.
 * Project is under GPL3-license, read LICENSE.md on the root.
 */

#include "3xJson/Decoder/Instance/InsideRoot/Bootstrap.h"
#include "3xJson/Decoder/Instance/GetValue.h"
#include "3xJson/Enums.h"

void
XJ_DecoderInstanceInsideRootBootstrap(
    XJ_DecoderInstance* instance
)
{
    XJ_Value current_value;
    XJ_DecoderTokenizerStep(&instance->tokenizer);
    current_value =
        XJ_DecoderInstanceGetValue(
            instance,
            XJ_ENUMS_INSTANCE_SCOPE_ACTION_ROOT_CLOSURE
        );
    /** 
     * NOTE: If the type got wasn't enough to open anything, then the
     * `GetValue()` function didn't open any scope.
     */
    if(
        NK_SUPPORT_UNLIKELY(
            (current_value.type != XJ_ENUMS_VALUE_TYPE_TABLE) ||
            (current_value.type != XJ_ENUMS_VALUE_TYPE_LIST)
        )
    )
    {
        /**
         * NOTE: In this case, we don't do anything, but we need to set that
         * the current value is not this:
         */
        instance->current_scope.value = current_value;
    }
}