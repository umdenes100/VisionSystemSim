#include "mainwindow.h"
#include "ui_mainwindow.h"

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
    connect(this, SIGNAL(windowClosed()), ui->settingswidget, SLOT(writeSettings()));
    connect(this, SIGNAL(windowClosed()), ui->arena->osv, SLOT(writeSettings()));
    readSettings();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::writeSettings()
{
    QSettings settings("UMD ENES100", "Simulator");
    settings.beginGroup("MainWindow");
    settings.setValue("size", size());
    settings.setValue("pos", pos());
    settings.endGroup();
}

void MainWindow::readSettings()
{
    QSettings settings("UMD ENES100", "Simulator");
    settings.beginGroup("MainWindow");
    resize(settings.value("size", size()).toSize());
    move(settings.value("pos", pos()).toPoint());
    settings.endGroup();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    emit windowClosed();
    writeSettings();
    event->accept();
}

void MainWindow::centerAndResize()
{
    QScreen* screen = QGuiApplication::primaryScreen();
    QSize availableSize = screen->availableGeometry().size();
    QRect screenrect = screen->geometry();

    setGeometry(0, 0, availableSize.width(), availableSize.height());
    move(screenrect.left(), screenrect.top());
}

