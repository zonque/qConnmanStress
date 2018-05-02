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

#include <QCoreApplication>
#include <QtCore/QCommandLineParser>
#include <QtCore/QCommandLineOption>

#include "connman.h"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    QCommandLineParser parser;

    parser.setApplicationDescription("Connman stress test");
    parser.addHelpOption();

    QCommandLineOption ssidOption(QStringList() <<
                                  "s" << "ssid",
                                  "SSID to connect to",
                                  QStringLiteral("ssid"));
    parser.addOption(ssidOption);

    QCommandLineOption pwOption(QStringList() <<
                                "p" << "pw",
                                "Passphrase",
                                QStringLiteral("pw"));
    parser.addOption(pwOption);

    QCommandLineOption timeoutOption(QStringList() <<
                                     "t" << "timeout",
                                     "Timeout for stuck service state",
                                     QStringLiteral("timeout"), "0");
    parser.addOption(timeoutOption);

    QCommandLineOption randomOption(QStringList() <<
                                    "r" << "random",
                                    "Random events (scan, disconnect)",
                                    QStringLiteral("random"));
    parser.addOption(randomOption);

    parser.process(app);

    if (parser.value(ssidOption).isEmpty() ||
        parser.value(pwOption).isEmpty()) {
        qWarning() << "SSID and passphrase options are mandatory!";
        return EXIT_FAILURE;
    }

    QStringList randomEvents = parser.value(randomOption).split(",");

    Connman c(parser.value(ssidOption),
              parser.value(pwOption),
              randomEvents,
              parser.value(timeoutOption).toInt(),
              &app);

    return app.exec();
}
