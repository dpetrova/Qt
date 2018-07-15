#include "SysInfoWindows.h"

#include <QDebug>
#include <windows.h>

SysInfoWindows::SysInfoWindows() :
    SysInfo(),
    mCpuLoadLastValues() //we do not perform cpuLoadLastValues = cpuRawData() here in the initialization list
                        //because when call a function from the initialization list, the object is not yet fully constructed!
                        //In some cases, it may be unsafe because the function can try to access a member variable that has not been constructed yet
{

}

void SysInfoWindows::init()
{
    mCpuLoadLastValues = cpuRawData();
}

double SysInfoWindows::cpuLoadAverage()
{
    QVector<qulonglong> firstSample = mCpuLoadLastValues;
    QVector<qulonglong> secondSample = cpuRawData();
    mCpuLoadLastValues = secondSample;

    qulonglong currentIdle = secondSample[0] - firstSample[0];
    qulonglong currentKernel = secondSample[1] - firstSample[1];
    qulonglong currentUser = secondSample[2] - firstSample[2];
    qulonglong currentSystem = currentKernel + currentUser;

    double percent = (currentSystem - currentIdle) * 100.0 / currentSystem;
    return qBound(0.0, percent, 100.0);
}

double SysInfoWindows::memoryUsed()
{
   MEMORYSTATUSEX memoryStatus;
   memoryStatus.dwLength = sizeof(MEMORYSTATUSEX);
   GlobalMemoryStatusEx(&memoryStatus);
   qulonglong memoryPhysicalUsed = memoryStatus.ullTotalPhys - memoryStatus.ullAvailPhys;
   return (double)memoryPhysicalUsed / (double)memoryStatus.ullTotalPhys * 100.0;
}

QVector<qulonglong> SysInfoWindows::cpuRawData()
{
    FILETIME idleTime;
    FILETIME kernelTime;
    FILETIME userTime;

    QVector<qulonglong> t = mCpuLoadLastValues;

    GetSystemTimes(&idleTime, &kernelTime, &userTime);

    QVector<qulonglong> rawData;

    rawData.append(convertFileTime(idleTime));
    rawData.append(convertFileTime(kernelTime));
    rawData.append(convertFileTime(userTime));
    return rawData;
}

qulonglong SysInfoWindows::convertFileTime(const FILETIME& filetime) const
{
    //Windows structure FILEFTIME stores 64-bit information on two 32-bit parts (low and high)
    //use Windows structure ULARGE_INTEGER to correctly build a 64-bit value in a single part
    //before returning it as a qulonglong type
    ULARGE_INTEGER largeInteger;
    largeInteger.LowPart = filetime.dwLowDateTime;
    largeInteger.HighPart = filetime.dwHighDateTime;
    return largeInteger.QuadPart;
}
