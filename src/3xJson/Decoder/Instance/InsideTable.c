/**
 * Ruka Raposa Project by Ruka Raposa Team & Contribuitors.
 * Project is under GPL3-license, read LICENSE.md on the root.
 */

#include "3xJson/Decoder/Instance/InsideTable.h"
#include "3xJson/Decoder/Instance/InsideTable/Closure.h"
#include "3xJson/Decoder/Instance/InsideTable/ConfirmAssignment.h"
#include "3xJson/Decoder/Instance/InsideTable/GetData.h"
#include "3xJson/Decoder/Instance/InsideTable/KeyGrab.h"
#include "3xJson/Decoder/Instance/InsideTable/Opening.h"
#include "3xJson/Enums.h"

void
XJ_DecoderInstanceInsideTable(
    XJ_DecoderInstance* instance
)
{
    switch(instance->current_scope.action)
    {
        case XJ_ENUMS_INSTANCE_SCOPE_ACTION_TABLE_OPENING:
            printf("%s: Table Opening\n", NK_CURRENT_WHERE);
            XJ_DecoderInstanceInsideTableOpening(instance);
            break;
        case XJ_ENUMS_INSTANCE_SCOPE_ACTION_TABLE_KEY_GRAB:
            printf("%s: Table Key Grab\n", NK_CURRENT_WHERE);
            XJ_DecoderInstanceInsideTableKeyGrab(instance);
            break;
        case XJ_ENUMS_INSTANCE_SCOPE_ACTION_TABLE_CONFIRM_ASSIGNMENT:
            printf("%s: Table Confirm Assignment\n", NK_CURRENT_WHERE);
            XJ_DecoderInstanceInsideTableConfirmAssignment(instance);
            break;
        case XJ_ENUMS_INSTANCE_SCOPE_ACTION_TABLE_GET_DATA:
            printf("%s: Table Get Data\n", NK_CURRENT_WHERE);
            XJ_DecoderInstanceInsideTableGetData(instance);
            break;
        case XJ_ENUMS_INSTANCE_SCOPE_ACTION_TABLE_CLOSURE:
            printf("%s: Table Closure\n", NK_CURRENT_WHERE);
            XJ_DecoderInstanceInsideTableClosure(instance);
            break;
        default:
            {
                NK_Panic(
                    "%s: Invalid action = %d",
                    NK_CURRENT_WHERE,
                    instance->current_scope.action
                );
            };
            break;
    };
}