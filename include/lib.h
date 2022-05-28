#ifndef LIB_H
#define LIB_H


#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <stdint.h>
#include <errno.h>
#include <fcntl.h>
#include <limits.h>
#include <stdnoreturn.h>
#include <stdarg.h>
#include <unistd.h>
#include <stdbool.h>


#define RESET   "\033[0m"
#define B       "\033[30m"      /* Black */
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
#define W       "\033[37m"      /* White */
#define BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow */
#define BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */
#define BOLDMAGENTA "\033[1m\033[35m"      /* Bold Magenta */
#define BOLDCYAN    "\033[1m\033[36m"      /* Bold Cyan */
#define BOLDWHITE   "\033[1m\033[37m"      /* Bold White */




typedef enum error_type_t {
    
    PARSAGE_OK,
    ERROR_OPENING_FILES,
    
} error_type_t;



/**
 * @brief permuter deux entier
 * 
 */
void permuter(int *a, int *b);


/**
 * @brief trie d'un tableau
 * 
 */
void triRapid(int tab[], int first, int last);


/**
 * @brief calculer la distance entre 2 points 2D
 * 
 */
double distance(double x1, double x2 , double y1, double y2);


/**
 * @brief panic with a message.
 *
 * @param syserr 1 if errno is set, 0 otherwise
 * @param fmt formated message to print
 * @note this function never returns
 */
noreturn void panic(int syserr, const char *restrict fmt, ...);

/**
 * @brief safe call to snprintf.
 *
 * @param str string to write to
 * @param size size of the string
 * @param fmt formated message to print
 */
void snprintf_s(char *restrict str, size_t size, const char *restrict fmt, ...);


/**
 * @brief print debug message if DEBUG is set.
 *
 * @param first 1 if the first message of a series, 0 otherwise
 * @param fmt formated message to print
 */
void debug(int first, const char *restrict fmt, ...);

/**
 * @brief print an info message.
 *
 * @param first 1 if the first message of a series, 0 otherwise
 * @param fmt formated message to print
 */
void info(int first, const char *restrict fmt, ...);

/**
 * @brief allocates memory and panics if it fails.
 *
 * @param size size of the memory to allocate
 * @return void* - pointer to the allocated memory
 */
void *xmalloc(size_t size);

#endif 