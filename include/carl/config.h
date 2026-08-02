#ifndef CARL_CONFIG_H
#define CARL_CONFIG_H

#define CARL_MEMORY_LIMIT      0x200000  
#define CARL_PAGE_SIZE         4096

#define CARL_TOTAL_PAGES       (CARL_MEMORY_LIMIT / CARL_PAGE_SIZE)

#define CARL_KERNEL_BASE       0x00100000   

#define CARL_KERNEL_MAX_SIZE   0x00040000 

#define CARL_VIDEO_MEMORY      0xB8000

#define CARL_SCREEN_COLS       80
#define CARL_SCREEN_ROWS       25

#define CARL_DEFAULT_COLOR     0x07

#define CARL_TIMER_FREQUENCY   100  

#define CARL_ENABLE_LOGS       1

#define CARL_SAFE_MODE         1

#define CARL_INTERNAL          static

#define CARL_NORETURN          __attribute__((noreturn))

#endif /* CARL_CONFIG_H */