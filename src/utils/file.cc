#include "utils/file.h"

#include <unistd.h>
#include <fcntl.h>

namespace perception
{
bool IsFileExist(const std::string& fileName)
{
    return access(fileName.c_str(), F_OK) != -1;
}
}