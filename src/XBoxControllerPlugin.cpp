#include "XBoxControllerPlugin.h"

#include <iostream>

namespace sofa
{

namespace component
{

//Here are just several convenient functions to help user to know what contains the plugin

extern "C" {
    SOFA_XBOXCONTROLLERPLUGIN_API void initExternalModule();
    SOFA_XBOXCONTROLLERPLUGIN_API const char* getModuleName();
    SOFA_XBOXCONTROLLERPLUGIN_API const char* getModuleVersion();
    SOFA_XBOXCONTROLLERPLUGIN_API const char* getModuleLicense();
    SOFA_XBOXCONTROLLERPLUGIN_API const char* getModuleDescription();
    SOFA_XBOXCONTROLLERPLUGIN_API const char* getModuleComponentList();
}

void initExternalModule()
{
    static bool first = true;
    //if (first)
    {
        first = false;

    }
}

const char* getModuleName()
{
    return "XBoxControllerPlugin";
}

const char* getModuleVersion()
{
    return "0.1";
}

const char* getModuleLicense()
{
    return "LGPL";
}


const char* getModuleDescription()
{
    return "TODO: XBoxControllerPlugin code";
}

const char* getModuleComponentList()
{
    /// string containing the names of the classes provided by the plugin
    return "XBoxControllerDriver";
}



}

}

/// Use the SOFA_LINK_CLASS macro for each class, to enable linking on all platforms
//SOFA_LINK_CLASS(XBoxControllerDriver)


