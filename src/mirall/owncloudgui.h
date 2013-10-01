/*
 * Copyright (C) by Klaas Freitag <freitag@owncloud.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 2 of the License.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License
 * for more details.
 */

#ifndef OWNCLOUDGUI_H
#define OWNCLOUDGUI_H

#include "mirall/systray.h"
#include "mirall/connectionvalidator.h"
#include "mirall/progressdispatcher.h"

#include <QObject>
#include <QPointer>
#include <QAction>
#include <QMenu>
#include <QSignalMapper>

namespace Mirall {

class SettingsDialog;
class ItemProgressDialog;
class Application;

class ownCloudGui : public QObject
{
    Q_OBJECT
public:
    explicit ownCloudGui(Application *parent = 0);

    void setupContextMenu();
    void startupConnected( ConnectionValidator::Status status );

    bool checkConfigExists(bool openSettings);

signals:

public slots:
    void computeOverallSyncStatus( const QStringList& startupFails );
    void slotShowTrayMessage(const QString &title, const QString &msg);
    void slotShowOptionalTrayMessage(const QString &title, const QString &msg);
    void slotFolderOpenAction( const QString& alias );
    void slotRefreshQuotaDisplay( qint64 total, qint64 used );
    void rebuildRecentMenus();
    void slotProgressSyncProblem(const QString& folder, const Progress::SyncProblem& problem);
    void slotUpdateProgress(const QString &folder, const Progress::Info& progress);
    void slotShowGuiMessage(const QString &title, const QString &message);
    void slotFoldersChanged();
    void slotItemProgressDialog();
    void slotSettings();
    void shutdown();
    void slotSyncStateChange( const QString& alias );
    void slotTrayClicked( QSystemTrayIcon::ActivationReason reason );
    void slotOpenLogBrowser();

private slots:
    void slotDisplayIdle();

private:
    void setupActions();

    QPointer<Systray> _tray;
    QPointer<SettingsDialog> _settingsDialog;
    QPointer<ItemProgressDialog> _progressDialog;

    // tray's menu
    QMenu *_contextMenu;
    QMenu *_recentActionsMenu;

    QAction *_actionOpenoC;
    QAction *_actionSettings;
    QAction *_actionQuota;
    QAction *_actionStatus;
    QAction *_actionRecent;
    QAction *_actionHelp;
    QAction *_actionQuit;

    Application *_app;

    QSignalMapper *_folderOpenActionMapper;

    QStringList _startupFail;
};

} // namespace Mirall

#endif // OWNCLOUDGUI_H