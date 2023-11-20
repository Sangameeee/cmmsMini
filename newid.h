#ifndef NEWID_H
#define NEWID_H

#include <QDialog>

namespace Ui {
class NewID;
}

class NewID : public QDialog
{
    Q_OBJECT

public:
    explicit NewID(QWidget *parent = nullptr);
    ~NewID();

private slots:
    void on_pushButton_clicked();

private:
    Ui::NewID *ui;
};

#endif // NEWID_H
