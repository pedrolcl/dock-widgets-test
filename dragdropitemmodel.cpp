/**
 * Copyright (c) 2023, Pedro López-Cabanillas
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * See:
 *  https://doc.qt.io/qt-5/model-view-programming.html#using-drag-and-drop-with-item-views
 */

#include <QIODevice>

#include "dragdropitemmodel.h"

DragDropItemModel::DragDropItemModel(QObject *parent)
    : QStandardItemModel(parent)
{}

Qt::DropActions DragDropItemModel::supportedDropActions() const
{
    return Qt::CopyAction;
}

QStringList DragDropItemModel::mimeTypes() const
{
    static QStringList types{DragDropItemModel::MIME_TYPE};
    return types;
}

QMimeData *DragDropItemModel::mimeData(const QModelIndexList &indexes) const
{
    QMimeData *mimeData = new QMimeData;
    QByteArray encodedData;

    QDataStream stream(&encodedData, QIODevice::WriteOnly);

    for (const QModelIndex &index : indexes) {
        if (index.isValid()) {
            QString text = data(index, DragDropItemModel::DRAGDROP_ROLE).toString();
            stream << text;
        }
    }

    mimeData->setData(DragDropItemModel::MIME_TYPE, encodedData);
    return mimeData;
}

bool DragDropItemModel::canDropMimeData(const QMimeData *data,
                                        Qt::DropAction action,
                                        int row,
                                        int column,
                                        const QModelIndex &parent) const
{
    Q_UNUSED(action);
    Q_UNUSED(row);
    Q_UNUSED(parent);

    if (!data->hasFormat(DragDropItemModel::MIME_TYPE))
        return false;

    if (column > 0)
        return false;

    return true;
}

bool DragDropItemModel::dropMimeData(
    const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent)
{
    if (!canDropMimeData(data, action, row, column, parent))
        return false;

    if (action == Qt::IgnoreAction)
        return true;

    QByteArray encodedData = data->data(DragDropItemModel::MIME_TYPE);
    if (encodedData.length() == 0)
        return false;

    QDataStream stream(&encodedData, QIODevice::ReadOnly);
    while (!stream.atEnd()) {
        QString text;
        stream >> text;
        if (!text.isEmpty()) {
            appendRow(new QStandardItem(text));
        }
    }

    return true;
}
