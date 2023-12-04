#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include"secwindow.h"
#include<QtPrintSupport/QPrinter>
#include<QtPrintSupport/QPrintDialog>

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

    void on_addRowButton_clicked();

    void on_columnAddButton_clicked();

    void on_buttonSub_clicked();

//    void on_clearButton_clicked();

//    void on_calButton_clicked();

    void on_headerClicked(int column);
    void convertColumn(int columnIndex, int originalTotal, int conversionTotal, const QString &columnName);

    void on_actionSave_triggered();

    void on_actionLoad_triggered();

    void on_actionPrint_triggered();

    void on_clear_triggered();

    void on_actionQt_Version_triggered();

    void on_calculateButton_clicked();

private:
    Ui::MainWindow *ui;
    //secWindow *secwindow;
    void TableWidgetDisplay();
    void buttonDisplays();
    void storeTableValues();
    void loadTableValues();
    void rowManipulation();
    void columnManipulation();
    void columnRemover();
    void removeAll();
    void calculateValues();
    bool isInteger(const QString&);
    void showAllTables();
    QString getSaveFileName();
    QString getOpenFileName();
    QString currentTableName;
    int totalColumnIndex;
    QStringList parseExpression(const QString &expression);
    int findOrCreateResultColumn(const QStringList &columnHeaders);
    void calculateResult(const QString &expression);
    double evaluateExpressionForRow(const QString &expression, int row);
    QString resultColumnName;

//private slots:
//    void on_tableWidget_cellClicked(int row, int column);
};

#endif // MAINWINDOW_H
