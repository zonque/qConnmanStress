/***
  Copyright (c) 2018 Daniel Mack

  This program is free software; you can redistribute it and/or
  modify it under the terms of the GNU General Public License
  as published by the Free Software Foundation; either version 2
  of the License, or (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, see <http://www.gnu.org/licenses/>.
***/

#include <QDebug>
#include <QTimer>
#include "connman.h"

#include <connman-qt5/useragent.h>
#include <connman-qt5/networkmanager.h>
#include <connman-qt5/networktechnology.h>

Q_LOGGING_CATEGORY(ConnmanLog, "Connman")

void Connman::scanWifi()
{
    NetworkTechnology *technology = manager->getTechnology("wifi");
    if (technology)
        technology->scan();
}

void Connman::enableWifi()
{
    NetworkTechnology *technology = manager->getTechnology("wifi");
    if (technology && !technology->powered())
        technology->setPowered(true);
}

void Connman::iterateServices()
{
    foreach (NetworkService *service, manager->getServices("wifi")) {
        if (service->name() != preconfiguredSSID)
            continue;

        qInfo(ConnmanLog) << "Current state of SSID" << preconfiguredSSID << "is" << service->state();

        if (service->state() == "online") {
            successCount++;
            qInfo(ConnmanLog) << "Successfully connected" << successCount << "times";
            service->requestDisconnect();
            scanWifi();
            return;
        }

        if (service->state() == "failure") {
            failureCount++;
            qInfo(ConnmanLog) << "Failures while connected" << failureCount;
            service->requestConnect();
            return;
        }

        if (service->state() == "idle") {
            service->requestConnect();
            return;
        }
    }
}

Connman::Connman(const QString &ssid, const QString &pw, QObject *parent) :
    QObject(parent)
{
    manager = new NetworkManager(this);
    preconfiguredPassword = pw;
    preconfiguredSSID = ssid;

    successCount = 0;
    failureCount = 0;

    QObject::connect(manager, &NetworkManager::stateChanged, [this]() {
        if (manager->state() == "offline") {
            manager->setOfflineMode(false);
        }
    });

    QObject::connect(manager, &NetworkManager::technologiesChanged, [this]() {
        enableWifi();
        scanWifi();
    });

    QObject::connect(manager, &NetworkManager::servicesChanged, [this]() {
        iterateServices();
    });

    agent = new UserAgent(this);
    agent->setAgentPath("/foo/bar/ConnmanAgent");

    QObject::connect(agent, &UserAgent::userInputRequested, [this](const QString &servicePath, const QVariantMap &fields) {
        Q_UNUSED(servicePath);
        Q_UNUSED(fields);

        QVariantMap reply;
        reply.insert("Passphrase", preconfiguredPassword);
        agent->sendUserReply(reply);
    });

    manager->setOfflineMode(false);
    enableWifi();
    scanWifi();
}
