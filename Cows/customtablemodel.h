#ifndef CUSTOMTABLEMODEL_H
#define CUSTOMTABLEMODEL_H

#include <QtCore/QAbstractTableModel>
#include <QtCore/QHash>
#include <QtCore/QRect>
#include <QMap>

#include <QTableView>

class CustomTableModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit CustomTableModel(QObject *parent = 0);

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
    Qt::ItemFlags flags(const QModelIndex &index) const;

    void addMapping(QString color, QRect area);
    void clearMapping() { m_mapping.clear(); }
    //添加数据
	void addData(const QMap<char, QList<qreal> * > &data);
    void addData(qreal t, qreal x, qreal y, qreal z);
    void addData(const QList<qreal> &ts, const QList<qreal> &xs, const QList<qreal> &ys, const QList<qreal> &zs);

	QMap<char, QList<qreal> * > *getData() const;

private:
    QList<char> headers;
    QMap<char, QList<qreal> * > *m_data;
    QHash<QString, QRect> m_mapping;
};

#endif // CUSTOMTABLEMODEL_H
