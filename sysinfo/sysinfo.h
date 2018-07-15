#ifndef SYSINFO_H
#define SYSINFO_H

//SINGLETON
//The singleton must guarantee that there will be only one instance of the class
//and that this instance will be easily accessible from a single access point

class SysInfo
{
public:
    static SysInfo& instance(); //"unique access point" -> static function instance that will return a reference of the SysInfo class
    //empty virtual destructor
    //this destructor must be virtual to ensure that any deletion of an instance of a derived class
    //will call the derived class destructor and not only the base class destructor
    virtual ~SysInfo();

    //virtual keyword indicates that the function can be overridden in a derived class
    //= 0 syntax means that this function is pure virtual, and must be overridden in any concrete derived class
    //a pure virtual function implicitly makes the class it is defined for abstract (cannot be instantiated)
    virtual void init() = 0; //allows the derived class to perform any initialization process depending on the OS platform
    virtual double cpuLoadAverage() = 0; //calls some OS-specific code to retrieve the average CPU load and returns it as a percentage value
    virtual double memoryUsed() = 0; //calls some OS-specific code to retrieve the memory used and returns it as a percentage value

protected:
    //change the visibility of the constructor to protected
    //this way, only this class and the child classes will be allowed to call the constructor
    explicit SysInfo();

private:
    SysInfo(const SysInfo& rhs); //copy constructor
    SysInfo& operator=(const SysInfo& rhs); //assignment operator
};

#endif // SYSINFO_H
