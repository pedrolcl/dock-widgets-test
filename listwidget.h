#ifndef LISTWIDGET_H
#define LISTWIDGET_H

/**
 * Copyright (c) 2023, Pedro López-Cabanillas
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <QDockWidget>

class QListView;
class DragDropItemModel;

class ListWidget : public QDockWidget
{
    Q_OBJECT
public:
    explicit ListWidget(QWidget *parent = nullptr);

private:
    QListView *m_list;
    DragDropItemModel *m_model;
};

#endif // LISTWIDGET_H
