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
    
    while(
        XJ_DecoderInstanceStep(&instance) == XJ_ENUMS_INSTANCE_STATE_RUNNING
    );

    switch(
        XJ_DecoderInstanceGetState(&instance)
    )
    {
        case XJ_ENUMS_INSTANCE_STATE_FINISHED:
            {
                printf("%s: Finished!\n", NK_CURRENT_WHERE);
            };
            break;
        case XJ_ENUMS_INSTANCE_STATE_DIED:
            {
                NK_Panic(
                    "%s: Died",
                    NK_CURRENT_WHERE
                );
            };
            break;
        default:
            {
                NK_Panic(
                    "%s: Invalid state = %d",
                    NK_CURRENT_WHERE,
                    XJ_DecoderInstanceGetState(&instance)
                );
            };
            break;
    };

    XJ_Value proc_value = XJ_DecoderInstanceExtractResult(&instance);

    XJ_DecoderInstanceDestruct(&instance);

    printf("=> Result:\n");
    XJ_ValueDebug(&proc_value);
    printf("\n");

    XJ_ValueDestruct(&proc_value);
    NK_ReaderClose(&fp);
    NK_FileReaderDestruct(&fp);

nothing_todo_ending:

    NK_Quit();
}
