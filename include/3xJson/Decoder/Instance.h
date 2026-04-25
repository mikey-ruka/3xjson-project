/**
 * Ruka Raposa Project by Ruka Raposa Team & Contribuitors.
 * Project is under GPL3-license, read LICENSE.md on the root.
 */
#ifndef XJDecoderInstance_h
#define XJDecoderInstance_h

#include "3xJson/Types/Basics.h"
#include "3xJson/Redirects.h"
#include "3xJson/Decoder/Tokenizer.h"
#include "3xJson/Data.h"

/**
 * @brief This holds the current scope we are in.
 */
typedef struct XJ_DecoderInstanceScope
{
    /**
     * @brief Contains the current value, this will be on the future be reduced
     * to the tree.
     */
    XJ_Value    value;
    
    /**
     * @brief What type we are inside of, this can be: None, List and Table.
     */
    XJ_U8       inside;

    /**
     * @brief This holds, inside the type, what type of action we are currently
     * in, there are two actions that can be stalled: Table and List, because
     * we don't know how big the table or list might be, we should continue it
     * until the end token is reached.
     */
    XJ_U8       action;
} XJ_DecoderInstanceScope;

/**
 * @brief The place to decode an source into the node tree.
 */
typedef struct XJ_DecoderInstance
{
    /**
     * @brief The place to get tokens.
     */
    XJ_DecoderTokenizer tokenizer;

    /**
     * @brief The current scope.
     */
    XJ_DecoderInstanceScope current_scope;

    /**
     * @brief The current stack containing the scopes.
     */
    NK_Vector scope_stack;

    /**
     * @brief The general state of the parser. This defines if the machine is
     * running, finished or died.
     */
    NK_U8 state;
} XJ_DecoderInstance;

/**
 * @brief Creates an new `XJ_DecodeInstance`
 */
XJ_DecoderInstance*
XJ_DecoderInstanceNew();

/**
 * @brief Frees an `XJ_DecodeInstance` created by `XJ_DecodeInstanceNew`
 */
void
XJ_DecoderInstanceFree(
    XJ_DecoderInstance* instance
);

/**
 * @brief Constructs the `XJ_DecodeInstance`
 */
void
XJ_DecoderInstanceConstruct(
    XJ_DecoderInstance* instance,
    NK_Reader* reader
);

/**
 * @brief Destruct the `XJ_DecodeInstance`
 */
void
XJ_DecoderInstanceDestruct(
    XJ_DecoderInstance* instance
);

/**
 * @brief Step on the decoding.
 */
NK_U8
XJ_DecoderInstanceStep(
    XJ_DecoderInstance* instance
);

#endif