#ifndef CONFIG_H
#define CONFIG_H

#if defined(__linux__) || defined(__linux) || defined(linux)
    #define JOSZVA_SYS_LINUX
#elif defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(_WIN64)
    #define JOSZVA_SYS_WINDOWS
#endif

#if defined(JOSZVA_SYS_LINUX)
    #include <X11/Xatom.h>
    #include <X11/Xlib.h>
    #include <X11/Xutil.h>
#elif defined(JOSZVA_SYS_WINDOWS)
    #include <Windows.h>

    #define JOSZVA_EXPORT __declspec(dllexport)
#endif
#endif