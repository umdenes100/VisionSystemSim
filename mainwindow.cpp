#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    srand(static_cast<unsigned int>(time(nullptr)));
    ui->setupUi(this);
    ui->communicationwidget->osv = ui->arena->osv;
    ui->communicationwidget->arena = ui->arena;
    ui->settingswidget->osv = ui->arena->osv;
    connect(ui->settingswidget, SIGNAL(randomizeClicked()), ui->arena, SLOT(randomize()));
    connect(ui->settingswidget, SIGNAL(resetClicked()), ui->arena, SLOT(reset()));
    connect(ui->settingswidget, SIGNAL(entropyBoxChanged(bool)), ui->arena, SLOT(entropyChanged(bool)));
    connect(ui->settingswidget, SIGNAL(obstaclesBoxChanged(bool)), ui->arena, SLOT(obstaclesToggled(bool)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

