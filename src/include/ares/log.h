
/*
 * Ares 64-bit Operating System
 *
 * Kernel logging facility
 */

#ifndef __ares_log_h_

#define __ares_log_h_

typedef enum {
    LOG_LEVEL_DEBUG = 0,
    LOG_LEVEL_INFO,
    LOG_LEVEL_WARN,
    LOG_LEVEL_ERROR
} log_level_t;

void log_set_level(log_level_t level);
void log_log(log_level_t level, const char *fmt, ...);

#define log_debug(...) log_log(LOG_LEVEL_DEBUG, __VA_ARGS__)
#define log_info(...)  log_log(LOG_LEVEL_INFO,  __VA_ARGS__)
#define log_warn(...)  log_log(LOG_LEVEL_WARN,  __VA_ARGS__)
#define log_error(...) log_log(LOG_LEVEL_ERROR, __VA_ARGS__)


#endif /* __ares_log_h_ */