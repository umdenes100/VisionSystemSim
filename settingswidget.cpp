#include "settingswidget.h"
#include "ui_settingswidget.h"

SettingsWidget::SettingsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SettingsWidget)
{
    ui->setupUi(this);
}

SettingsWidget::~SettingsWidget()
{
    delete ui;
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
