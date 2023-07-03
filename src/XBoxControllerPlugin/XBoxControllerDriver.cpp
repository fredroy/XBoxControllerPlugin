#include <XBoxControllerPlugin/XBoxControllerDriver.h>

#include <sofa/core/ObjectFactory.h>
#include <sofa/simulation/AnimateBeginEvent.h>

#include <XBoxControllerPlugin/XBoxControllerDriverWindows.h>

namespace sofa::component::controller
{

SOFA_DECL_CLASS(XBoxControllerDriver)

std::ostream& operator<< (std::ostream& os, const AbstractXBoxControllerDriver::ControllerData& cd)
{
    using Button = AbstractXBoxControllerDriver::ControllerData::Button;

    os << "Buttons: " << std::endl;
    os << "A: " << ((cd.buttonsState & Button::BUTTON_A) ? "O" : "X") << " | "
              << "B: " << ((cd.buttonsState & Button::BUTTON_B) ? "O" : "X") << " | "
              << "X: " << ((cd.buttonsState & Button::BUTTON_X) ? "O" : "X") << " | "
              << "Y: " << ((cd.buttonsState & Button::BUTTON_Y) ? "O" : "X") << " | "
              << std::endl;

    os << "Triggers: " << std::endl;
    os << "Left: " << +cd.leftTrigger << " | "
              << "Right: " << +cd.rightTrigger
              << std::endl;

    os << "Thumbs: " << std::endl;
    os << "Left: " << cd.leftThumbX << "," << cd.leftThumbY << " | "
              << "Right: " << cd.rightThumbX << "," << cd.rightThumbY
              << std::endl;

    return os;
}


int XBoxControllerDriverClass = core::RegisterObject("This object allows to control an XBox 360 Controller into Sofa.")
.add< XBoxControllerDriver >();

XBoxControllerDriver::XBoxControllerDriver()
    : Inherit()
    , d_controllerNumber(initData(&d_controllerNumber, (int)0,  "number", "ID number of the controller"))
    , d_buttonA(initData(&d_buttonA, false, "buttonA", "Button A state"))
    , d_buttonB(initData(&d_buttonB, false, "buttonB", "Button B state"))
    , d_buttonX(initData(&d_buttonX, false, "buttonX", "Button X state"))
    , d_buttonY(initData(&d_buttonY, false, "buttonY", "Button Y state"))
    , d_leftThumbX(initData(&d_leftThumbX, (short) 0, "leftThumbX", "Left Stick X value"))
    , d_leftThumbY(initData(&d_leftThumbY, (short)0, "leftThumbY", "Left Stick Y value"))
    , d_rightThumbX(initData(&d_rightThumbX, (short)0, "rightThumbX", "Right Stick X value"))
    , d_rightThumbY(initData(&d_rightThumbY, (short)0, "rightThumbY", "Right Stick Y value"))
    , d_leftTrigger(initData(&d_leftTrigger, (unsigned char)0, "leftTrigger", "Left Trigger value"))
    , d_rightTrigger(initData(&d_rightTrigger, (unsigned char)0, "rightTrigger", "Right Trigger value"))
    , m_XBoxControllerDriverImpl(nullptr)
{
    f_listening.setValue(true);
    m_XBoxControllerDriverImpl = std::make_shared<XBoxControllerDriverWindows>();

    this->addAlias(&d_controllerNumber, "id");
    d_buttonA.setReadOnly(true);
    d_buttonB.setReadOnly(true);
    d_buttonX.setReadOnly(true);
    d_buttonY.setReadOnly(true);
    d_leftThumbX.setReadOnly(true);
    d_leftThumbY.setReadOnly(true);
    d_rightThumbX.setReadOnly(true);
    d_rightThumbY.setReadOnly(true);
    d_leftTrigger.setReadOnly(true);
    d_rightTrigger.setReadOnly(true);
}

void XBoxControllerDriver::init()
{
    assert(m_XBoxControllerDriverImpl);

    m_XBoxControllerDriverImpl->setControllerNumber(d_controllerNumber.getValue());

    if (m_XBoxControllerDriverImpl->initController())
    {
        msg_info("XBoxControllerDriver::init") << "Correctly initialized.";
        d_componentState.setValue(sofa::core::objectmodel::ComponentState::Valid);
    }
    else
    {
        msg_error("XBoxControllerDriver::init") << "Error while initializing.";
        d_componentState.setValue(sofa::core::objectmodel::ComponentState::Invalid);
    }
}

void XBoxControllerDriver::fillData(const ControllerData& data)
{
    d_buttonA.setValue(data.buttonsState & ControllerData::Button::BUTTON_A);
    d_buttonB.setValue(data.buttonsState & ControllerData::Button::BUTTON_B);
    d_buttonX.setValue(data.buttonsState & ControllerData::Button::BUTTON_X);
    d_buttonY.setValue(data.buttonsState & ControllerData::Button::BUTTON_Y);

    d_leftThumbX.setValue(data.leftThumbX);
    d_leftThumbY.setValue(data.leftThumbY);
    d_rightThumbX.setValue(data.rightThumbX);
    d_rightThumbY.setValue(data.rightThumbY);

    d_leftTrigger.setValue(data.leftTrigger);
    d_rightTrigger.setValue(data.rightTrigger);
}

void XBoxControllerDriver::handleEvent(sofa::core::objectmodel::Event* event)
{
    if (sofa::simulation::AnimateBeginEvent::checkEventType(event))
    {
        if (this->isComponentStateValid())
        {
            ControllerData data;
            assert(m_XBoxControllerDriverImpl);

            m_XBoxControllerDriverImpl->getData(data);
            this->fillData(data);

            msg_info() << data;

            //if (data.buttonsState & ControllerData::BUTTON_X)
            //    m_XBoxControllerDriverImpl->rumble(10000, 0);
            //if (data.buttonsState & ControllerData::BUTTON_B)
            //    m_XBoxControllerDriverImpl->rumble(0, 10000);
            //if (data.buttonsState & ControllerData::BUTTON_Y)
            //    m_XBoxControllerDriverImpl->rumble(0, 0);
            //if (data.buttonsState & ControllerData::BUTTON_A)
            //    m_XBoxControllerDriverImpl->rumble(10000, 10000);

        }
    }
}

} // namespace sofa::component::controller
