#ifndef COMM_H
#define COMM_H

#include <string>
#include <unordered_map>
#include <vector>

#include <QtNetwork>
#include <QString>
#include <QByteArray>
#include <nlohmann/json.hpp>

#include "logging.hpp"

using json = nlohmann::json;
using args_t = std::unordered_map<std::string, std::string>;

class Comm
{
public:
    Comm();
    ~Comm();
    void connect(const QString& host);
    void write(const QByteArray& data);
    QString read();

private:
    QTcpSocket socket;

    spdlogger _log{NewLogger("comm")};
};

class Command {
public:
	Command(Comm& c, const std::string& cmd);

	void send();

	template<typename T>
	void addArg(const std::string& key, T val) {
    	_packet["args"][key] = val;
	}

	const std::string getAnswer() const;
	const args_t getArgs() const;
	const std::vector<std::string> getArgsAsList() const;

private:
	Comm& _conn;
	json _packet;
	json _received;

	spdlogger _log{NewLogger("command")};

};

#endif // COMM_H
