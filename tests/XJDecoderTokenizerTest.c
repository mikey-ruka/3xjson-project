/**
 * Ruka Raposa Project by Ruka Raposa Team & Contribuitors.
 * Project is under GPL3-license, read LICENSE.md on the root.
 */

#include "3xJson/3xJson.h"
#include "NK/NK.h"

int main(
    int argc,
    char *argv[]
)
{
    NK_Init();

    /** Set the tokenizer ready: */
    NK_FileReader fp;
    NK_FileReaderConstruct(&fp);
    if(
        !NK_ReaderOpen(&fp, (void*)("./tests/A.json"))
    )
    {
        printf("nothing to do.\n");
        goto nothing_todo_ending;
    }

    /** Test the tokenizer: */
    XJ_DecoderTokenizer tk;
    XJ_DecoderTokenizerConstruct(&tk, (NK_Reader*)(&fp));
    
    while(
        XJ_DecoderTokenizerStep(&tk)
    )
    {
        if(tk.state_register_bits.special_token)
        {
            printf("HIGHLIGHT TOKEN: %c\n", tk.special_token_handler);
        }
        else if(tk.state_register_bits.number)
        {
            printf("NUMBER: %d\n", tk.number_handler);
        }
        else if(tk.state_register_bits.string)
        {
            printf("STRING: %s\n", NK_DynamicStringGetBuffer(&tk.token));
        }
        else
        {
            printf("TOKEN: %s\n", NK_DynamicStringGetBuffer(&tk.token));
        }
    }

    /** Say the final one. */
    printf("%s\n", NK_DynamicStringGetBuffer(&tk.token));

    XJ_DecoderTokenizerDestruct(&tk);

    NK_ReaderClose(&fp);
    NK_FileReaderDestruct(&fp);

nothing_todo_ending:

    NK_Quit();
}