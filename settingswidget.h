#ifndef SETTINGSWIDGET_H
#define SETTINGSWIDGET_H

#include <QWidget>
#include <QDesktopServices>
#include <QUrl>
#include "osveditorwindow.h"
#include "osv.h"

namespace Ui {
class SettingsWidget;
}

class SettingsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SettingsWidget(QWidget *parent = nullptr);
    OSV* osv;
    ~SettingsWidget();

signals:
    void randomizeClicked();
    void resetClicked();
    void sliderMoved(int pos);
    void obstaclesBoxChanged(bool enabled);
    void entropyBoxChanged(bool enabled);

private slots:
    void on_RandomizeButton_clicked();
    void on_OSVButton_clicked();
    void on_ResetButton_clicked();
    void on_documentationButton_clicked();
    void on_obstaclesEnabled_stateChanged(int arg1);
    void on_entropyEnabled_stateChanged(int arg1);

private:
    Ui::SettingsWidget *ui;
};

#endif // SETTINGSWIDGET_H
