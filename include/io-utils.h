#ifndef IO_UTILS_H
#define IO_UTILS_H

#include "args-parser.h"
#include "lib.h"

/**
 * @brief opens the necessary files
 * returns an error type (see types.h)
 * 
 * @param options 
 */
error_type_t openFiles(options_t * options);


const char * errorToString(error_type_t err);

#endif
