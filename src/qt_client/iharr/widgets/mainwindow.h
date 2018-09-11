#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <string>

#include <QMainWindow>

#include "comm.h"
#include "configuration.h"
#include "newchannel.h"

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

private:
    std::string _token;

    Ui::MainWindow *ui;

    Comm _c;
    Configuration _cfg_wg{_c, this};
    NewChannel _new_channel_wg{_token, _c, this};
};

#endif // MAINWINDOW_H
