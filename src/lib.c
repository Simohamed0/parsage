#include "../include/lib.h"



void permuter(int *a, int *b) {
    int tmp;
    tmp = *a;
    *a = *b;
    *b = tmp;
}

void triRapid(int tab[], int first, int last) {
    int pivot, i, j;
    if(first < last) {
        pivot = first;
        i = first;
        j = last;
        while (i < j) {
            while(tab[i] <= tab[pivot] && i < last)
                i++;
            while(tab[j] > tab[pivot])
                j--;
            if(i < j) {
                permuter(&tab[i], &tab[j]);
            }
        }
        permuter(&tab[pivot], &tab[j]);
        triRapid(tab, first, j - 1);
        triRapid(tab, j + 1, last);
    }
}

double distance(double x1, double x2 , double y1, double y2) {
    
    return sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2));
}


void snprintf_s(char *restrict str, size_t size, const char *restrict fmt,
                ...) {
    int n;
    va_list ap;

    va_start(ap, fmt);
    n = vsnprintf(str, size, fmt, ap);
    va_end(ap);

    if (n < 0) {
        panic(1, "vsnprintf failure");
    }
    if ((size_t)n >= size) {
        panic(1, "format string too long");
    }
}

int strtoi(const char *restrict nptr, int (*f)(int)) {
    char *endptr;
    int x = strtol(nptr, &endptr, 10);

    if (endptr == nptr || *endptr != '\0') {
        panic(1, "must be a number");
    } // if not a number
    if (errno == ERANGE) {
        panic(1, "out of range [%ld, %ld]", LONG_MIN, LONG_MAX);
    } // if out of range of long (might be a problem with implicit cast)
    if (f != NULL && !f(x)) {
        panic(0, "non legal value for our program");
    } // if non legal value for our program

    return x;
}



void debug(int first, const char *restrict fmt, ...) {

#ifndef DEBUG
    (void)first;
    (void)fmt;
#else
    va_list ap;

    va_start(ap, fmt);
    if (first) {
        fprintf(stdout, FG_GRN "  DEBUG: " RST);
    }
    vfprintf(stdout, fmt, ap);
    va_end(ap);

    int n = fflush(stdout);
    if (n == EOF) {
        panic(1, "fflush failure");
    }
#endif
}

void info(int first, const char *restrict fmt, ...) {
    va_list ap;

    va_start(ap, fmt);
    if (first) {
        fprintf(stdout, "info :");
    }
    vfprintf(stdout, fmt, ap);
    va_end(ap);
    int n = fflush(stdout);
    if (n == EOF) {
        panic(1, "fflush failure");
    }
}

void *xmalloc(size_t size) {
    

    void *p = malloc(size);
    if (p == NULL) {
        panic(1, "malloc failure");
    }
    return p;
}

noreturn void panic(int syserr, const char *restrict fmt, ...) {
    va_list ap;

    va_start(ap, fmt);
    fprintf(stderr, "  ERROR: " );
    vfprintf(stderr, fmt, ap);
    fprintf(stderr, "\n");
    va_end(ap);

    if (syserr == 1) {
        perror("\t");
    }

    exit(EXIT_FAILURE);
}
