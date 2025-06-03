#pragma once

#include <QAbstractTableModel>
#include <vector>
#include "Movie.h"

class WatchListModel : public QAbstractTableModel {
    Q_OBJECT

private:
    std::vector<Movie>& watchlist;

public:
    explicit WatchListModel(std::vector<Movie>& watchlist, QObject* parent = nullptr);

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
};