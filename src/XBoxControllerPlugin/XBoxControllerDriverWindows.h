#pragma once
#include <XBoxControllerPlugin/XBoxControllerDriver.h>

#define WIN32_LEAN_AND_MEAN //reduce windows useless includes

#include <windows.h>
#include <Xinput.h>

namespace sofa::component::controller
{

class SOFA_XBOXCONTROLLERPLUGIN_API XBoxControllerDriverWindows : public AbstractXBoxControllerDriver
{
public:
    typedef AbstractXBoxControllerDriver Inherit;
    typedef Inherit::ControllerData ControllerData;

    XBoxControllerDriverWindows();
    virtual ~XBoxControllerDriverWindows() = default;

    bool initController();
    bool getData(ControllerData& data);
    void rumble(int leftMotorValue, int rightMotorValue);
private:
    DWORD getXInputState(XINPUT_STATE& controllerState);
    void convertXinputData(ControllerData& data, const XINPUT_STATE& controllerState);
};

} // namespace sofa::component::controller
