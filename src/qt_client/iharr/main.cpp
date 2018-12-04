#include <iostream>

#include "widgets/mainwindow.h"
#include <QApplication>

int main(int argc, char* argv[]) {
    QApplication a(argc, argv);

    try {
        MainWindow w;
        w.show();
        return a.exec();
    } catch(std::exception& e) {
        std::cout << e.what() << std::endl;
    } catch(...) {
        std::cout << "Unknown error\n";
    }
}
