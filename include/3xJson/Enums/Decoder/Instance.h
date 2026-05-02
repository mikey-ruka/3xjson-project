/**
 * Ruka Raposa Project by Ruka Raposa Team & Contribuitors.
 * Project is under GPL3-license, read LICENSE.md on the root.
 */
#ifndef XJEnumsDecoderInstance_h
#define XJEnumsDecoderInstance_h

/**
 * State:
 */

/**
 * @brief In this case, the machine still is running, we haven't finished the
 * operations.
 */
#define XJ_ENUMS_INSTANCE_STATE_RUNNING                                         0

/** 
 * @brief In this case, the machine has finished and you can extract the
 * `result` without any problems.
 */
#define XJ_ENUMS_INSTANCE_STATE_FINISHED                                        1

/**
 * @brief In this case, the machine has NOT finished good, something went
 * wrong and no data was set, everything was probably destroyed.
 */
#define XJ_ENUMS_INSTANCE_STATE_DIED                                            2

/**
 * Inside:
 */

/**
 * @brief `Root` is the early place where the scope begins.
 */
#define XJ_ENUMS_INSTANCE_SCOPE_INSIDE_ROOT                                     0

/**
 * @brief `List` is basically an list.
 */
#define XJ_ENUMS_INSTANCE_SCOPE_INSIDE_LIST                                     1

/**
 * @brief `Table` is the name given to the `Object`
 */
#define XJ_ENUMS_INSTANCE_SCOPE_INSIDE_TABLE                                    2

/**
 * Action:
 */

/**
 * @brief `Root` is the early place where the scope begins, this mode is
 * basically too bootstrap everything, we need to get the first to start the
 * machine.
 */
#define XJ_ENUMS_INSTANCE_SCOPE_ACTION_ROOT_BOOTSTRAP                           0

/**
 * @brief In `Root`, this is the mode to finish the machine, if the parsing is
 * good, then the final state is always reached, if the parsing was bad, then
 * the parsing is NEVER good.
 */
#define XJ_ENUMS_INSTANCE_SCOPE_ACTION_ROOT_CLOSURE                             1

/**
 * @brief In the `List` mode, an `Opening` means we starting the list parsing,
 * this will check for potential ']', which we can expect, but if we don't get
 * anything similar to that, we do `Get Data` logic, but inside the opening.
 * This mode implies on:
 *      > [] -> valid.
 */
#define XJ_ENUMS_INSTANCE_SCOPE_ACTION_LIST_OPENING                             2

/**
 * @brief In the `List` mode, an `Get Data` is when the data is to be handled
 * from the list.
 */
#define XJ_ENUMS_INSTANCE_SCOPE_ACTION_LIST_GET_DATA                            3

/**
 * @brief In the `List` mode, an `Closure` is when the token ']' was hit, this
 * means the list will close and return to the last stack position, but if an
 * ',' was found, then we return to `Get Data` and continue the loop.
 */
#define XJ_ENUMS_INSTANCE_SCOPE_ACTION_LIST_CLOSURE                             4

/**
 * @brief In the `Table` mode, an `Opening` means we will be loooking for the
 * character '}', in case it was NOT found, then, we perform `Get Key` inside
 * the Opening and skip to `Get Data`, this mode implies on:
 *      > {} -> valid.
 */
#define XJ_ENUMS_INSTANCE_SCOPE_ACTION_TABLE_OPENING                            5

/**
 * @brief In the `Table` mode, an `Key Grab` means we will be looking for a
 * string to be handled by the tokenizer, if we find it, we advance on the
 * parsing line, we also check if the ':' is present, if not, then we will
 * fail on this state, we assume ':' is part of the "key" itself since:
 *      > {"key"} -> invalid pattern, expected ':', got '}'
 */
#define XJ_ENUMS_INSTANCE_SCOPE_ACTION_TABLE_KEY_GRAB                           6

/**
 * @brief In the `Table` mode, an `Get Data ` is when the data is to be handled
 * from the list.
 */
#define XJ_ENUMS_INSTANCE_SCOPE_ACTION_TABLE_GET_DATA                           7

/**
 * @brief In the `Table` mode, an `Closure` is when the token '}' is found, but
 * if an ',' is found, then the loop returns to `Key Grab`. Anything else is 
 * NOT going to be considered, like:
 *      > {"key": "value"|} -> invalid pattern, expected either '}' or ','
 */
#define XJ_ENUMS_INSTANCE_SCOPE_ACTION_TABLE_CLOSURE                            8

#endif