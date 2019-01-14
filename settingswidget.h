#ifndef SETTINGSWIDGET_H
#define SETTINGSWIDGET_H

#include <QWidget>
#include <QDesktopServices>
#include <QUrl>
#include <QSettings>
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

public slots:
    void writeSettings();

private slots:
    void on_RandomizeButton_clicked();
    void on_OSVButton_clicked();
    void on_ResetButton_clicked();
    void on_documentationButton_clicked();
    void on_obstaclesOn_clicked();
    void on_obstaclesOff_clicked();
    void on_commIdeal_clicked();
    void on_commRealistic_clicked();

private:
    Ui::SettingsWidget *ui;
    void readSettings();
    bool entropyEnabled = false;
    bool obstaclesEnabled = true;
};

#endif // SETTINGSWIDGET_H
