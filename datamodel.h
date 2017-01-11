#ifndef DATAMODEL_H
#define DATAMODEL_H

#include <QAbstractListModel>
#include <QVariant>
#include <QString>
#include <QMap>


class DataModel : public QAbstractListModel
{

    Q_OBJECT

public:
    enum Roles {
        NameRole = Qt::UserRole + 1, //gli dico che aggiungo altri nomi alla lista dei ruoli già definiti
        ValueRole
    };
    Q_ENUM(Roles) //la chiamo sempre quando devo esporre una enum al qml

    DataModel();
    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QHash<int, QByteArray> roleNames() const;

public slots:
    void mapReceived(QVariantMap map);

private:
    QVariantMap m_data;

};

#endif // DATAMODEL_H
