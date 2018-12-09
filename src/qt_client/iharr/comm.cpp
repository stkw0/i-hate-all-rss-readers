#include <iostream>
#include <stdexcept>

#include "comm.h"

Comm::Comm() {
}

Comm::~Comm() {
    socket.disconnectFromHost();
}

void Comm::connect(const QString& host) {
    _log->info("Connecting to {}", host.toStdString());

    socket.connectToHost(host, 1234);
    if(!socket.waitForConnected()) {
        auto err_msg = socket.errorString().toStdString();
        _log->error(err_msg);
        throw std::runtime_error(err_msg);
    }
}

void Comm::write(const QByteArray& data) {
    _log->debug("Writing data: \"{}\"", data);
    if(socket.state() != QAbstractSocket::ConnectedState) throw socket.state();

    socket.write(data);
    socket.waitForBytesWritten();
}

QString Comm::read() {
    if(socket.state() != QAbstractSocket::ConnectedState) throw socket.state();
    socket.waitForReadyRead();

    return socket.readAll();
}

Command::Command(Comm& c, const std::string& cmd) : _conn{c} {
    _packet["command"] = cmd;
}

void Command::send() {
    auto p = _packet.dump();

    _log->debug("Sending json: \"{}\"", p);
    _conn.write(p.c_str());

    auto response = _conn.read().toStdString();
    _log->debug("Received response: \"{}\"", response);

    if(response.empty()) return;

    _received = json::parse(response);

    if(_received["error"] != "") throw std::runtime_error(_received["error"]);
}

const std::string Command::getAnswer() const {
    return _received["answer"];
}

const args_t Command::getArgs() const {
    return _received["args"];
}

const std::vector<std::string> Command::getArgsAsList() const {
    return _received["args"];
}