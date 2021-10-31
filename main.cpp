#include "mainwindow.h"


#include <QApplication>
#include <QFile>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //QFile file(":/combinear.qss");
    //QFile file(":/adaptic.qss");
    //QFile file(":/style/Ubuntu.qss");
    //QFile file(":/style/ManjaroMix.qss");

    //QFile file(":/style/Chatbee.qss");
    //QFile file(":/style/material.qss");

//    file.open(QFile::ReadOnly);

//    QString styleSheet {
//        QLatin1String(file.readAll())
//    };

//    a.setStyleSheet(styleSheet);



    MainWindow w;
    w.show();
    return a.exec();
}
