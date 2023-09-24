/**
 * Copyright (c) 2023, Pedro López-Cabanillas
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <QDebug>
#include <QFile>
#include <QFileInfo>
#include <QLineEdit>
#include <QMimeData>
#include <QSortFilterProxyModel>
#include <QStandardItem>
#include <QStandardItemModel>
#include <QTextStream>
#include <QTreeView>
#include <QVBoxLayout>

#include "dragdropitemmodel.h"
#include "treewidget.h"

TreeWidget::TreeWidget(QWidget *parent)
    : QDockWidget{parent}
{
    setWindowTitle("Tree View");
    setObjectName("TreeWidget");
    setAllowedAreas(Qt::AllDockWidgetAreas);
    m_filter = new QLineEdit(this);
    m_filter->setClearButtonEnabled(true);
    m_model = new DragDropItemModel(this);
    m_proxy = new QSortFilterProxyModel(this);
    m_proxy->setSourceModel(m_model);
    m_proxy->setFilterCaseSensitivity(Qt::CaseInsensitive);
    m_proxy->setFilterKeyColumn(0);
    m_proxy->setRecursiveFilteringEnabled(true);
    m_proxy->setAutoAcceptChildRows(true);
    m_tree = new QTreeView(this);
    m_tree->setModel(m_proxy);
    m_tree->setHeaderHidden(true);
    m_tree->setDragDropMode(QAbstractItemView::DragOnly);
    m_tree->setSelectionMode(QAbstractItemView::SingleSelection);

    auto container = new QWidget(this);
    auto layout = new QVBoxLayout(container);
    layout->addWidget(m_filter);
    layout->addWidget(m_tree);
    setWidget(container);

    connect(m_filter,
            &QLineEdit::textChanged,
            m_proxy,
            &QSortFilterProxyModel::setFilterFixedString);
    connect(m_filter, &QLineEdit::textChanged, this, [=](const QString &text) {
        if (text.isEmpty()) {
            m_tree->collapseAll();
        } else {
            m_tree->expandAll();
        }
    });
}

void TreeWidget::appendToModel(DragDropItemModel *model, const QString &line)
{
    QStringList list = line.split('.', Qt::SkipEmptyParts);
    QStandardItem *parent = model->invisibleRootItem();
    foreach (const auto &text, list) {
        QStandardItem *item = nullptr;
        if (parent->hasChildren()) {
            for (int i = 0; i < parent->rowCount(); ++i) {
                if (parent->child(i)->text() == text) {
                    item = parent->child(i);
                    break;
                }
            }
        }
        if (item) {
            parent = item;
            parent->setDragEnabled(false);
            continue;
        }
        item = new QStandardItem(text);
        item->setData(line, DragDropItemModel::DRAGDROP_ROLE);
        item->setEditable(false);
        parent->appendRow(item);
        parent = item;
    }
}

void TreeWidget::parseFile(const QString &fileName)
{
    QFile file(fileName);
    if (file.open(QFile::Text | QFile::ReadOnly)) {
        QTextStream stream(&file);
        while (!stream.atEnd()) {
            appendToModel(m_model, stream.readLine());
        }
    }
}
