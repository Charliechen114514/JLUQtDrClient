#ifndef CONSTPARAMS_H
#define CONSTPARAMS_H

struct ParamsConst {
    static constexpr const char* UiLoaderQSS =
        ":/qdarkstyle/light/lightstyle.qss";
    static constexpr const char* _DIR  = "core";
    static constexpr const char* _FILE = "cygnus-x86_64-windows-gnu.exe";
    static constexpr const char* _MIDDLE_USR_CONFIG = "middlewares.usr";
#ifdef CLEAR_LOG_IF_REACH_LIMITATION
    static constexpr unsigned int MAX_ALLOWED_BUFFER_FOR_CLEAR =
        __CLEAR_LIMITATION;
#endif
};

#endif  // CONSTPARAMS_H
