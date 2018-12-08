#include <iostream>

#include <QEvent>
#include <QKeyEvent>
#include <nlohmann/json.hpp>

#include "mainwindow.h"
#include "ui_mainwindow.h"

using json = nlohmann::json;

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    ui->listWidget->installEventFilter(this);

    connect(&_new_channel_wg, &NewChannel::on_feed_added, this, &MainWindow::update_feeds);

    _c.connect("127.0.0.1");

    Config _cfg{"iharr_qt"};

    {
        Command cmd{_c, "login"};
        cmd.addArg("username", _cfg.getUsername().toStdString());
        cmd.addArg("password", _cfg.getPassword().toStdString());
        cmd.send();

        if(cmd.getAnswer() == "") return;
        _token = cmd.getArgs().at("token");
    }

    for(auto& v : _feeds_cmd.getFeeds()) ui->listWidget->addItem(v.c_str());
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
                                                  QListWidgetItem* previous) {
    if(current) ui->webEngineView->load(current->text());
}

void MainWindow::update_feeds() {
    ui->listWidget->clear();
    for(auto& v : _feeds_cmd.getFeeds()) ui->listWidget->addItem(v.c_str());
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
