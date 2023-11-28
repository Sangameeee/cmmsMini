#ifndef VALWINDOW_H
#define VALWINDOW_H

#include <QDialog>

namespace Ui {
class ValWindow;
}

class ValWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ValWindow(QWidget *parent = nullptr);
    ~ValWindow();

private:
    Ui::ValWindow *ui;

};

#endif // VALWINDOW_H
