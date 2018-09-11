#include <iostream>

#include <nlohmann/json.hpp>

#include "mainwindow.h"
#include "ui_mainwindow.h"

using json = nlohmann::json;

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    _c.connect("127.0.0.1");

    Config _cfg{"iharr_qt"};

    {
        Command cmd{_c, "login"};
        cmd.addArg("username", _cfg.getUsername().toStdString());
        cmd.addArg("password", _cfg.getPassword().toStdString());
        cmd.send();

        if(cmd.getAnswer() != "") _token = cmd.getArgs().at("token");
    }
    {
        Command cmd{_c, "get_feeds"};
        cmd.addArg("username", _cfg.getUsername().toStdString());
        cmd.send();
    }
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_actionConfiguration_triggered() {
    _cfg_wg.show();
}

void MainWindow::on_actionChannel_triggered() {
    _new_channel_wg.show();
}
