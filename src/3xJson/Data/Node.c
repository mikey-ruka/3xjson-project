/**
 * Ruka Raposa Project by Ruka Raposa Team & Contribuitors.
 * Project is under GPL3-license, read LICENSE.md on the root.
 */

#include "3xJson/Data/Node.h"
#include "3xJson/Redirects.h"

XJ_Node*
XJ_NodeNew()
{
    XJ_Node* new_node =
        (XJ_Node*)(
            NK_AllocatorGet(sizeof(XJ_Node))
        );
    return new_node;
}

void
XJ_NodeFree(
    XJ_Node* node
)
{
    NK_AllocatorFree(node);
}

void
XJ_NodeConstruct(
    XJ_Node* node
)
{
    /** 
     * NOTE: We don't construct anything, this is done by the
     * `XJ_DecoderInstance` internal functions. Because the initial root is
     * always determined by it.
     */
    XJ_ValueConstruct(&node->root);
}

void
XJ_NodeDestruct(
    XJ_Node* node
)
{
    XJ_ValueDestruct(&node->root);
}
