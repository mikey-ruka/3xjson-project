/**
 * Ruka Raposa Project by Ruka Raposa Team & Contribuitors.
 * Project is under GPL3-license, read LICENSE.md on the root.
 */

#include "3xJson/Decoder/Instance/Scope.h"
#include "3xJson/Enums.h"

void
XJ_DecoderInstancePushCurrentScope(
    XJ_DecoderInstance* instance
)
{
    /** NOTE: We save on the stack the current scope: */
    NK_VectorPush(
        &instance->scope_stack,
        (void*)(&instance->current_scope)
    );
}

void
XJ_DecoderInstancePopCurrentScope(
    XJ_DecoderInstance* instance
)
{
    /** 
     * NOTE: When removing from the stack, we need to carry for the orphaned
     * `XJ_Value`, since you are destroying the current `XJ_Value` we were 
     * actually constructing.
     */
    XJ_Value orphaned_value = instance->current_scope.value;
    printf("%s: me is = %d\n", NK_CURRENT_WHERE, orphaned_value.type);

    NK_VectorPop(&instance->scope_stack, (void*)(&instance->current_scope));
    
    /** How can we take care of this orphan? */
    switch(instance->current_scope.inside)
    {
        case XJ_ENUMS_INSTANCE_SCOPE_INSIDE_ROOT:
            {
                instance->current_scope.value = orphaned_value;
            };
            break;
        case XJ_ENUMS_INSTANCE_SCOPE_INSIDE_LIST:
            {
                NK_VectorPush(
                    instance->current_scope.value.data.list,
                    (const void*)(&orphaned_value)
                );
            };
            break;
        case XJ_ENUMS_INSTANCE_SCOPE_INSIDE_TABLE:
            {
                NK_MapInsert(
                    instance->current_scope.value.data.table,
                    NK_SubmergedStringGet(&instance->current_scope.current_key),
                    (void*)(&orphaned_value)
                );
            };
            break;
        default:
            {
                NK_Panic(
                    "%s: Invalid mode = %d",
                    NK_CURRENT_WHERE,
                    instance->current_scope.inside 
                );
            };
            break;
    }
}