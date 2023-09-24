/**
 * Copyright (c) 2023, Pedro López-Cabanillas
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <QAction>
#include <QApplication>
#include <QFileInfo>
#include <QMenu>
#include <QSettings>
#include <QStyle>

#include "recentfileshelper.h"

RecentFilesHelper::RecentFilesHelper(QObject *parent)
	: QObject(parent)
{
    QMenu *menu = qobject_cast<QMenu *>(parent);
    if (menu) {
        for (int i = 0; i < RecentFilesHelper::MaxRecentFiles; ++i) {
            recentFileActs[i] = new QAction(this);
            recentFileActs[i]->setVisible(false);
            menu->addAction(recentFileActs[i]);
            connect(recentFileActs[i],
                    &QAction::triggered,
                    this,
                    &RecentFilesHelper::openRecentFile);
        }
        menu->addSeparator();
        clearAct = new QAction(tr("Clear recent files"), this);
        clearAct->setIcon(qApp->style()->standardIcon(QStyle::SP_LineEditClearButton));
        menu->addAction(clearAct);
        connect(clearAct, &QAction::triggered, this, &RecentFilesHelper::clear);
    }
}

void RecentFilesHelper::openRecentFile()
{
    QAction *action = qobject_cast<QAction *>(sender());
    if (action) {
        emit selectedFile(action->data().toString());
    }
}

void RecentFilesHelper::clear()
{
    QSettings settings;
    settings.setValue("recent_files", QStringList());
    updateRecentFileActions();
}

void RecentFilesHelper::setCurrentFile(const QString &fileName)
{
    QSettings settings;
    QStringList files = settings.value("recent_files").toStringList();
    files.removeAll(fileName);
    files.prepend(fileName);
    while (files.size() > RecentFilesHelper::MaxRecentFiles) {
        files.removeLast();
    }

    settings.setValue("recent_files", files);
    updateRecentFileActions();
}

void RecentFilesHelper::updateRecentFileActions()
{
    QSettings settings;
    QStringList files = settings.value("recent_files").toStringList();
    int numRecentFiles = qMin(files.size(), (int) RecentFilesHelper::MaxRecentFiles);
    for (int i = 0; i < numRecentFiles; ++i) {
        QString text = tr("&%1 %2").arg(i + 1).arg(strippedName(files[i]));
        recentFileActs[i]->setText(text);
        recentFileActs[i]->setData(files[i]);
        recentFileActs[i]->setVisible(true);
    }
    for (int j = numRecentFiles; j < RecentFilesHelper::MaxRecentFiles; ++j) {
        recentFileActs[j]->setVisible(false);
    }
    clearAct->setEnabled(numRecentFiles > 0);
}

QString RecentFilesHelper::strippedName(const QString &fullFileName)
{
    return QFileInfo(fullFileName).fileName();
}

QStringList RecentFilesHelper::files()
{
    QSettings settings;
    QStringList files = settings.value("recent_files").toStringList();
    return files;
}
