/**
 * Ruka Raposa Project by Ruka Raposa Team & Contribuitors.
 * Project is under GPL3-license, read LICENSE.md on the root.
 */
#ifndef XJDataNode_h
#define XJDataNode_h

#include "3xJson/Data/Value.h"

/**
 * @brief `XJ_Node` contains the root `XJ_Value` and some easy pointers to 
 * `XJ_Values`.
 */
typedef struct XJ_Node
{
    /**
     * @brief This is the root of the `XJ_Node`, contains all the elements.
     */
    XJ_Value root;

    /**
     * @todo Implement some cache for XJ_NodeGet() function, some keys might
     * have more frequent access, which is useless to be O(n) them all the
     * time!
     */
} XJ_Node;

/**
 * @brief Creates an new `XJ_Node`
 */
XJ_Node*
XJ_NodeNew();

/**
 * @brief Destroys an `XJ_Node` created by `XJ_NodeNew` function.
 */
void
XJ_NodeFree(
    XJ_Node* node
);

/**
 * @brief Constructs an `XJ_Node`
 */
void
XJ_NodeConstruct(
    XJ_Node* node
);

/**
 * @brief Destructs an `XJ_Node`
 */
void
XJ_NodeDestruct(
    XJ_Node* node
);

#endif