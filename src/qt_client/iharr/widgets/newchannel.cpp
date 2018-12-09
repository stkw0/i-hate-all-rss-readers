#include <iostream>
#include <stdexcept>

#include <QMessageBox>

#include "comm.h"
#include "lib/utils.hpp"
#include "newchannel.h"
#include "ui_newchannel.h"

NewChannel::NewChannel(FeedsCommands& f, QWidget* parent)
    : _feeds_cmd{f}, QDialog(parent), ui(new Ui::NewChannel) {
    ui->setupUi(this);
}

NewChannel::~NewChannel() {
    delete ui;
}

void NewChannel::on_buttonBox_accepted() try {
    const auto url = ui->url->text().toStdString();

    if(!IsValidURL(url)) throw std::runtime_error("Not an url");

    _feeds_cmd.addFeed(url);

    emit on_feed_added();
} catch(std::exception& e) {
    QMessageBox::critical(this, tr("IHARR"), tr(e.what()), QMessageBox::Ok);
}
