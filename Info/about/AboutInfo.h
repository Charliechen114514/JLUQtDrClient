#ifndef ABOUTINFO_H
#define ABOUTINFO_H
#include <QString>
class QWidget;
class AboutInfo {
    static constexpr const char*          NAME          = __NAME;
    static constexpr const unsigned short MINOR_VERSION = __MINOR_VERISON;
    static constexpr const unsigned short MAJOR_VERISON = __MAJOR_VERSION;
    static constexpr const char*          CORE_REPO_ADDR =
        "https://github.com/Dessera/cygnus-rs";
    static constexpr const char* CORE_AUTHOR = "https://github.com/Dessera";
    static constexpr const char* THIS_REPO_NAME =
        "https://github.com/Charliechen114514/JLUQtDrClient";
    static constexpr const char* THIS_AUTHOR =
        "https://github.com/Charliechen114514";

    static constexpr const char* INFOS = "本软件使用Qt6 Community框架开发";

    struct AboutInfoFactory {
        static QString createInfo();
        static QString createVersion();
        static QString createRepoInfo();
    };

public:
    static void showAbout(QWidget* bindings = nullptr);
};

#endif  // ABOUTINFO_H
