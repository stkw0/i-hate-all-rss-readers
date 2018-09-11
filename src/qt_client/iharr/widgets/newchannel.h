#ifndef NEWCHANNEL_H
#define NEWCHANNEL_H

#include <string>

#include <QDialog>

#include "comm.h"

namespace Ui {
class NewChannel;
}

class NewChannel : public QDialog
{
    Q_OBJECT

public:
    explicit NewChannel(const std::string& t, Comm& c, QWidget *parent = 0);
    ~NewChannel();

private slots:
    void on_buttonBox_accepted();

private:
    Comm& _c;
    Ui::NewChannel *ui;
    const std::string& _token;
};

#endif // NEWCHANNEL_H
