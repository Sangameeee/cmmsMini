#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_loadButton_clicked();

private:
    Ui::MainWindow *ui;
    void TableWidgetDisplay();
    void storeTableValues();
    void loadTableValues();
//private slots:
//    void on_tableWidget_cellClicked(int row, int column);
};

#endif // MAINWINDOW_H
