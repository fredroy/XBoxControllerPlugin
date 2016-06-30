#ifndef XBOXCONTROLLERPLUGIN_H
#define XBOXCONTROLLERPLUGIN_H


#include <sofa/helper/system/config.h>

#ifndef WIN32
	#define SOFA_EXPORT_DYNAMIC_LIBRARY 
	#define SOFA_IMPORT_DYNAMIC_LIBRARY
	#define SOFA_XBOXCONTROLLERPLUGIN_API
#else
	#ifdef SOFA_BUILD_XBOXCONTROLLERPLUGIN
		#define SOFA_EXPORT_DYNAMIC_LIBRARY __declspec( dllexport )
		#define SOFA_XBOXCONTROLLERPLUGIN_API SOFA_EXPORT_DYNAMIC_LIBRARY
	#else
		#define SOFA_IMPORT_DYNAMIC_LIBRARY __declspec( dllimport )
		#define SOFA_XBOXCONTROLLERPLUGIN_API SOFA_IMPORT_DYNAMIC_LIBRARY
	#endif
#endif

/** \mainpage
  This is a the starting page of the plugin documentation.
  */

#endif // XBOXCONTROLLERPLUGIN_H
