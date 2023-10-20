#ifndef __PERCEPTION__LOG_H__
#define __PERCEPTION__LOG_H__

namespace perception
{
#ifndef _NDEBUG
    #define LOG(LEVEL, FORMAT, ...) printf("[%s][%s][%s][%d]"FORMAT, ##LEVEL, __FILE__,__FUNCTION__,__LINE__,##__VA_ARGS__)
#else
    #define LOG(fmt, ...) NULL
#endif 

#define LOG_ERROR(FORMAT, ...) LOG(ERROR, FORMAT, ##__VA_ARGS__)
#define LOG_WARN(FORMAT, ...) LOG(WARN, FORMAT, ##__VA_ARGS__)
#define LOG_INFO(FORMAT, ...) LOG(INFO, FORMAT, ##__VA_ARGS__)
#define LOG_DEBUG(FORMAT, ...) LOG(DEBUG, FORMAT, ##__VA_ARGS__)

} // namespace perception

#endif // __PERCEPTION__LOG_H__