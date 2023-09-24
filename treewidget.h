#ifndef EXPLORERWIDGET_H
#define EXPLORERWIDGET_H

/**
 * Copyright (c) 2023, Pedro López-Cabanillas
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <QDockWidget>

class QTreeView;
class QLineEdit;
class DragDropItemModel;
class QSortFilterProxyModel;

class TreeWidget : public QDockWidget
{
    Q_OBJECT
public:
    explicit TreeWidget(QWidget *parent = nullptr);

public slots:
    void parseFile(const QString &fileName);
    void appendToModel(DragDropItemModel *model, const QString &line);

private:
    QTreeView *m_tree;
    QLineEdit *m_filter;
    DragDropItemModel *m_model;
    QSortFilterProxyModel *m_proxy;
};

#endif // EXPLORERWIDGET_H
