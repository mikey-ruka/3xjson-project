/**
 * Ruka Raposa Project by Ruka Raposa Team & Contribuitors.
 * Project is under GPL3-license, read LICENSE.md on the root.
 */
#ifndef XJDataValue_h
#define XJDataValue_h

#include "3xJson/Types/Basics.h"
#include "3xJson/Redirects.h"

/**
 * @brief Contains an variant of the type here.
 * 
 * @note This is a alias for `NK_Any`, since `NK_Any` can become any value and
 * hold it inside an buffer.
 */
typedef struct XJ_Value
{
    NK_Any container;
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
 * @brief Set the value for real.
 * 
 * @warning This is supposed to be a `oneshot` function, once you set the type,
 * it is over, you can't set something else, to do so, you need to drop the
 * `NK_Any` value (unallocate the buffer). There is a function for this named
 * `XJ_ValueDrop`, which calls `NK_AnyDestruct` and `NK_AnyConstruct` again.
 * 
 * @todo Implement `XJ_ValueDrop`.
 */
void
XJ_ValueAssume(
    XJ_Value* value,
    const XJ_U8 type,
    const void* source,
    const XJ_Size size
);

#endif