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
    explicit Connman(const QString &ssid, const QString &pw, QObject *parent);

signals:

public slots:

private:
    NetworkManager *manager;
    UserAgent *agent;
    QString preconfiguredSSID;
    QString preconfiguredPassword;

    int successCount;
    int failureCount;

    void enableWifi();
    void iterateServices();
    void scanWifi();
};

#endif // CONNMAN_H
