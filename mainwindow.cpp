/**
 * Copyright (c) 2023, Pedro López-Cabanillas
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <QCoreApplication>
#include <QDebug>
#include <QFileDialog>
#include <QMenu>
#include <QMenuBar>
#include <QSettings>

#include "treewidget.h"
#include "listwidget.h"
#include "mainwindow.h"
#include "recentfileshelper.h"
#include "tablewidget.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("Docking Widgets Test Application");

    QMenu *fileMenu = new QMenu("File", this);
    QAction *fileOpenAction = fileMenu->addAction("Open...");
    QMenu *recentFilesMenu = fileMenu->addMenu("Recent Files");
    fileMenu->addSeparator();
    QAction *quitAction = fileMenu->addAction("Quit");
    QMenu *viewMenu = new QMenu("View", this);
    menuBar()->addMenu(fileMenu);
    menuBar()->addMenu(viewMenu);

    connect(fileOpenAction, &QAction::triggered, this, &MainWindow::openFile);
    connect(quitAction, &QAction::triggered, this, &MainWindow::close);

    m_recentFiles = new RecentFilesHelper(recentFilesMenu);
    connect(m_recentFiles, &RecentFilesHelper::selectedFile, this, &MainWindow::openTextFile);
    m_recentFiles->updateRecentFileActions();

    m_explorer = new TreeWidget(this);
    m_list = new ListWidget(this);
    m_table = new TableWidget(this);

    addDockWidget(Qt::LeftDockWidgetArea, m_explorer);
    addDockWidget(Qt::RightDockWidgetArea, m_list);
    addDockWidget(Qt::RightDockWidgetArea, m_table);

    viewMenu->addActions(createPopupMenu()->actions());

    resize(1024, 800);

    QSettings settings;
    restoreGeometry(settings.value("geometry").toByteArray());
    restoreState(settings.value("state").toByteArray());

    openTextFile(":/testdata.txt");
}

MainWindow::~MainWindow() {}

void MainWindow::openTextFile(const QString &fileName)
{
    //qDebug() << Q_FUNC_INFO << fileName;
    m_explorer->parseFile(fileName);
    if (!fileName.startsWith(":/")) {
        m_recentFiles->setCurrentFile(fileName);
    }
}

void MainWindow::openFile()
{
    QFileDialog dialog(this);
    dialog.setWindowTitle("Open Text File");
    dialog.setNameFilter(tr("Text Files (*.txt)"));
    dialog.setFileMode(QFileDialog::ExistingFile);
    if (dialog.exec()) {
        openTextFile(dialog.selectedFiles().constFirst());
    }
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    QSettings settings;
    settings.setValue("geometry", saveGeometry());
    settings.setValue("state", saveState());
    settings.sync();
}
