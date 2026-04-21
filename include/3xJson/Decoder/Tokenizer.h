/**
 * Ruka Raposa Project by Ruka Raposa Team & Contribuitors.
 * Project is under GPL3-license, read LICENSE.md on the root.
 */
#ifndef XJDecoderTokenizer_h
#define XJDecoderTokenizer_h

#include "3xJson/Types/Basics.h"
#include "3xJson/Redirects.h"

/**
 * @brief The `XJ_DecoderTokenizer`, contains an state machine for the token
 * adquiring mechanism.
 */
typedef struct XJ_DecoderTokenizer
{
    /**
     * @brief The token handler itself.
     */
    NK_DynamicString token;

    /**
     * @brief The number handler.
     * 
     * @warning This was done to speed up parsing, the number is already here,
     * but only works when the state_register said so, in any case, this handler
     * is not reliable.
     */
    XJ_S64 number_handler;

    /**
     * @brief Sets the source from where we are reading from.
     */
    NK_Reader* source;

    /**
     * @brief Sets the position of the line.
     */
    XJ_Size line_counter;

    /**
     * @brief Sets the max. position of the buffer.
     */
    XJ_Size max_buffer_position;

    /**
     * @brief Holds an single special token.
     */
    XJ_U8 special_token_handler;

    /**
     * @brief We want to have the register here.
     */
    union
    {
        /**
         * @brief Contains the bits for the runtime information about the
         * tokenizer machine.
         */
        XJ_U8 state_register;  
        struct
        {
            /**
             * @brief Says if we got an special token.
             */
            XJ_U8 special_token: 1;

            /**
             * @brief Says if the token adquired was an number.
             */
            XJ_U8 number: 1;

            /**
             * @brief Says if the token adquired was an decimal number.
             */
            XJ_U8 decimal: 1;

            /**
             * @brief Says if the token adquired was an string.
             */
            XJ_U8 string: 1;

            /**
             * @brief An empty reserved place.
             */
            XJ_U8 res: 4;
        } state_register_bits;
    };
} XJ_DecoderTokenizer;

/**
 * @brief Creates an new `XJ_DecoderTokenizer`
 */
XJ_DecoderTokenizer*
XJ_DecoderTokenizerNew();

/**
 * @brief Frees an `XJ_DecoderTokenizer` created by `XJ_DecoderTokenizerNew`
 */
void
XJ_DecoderTokenizerFree(
    XJ_DecoderTokenizer* tokenizer
);

/**
 * @brief Constructs an `XJ_DecoderTokenizer`
 */
void
XJ_DecoderTokenizerConstruct(
    XJ_DecoderTokenizer* tokenizer,
    NK_Reader* source
);

/**
 * @brief Destructs an `XJ_DecoderTokenizer`
 */
void
XJ_DecoderTokenizerDestruct(
    XJ_DecoderTokenizer* tokenizer
);

/**
 * @brief Step on the token.
 * 
 * @returns If the `XJ_DecoderTokenizer` still has tokens to process, if not,
 * then it returns `false`
 */
XJ_Result
XJ_DecoderTokenizerStep(
    XJ_DecoderTokenizer* tokenizer
);

#endif