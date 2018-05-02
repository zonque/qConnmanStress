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
    explicit Connman(const QString &_preconfiguredSSID,
                     const QString &_preconfiguredPassword,
                     const QStringList &_randomEvents,
                     int _stuckTimeout,
                     QObject *parent);

private:
    NetworkManager *manager;
    UserAgent *agent;
    QString preconfiguredSSID;
    QString preconfiguredPassword;
    QString lastState;
    QTimer *stuckTimer;
    QTimer *randomScanTimer;
    QTimer *randomDisconnectTimer;
    QStringList randomEvents;
    int stuckTimeout;

    int successCount;
    int failureCount;
    int stuckCount;

    void enableWifi();
    void iterateServices();
    void scanWifi();
    int timeoutForRandomEvent();
};

#endif // CONNMAN_H
