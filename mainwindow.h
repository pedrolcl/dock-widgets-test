#ifndef MAINWINDOW_H
#define MAINWINDOW_H

/**
 * Copyright (c) 2023, Pedro López-Cabanillas
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <QMainWindow>

class TreeWidget;
class ListWidget;
class TableWidget;
class RecentFilesHelper;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void openTextFile(const QString &fileName);

public slots:
    void openFile();

    // QWidget interface
protected:
    void closeEvent(QCloseEvent *event) override;

private:
    TreeWidget *m_explorer;
    ListWidget *m_list;
    TableWidget *m_table;
    RecentFilesHelper *m_recentFiles;
};
#endif // MAINWINDOW_H
