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

    printf("%s: Continue.\n", NK_CURRENT_WHERE);

    XJ_DecoderInstance instance;
    XJ_DecoderInstanceConstruct(&instance, &fp);
    XJ_DecoderInstanceStep(&instance);
    XJ_DecoderInstanceDestruct(&instance);

    printf("%s: Done.\n", NK_CURRENT_WHERE);

    NK_ReaderClose(&fp);
    NK_FileReaderDestruct(&fp);

nothing_todo_ending:

    NK_Quit();
}