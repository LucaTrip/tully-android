#include <QDebug>

#include "datamodel.h"

DataModel::DataModel()
{

}

int DataModel::rowCount(const QModelIndex &parent) const
{
    return m_data.size();
}

QVariant DataModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() >= m_data.size()) {
        return QVariant();
    }

    if (role == NameRole) {
        return QVariant(m_data.keys().at(index.row()));
    } else if (role == ValueRole) {
        return m_data.values().at(index.row());
    }
}

QHash<int, QByteArray> DataModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles.insert(NameRole, "name");
    roles.insert(ValueRole, "value");
    return roles;
}

void DataModel::mapReceived(QVariantMap map)
{
    beginResetModel();
    m_data = map;
    endResetModel();
}


