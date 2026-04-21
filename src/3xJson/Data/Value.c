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
    NK_AnyConstruct(
        &value->container
    );
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
    switch(NK_AnyGetType(&value->container))
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
                    NK_AnyGet(NK_SubmergedString, &value->container)
                );
            };
            return;
        case XJ_ENUMS_VALUE_TYPE_LIST:
            /**
             * In this case, we need to iterate on the NK_Vector.
             */
            {
                NK_VectorIterate(
                    NK_AnyGet(NK_Vector, &value->container),
                    (NK_VectorIteratorFunction)(
                        P_XJ_ValueDestructCleanVectorIterator
                    ),
                    NULL
                );
                NK_VectorDestruct(NK_AnyGet(NK_Vector, &value->container));
            };
            return;
        case XJ_ENUMS_VALUE_TYPE_MAP:
            /**
             * In this case, we need to iterate on the NK_Map.
             */
            {
                NK_MapIterate(
                    NK_AnyGet(NK_Map, &value->container),
                    (NK_MapIteratorFunction)(
                        P_XJ_ValueDestructCleanMapIterator
                    ),
                    NULL
                );
                NK_MapDestruct(NK_AnyGet(NK_Map, &value->container));
            };
            return;
        default:
            /** NOTE: in this case, something wrong happened. */
            NK_Panic(
                "%s: invalid state = %d",
                NK_CURRENT_WHERE,
                (int)(NK_AnyGetType(&value->container))
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
    NK_AnyDestruct(&value->container);
}

void
XJ_ValueAssume(
    XJ_Value* value,
    const XJ_U8 type,
    const void* source,
    const XJ_Size size
)
{
    NK_AnySetType(&value->container, type);
    NK_AnyCopy(&value->container, source, size);
}