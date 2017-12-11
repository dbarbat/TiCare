#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    auto edit_list = {ui->high, ui->last,ui->timestamp,ui->bid,
                  ui->vwap,ui->volume,ui->low,ui->ask,ui->open};

    for(auto line_edit : edit_list) {
        line_edit->setReadOnly(true);
        line_edit->setText("Loading in 10 seconds...");
    }

    network_Manager = new QNetworkAccessManager(this);
    connect(network_Manager, &QNetworkAccessManager::finished, this, &MainWindow::onNetworkManagerFinished);


    timer=new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::onTimeOut );
    timer->start(10000);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onNetworkManagerFinished(QNetworkReply *reply)
{
    if(reply->error() != QNetworkReply::NoError){
        ui->high->setText("Error");
        ui->last->setText("Error");
        ui->timestamp->setText("Error");
        ui->bid->setText("Error");
        ui->vwap->setText("Error");
        ui->volume->setText("Error");
        ui->low->setText("Error");
        ui->ask->setText("Error");
        ui->open->setText("Error");

        network_Manager->clearAccessCache();

    } else {
        //Parsing reply JSON
        QJsonObject jsonObject= QJsonDocument::fromJson(reply->readAll()).object();
        ui->high->setText(jsonObject["high"].toString());
        ui->last->setText(jsonObject["last"].toString());
        ui->timestamp->setText(jsonObject["timestamp"].toString());
        ui->bid->setText(jsonObject["bid"].toString());
        ui->vwap->setText(jsonObject["vwap"].toString());
        ui->volume->setText(jsonObject["volume"].toString());
        ui->low->setText(jsonObject["low"].toString());
        ui->ask->setText(jsonObject["ask"].toString());
        ui->open->setText(jsonObject["open"].toString());
    }

    reply->deleteLater();

}


void MainWindow::onTimeOut()
{
    QUrlQuery query;
    query.addQueryItem("amount", "1");
    query.addQueryItem("region", "United States");
    QUrl url("https://www.bitstamp.net/api/v2/ticker/btceur/");
    url.setQuery(query);
    QNetworkRequest networkRequest(url);

    network_Manager->get(networkRequest);

    ui->high->setText("Loading. . .");
    ui->last->setText("Loading. . .");
    ui->timestamp->setText("Loading. . .");
    ui->bid->setText("Loading. . .");
    ui->vwap->setText("Loading. . .");
    ui->volume->setText("Loading. . .");
    ui->low->setText("Loading. . .");
    ui->ask->setText("Loading. . .");
    ui->open->setText("Loading. . .");

}
