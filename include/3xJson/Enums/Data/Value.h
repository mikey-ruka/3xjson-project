/**
 * Ruka Raposa Project by Ruka Raposa Team & Contribuitors.
 * Project is under GPL3-license, read LICENSE.md on the root.
 */
#ifndef XJEnumsDataValue_h
#define XJEnumsDataValue_h

/**
 * @brief In this case, it is either holding nothing or `null`, specified by
 * JSON.
 */
#define XJ_ENUMS_VALUE_TYPE_NOTHING                                             0

/**
 * @brief The type `integer` of the json format.
 */
#define XJ_ENUMS_VALUE_TYPE_INTEGER                                             1

/**
 * @brief The type `decimal` of the json format.
 * 
 * @warning Why decimal is not integer? Simple, because `float` isn't the most
 * precise arrangement, an integer is a integer, an rational number is d/n 
 * anyways.
 */
#define XJ_ENUMS_VALUE_TYPE_DECIMAL                                             2

/**
 * @brief The type `boolean` of the json format.
 */
#define XJ_ENUMS_VALUE_TYPE_BOOLEAN                                             3

/**
 * @brief The type `string` of the json format.
 */
#define XJ_ENUMS_VALUE_TYPE_STRING                                              4

/**
 * @brief The type `list` of the json format.
 * 
 * @note The list is `NK_List<XJ_Value>` which is a list that contains other
 * XJ_Value(s).
 */
#define XJ_ENUMS_VALUE_TYPE_LIST                                                5

/**
 * @brief The type `map` of the json format.
 * 
 * @note The map is `NK_Map<XJ_Value>` which is a map that contains other
 * `XJ_Value`(s)
 */
#define XJ_ENUMS_VALUE_TYPE_MAP                                                 6

#endif