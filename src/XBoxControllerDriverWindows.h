#ifndef XBOXCONTROLLERDRIVERWINDOWS_H
#define XBOXCONTROLLERDRIVERWINDOWS_H

#include <XBoxControllerDriver.h>

#define WIN32_LEAN_AND_MEAN //reduce windows useless includes

#include <windows.h>
#include <Xinput.h>

namespace sofa
{

namespace component
{

namespace controller
{

class SOFA_XBOXCONTROLLERPLUGIN_API XBoxControllerDriverWindows : public AbstractXBoxControllerDriver
{
public:
    typedef AbstractXBoxControllerDriver Inherit;
    typedef Inherit::ControllerData ControllerData;

    XBoxControllerDriverWindows();
    virtual ~XBoxControllerDriverWindows();

    bool initController();
    bool getData(ControllerData& data);
    void rumble(int leftMotorValue, int rightMotorValue);
private:
    DWORD getXInputState(XINPUT_STATE& controllerState);
    void convertXinputData(ControllerData& data, const XINPUT_STATE& controllerState);
};

} // namespace controller

} // namespace component

} // namespace sofa

#endif // XBOXCONTROLLERDRIVERWINDOWS_H
