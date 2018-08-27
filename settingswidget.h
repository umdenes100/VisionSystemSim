#ifndef SETTINGSWIDGET_H
#define SETTINGSWIDGET_H

#include <QWidget>

#include "osveditorwindow.h"
#include "osv.h"

namespace Ui {
class SettingsWidget;
}

class SettingsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SettingsWidget(QWidget *parent = 0);
    OSV* osv;
    ~SettingsWidget();

signals:
    void randomizeClicked();
    void customClicked(int arg1);
    void coordinateChanged(float value, bool isX);

private slots:
    void on_RandomizeButton_clicked();

    void on_OSVButton_clicked();

    void on_CustomPointCheck_stateChanged(int arg1);

    void on_CustomX_valueChanged(double arg1);

    void on_CustomY_valueChanged(double arg1);

private:
    Ui::SettingsWidget *ui;
};

#endif // SETTINGSWIDGET_H
