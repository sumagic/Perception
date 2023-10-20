#ifndef __PERCEPTION__LOG_H__
#define __PERCEPTION__LOG_H__

namespace perception
{
#ifndef _NDEBUG
    #define LOG_ERROR(FORMAT, ...) printf("[ERROR][%s]:[%s]:[%d]" FORMAT "\n", __FILE__,__FUNCTION__,__LINE__,##__VA_ARGS__)
    #define LOG_WARN(FORMAT, ...) printf("[WARN][%s]:[%s]:[%d]" FORMAT "\n", __FILE__,__FUNCTION__,__LINE__,##__VA_ARGS__)
    #define LOG_INFO(FORMAT, ...) printf("[INFO][%s]:[%s]:[%d]" FORMAT "\n", __FILE__,__FUNCTION__,__LINE__,##__VA_ARGS__)
    #define LOG_DEBUG(FORMAT, ...) printf("[DEBUG][%s]:[%s]:[%d]" FORMAT "\n", __FILE__,__FUNCTION__,__LINE__,##__VA_ARGS__)
#else
    #define LOG(LEVEL, FORMAT, ...) NULL
#endif 

} // namespace perception

#endif // __PERCEPTION__LOG_H__