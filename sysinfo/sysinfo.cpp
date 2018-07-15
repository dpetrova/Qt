#include "sysinfo.h"

#include <QtGlobal>

//Qt provides some macro Q_OS_WIN, Q_OS_LINUX, or Q_OS_MAC
//Qt OS macro will be defined only on the corresponding OS
#ifdef Q_OS_WIN
    #include "SysInfoWindows.h"
#elif defined(Q_OS_LINUX)
    #include "SysInfoLinux.h"
#endif

SysInfo& SysInfo::instance()
{
    //declaring singleton variable as a static variable in the instance() function is a way to make a singleton in C++
    #ifdef Q_OS_WIN
        static SysInfoWindows singleton;
    #elif defined(Q_OS_LINUX)
        static SysInfoLinux singleton;
    #endif

    return singleton;
}

SysInfo::SysInfo()
{
}

SysInfo::~SysInfo()
{
}
