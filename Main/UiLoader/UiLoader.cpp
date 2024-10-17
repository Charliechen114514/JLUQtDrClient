#include "UiLoader.h"
#include <QFile>

class UiFileError {
public:
    QString _gainErrorString() const {
        return errorString;
    }

    void setError(const QFile::FileError e, const QString s) {
        errorIndex  = e;
        errorString = std::move(s);
    }

    bool ownsError() const {
        return errorIndex != QFile::FileError::NoError;
    }

    static constexpr const char* NO_ERROR_UI_FILE = "No Error Current now";

private:
    QString          errorString{NO_ERROR_UI_FILE};
    QFile::FileError errorIndex{QFile::FileError::NoError};
};

std::optional<QString> UiLoader::fromUiFile(const QString& path) {
    QFile f(path);
    uiFileError = std::make_unique<UiFileError>();
    f.open(QIODevice::ReadOnly);
    if (!f.isOpen()) {
        uiFileError->setError(f.error(), f.errorString());
        return {};
    }
    return {f.readAll()};
}

bool UiLoader::ownsError() const {
    return uiFileError && uiFileError->ownsError();
}

QString UiLoader::errorString() const {
    if (!uiFileError) return UiFileError::NO_ERROR_UI_FILE;
    return uiFileError->_gainErrorString();
}
