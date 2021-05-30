#ifndef API_HPP
#define API_HPP

#ifdef _WIN32
    #ifdef ENGINE_BUILD_SHARED
        #define ENGINE_API __declspec(dllexport)
    #else
        #define ENGINE_API __declspec(dllexport)
    #endif
#else
    #error Engine Supports Only Windows
#endif

#endif
