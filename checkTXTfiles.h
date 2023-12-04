#ifndef CHECKTXTFILES_H
#define CHECKTXTFILES_H

#include <QObject>

class CheckTXTFiles : public QObject {
    Q_OBJECT

public:
    explicit CheckTXTFiles(QObject *parent = nullptr);

    bool isPasswordFileEmpty();
    bool isUsernameFileEmpty();
};

#endif // CHECKTXTFILES_H
