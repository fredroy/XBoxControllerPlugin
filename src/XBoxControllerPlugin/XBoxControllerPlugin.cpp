#include <XBoxControllerPlugin/config.h>
#include <sofa/core/ObjectFactory.h>

namespace sofa::component
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
    return sofa_tostring(SOFA_TARGET);
}

const char* getModuleVersion()
{
    return sofa_tostring(XBOXCONTROLLERPLUGIN_VERSION);
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
    static std::string classes = sofa::core::ObjectFactory::getInstance()->listClassesFromTarget(sofa_tostring(SOFA_TARGET));
    return classes.c_str();
}

} // namespace sofa::component
