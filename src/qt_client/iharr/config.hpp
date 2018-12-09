#pragma once

#include <QString>

#include "lib/config/config.hpp"

class Config : BaseConfig {
public:
	Config(const std::string& f_name);
	~Config();

	const QString getPassword() const;
	void setPassword(const QString& p);

	const QString getUsername() const;
	void setUsername(const QString& u);

	const QString getEmail() const;
	void setEmail(const QString& e);

	void store();

private:
	void load();

	struct Options {
		std::string password;
		std::string username;
		std::string email;
	} opt;
};
