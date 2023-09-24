#ifndef TABLEWIDGET_H
#define TABLEWIDGET_H

/**
 * Copyright (c) 2023, Pedro López-Cabanillas
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <QDockWidget>

class QTableView;
class DragDropItemModel;

class TableWidget : public QDockWidget
{
    Q_OBJECT
public:
    explicit TableWidget(QWidget *parent = nullptr);

private:
    QTableView *m_table;
    DragDropItemModel *m_model;
};

#endif // TABLEWIDGET_H
