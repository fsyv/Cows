#ifndef DATALISTITEM_H
#define DATALISTITEM_H

#include <QListWidgetItem>


class DataListItem : public QListWidgetItem
{
public:
    DataListItem(QString tableName, QListWidget *view = nullptr);
    ~DataListItem();

    QString getTableName() const;
    void setTableName(const QString &name);

private:

    QString m_TableName;
};

#endif // DATALISTITEM_H
