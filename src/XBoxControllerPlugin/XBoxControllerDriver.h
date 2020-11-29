#pragma once

#include <XBoxControllerPlugin/config.h>

#include <sofa/core/objectmodel/BaseObject.h>
#include <sofa/helper/system/FileRepository.h>


namespace sofa::component::controller
{

class AbstractXBoxControllerDriver
{
protected:
    unsigned int m_controllerNumber;

public:
    struct ControllerData
    {
        enum Button
        {
            BUTTON_NULL=0, 
            BUTTON_A=1, 
            BUTTON_B=2, 
            BUTTON_X=4, 
            BUTTON_Y=8
        };

        unsigned int buttonsState;

        unsigned char leftTrigger;
        unsigned char rightTrigger;

        short leftThumbX;
        short leftThumbY;
        short rightThumbX;
        short rightThumbY;

        void print();

    };

    virtual bool initController() = 0;
    virtual bool getData(ControllerData& data) = 0;
    virtual void rumble(int leftMotorValue, int rightMotorValue) = 0;

    int getControllerNumber() { return m_controllerNumber; }
    void setControllerNumber(int controllerNumber) { m_controllerNumber = controllerNumber; }
};

class SOFA_XBOXCONTROLLERPLUGIN_API XBoxControllerDriver : public sofa::core::objectmodel::BaseObject
{

public:
    SOFA_CLASS(XBoxControllerDriver, sofa::core::objectmodel::BaseObject);

    typedef sofa::core::objectmodel::BaseObject Inherit;
    typedef AbstractXBoxControllerDriver::ControllerData ControllerData;

    void init();
    void update() {}
    void handleEvent(sofa::core::objectmodel::Event* event);

    Data<int> d_controllerNumber;

    //Outputs
    Data<bool> d_buttonA;
    Data<bool> d_buttonB;
    Data<bool> d_buttonX;
    Data<bool> d_buttonY;

    Data<short> d_leftThumbX;
    Data<short> d_leftThumbY;
    Data<short> d_rightThumbX;
    Data<short> d_rightThumbY;

    Data<unsigned char> d_leftTrigger;
    Data<unsigned char> d_rightTrigger;

protected:
    /** Default constructor
    */
    XBoxControllerDriver();
    virtual ~XBoxControllerDriver();

    void fillData(const ControllerData& data);

private:
    std::shared_ptr<AbstractXBoxControllerDriver> m_XBoxControllerDriverImpl;


};

} // namespace sofa::component::controller
