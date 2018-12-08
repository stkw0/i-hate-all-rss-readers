#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <QDialog>

#include "comm.h"
#include "config.hpp"


namespace Ui {
class Configuration;
}

class Configuration : public QDialog
{
    Q_OBJECT

public:
    explicit Configuration(Comm& c, QWidget *parent = 0);
    ~Configuration();

signals:
	void on_config_change();

private slots:
    void on_buttonBox_accepted();

private:    

	Config _cfg{"iharr_qt"};

    Comm& _c;

    Ui::Configuration *ui;

};

#endif // CONFIGURATION_H
