#include "WatchListModel.h"
#include <QStringList>

WatchListModel::WatchListModel(std::vector<Movie>& watchlist, QObject* parent)
    : QAbstractTableModel(parent), watchlist(watchlist) {
}

int WatchListModel::rowCount(const QModelIndex& ) const {
    return watchlist.size();
}

int WatchListModel::columnCount(const QModelIndex& ) const {
    return 5; 
}

QVariant WatchListModel::data(const QModelIndex& index, int role) const {
    if (!index.isValid() || role != Qt::DisplayRole)
        return {};

    const Movie& m = watchlist[index.row()];

    switch (index.column()) {
    case 0: return QString::fromStdString(m.getTitle());
    case 1: return QString::fromStdString(m.getGenre());
    case 2: return m.getYear();
    case 3: return m.getLikes();
    case 4: return QString::fromStdString(m.getTrailer());
    default: return {};
    }
}

QVariant WatchListModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role != Qt::DisplayRole || orientation != Qt::Horizontal)
        return {};

    static const QStringList headers = { "             Title              ", "             Genre             ", "             Year             ", "             Likes             ", "             Trailer             " };
    if (section >= 0 && section < headers.size())
        return headers[section];

    return {};
}
