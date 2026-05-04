/**
 * Ruka Raposa Project by Ruka Raposa Team & Contribuitors.
 * Project is under GPL3-license, read LICENSE.md on the root.
 */

#include "3xJson/Decoder/Instance/GetValue.h"
#include "3xJson/Decoder/Instance/Scope.h"
#include "3xJson/Enums.h"

/** TODO: implement an more fancy way to parse this :| */
#include <stdlib.h>

static
void
P_XJ_DecoderInstanceGetValueEnterTable(
    XJ_DecoderInstance* instance
)
{
    /** Open the table here: */
    XJ_DecoderInstancePushCurrentScope(instance);
    instance->current_scope.action = 
        XJ_ENUMS_INSTANCE_SCOPE_ACTION_TABLE_OPENING;
    instance->current_scope.inside =
        XJ_ENUMS_INSTANCE_SCOPE_INSIDE_TABLE;

    /** Set the table: */
    instance->current_scope.value.type = XJ_ENUMS_VALUE_TYPE_TABLE;
    instance->current_scope.value.data.table = NK_MapNew();
    NK_MapConstruct(
        instance->current_scope.value.data.table,
        256,
        sizeof(XJ_Value)
    );
    printf("%s: Constructed Map = %p\n", NK_CURRENT_WHERE, instance->current_scope.value.data.list);
}

static
void
P_XJ_DecoderInstanceGetValueEnterList(
    XJ_DecoderInstance* instance
)
{
    /** We need to save the old scope: */
    XJ_DecoderInstancePushCurrentScope(instance);

    /** We say the list is currently to be open: */
    instance->current_scope.action =
        XJ_ENUMS_INSTANCE_SCOPE_ACTION_LIST_OPENING;
    instance->current_scope.inside = 
        XJ_ENUMS_INSTANCE_SCOPE_INSIDE_LIST;

    /** Adjust the `XJ_Value` to be holding what we need: */
    instance->current_scope.value.type = XJ_ENUMS_VALUE_TYPE_LIST;
    instance->current_scope.value.data.list = NK_VectorNew();
    NK_VectorConstruct(
        instance->current_scope.value.data.list,
        sizeof(XJ_Value)
    );
    printf("%s: Constructed Vector = %p\n", NK_CURRENT_WHERE, instance->current_scope.value.data.list);
}

XJ_Value
XJ_DecoderInstanceGetValue(
    XJ_DecoderInstance* instance,
    XJ_U8 next_action
)
{
    XJ_Value value;
    XJ_U8 first_token;

    /** We need to set on the current scope, the next action: */
    instance->current_scope.action = next_action;

    /** We assume you did already get an token: */
    if(instance->tokenizer.state_register_bits.special_token)
    {
        /** NOTE: in this scenario, we have either '[' or '{' as valid. */
        switch(instance->tokenizer.special_token_handler)
        {
            case '{':
                P_XJ_DecoderInstanceGetValueEnterTable(instance);
                value.type = XJ_ENUMS_VALUE_TYPE_TABLE;
                break;
            case '[':
                P_XJ_DecoderInstanceGetValueEnterList(instance);
                value.type = XJ_ENUMS_VALUE_TYPE_LIST;
                break;
            default:
                {
                    NK_Panic(
                        "%s: Expected special token to be '{' or '[', got = %c",
                        NK_CURRENT_WHERE,
                        instance->tokenizer.special_token_handler
                    );
                };
                break;
        };
    }
    else
    {
        /** begin to parse: */
        if(instance->tokenizer.state_register_bits.number)
        {
            value.type = XJ_ENUMS_VALUE_TYPE_INTEGER;
            value.data.integer = instance->tokenizer.number_handler;
        }
        else if(instance->tokenizer.state_register_bits.decimal)
        {
            /** TODO: implement an more fancy way to parse things here! */
            value.type = XJ_ENUMS_VALUE_TYPE_DECIMAL;
            value.data.decimal = 
                (XJ_NatureDecimal)(
                    atof(
                        NK_DynamicStringGetBuffer(&instance->tokenizer.token)
                    )
                );
        }
        else if(instance->tokenizer.state_register_bits.string)
        {
            value.type = XJ_ENUMS_VALUE_TYPE_STRING;
            NK_SubmergedStringConstruct(
                &value.data.string,
                NK_DynamicStringGetBuffer(
                    &instance->tokenizer.token
                )
            );
        }
        else
        {
            /**
             * NOTE: Can we have the big three? 't', 'f', 'n'?
             * 
             * And no, we don't care if you said 'fals', parsing for correctness
             * is definitely too slow, you can say 'falcon' or 'falso' and the
             * parser wouldn't mind.
             */
            first_token = 
                NK_DynamicStringGet(&instance->tokenizer.token, 0);
            switch(first_token)
            {
                case 't':
                case 'f':
                    /** In this scenario, we have boolean. */
                    value.type = XJ_ENUMS_VALUE_TYPE_BOOLEAN;
                    value.data.boolean = first_token == 't' ? 1 : 0;
                    break;
                case 'n':
                    /** In this scenario, we have NULL */
                    value.type = XJ_ENUMS_NODE_TYPE_NULL;
                    break;
                default:
                    /** BAD, we exausted all the options. */
                    NK_Panic(
                        "%s: Invalid token = %s",
                        NK_CURRENT_WHERE,
                        NK_DynamicStringGetBuffer(&instance->tokenizer.token)
                    );
                    break;
            };
        }
    }
    
    /** Return the value: */
    return value;
}