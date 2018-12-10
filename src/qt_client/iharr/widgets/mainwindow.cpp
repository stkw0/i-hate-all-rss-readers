#include <iostream>

#include <QEvent>
#include <QKeyEvent>
#include <QMessageBox>
#include <nlohmann/json.hpp>

#include "feed.hpp"
#include "lib/utils.hpp"
#include "mainwindow.h"
#include "ui_mainwindow.h"

using json = nlohmann::json;

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    ui->listWidget->installEventFilter(this);

    connect(&_new_channel_wg, &NewChannel::on_feed_added, this, &MainWindow::update_feeds);
    connect(&_cfg_wg, &Configuration::on_config_change, this, &MainWindow::update_login);

    _c.connect("127.0.0.1");

    update_login();
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

void MainWindow::on_listWidget_currentItemChanged(QListWidgetItem* current,
                                                  QListWidgetItem* previous) try {
    if(current) {
        ui->listWidget_2->clear();
        auto feed = static_cast<QFeed*>(current);
        for(auto& e : feed->content()["items"]) {
            ui->listWidget_2->addItem(std::string(e["url"]).c_str());
        }
        //   ui->webEngineView->load(feed->text());
    }
} catch(std::exception& e) {
    _log->critical("{}: {}", __PRETTY_FUNCTION__, e.what());
    QMessageBox::critical(this, tr("IHARR"), tr(e.what()), QMessageBox::Ok);
}

void MainWindow::update_feeds() try {
    ui->listWidget->clear();
    for(auto& v : _feeds_cmd.getFeeds()) ui->listWidget->addItem(v);
} catch(std::exception& e) {
    _log->critical("{}: {}", __PRETTY_FUNCTION__, e.what());
    QMessageBox::critical(this, tr("IHARR"), tr(e.what()), QMessageBox::Ok);
}

void MainWindow::update_login() try {
    Config _cfg{"iharr_qt"};

    Command cmd{_c, "login"};
    cmd.addArg("username", _cfg.getUsername().toStdString());
    cmd.addArg("password", _cfg.getPassword().toStdString());
    cmd.send();

    if(cmd.getAnswer() == "") return;
    _token = cmd.getArgs().at("token");

    update_feeds();
} catch(std::exception& e) {
    _log->error("{}: {}", __PRETTY_FUNCTION__, e.what());
    QMessageBox::warning(this, tr("IHARR"), tr(e.what()), QMessageBox::Ok);
}

void MainWindow::on_listWidget_customContextMenuRequested(const QPoint& pos) {
    std::cout << "TEST" << std::endl;
}

bool MainWindow::eventFilter(QObject* obj, QEvent* event) {
    if(event->type() == QEvent::KeyPress) {
        QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);
        if(keyEvent->key() == Qt::Key_Delete) {
            auto current = ui->listWidget->currentRow();
            auto item = ui->listWidget->item(current);
            _feeds_cmd.deleteFeed(item->text().toStdString());
            ui->listWidget->takeItem(current);
        }
        return true;
    } else {
        return QObject::eventFilter(obj, event);
    }
}

void MainWindow::on_listWidget_2_currentItemChanged(QListWidgetItem* current,
                                                    QListWidgetItem* previous) {
    if(current) ui->webEngineView->load(current->text());
}
