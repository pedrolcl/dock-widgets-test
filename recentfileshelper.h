#ifndef RECENTFILESHELPER_H
#define RECENTFILESHELPER_H

/**
 * Copyright (c) 2023, Pedro López-Cabanillas
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <QObject>
#include <QAction>
#include <QString>

class RecentFilesHelper : public QObject
{
    Q_OBJECT

public:
    RecentFilesHelper(QObject *parent);
    ~RecentFilesHelper() {}

    void setCurrentFile(const QString &fileName);
    void updateRecentFileActions();
    QString strippedName(const QString &fullFileName);
    QStringList files();
    void retranslateUi();

    static constexpr int MaxRecentFiles{10};

signals:
    void selectedFile(QString fileName);

public slots:
    void openRecentFile();
    void clear();

private:
    QAction *recentFileActs[MaxRecentFiles];
    QAction *clearAct;
};

#endif // RECENTFILESHELPER_H
