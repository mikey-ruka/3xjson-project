/**
 * Ruka Raposa Project by Ruka Raposa Team & Contribuitors.
 * Project is under GPL3-license, read LICENSE.md on the root.
 */
#ifndef XJDataValue_h
#define XJDataValue_h

#include "3xJson/Types/Basics.h"
#include "3xJson/Types/Nature.h"
#include "3xJson/Redirects.h"

/**
 * @brief Contains an variant of the type here.
 * 
 * @note This is a alias for `NK_Any`, since `NK_Any` can become any value and
 * hold it inside an buffer.
 */
typedef struct XJ_Value
{
    /**
     * @brief The current type of value.
     */
    XJ_U8 type;

    /**
     * @brief Contains the data union, depending on the `type`, you can should
     * read accordingly.
     */
    union
    {
        /**
         * @brief The representation for integer.
         */
        XJ_NatureInteger    integer;
        
        /**
         * @brief The representation for decimal.
         * 
         * @warning Decimal does NOT imply on integer, we want
         */
        XJ_NatureDecimal    decimal;

        /**
         * @brief The representation for boolean.
         */
        XJ_NaturalBoolean   boolean;

        /**
         * @brief The representation for string.
         * 
         * @warning This is a _pooled string_, meaning we aren't storing the
         * string here, instead, we are storing the handler, this avoids having
         * many duplicated strings inside the `XJ_Value`.
         */
        NK_SubmergedString  string;

        /**
         * @brief The representation for list.
         * 
         * @note This is a `NK_Vector` with the stride of `XJ_Value`, it is
         * constructed by `NK_VectorConstruct(data->list, sizeof(XJ_Value))`
         */
        NK_Vector*          list;

        /**
         * @brief The representation for table.
         * 
         * @note This is `NK_Map` with the stride of `XJ_Value`, it is
         * constructed by `NK_MapConstruct(data->table, XJ_CONFIG_TABLE_BUCKETS, sizeof(XJ_Value))`
         * 
         * @warning The size of the buckets is fixed on `XJ_CONFIG_TABLE_BUCKETS`, but this is
         * the early value to start, the `data->table`, the `NK_Map` is always 
         * (or is to have) the algorithm necessary to do the certain
         * optimizations to fix everything.
         */
        NK_Map*             table;
    } data;
} XJ_Value;

/**
 * @brief Creates an new `XJ_Value`
 */
XJ_Value*
XJ_ValueNew();

/**
 * @brief Frees an `XJ_Value` created by `XJ_ValueNew`
 */
void
XJ_ValueFree(
    XJ_Value* value
);

/**
 * @brief Construct the `XJ_Value`
 */
void
XJ_ValueConstruct(
    XJ_Value* value
);

/**
 * @brief Destruct the `XJ_Value`
 */
void
XJ_ValueDestruct(
    XJ_Value* value
);

/**
 * @brief Debug the `XJ_Value`
 */
void
XJ_ValueDebug(
    XJ_Value* value
);

#endif