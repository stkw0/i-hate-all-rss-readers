#include <regex>
#include <stdexcept>

#include <QMessageBox>

#include "comm.h"

#include "newchannel.h"
#include "ui_newchannel.h"

NewChannel::NewChannel(const std::string& t, Comm& c, QWidget* parent)
    : _token{t}, _c{c}, QDialog(parent), ui(new Ui::NewChannel) {
    ui->setupUi(this);
}

NewChannel::~NewChannel() {
    delete ui;
}

void NewChannel::on_buttonBox_accepted() try {
    auto url = ui->url->text();
    std::regex r("(?:http|https)://([\\S]+[^<>]*)");
    if(!std::regex_match(url.toStdString(), r))
        throw std::runtime_error("Not an url");

    Command cmd{_c, "add_feed"};
    cmd.addArg("url", url.toStdString());
    cmd.addArg("token", _token);
    cmd.send();
} catch(std::exception& e) {
    QMessageBox::critical(this, tr("IHARR"), tr(e.what()), QMessageBox::Ok);
}
