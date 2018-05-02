#ifndef CONNMAN_H
#define CONNMAN_H

#include <QObject>

#include <connman-qt5/useragent.h>
#include <connman-qt5/networkmanager.h>
#include <connman-qt5/networktechnology.h>

class Connman : public QObject
{
    Q_OBJECT
public:
    explicit Connman(const QString &ssid,
                     const QString &pw,
                     int _stuckTimeout,
                     QObject *parent);

private:
    NetworkManager *manager;
    UserAgent *agent;
    QString preconfiguredSSID;
    QString preconfiguredPassword;
    QString lastState;
    QTimer *timer;
    int stuckTimeout;

    int successCount;
    int failureCount;
    int stuckCount;

    void enableWifi();
    void iterateServices();
    void scanWifi();
};

#endif // CONNMAN_H
