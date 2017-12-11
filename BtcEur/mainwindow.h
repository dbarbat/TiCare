#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QUrlQuery>
#include <QJsonDocument>
#include <QJsonObject>

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
    void onNetworkManagerFinished(QNetworkReply* reply);
    void onTimeOut();

private:
    Ui::MainWindow *ui;
    QTimer *timer;
    QNetworkAccessManager *network_Manager;
};

#endif // MAINWINDOW_H
