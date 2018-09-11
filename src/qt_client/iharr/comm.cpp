#include <iostream>

#include "comm.h"

Comm::Comm() {
}

Comm::~Comm() {
    socket.disconnectFromHost();
}

void Comm::connect(const QString& host) {
    socket.connectToHost(host, 1234);
    if(!socket.waitForConnected()) qDebug(socket.errorString().toLatin1());
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

    auto parsed_response = json::parse(response);
    _answer = parsed_response["answer"];

    // json library workaround
    args_t tmp = parsed_response["args"];
    _args = tmp;
}

const std::string Command::getAnswer() const {
    return _answer;
}

const args_t Command::getArgs() const {
    return _args;
}