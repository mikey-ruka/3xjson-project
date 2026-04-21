/**
 * Ruka Raposa Project by Ruka Raposa Team & Contribuitors.
 * Project is under GPL3-license, read LICENSE.md on the root.
 */
#ifndef XJEnumsDataNode_h
#define XJEnumsDataNode_h

/**
 * @brief When a node is NULL, it means it is holding nothing.
 */
#define XJ_ENUMS_NODE_TYPE_NULL                                                 0

/**
 * @brief When the node is holding a value, it can be any value, even an branch,
 * which is `NK_Map<str, XJ_Value>`
 */
#define XJ_ENUMS_NODE_TYPE_VALUE                                                1

#endif