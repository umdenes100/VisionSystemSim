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
    connect(ui->settingswidget, SIGNAL(customClicked(int)), ui->arena, SLOT(customButtonClicked(int)));
    connect(ui->settingswidget, SIGNAL(coordinateChanged(float,bool)), ui->arena, SLOT(customCoordinateChanged(float,bool)));
    connect(ui->settingswidget, SIGNAL(sliderMoved(int)), ui->arena, SLOT(entropyChanged(int)));
}

MainWindow::~MainWindow()
{
    delete ui;
}
