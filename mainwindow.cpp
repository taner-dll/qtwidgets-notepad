#include <QFileDialog>
#include <QMessageBox>

#if defined(QT_PRINTSUPPORT_LIB)
#include <QtPrintSupport/qtprintsupportglobal.h>
#if QT_CONFIG(printer)
#if QT_CONFIG(printdialog)
#include <QPrintDialog>
#endif // QT_CONFIG(printdialog)
#include <QPrinter>
#endif // QT_CONFIG(printer)
#endif // QT_PRINTSUPPORT_LIB



#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setCentralWidget(ui->textEdit);

//    connect(ui->saveDocument, &QAction::triggered, this, &MainWindow::save);


    // Disable menu actions for unavailable features
    #if !defined(QT_PRINTSUPPORT_LIB) || !QT_CONFIG(printer)
        ui->actionPrint->setEnabled(false);
    #endif
}

MainWindow::~MainWindow()
{
    delete ui;
}




void MainWindow::on_openDocument_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this,"Open the file");
    QFile file(fileName);

    currentFile = fileName;

    if(!file.open(QIODevice::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(this,"Warning","Cannot open the file: " + file.errorString());
        return;
    }

    setWindowTitle(fileName);

    QTextStream in(&file);

    QString text = in.readAll();

    ui->textEdit->setText(text);

    file.close();
}



void MainWindow::on_saveAsDocument_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Save as");
    QFile file(fileName);

    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Cannot save file: " + file.errorString());
        return;
    }
    currentFile = fileName;
    setWindowTitle(fileName);
    QTextStream out(&file);
    QString text = ui->textEdit->toPlainText();
    out << text;
    file.close();
//     qDebug() << "tıklandı";
}


void MainWindow::on_actionPrint_triggered()
{
#if defined(QT_PRINTSUPPORT_LIB) && QT_CONFIG(printer)
    QPrinter printDev;
    #if QT_CONFIG(printdialog)
    QPrintDialog dialog(&printDev, this);
    if (dialog.exec() == QDialog::Rejected)
        return;
    #endif // QT_CONFIG(printdialog)
    ui->textEdit->print(&printDev);
#endif // QT_CONFIG(printer)
}


void MainWindow::on_saveDocument_triggered()
{
    QString fileName;
    // If we don't have a filename from before, get one.
    if (currentFile.isEmpty()) {
        //save filename
        fileName = QFileDialog::getSaveFileName(this, "Save");
        currentFile = fileName;
    } else {
        fileName = currentFile;
    }
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Cannot save file: " + file.errorString());
        return;
    }

    setWindowTitle(fileName);
    QTextStream out(&file);
//    QString text = ui->textEdit->toPlainText();
        QString text = ui->textEdit->toHtml();
    out << text;
    file.close();
}

void MainWindow::on_toolbarNewButton_triggered()
{
    currentFile.clear();
    ui->textEdit->setText(QString());
}


void MainWindow::on_actionExit_triggered()
{
    QApplication::quit();
}


void MainWindow::on_textEdit_textChanged()
{
    if (!currentFile.isEmpty()) {
        setWindowTitle(currentFile + "*");
    }

}


void MainWindow::on_actionBold_triggered()
{

    int bold = ui->textEdit->fontWeight();

    //qDebug() << bold;

    if (bold == QFont::Bold)
        ui->textEdit->setFontWeight(QFont::Normal); //400
    else
        ui->textEdit->setFontWeight(QFont::Bold); //700

}


void MainWindow::on_actionItalic_triggered()
{


    bool italic = ui->textEdit->fontItalic();
    if (italic)
        ui->textEdit->setFontItalic(false);
    else
        ui->textEdit->setFontItalic(true);



}

void MainWindow::on_textEdit_cursorPositionChanged()
{
    QTextCursor cursor = ui->textEdit->textCursor();
    cursor.select(QTextCursor::WordUnderCursor);

    //QString text = cursor.selectedText();
    //qDebug() << text;


    //TODO bold, italic, underline checked yapılacak.

    //is bold
    bool isBold = cursor.charFormat().font().bold();
    if (isBold)
        ui->actionBold->setDisabled(true);
    else
        ui->actionBold->setDisabled(false);

    //qDebug() << ;

    //is italic


}

void MainWindow::on_actionAbout_triggered()
{
    QMessageBox::about(this, tr("About MDI"),
                    tr("The <b>Notepad</b> example demonstrates how to code a basic "
                       "text editor using QtWidgets"));
}

