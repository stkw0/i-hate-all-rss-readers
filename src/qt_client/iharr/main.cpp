#include <iostream>

#include <QApplication>
#include <QMessageBox>

#include "widgets/mainwindow.h"

int main(int argc, char* argv[]) {
    QApplication a(argc, argv);

    try {
        MainWindow w;
        w.show();
        return a.exec();
    } catch(std::exception& e) {
        std::cout << e.what() << std::endl;
        QMessageBox::critical(a.activeWindow(), "IHARR", e.what(), QMessageBox::Ok);
    } catch(...) {
        std::cout << "Unknown error\n";
        QMessageBox::critical(a.activeWindow(), "IHARR", "Unknown error", QMessageBox::Ok);
    }
}
