/**
 * Ruka Raposa Project by Ruka Raposa Team & Contribuitors.
 * Project is under GPL3-license, read LICENSE.md on the root.
 */

#include "3xJson/Data/Value.h"
#include "3xJson/Redirects.h"
#include "3xJson/Enums.h"

XJ_Value*
XJ_ValueNew()
{
    XJ_Value* new_value =
        (XJ_Value*)(
            NK_AllocatorGet(sizeof(XJ_Value))
        );
    return new_value;
}

void
XJ_ValueFree(
    XJ_Value* value
)
{
    NK_AllocatorFree(value);
}

void
XJ_ValueConstruct(
    XJ_Value* value
)
{
    /**
     * NOTE: This is guaranteed to be safe, since nothing doesn't require any
     * internal freeing.
     */
    value->type = XJ_ENUMS_NODE_TYPE_NULL;
}

static
NK_Result
P_XJ_ValueDestructCleanVectorIterator(
    NK_Vector* vector,
    const NK_Size index,
    XJ_Value* data,
    void* userdata
)
{
    /** Destroy the `XJ_Value` */
    XJ_ValueDestruct(data);
    
    /** Continue to the next one. */
    return true;
}

static
NK_Result
P_XJ_ValueDestructCleanMapIterator(
    NK_Map* map,
    const NK_C8* key,
    const NK_Size index,
    XJ_Value* data,
    void* userdata
)
{
    /** Destroy the `XJ_Value` */
    XJ_ValueDestruct(data);

    /** Continue to the next one. */
    return true;
}

static
void
P_XJ_ValueDestructClean(
    XJ_Value* value
)
{
    switch(value->type)
    {
        case XJ_ENUMS_VALUE_TYPE_NOTHING:
        case XJ_ENUMS_VALUE_TYPE_INTEGER:
        case XJ_ENUMS_VALUE_TYPE_DECIMAL:
        case XJ_ENUMS_VALUE_TYPE_BOOLEAN:
            /** 
             * In this case, the buffer doesn't contain anything special to be
             * deleted.
             */
            return;
        case XJ_ENUMS_VALUE_TYPE_STRING:
            /**
             * In this case, we need to drop the NK_SubmergedString.
             */
            {
                NK_SubmergedStringDestruct(
                    &value->data.string
                );
            };
            return;
        case XJ_ENUMS_VALUE_TYPE_LIST:
            /**
             * In this case, we need to iterate on the NK_Vector.
             */
            {
                NK_VectorIterate(
                    value->data.list,
                    (NK_VectorIteratorFunction)(
                        P_XJ_ValueDestructCleanVectorIterator
                    ),
                    NULL
                );
                NK_VectorDestruct(value->data.list);
                NK_VectorFree(value->data.list);
            };
            return;
        case XJ_ENUMS_VALUE_TYPE_TABLE:
            /**
             * In this case, we need to iterate on the NK_Map.
             */
            {
                NK_MapIterate(
                    value->data.table,
                    (NK_MapIteratorFunction)(
                        P_XJ_ValueDestructCleanMapIterator
                    ),
                    NULL
                );
                NK_MapDestruct(value->data.table);
                NK_MapFree(value->data.table);
            };
            return;
        default:
            /** NOTE: in this case, something wrong happened. */
            NK_Panic(
                "%s: invalid state = %d",
                NK_CURRENT_WHERE,
                (int)(value->type)
            );
            return;
    }
}

void
XJ_ValueDestruct(
    XJ_Value* value
)
{
    /** Destroy the any container itself. */
    P_XJ_ValueDestructClean(value);
}

static
void
P_XJ_ValueDebug(
    XJ_Value* value,
    const NK_U8 depth
);

static
void
P_XJ_ValueDebugIterateTable(
    NK_Map* map,
    const NK_C8* key,
    const NK_Size index,
    XJ_Value* data,
    NK_U8* userdata
)
{
    P_XJ_ValueDebug(
        data,
        ((*userdata) + 1)
    );

    /** NOTE: Can we put ',' on it? */
    if(index < (NK_MapSize(map) - 1))
    {
        printf(", ");
    }
}

static
void
P_XJ_ValueDebugIterateList(
    NK_Vector* vector,
    const NK_Size index,
    XJ_Value* data,
    NK_U8* userdata
)
{
    P_XJ_ValueDebug(
        data,
         ((*userdata) + 1)
    );

    /** NOTE: Can we put ',' on it? */
    if(index < (NK_VectorSize(vector) - 1))
    {
        printf(", ");
    }
}

static
void
P_XJ_ValueDebug(
    XJ_Value* value,
    const NK_U8 depth
)
{
    switch(value->type)
    {
        case XJ_ENUMS_VALUE_TYPE_NOTHING:
            {
                printf("null");
            };
            break;
        case XJ_ENUMS_VALUE_TYPE_INTEGER:
            {
                printf("%d", value->data.integer);
            };
            break;
        case XJ_ENUMS_VALUE_TYPE_DECIMAL:
            {
                printf("%f", value->data.decimal);
            };
            break;
        case XJ_ENUMS_VALUE_TYPE_BOOLEAN:
            {
                printf(
                    "%s",
                    value->data.boolean ? "true" : "false"
                );
            };
            break;
        case XJ_ENUMS_VALUE_TYPE_STRING:
            {
                printf(
                    "\"%s\"",
                    NK_SubmergedStringGet(&value->data.string)
                );
            };
            break;
        case XJ_ENUMS_VALUE_TYPE_LIST:
            {
                printf("[");
                    NK_VectorIterate(
                        value->data.list,
                        (NK_VectorIteratorFunction)(P_XJ_ValueDebugIterateList),
                        (void*)(&depth)
                    );
                printf("]");
            };
            break;
        case XJ_ENUMS_VALUE_TYPE_TABLE:
            {
                printf("{");
                    NK_MapIterate(
                        value->data.table,
                        (NK_MapIteratorFunction)(P_XJ_ValueDebugIterateTable),
                        (void*)(&depth)
                    );
                printf("}");
            };
            break;
        default:
            /**
             * NOTE: This means the machine has found an error.
             */
            {
                NK_Panic(
                    "%s: Invalid type = %d",
                    NK_CURRENT_WHERE,
                    value->type
                );
            };
            break;
    };
}

void
XJ_ValueDebug(
    XJ_Value* value
)
{
    return P_XJ_ValueDebug(value, 0);
}