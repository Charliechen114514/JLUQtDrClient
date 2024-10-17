#ifndef HELPINFO_H
#define HELPINFO_H
#include <QString>
class HelpInfo {
public:
    static constexpr const char* helpPath =
        ":/doc/Documentations/Help Documentations.md";
    static QString gainHelpMarkDown(const char* path = helpPath);
};

#endif  // HELPINFO_H
