#ifndef NEWCHANNEL_H
#define NEWCHANNEL_H

#include <string>

#include <QDialog>

#include "feeds_commands.hpp"

namespace Ui {
class NewChannel;
}

class NewChannel : public QDialog
{
    Q_OBJECT

public:
    explicit NewChannel( FeedsCommands& f, QWidget *parent = 0);
    ~NewChannel();

signals:
	void on_feed_added();

private slots:
    void on_buttonBox_accepted();

private:
	 FeedsCommands& _feeds_cmd;

    Ui::NewChannel *ui;
};

#endif // NEWCHANNEL_H
