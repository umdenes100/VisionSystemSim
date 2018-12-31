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
    qDebug() << "Writing settingsWidget settings";
    QSettings settings("UMD ENES100", "Simulator");
    settings.beginGroup("SettingsWidget");
    settings.setValue("entropy", entropyEnabled);
    settings.setValue("obstacles", obstaclesEnabled);
}

void SettingsWidget::readSettings()
{
    qDebug() << "Reading settingsWidget settings";
    QSettings settings("UMD ENES100", "Simulator");
    settings.beginGroup("SettingsWidget");
    entropyEnabled = settings.value("entropy", QVariant(false)).toBool();
    obstaclesEnabled = settings.value("obstacles", QVariant(true)).toBool();
    ui->obstaclesEnabled->setChecked(obstaclesEnabled);
    ui->entropyEnabled->setChecked(entropyEnabled);
    emit obstaclesBoxChanged(obstaclesEnabled);
    emit entropyBoxChanged(entropyEnabled);
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

void SettingsWidget::on_obstaclesEnabled_stateChanged(int enabled)
{
    obstaclesEnabled = enabled;
    emit obstaclesBoxChanged(enabled);
}

void SettingsWidget::on_entropyEnabled_stateChanged(int enabled)
{
    entropyEnabled = enabled;
    emit entropyBoxChanged(enabled);
}
