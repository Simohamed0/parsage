#ifndef IO_UTILS_H
#define IO_UTILS_H

#include "args-parser.h"
#include "lib.h"

/**
 * @brief opens the necessary files
 * returns an error type (see lib.h)
 * 
 * @param options 
 */
typedef enum error_type_t {
    
    PARSAGE_OK,
    ERROR_OPENING_FILES
} error_type_t;

const char * errorToString(error_type_t err);


#endif
