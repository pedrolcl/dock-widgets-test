#ifndef DRAGDROPITEMMODEL_H
#define DRAGDROPITEMMODEL_H

/**
 * Copyright (c) 2023, Pedro López-Cabanillas
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <QMimeData>
#include <QObject>
#include <QStandardItemModel>

using namespace Qt::Literals::StringLiterals;

class DragDropItemModel : public QStandardItemModel
{
    Q_OBJECT

public:
    static inline const QString MIME_TYPE{u"application/vnd.text.list"_s};
    static inline const int DRAGDROP_ROLE{Qt::UserRole + 1};

    DragDropItemModel(QObject *parent = nullptr);
    Qt::DropActions supportedDropActions() const override;
    QStringList mimeTypes() const override;
    QMimeData *mimeData(const QModelIndexList &indexes) const override;
    bool canDropMimeData(const QMimeData *data,
                         Qt::DropAction action,
                         int row,
                         int column,
                         const QModelIndex &parent) const override;
    bool dropMimeData(const QMimeData *data,
                      Qt::DropAction action,
                      int row,
                      int column,
                      const QModelIndex &parent) override;
};

#endif // DRAGDROPITEMMODEL_H
