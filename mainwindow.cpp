#include "mainwindow.h"
#include "./ui_mainwindow.h"
//#include "valwindow.h"
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QFile>
#include <QTextStream>
#include <QInputDialog>
#include <QFileDialog>
#include <QDir>
#include <QPainter>
#include <QtPrintSupport/QPrintDialog>
#include <QPageSize>
#include <QHeaderView>
#include <QFontMetrics>
#include <QCoreApplication>
#include <QListWidget>
#include <QFileInfo>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow),
    currentTableName("")
{
    ui->setupUi(this);
    TableWidgetDisplay();

    // Connect the header click event to the on_headerClicked slot
    connect(ui->tableWidget->horizontalHeader(), SIGNAL(sectionClicked(int)), this, SLOT(on_headerClicked(int)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::TableWidgetDisplay()
{
    this->setWindowTitle("Table");
    QTableWidget *table = ui->tableWidget;  // creating a table object
    // setting up row number and columns.
    table->setRowCount(48);

    table->setColumnCount(5);

    // for row topics
    QStringList hlabels;
    hlabels << "Name" << "Roll no" << "Marks" << "Assignments" << "Assessments" << "Practicals";
    table->setHorizontalHeaderLabels(hlabels);

    // showing table in a whole windows
    this->setCentralWidget(table);
    buttonDisplays();
}
void MainWindow::buttonDisplays()
{
    ui->pushButton->hide();
    ui->loadButton->hide();

    QTableWidget *table = ui->tableWidget;
    QPushButton *button = ui->pushButton;
    QPushButton *lbutton = ui->loadButton;
    QLineEdit *rowEdit = ui->lineEditR;
    rowEdit->setPlaceholderText("No of rows");

    QPushButton *addRowButton = ui->addRowButton;
    QPushButton *addColumnButton = ui->columnAddButton;

    QLineEdit *columnEdit = ui->lineEditC;
    columnEdit->setPlaceholderText("Write Heading title..");

    QPushButton *subColumnButton = ui->buttonSub;


    QVBoxLayout *rowLayout = new QVBoxLayout;
    rowLayout->addWidget(addRowButton);
    rowLayout->addWidget(rowEdit);

    QHBoxLayout *columnHLayout = new QHBoxLayout;
    columnHLayout->addWidget(addColumnButton);
    columnHLayout->addWidget(subColumnButton);

    QVBoxLayout *columnLayout = new QVBoxLayout;
    columnLayout->addLayout(columnHLayout);
    columnLayout->addWidget(columnEdit);

    QHBoxLayout *hlayout = new QHBoxLayout;
    hlayout->addWidget(button);
    hlayout->addWidget(lbutton);
    hlayout->addLayout(rowLayout);
    hlayout->addLayout(columnLayout);


    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(table);
    layout->addLayout(hlayout);


    QWidget *centralWidget = new QWidget;
    centralWidget->setLayout(layout);

    this->setCentralWidget(centralWidget);

    // Connect signals and slots for the buttons
    //    connect(addRowButton, &QPushButton::clicked, this, &MainWindow::on_addRowButton_clicked);
    //    connect(addColumnButton, &QPushButton::clicked, this, &MainWindow::on_columnAddButton_clicked);
    //    connect(subColumnButton, &QPushButton::clicked, this, &MainWindow::on_buttonSub_clicked);
    //    connect(clearButton, &QPushButton::clicked, this, &MainWindow::on_clearButton_clicked);
    //    connect(calButton, &QPushButton::clicked, this, &MainWindow::on_calButton_clicked);
    //    connect(button, &QPushButton::clicked, this, &MainWindow::on_pushButton_clicked);
    //    connect(lbutton, &QPushButton::clicked, this, &MainWindow::on_loadButton_clicked);

}
void MainWindow::on_headerClicked(int column)
{
    QTableWidget *table = ui->tableWidget;

    // Get the column header name
    QString columnHeader = table->horizontalHeaderItem(column)->text();

    // Ask the user for the original and conversion total scores
    bool ok;
    int originalTotal = QInputDialog::getInt(this, "Enter Original Total Score", "Enter the original total score for column " + columnHeader + ":", 40, 0, 100, 1, &ok);

    if (!ok)
        return;  // User canceled the input

    int conversionTotal = QInputDialog::getInt(this, "Enter Conversion Total Score", "Enter the conversion total score for column " + columnHeader + ":", 20, 0, 100, 1, &ok);

    if (!ok)
        return;  // User canceled the input

    // Perform the conversion for the entire column
    convertColumn(column, originalTotal, conversionTotal, columnHeader);
}
void MainWindow::convertColumn(int columnIndex, int originalTotal, int conversionTotal, const QString &columnName)
{
    QTableWidget *table = ui->tableWidget;

    // Calculate the scaling factor
    static_cast<double>(conversionTotal) / originalTotal;

    // Iterate through the values in the clicked column and perform the conversion
    for (int row = 0; row < table->rowCount(); ++row)
    {
        QTableWidgetItem *item = table->item(row, columnIndex);
        if (item)
        {
            bool isNumeric;
            double originalValue = item->text().toDouble(&isNumeric);
            if (isNumeric)
            {
                // Perform the conversion using the provided formula
                double convertedValue = (originalValue / originalTotal) * conversionTotal;
                item->setText(QString::number(convertedValue));
            }
        }
    }

    QMessageBox::information(this, "Conversion Completed", QString("Values in the '%1' column converted based on original total %2 and conversion total %3.").arg(columnName).arg(originalTotal).arg(conversionTotal));
}
void MainWindow::on_pushButton_clicked()
{
    storeTableValues();
}

void MainWindow::on_loadButton_clicked()
{
    showAllTables();
}

void MainWindow::on_addRowButton_clicked()
{
    rowManipulation();
}

void MainWindow::on_columnAddButton_clicked()
{
    columnManipulation();
}

void MainWindow::on_buttonSub_clicked()
{
    columnRemover();
}



void MainWindow::rowManipulation()
{
    QTableWidget *table = ui->tableWidget;
    QLineEdit *rowEdit = ui->lineEditR;
    QString rowInput = rowEdit->text();
    QString inputText = ui->lineEditR->text();

    bool ok;
    inputText.toInt(&ok);

    if (rowInput.isEmpty())
    {
        QMessageBox::warning(this, "Error", "Please Enter a value");
    }
    else if (!ok)
    {
        QMessageBox::warning(this, "Error", "Please Enter a Numeric value");
    }
    else
    {
        QFile rowFile("row_value.txt");
        if (rowFile.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            // Create a QTextStream associated with the file
            QTextStream out(&rowFile);

            // Write the QLineEdit text to the file
            out << rowInput;

            // Close the file
            rowFile.close();
        }
        else
        {
            qDebug() << "Error: Could not open the file for writing.";
        }

        int rowValues = rowInput.toInt();
        int currentRowCount = table->rowCount();

        if (rowValues < currentRowCount)
        {
            // Check if there is any data in the rows that will be removed
            bool hasDataInRemovedRows = false;
            for (int row = rowValues; row < currentRowCount; ++row)
            {
                for (int col = 0; col < table->columnCount(); ++col)
                {
                    QTableWidgetItem *item = table->item(row, col);
                    if (item && !item->text().isEmpty())
                    {
                        hasDataInRemovedRows = true;
                        break;
                    }
                }
                if (hasDataInRemovedRows)
                {
                    break;
                }
            }

            if (hasDataInRemovedRows)
            {
                QMessageBox::StandardButton reply = QMessageBox::question(this, "Warning", "Decreasing Row count may cause loss of data. Do you want to proceed?", QMessageBox::Yes | QMessageBox::No);
                if (reply == QMessageBox::Yes)
                {
                    table->setRowCount(rowValues);
                }
                else
                {
                    qDebug() << "No of row wasn't reduced!!!";
                }
            }
            else
            {
                table->setRowCount(rowValues);
            }
        }
        else
        {
            table->setRowCount(rowValues);
        }
    }
}

void MainWindow::columnManipulation()
{
    QTableWidget *table = ui->tableWidget;
    QLineEdit *columnEdit = ui->lineEditC;
    QString columnInput = columnEdit->text();
    int columnNo = table->columnCount();
    if (columnInput.isEmpty())
    {
        QMessageBox::warning(this, "Warning", "Column heading cannot be empty");
        return;
    }
    QStringList oldTitle;
    for (int col = 0; col < columnNo; ++col)
    {
        oldTitle << table->horizontalHeaderItem(col)->text();
    }
    table->setColumnCount(columnNo + 1);
    oldTitle << columnInput;
    table->setHorizontalHeaderLabels(oldTitle);
}

void MainWindow::columnRemover()
{
    QTableWidget *table = ui->tableWidget;
    QLineEdit *columnEdit = ui->lineEditC;
    QString columnName = columnEdit->text();

    int columnToRemove = -1;

    // Find the column index based on the column header (case-insensitive)
    for (int col = 0; col < table->columnCount(); ++col) {
        if (table->horizontalHeaderItem(col)->text().compare(columnName, Qt::CaseInsensitive) == 0) {
            columnToRemove = col;
            break;
        }
    }

    if (columnToRemove == -1) {
        // The specified column header was not found
        QMessageBox::warning(this, "Error", "Column not found. Please enter a valid column header.");
    } else {
        // Remove the specified column
        table->removeColumn(columnToRemove);
    }
}


//void MainWindow::removeAll()
//{
//    QWidget *centralWidget = this->centralWidget();
//    centralWidget->hide();
//}

//void MainWindow::calculateValues()
//{
//    QTableWidget *table = ui->tableWidget;

//    for (int row = 0; row < table->rowCount(); ++row) {
//        for (int col = 0; col < table->columnCount(); ++col) {
//            QTableWidgetItem *item = table->item(row, col);
//            QString headerText = table->horizontalHeaderItem(col)->text().toLower();

//            if ((headerText == "marks" || headerText == "assessments") && isInteger(item->text())) {
//                int originalValue = item->text().toInt();
//                item->setText(QString::number(originalValue / 10));
//            }
//        }
//    }

//    QMessageBox::information(this, "Calculation Completed", "Values under 'Marks' and 'Assessments' headers reduced by 10 times.");
//}

bool MainWindow::isInteger(const QString &text)
{
    bool isNumeric;
    text.toInt(&isNumeric);
    return isNumeric;
}

void MainWindow::storeTableValues()
{
    QTableWidget *table = ui->tableWidget;
    QString fileName = getSaveFileName();
    if (fileName.isEmpty())
    {
        return;  // User canceled the operation
    }

    QFile file(fileName);

    // Check for empty cells and set red border
    for (int row = 0; row < table->rowCount(); ++row) {
        for (int col = 0; col < table->columnCount(); ++col) {
            QTableWidgetItem *item = table->item(row, col);
            if (!item || item->text().isEmpty()) {
                table->setItem(row, col, new QTableWidgetItem());
                table->item(row, col)->setBackground(QBrush(Qt::red));
                table->item(row, col)->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsEnabled);
            } else {
                table->item(row, col)->setBackground(QBrush(Qt::white)); // Reset background color
                table->item(row, col)->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsEnabled);
            }
        }
    }

    // Continue with saving if no empty cells are found
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);

        // Write header
        QStringList headers;
        for (int col = 0; col < table->columnCount(); ++col) {
            headers << table->horizontalHeaderItem(col)->text();
        }
        out << headers.join(",") << "\n";

        // Write data
        for (int row = 0; row < table->rowCount(); ++row) {
            QStringList rowData;
            for (int col = 0; col < table->columnCount(); ++col) {
                QTableWidgetItem *item = table->item(row, col);
                if (item) {
                    rowData << item->text();
                }
            }
            out << rowData.join(",") << "\n";
        }

        file.close();
        QMessageBox::information(this, "Table Values Saved", "The table values were successfully stored.");
    } else {
        QMessageBox::critical(this, "Error Saving Table Values", "An error occurred while trying to save the table values to a file.");
    }
}

void MainWindow::loadTableValues()
{
    QString fileName = getOpenFileName();
    if (fileName.isEmpty())
    {
        QMessageBox::warning(this,"No filename","please give a filename."); // User canceled the operation
    }

    QTableWidget *table = ui->tableWidget;
    QFile file(fileName);

    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);

        // Read header
        QStringList headers = in.readLine().split(",");
        table->setColumnCount(headers.size());
        table->setHorizontalHeaderLabels(headers);

        // Clear existing data
        table->clearContents();
        table->setRowCount(0);

        // Read data
        while (!in.atEnd()) {
            QStringList rowData = in.readLine().split(",");
            int row = table->rowCount();
            table->insertRow(row);
            for (int col = 0; col < headers.size(); ++col) {
                if (col < rowData.size()) {
                    QTableWidgetItem *item = new QTableWidgetItem(rowData.at(col));
                    table->setItem(row, col, item);
                } else {
                    QTableWidgetItem *item = new QTableWidgetItem("");
                    table->setItem(row, col, item);
                }
            }
        }

        file.close();
        QMessageBox::information(this, "Table Values Loaded", "The table values were successfully loaded.");
    } else {
        QMessageBox::critical(this, "Error Loading Table Values", "An error occurred while trying to load the table values from the file.");
    }
}

void MainWindow::showAllTables()
{
    QDir dir("tables");
    QStringList fileNames = dir.entryList(QStringList("*.csv"));

    if (fileNames.isEmpty()) {
        QMessageBox::information(this, "No Tables Found", "No tables found in the 'tables' directory.");
        return;
    }

    QTableWidget tempTable;
    QStringList tableNames;

    for (const QString &fileName : fileNames) {
        QFile file(dir.path() + "/" + fileName);

        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream in(&file);

            // Read header
            QStringList headers = in.readLine().split(",");
            tempTable.setColumnCount(headers.size());
            tempTable.setHorizontalHeaderLabels(headers);

            // Clear existing data
            tempTable.clearContents();
            tempTable.setRowCount(0);

            // Read data
            while (!in.atEnd()) {
                QStringList rowData = in.readLine().split(",");
                int row = tempTable.rowCount();
                tempTable.insertRow(row);
                for (int col = 0; col < headers.size(); ++col) {
                    if (col < rowData.size()) {
                        QTableWidgetItem *item = new QTableWidgetItem(rowData.at(col));
                        tempTable.setItem(row, col, item);
                    } else {
                        QTableWidgetItem *item = new QTableWidgetItem("");
                        tempTable.setItem(row, col, item);
                    }
                }
            }

            file.close();

            tableNames << fileName + " (Preview)";
        } else {
            QMessageBox::critical(this, "Error Loading Table Values", "An error occurred while trying to load the table values from the file.");
            return;
        }
    }

    bool ok;
    QString chosenTable = QInputDialog::getItem(this, "Choose a Table", "Select a table to load:", tableNames, 0, false, &ok);

    if (ok && !chosenTable.isEmpty()) {
        currentTableName = chosenTable;
        loadTableValues();
    }
}

QString MainWindow::getSaveFileName()
{
    QString directoryPath = QDir::currentPath() + "/tables";
    QDir directory(directoryPath);

    if (!directory.exists()) {
        if (!directory.mkpath(".")) {
            QMessageBox::critical(this, "Error Creating Directory", "Failed to create the 'tables' directory.");
            return "";
        }
    }

    QString fileName = QFileDialog::getSaveFileName(this, "Save Table", directoryPath, "CSV Files (*.csv)");

    if (!fileName.endsWith(".csv", Qt::CaseInsensitive)) {
        fileName += ".csv";
    }

    return fileName;
}

QString MainWindow::getOpenFileName()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Load Table", QDir::currentPath() + "/tables", "CSV Files (*.csv);;All Files (*)");

    if (fileName.isEmpty()) {
        QMessageBox::warning(this, "No filename", "Please select a file.");
    }

    return fileName;
}

void MainWindow::on_actionSave_triggered()
{
    QTableWidget *table = ui->tableWidget;

    QStringList previousFiles; // Populate this with previous file names

    // Additional customization: Make user input case-insensitive
    QString fileName = showSaveDialog(previousFiles).toLower();

    if (fileName.isEmpty())
    {
        return;  // User canceled the operation
    }

    // Ensure that the file has the .csv extension
    if (!fileName.endsWith(".csv"))
    {
        fileName += ".csv";
    }

    // Check for empty cells and set red border
    for (int row = 0; row < table->rowCount(); ++row)
    {
        for (int col = 0; col < table->columnCount(); ++col)
        {
            QTableWidgetItem *item = table->item(row, col);
            if (!item || item->text().isEmpty())
            {
                table->setItem(row, col, new QTableWidgetItem());
                table->item(row, col)->setBackground(QBrush(Qt::red));
                table->item(row, col)->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsEnabled);
            }
            else
            {
                table->item(row, col)->setBackground(QBrush(Qt::white)); // Reset background color
                table->item(row, col)->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsEnabled);
            }
        }
    }

    // Continue with saving if no empty cells are found
    QFile file(fileName);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream out(&file);

        // Write header
        QStringList headers;
        for (int col = 0; col < table->columnCount(); ++col)
        {
            headers << table->horizontalHeaderItem(col)->text();
        }
        out << headers.join(",") << "\n";

        // Write data
        for (int row = 0; row < table->rowCount(); ++row)
        {
            QStringList rowData;
            for (int col = 0; col < table->columnCount(); ++col)
            {
                QTableWidgetItem *item = table->item(row, col);
                if (item)
                {
                    rowData << item->text();
                }
            }
            out << rowData.join(",") << "\n";
        }

        file.close();
        QMessageBox::information(this, "Table Values Saved", "The table values were successfully stored.");
    }
    else
    {
        QMessageBox::critical(this, "Error Saving Table Values", "An error occurred while trying to save the table values to a file: " + file.errorString());
    }
}


QString MainWindow::showSaveDialog(const QStringList &previousFiles)
{
    bool ok;
    return QInputDialog::getItem(this, "Save File",
                                 "Select a file or enter a new file name:",
                                 previousFiles, 0, false, &ok);
}

QString MainWindow::showNewFileDialog()
{
    bool ok;
    return QInputDialog::getText(this, "Save As New File",
                                 "Enter a new file name:", QLineEdit::Normal, "", &ok);
}

void MainWindow::on_actionLoad_triggered()
{
    QString tableName = QInputDialog::getText(this, "Enter Table Name", "Enter the name of the Faculty:");

    if (tableName.isEmpty()) {
        return;  // User canceled the operation
    }

    QString fileName = QDir::currentPath() + "/" + tableName + ".csv";

    if (!QFile::exists(fileName)) {
        QMessageBox::critical(this, "Error", "File not found. Please enter a valid table name.");
        return;
    }

    QTableWidget *table = ui->tableWidget;

    // Clear existing data
    table->clearContents();
    table->setRowCount(0);

    QFile file(fileName);

    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);

        // Read header
        QStringList headers = in.readLine().split(",");
        table->setColumnCount(headers.size());
        table->setHorizontalHeaderLabels(headers);

        // Read data
        while (!in.atEnd()) {
            QStringList rowData = in.readLine().split(",");
            int row = table->rowCount();
            table->insertRow(row);
            for (int col = 0; col < headers.size(); ++col) {
                if (col < rowData.size()) {
                    QTableWidgetItem *item = new QTableWidgetItem(rowData.at(col));
                    table->setItem(row, col, item);
                } else {
                    QTableWidgetItem *item = new QTableWidgetItem("");
                    table->setItem(row, col, item);
                }
            }
        }

        file.close();
        QMessageBox::information(this, "Table Values Loaded", "The table values from file " + QFileInfo(fileName).fileName() + " were successfully loaded.");
    } else {
        QMessageBox::critical(this, "Error Loading Table Values", "An error occurred while trying to load the table values from the file.");
    }
}


void MainWindow::on_actionPrint_triggered()
{
    QPrinter printer;
    QPrintDialog dialog(&printer, this);
    dialog.setWindowTitle("Print Table");

    if (dialog.exec() == QDialog::Rejected)
        return;

    // Set the number of copies to 1
    printer.setCopyCount(1);

    QPainter painter;
    painter.begin(&printer);

    QTableWidget *table = ui->tableWidget;

    // Get the A4 page size
    QPageSize pageSize(QPageSize::A4);
    QSizeF printableSize = pageSize.size(QPageSize::Point);

    // Calculate total width and height of the table
    int totalWidth = 0;
    int totalHeight = 0;

    for (int col = 0; col < table->columnCount(); ++col)
        totalWidth += table->columnWidth(col);

    for (int row = 0; row < table->rowCount(); ++row)
        totalHeight += table->rowHeight(row);

    // Calculate the scale factor to fit the table into the printable area
    qreal scaleX = printableSize.width() / qreal(totalWidth);
    qreal scaleY = printableSize.height() / qreal(totalHeight);
    qreal scale = qMin(scaleX, scaleY);

    // Set the transformation matrix to scale the painter
    painter.scale(scale, scale);

    // Adjust font size based on the scaling factor
    QFont font = painter.font();
    font.setPointSizeF(font.pointSizeF() * scale);
    painter.setFont(font);

    // Calculate maximum font size to fit within cell width and height
    QFontMetrics metrics(font);
    int maxFontSize = qMin(metrics.height(), table->columnWidth(0) / table->horizontalHeader()->count());

    // Set the font size to the maximum calculated font size
    font.setPointSize(maxFontSize);
    painter.setFont(font);

    int yOffset = 0;

    // Draw table heading on each page
    for (int col = 0; col < table->columnCount(); ++col) {
        if (!table->isColumnHidden(col) && table->columnWidth(col) > 0) {
            painter.drawText(QRect(table->columnViewportPosition(col), yOffset, table->columnWidth(col), table->rowHeight(0)),
                             Qt::AlignCenter, table->horizontalHeaderItem(col)->text());
        }
    }

    yOffset += table->rowHeight(0);

    // Draw each cell on the current page
    for (int row = 0; row < table->rowCount(); ++row) {
        for (int col = 0; col < table->columnCount(); ++col) {
            if (!table->isColumnHidden(col) && table->columnWidth(col) > 0) {
                painter.drawText(QRect(table->columnViewportPosition(col), yOffset, table->columnWidth(col), table->rowHeight(row)),
                                 Qt::AlignCenter | Qt::AlignVCenter, table->item(row, col) ? table->item(row, col)->text() : "");

                // Draw cell borders
                painter.drawRect(QRect(table->columnViewportPosition(col), yOffset, table->columnWidth(col), table->rowHeight(row)));
            }
        }
        yOffset += table->rowHeight(row);
    }

    painter.end();
}

