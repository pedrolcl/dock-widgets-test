/**
 * Copyright (c) 2023, Pedro López-Cabanillas
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <QListView>

#include "dragdropitemmodel.h"
#include "listwidget.h"

ListWidget::ListWidget(QWidget *parent)
    : QDockWidget{parent}
{
    setWindowTitle("List View");
    setObjectName("ListWidget");
    setAllowedAreas(Qt::AllDockWidgetAreas);

    m_model = new DragDropItemModel(this);
    m_list = new QListView(this);
    m_list->setModel(m_model);
    m_list->setAcceptDrops(true);
    setWidget(m_list);
}
