/**
 * Copyright (c) 2023, Pedro López-Cabanillas
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <QTableView>

#include "dragdropitemmodel.h"
#include "tablewidget.h"

TableWidget::TableWidget(QWidget *parent)
    : QDockWidget{parent}
{
    setWindowTitle("Table View");
    setObjectName("TableWidget");
    setAllowedAreas(Qt::AllDockWidgetAreas);

    m_model = new DragDropItemModel(this);
    m_table = new QTableView(this);
    m_table->setModel(m_model);
    m_table->setAcceptDrops(true);
    setWidget(m_table);
}
