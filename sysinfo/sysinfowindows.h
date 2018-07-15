#ifndef SYSINFOWINDOWS_H
#define SYSINFOWINDOWS_H

#include <QtGlobal> // includes the fundamental global declarations (qlonglong, qint,...)
#include <QVector>

#include "SysInfo.h"

//kind of forward declaration for FILENAME syntax
//as we only use a reference, we can avoid including the <windows.h> tag in our .h file and keep it in the .cpp file
typedef struct _FILETIME FILETIME;

//this classis one of the classes derived from the SysInfo class.
//The main purpose of this class is to encapsulate the Windows-specific code to retrieve CPU and memory usage
class SysInfoWindows : public SysInfo
{
public:
    SysInfoWindows();

    //put your cursor on a derived class name (after the keyword class) and press Alt + Enter
    //to automatically insert virtual functions of the base class
    void init() override;
    double cpuLoadAverage() override;
    double memoryUsed() override;

private:
    QVector<qulonglong> cpuRawData(); //qulonglong type is a Qt unsigned long long int
    qulonglong convertFileTime(const FILETIME& filetime) const;

private:
    QVector<qulonglong> mCpuLoadLastValues;
};

#endif // SYSINFOWINDOWS_H
