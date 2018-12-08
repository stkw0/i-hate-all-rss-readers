#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <string>

#include <QMainWindow>
#include <QListWidgetItem>
#include <QPoint>

#include "comm.h"
#include "configuration.h"
#include "newchannel.h"
#include "logging.hpp"
#include "feeds_commands.hpp"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionConfiguration_triggered();

    void on_actionChannel_triggered();

    void on_listWidget_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);

    void on_listWidget_customContextMenuRequested(const QPoint &pos);

    void update_feeds();

    void update_login();

private:

    bool eventFilter(QObject *obj, QEvent *event);

    std::string _token;

    Ui::MainWindow *ui;

    Comm _c;
    FeedsCommands _feeds_cmd{_c, _token};
    Configuration _cfg_wg{_c, this};
    NewChannel _new_channel_wg{_feeds_cmd, this};

    spdlogger _log{NewLogger("iharr_qt")};
};

#endif // MAINWINDOW_H
