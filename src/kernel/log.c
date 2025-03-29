#include <ares/log.h>
#include <ares/stdio.h>
#include <stdarg.h>

static log_level_t current_log_level = LOG_LEVEL_DEBUG;

void log_set_level(log_level_t level) {
    current_log_level = level;
}

void log_log(log_level_t level, const char* fmt, ...) {
    if (level < current_log_level) return;

    const char* level_str = "???";
    switch (level) {
        case LOG_LEVEL_DEBUG: level_str = "DEBUG"; break;
        case LOG_LEVEL_INFO:  level_str = "INFO "; break;
        case LOG_LEVEL_WARN:  level_str = "WARN "; break;
        case LOG_LEVEL_ERROR: level_str = "ERROR"; break;
    }

    printf("[%s] ", level_str);

    va_list args;
    va_start(args, fmt);
    vprintf(fmt, args);
    va_end(args);

    printf("\n");
}
