#ifndef __PERCEPTION_COMMON_H__
#define __PERCEPTION_COMMON_H__

#include <cstddef>
#include <stdio.h>

#ifndef _NDEBUG
    #define LOG_ERROR(FORMAT, ...) printf("[ERROR][%s]:[%s]:[%d]" FORMAT "\n", __FILE__,__FUNCTION__,__LINE__,##__VA_ARGS__)
    #define LOG_WARN(FORMAT, ...) printf("[WARN][%s]:[%s]:[%d]" FORMAT "\n", __FILE__,__FUNCTION__,__LINE__,##__VA_ARGS__)
    #define LOG_INFO(FORMAT, ...) printf("[INFO][%s]:[%s]:[%d]" FORMAT "\n", __FILE__,__FUNCTION__,__LINE__,##__VA_ARGS__)
    #define LOG_DEBUG(FORMAT, ...) printf("[DEBUG][%s]:[%s]:[%d]" FORMAT "\n", __FILE__,__FUNCTION__,__LINE__,##__VA_ARGS__)

#else
    #define LOG(LEVEL, FORMAT, ...) NULL
#endif

namespace perception
{

const size_t MEMORY_ALLOC_MAX = 1024 * 1024 * 1024; // 1GB max

enum Status {
    SUCCESS = 0,
    // file operation
    FILE_NOT_FOUND,

    // memory operation
    MEMORY_PTR_IS_NULL,
    MEMORY_ALLOC_TOO_LARGE,
    MEMORY_ALLOC_IS_ZERO,

    // vector operation
    INDEX_OUT_OF_RANGE,
    KEY_NOT_FOUND,

    UNKNOWN
}; // Status

} // namespace perception

#endif // __PERCEPTION__LOG_H__