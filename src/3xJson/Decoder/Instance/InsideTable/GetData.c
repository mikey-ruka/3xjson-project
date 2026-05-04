/**
 * Ruka Raposa Project by Ruka Raposa Team & Contribuitors.
 * Project is under GPL3-license, read LICENSE.md on the root.
 */

#include "3xJson/Decoder/Instance/InsideTable/GetData.h"
#include "3xJson/Decoder/Instance/GetValue.h"
#include "3xJson/Decoder/Instance/Scope.h"
#include "3xJson/Enums.h"

/**
 * @brief This steps the inside table options.
 */
void
XJ_DecoderInstanceInsideTableGetData(
    XJ_DecoderInstance* instance
)
{
    XJ_Value maybe_value;
    XJ_DecoderTokenizerStep(&instance->tokenizer);
    maybe_value =  
        XJ_DecoderInstanceGetValue(
            instance,
            XJ_ENUMS_INSTANCE_SCOPE_ACTION_TABLE_CLOSURE
        );
    switch(maybe_value.type)
    {
        case XJ_ENUMS_VALUE_TYPE_NOTHING:
        case XJ_ENUMS_VALUE_TYPE_INTEGER:
        case XJ_ENUMS_VALUE_TYPE_DECIMAL:
        case XJ_ENUMS_VALUE_TYPE_BOOLEAN:
        case XJ_ENUMS_VALUE_TYPE_STRING:
            {
                NK_MapInsert(
                    instance->current_scope.value.data.table,
                    NK_SubmergedStringGet(&instance->current_scope.current_key),
                    (void*)(&maybe_value)
                );
            };
            break;
        default:
            /** Anything else, we don't touch. */
            break;
    }
}