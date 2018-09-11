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

void NewChannel::on_buttonBox_accepted() {
    Command cmd{_c, "add_feed"};
    auto url = ui->url->text();
    cmd.addArg("url", url.toStdString());
    cmd.addArg("token", _token);
    cmd.send();
}
