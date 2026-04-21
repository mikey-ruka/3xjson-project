/**
 * Ruka Raposa Project by Ruka Raposa Team & Contribuitors.
 * Project is under GPL3-license, read LICENSE.md on the root.
 */
#ifndef XJDecoderInstance_h
#define XJDecoderInstance_h

#include "3xJson/Types/Basics.h"
#include "3xJson/Redirects.h"
#include "3xJson/Decoder/Tokenizer.h"

/**
 * @brief The place to decode an source into the node tree.
 */
typedef struct XJ_DecoderInstance
{
    /**
     * @brief The place to get tokens.
     */
    XJ_DecoderTokenizer tokenizer;
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

#endif