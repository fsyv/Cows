#include "stdafx.h"

#include "datalistitem.h"

DataListItem::DataListItem(QString tableName, QListWidget *view) :
    QListWidget(view)
{
    int index = tableName.indexOf(QString("_"));
    QString name = tableName.left(index);
    setText(name);
}

DataListItem::~DataListItem()
{

}

QString DataListItem::getTableName() const
{
    return m_TableName;
}

void DataListItem::setTableName(const QString &name)
{
    m_TableName = name;
}
