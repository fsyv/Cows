#include "customtablemodel.h"
#include <QtCore/QVector>
#include <QtCore/QTime>
#include <QtCore/QRect>
#include <QtGui/QColor>

CustomTableModel::CustomTableModel(QObject *parent) :
    QAbstractTableModel(parent)
{
    headers << 't' << 'x' << 'y' << 'z';

    m_data = new QMap<char, QList<qreal> * >;


    m_data->insert('t', new QList<qreal>);
    m_data->insert('x', new QList<qreal>);
    m_data->insert('y', new QList<qreal>);
    m_data->insert('z', new QList<qreal>);
}

int CustomTableModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_data->value('t')->count();
}

int CustomTableModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return headers.count();
}

QVariant CustomTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal) {
        return QString("%1").arg(headers.at(section));
    } else {
        return QString("%1").arg(section + 1);
    }
}

QVariant CustomTableModel::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole) {
		return m_data->value(headers.at(index.column()))->at(index.row());
    } else if (role == Qt::EditRole) {
		return m_data->value(headers.at(index.column()))->at(index.row());
    } else if (role == Qt::BackgroundRole) {
        foreach (QRect rect, m_mapping) {
            if (rect.contains(index.column(), index.row()))
                return QColor(m_mapping.key(rect));
        }
        // cell not mapped return white color
        return QColor(Qt::white);
    }
    return QVariant();
}

bool CustomTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.isValid() && role == Qt::EditRole) {
		m_data->value(headers.at(index.column()))->replace(index.row(), value.toDouble());
        emit dataChanged(index, index);
        return true;
    }
    return false;
}

Qt::ItemFlags CustomTableModel::flags(const QModelIndex &index) const
{
	return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
}

void CustomTableModel::addMapping(QString color, QRect area)
{
    m_mapping.insertMulti(color, area);
}

void CustomTableModel::addData(const QMap<char, QList<qreal> * > &data)
{
	addData(
		*data.value('t'),
		*data.value('x'), 
		*data.value('y'), 
		*data.value('z')
		);
}

void CustomTableModel::addData(qreal t, qreal x, qreal y, qreal z)
{
	int keep = rowCount();

    m_data->value('t')->append(t);
    m_data->value('x')->append(x);
    m_data->value('y')->append(y);
    m_data->value('z')->append(z);

	insertRow(keep);
}

void CustomTableModel::addData(const QList<qreal> &ts, const QList<qreal> &xs, const QList<qreal> &ys, const QList<qreal> &zs)
{
	int keep = rowCount();

    m_data->value('t')->append(ts);
    m_data->value('x')->append(xs);
    m_data->value('y')->append(ys);
    m_data->value('z')->append(zs);

	insertRows(keep, ts.count());
}

QMap<char, QList<qreal> * > *CustomTableModel::getData() const
{
	return m_data;
}

bool CustomTableModel::insertRows(int row, int count, const QModelIndex &parent)
{
	bool state = QAbstractTableModel::insertRows(row, count, parent);
	for (int i = 0; i < count; ++i)
	{
		data(index(row + i, 0), Qt::DisplayRole);
		//dataChanged(index(row + i, 0), index(row + i, 0));
		//dataChanged(index(row + i, 1), index(row + i, 1));
		//dataChanged(index(row + i, 2), index(row + i, 2));
		//dataChanged(index(row + i, 3), index(row + i, 3));
	}
	return state;
}
