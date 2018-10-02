#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->communicationwidget->osv = ui->arena->osv;
    ui->communicationwidget->arena = ui->arena;
    ui->settingswidget->osv = ui->arena->osv;
    connect(ui->settingswidget, SIGNAL(randomizeClicked()), ui->arena, SLOT(randomize()));
    connect(ui->settingswidget, SIGNAL(resetClicked()), ui->arena, SLOT(reset()));
    connect(ui->settingswidget, SIGNAL(sliderMoved(int)), ui->arena, SLOT(entropyChanged(int)));
    checkForUpdates();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::checkForUpdates() {
    // Here we will check the tags in git for updates to notify the users.
    QNetworkAccessManager manager;
    QNetworkRequest request(QUrl("https://github.com/umdenes100/VisionSystemSimulatorInstallers/releases"));
    request.setSslConfiguration(QSslConfiguration::defaultConfiguration());
    QNetworkReply *response = manager.get(request);
    QEventLoop event;
    connect(response,SIGNAL(finished()),&event,SLOT(quit()));
    event.exec();
    qDebug() << response->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    QByteArray html = response->readAll();
    qDebug() << "HELLO";
    qDebug() << response->errorString();
    QString body(html);
    qDebug() << body;
}
