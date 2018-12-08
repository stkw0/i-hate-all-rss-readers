#include <iostream>

#include <nlohmann/json.hpp>

#include "configuration.h"
#include "ui_configuration.h"

using json = nlohmann::json;

Configuration::Configuration(Comm& c, QWidget* parent)
    : _c{c}, QDialog(parent), ui(new Ui::Configuration) {
    ui->setupUi(this);

    ui->username->setText(_cfg.getUsername());
    ui->password->setText(_cfg.getPassword());
    ui->email->setText(_cfg.getEmail());
}

Configuration::~Configuration() {
    delete ui;
}

void Configuration::on_buttonBox_accepted() {
    auto user = ui->username->text();
    _cfg.setUsername(user);

    auto pass = ui->password->text();
    _cfg.setPassword(pass);

    auto email = ui->email->text();
    _cfg.setEmail(email);

    _cfg.store();

    Command cmd{_c, "register"};
    cmd.addArg("username", user.toStdString());
    cmd.addArg("password", pass.toStdString());
    cmd.addArg("email", email.toStdString());
    cmd.send();
    emit on_config_change();
}
