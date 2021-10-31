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
    void on_openDocument_triggered();
    void on_saveAsDocument_triggered();
    void on_actionPrint_triggered();
    void on_saveDocument_triggered();
    void on_toolbarNewButton_triggered();
    void on_actionExit_triggered();
    void on_textEdit_textChanged();
    void on_actionBold_triggered();
    void on_actionItalic_triggered();

    void on_textEdit_cursorPositionChanged();

    void on_actionAbout_triggered();

private:
    Ui::MainWindow *ui;
    QString currentFile;
};
#endif // MAINWINDOW_H
