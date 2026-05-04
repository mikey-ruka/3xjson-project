/**
 * Ruka Raposa Project by Ruka Raposa Team & Contribuitors.
 * Project is under GPL3-license, read LICENSE.md on the root.
 */

#include "3xJson/Decoder/Instance/InsideRoot/Bootstrap.h"
#include "3xJson/Decoder/Instance/GetValue.h"
#include "3xJson/Enums.h"

void
XJ_DecoderInstanceInsideRootClosure(
    XJ_DecoderInstance* instance
)
{
    /**
     * In this case, we save the `XJ_Value` on the dump, doing an reference
     * switch.
     */
    instance->result = instance->current_scope.value;
    instance->state = XJ_ENUMS_INSTANCE_STATE_FINISHED;
}