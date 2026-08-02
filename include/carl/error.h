#ifndef CARL_ERROR_H
#define CARL_ERROR_H

typedef enum {
    C_ERROR_NONE = 0,
    C_ERROR_MEMORY,
    C_ERROR_DRIVER,
    C_ERROR_KERNEL,
    C_ERROR_BOOT, 
    C_ERROR_UNKNOWN
} carl_error_t;

void c_set_error(carl_error_t error);
carl_error_t c_get_error(void);

void c_gsod(const char *message);

#endif /* CARL_ERROR_H */
