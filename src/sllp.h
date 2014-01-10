#ifndef SLLP_H
#define SLLP_H

#include <stdint.h>
#include <stdbool.h>

#define SLLP_HEADER_SIZE        2
#define SLLP_MAX_PAYLOAD        16387
#define SLLP_MAX_MESSAGE        (SLLP_HEADER_SIZE+SLLP_MAX_PAYLOAD)

#define SLLP_MAX_VARIABLES      128
#define SLLP_MAX_GROUPS         8
#define SLLP_MAX_CURVES         128
#define SLLP_MAX_FUNCTIONS      128

#define SLLP_LIST_STRUCT(name, type, max)\
    struct name {\
        uint32_t count;\
        type list[max];\
    }

#define SLLP_VERSION_STR_MAX_LEN 20
struct sllp_version
{
    uint8_t major;
    uint8_t minor;
    uint8_t revision;
    char    str[SLLP_VERSION_STR_MAX_LEN];
};

enum sllp_bin_op
{
    BIN_OP_AND,
    BIN_OP_OR,
    BIN_OP_XOR,
    BIN_OP_SET,
    BIN_OP_CLEAR,
    BIN_OP_TOGGLE,

    BIN_OP_COUNT,   // Number of binary operations
};

typedef void (*bin_op_function) (uint8_t *data, uint8_t *mask, uint8_t size);
extern bin_op_function bin_op[256];

enum sllp_err
{
    SLLP_SUCCESS,                   // Operation executed successfully
    SLLP_ERR_PARAM_INVALID,         // An invalid parameter was passed
    SLLP_ERR_PARAM_OUT_OF_RANGE,    // A param not in the acceptable range was
                                    // passed
    SLLP_ERR_OUT_OF_MEMORY,         // Not enough memory to complete operation
    SLLP_ERR_DUPLICATE,             // Trying to register an already registered
                                    // object
    SLLP_ERR_COMM,                  // There was a communication error reported
                                    // by one of the communication functions.
    SLLP_ERR_MAX
};

/**
 * Returns an error string associated with the given error code
 *
 * @param error [input] The error code
 *
 * @return A string that describes the error
 */
char * sllp_error_str (enum sllp_err error);

/**
 * Returns a string that represents the SLLP version number supported by
 * this library version
 *
 * @return String containing the version supported.
 */
char *sllp_proto_version (void);

#endif
