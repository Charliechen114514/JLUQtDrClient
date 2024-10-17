#ifndef UILOADER_H
#define UILOADER_H
#include <QString>
#include <QtClassHelperMacros>
class UiFileError;

class UiLoader {
public:
    Q_DISABLE_COPY(UiLoader);
    UiLoader() = default;
    std::optional<QString> fromUiFile(const QString& path);
    bool                   ownsError() const;
    QString                errorString() const;

private:
    std::shared_ptr<UiFileError> uiFileError{nullptr};
};

#endif  // UILOADER_H
