#include "settingswidget.h"
#include "ui_settingswidget.h"

SettingsWidget::SettingsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SettingsWidget)
{
    ui->setupUi(this);
    readSettings();
}

SettingsWidget::~SettingsWidget()
{
    delete ui;
}

void SettingsWidget::writeSettings()
{
    QSettings settings("UMD ENES100", "Simulator");
    settings.beginGroup("SettingsWidget");
    settings.setValue("entropy", entropyEnabled);
    settings.setValue("obstacles", obstaclesEnabled);
    settings.endGroup();
}

void SettingsWidget::readSettings()
{
    QSettings settings("UMD ENES100", "Simulator");
    settings.beginGroup("SettingsWidget");
    entropyEnabled = settings.value("entropy", QVariant(false)).toBool();
    obstaclesEnabled = settings.value("obstacles", QVariant(true)).toBool();
    ui->obstaclesOn->setChecked(obstaclesEnabled);
    ui->obstaclesOff->setChecked(!obstaclesEnabled);
    ui->commIdeal->setChecked(!entropyEnabled);
    ui->commRealistic->setChecked(entropyEnabled);
    settings.endGroup();
}

void SettingsWidget::on_RandomizeButton_clicked()
{
    emit randomizeClicked();
}

void SettingsWidget::on_OSVButton_clicked()
{
    OSVEditorWindow *window = new OSVEditorWindow(this);
    window->init(osv);
    window->show();
}

void SettingsWidget::on_ResetButton_clicked()
{
    emit resetClicked();
}

void SettingsWidget::on_documentationButton_clicked()
{
    QDesktopServices::openUrl(QUrl("https://github.com/umdenes100/VisionSystemSimulatorInstallers/blob/master/README.md"));
}

void SettingsWidget::on_obstaclesOn_clicked()
{
    obstaclesEnabled = true;
    emit obstaclesBoxChanged(true);
    ui->obstaclesOn->setChecked(true);
    ui->obstaclesOff->setChecked(false);
}

void SettingsWidget::on_obstaclesOff_clicked()
{
    obstaclesEnabled = false;
    emit obstaclesBoxChanged(false);
    ui->obstaclesOn->setChecked(false);
    ui->obstaclesOff->setChecked(true);
}

void SettingsWidget::on_commIdeal_clicked()
{
    entropyEnabled = false;
    emit entropyBoxChanged(false);
    ui->commIdeal->setChecked(true);
    ui->commRealistic->setChecked(false);
}

void SettingsWidget::on_commRealistic_clicked()
{
    entropyEnabled = true;
    emit entropyBoxChanged(true);
    ui->commIdeal->setChecked(false);
    ui->commRealistic->setChecked(true);
}
