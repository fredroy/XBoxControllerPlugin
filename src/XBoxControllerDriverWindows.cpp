#include <XBoxControllerDriverWindows.h>


namespace sofa
{

namespace component
{

namespace controller
{

XBoxControllerDriverWindows::XBoxControllerDriverWindows()
    : Inherit()
{

}
XBoxControllerDriverWindows::~XBoxControllerDriverWindows()
{

}

bool XBoxControllerDriverWindows::getData(ControllerData& data)
{
    XINPUT_STATE controllerState;
    DWORD Result = getXInputState(controllerState);

    if (Result == ERROR_SUCCESS)
    {
        convertXinputData(data, controllerState);
        return true;
    }
    else
    {
        //reset values
        data = ControllerData();
        return false;
    }
}

bool XBoxControllerDriverWindows::initController()
{
    XINPUT_STATE controllerState;
    DWORD Result = getXInputState(controllerState);

    if (Result == ERROR_SUCCESS)
    {
        rumble(10000, 10000);
        Sleep(500);
        rumble(0, 0);
        return true;
    }
    else
    {
        return false;
    }

}

DWORD XBoxControllerDriverWindows::getXInputState(XINPUT_STATE& controllerState)
{
    //make sure to initialize with 0's
    memset(&controllerState, 0, sizeof(XINPUT_STATE));

    DWORD result = XInputGetState(this->getControllerNumber(), &controllerState);

    return result;
}

void XBoxControllerDriverWindows::convertXinputData(ControllerData& data, const XINPUT_STATE& controllerState)
{
    //Buttons
    data.buttonsState = ControllerData::BUTTON_NULL;
    if (controllerState.Gamepad.wButtons & XINPUT_GAMEPAD_A)
        data.buttonsState += ControllerData::BUTTON_A;
    if (controllerState.Gamepad.wButtons & XINPUT_GAMEPAD_B)
        data.buttonsState += ControllerData::BUTTON_B;
    if (controllerState.Gamepad.wButtons & XINPUT_GAMEPAD_X)
        data.buttonsState += ControllerData::BUTTON_X;
    if (controllerState.Gamepad.wButtons & XINPUT_GAMEPAD_Y)
        data.buttonsState += ControllerData::BUTTON_Y;
    
    //Triggers
    data.leftTrigger = controllerState.Gamepad.bLeftTrigger;
    data.rightTrigger = controllerState.Gamepad.bRightTrigger;

    //Thumbs
    data.leftThumbX = controllerState.Gamepad.sThumbLX;
    data.leftThumbY = controllerState.Gamepad.sThumbLY;
    data.rightThumbX = controllerState.Gamepad.sThumbRX;
    data.rightThumbY = controllerState.Gamepad.sThumbRY;
}

void XBoxControllerDriverWindows::rumble(int leftMotorValue, int rightMotorValue)
{
    // Create a Vibraton State
    XINPUT_VIBRATION vibration;

    // Zeroise the Vibration
    memset(&vibration, 0, sizeof(XINPUT_VIBRATION));

    // Set the Vibration Values
    vibration.wLeftMotorSpeed = leftMotorValue;
    vibration.wRightMotorSpeed = rightMotorValue;

    // Vibrate the controller
    XInputSetState(this->getControllerNumber(), &vibration);
}

} // namespace controller

} // namespace component

} // namespace sofa
