#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDesktopWidget>
#include <QStyle>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    srand(static_cast<unsigned int>(time(nullptr)));
    ui->setupUi(this);
    centerAndResize();
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

void MainWindow::centerAndResize()
{
    QSize availableSize = qApp->desktop()->availableGeometry().size();
    QSize newSize(availableSize.width(), availableSize.height());

    setGeometry(QStyle::alignedRect(Qt::LeftToRight, Qt::AlignCenter, newSize, qApp->desktop()->availableGeometry()));
}

