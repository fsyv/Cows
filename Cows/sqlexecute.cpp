#include "stdafx.h"

#include "sqlexecute.h"

SQLExecute *SQLExecute::m_pInstance = nullptr;
QMutex SQLExecute::mutex;

SQLExecute::SQLExecute(QObject *parent) : QObject(parent)
{
    db = new QSqlDatabase();
    *db = QSqlDatabase::addDatabase(QString("QSQLITE"));
    db->setDatabaseName(QString("cows.db"));
    db->open();
}

SQLExecute::~SQLExecute()
{
    db->close();
    delete db;
}

SQLExecute *SQLExecute::getInstance()
{
    if (m_pInstance == nullptr)
    {
        mutex.lock();
        if (m_pInstance == nullptr)
        {
            m_pInstance = new SQLExecute;
        }
        mutex.unlock();
    }

    return m_pInstance;
}

//导出数据
void SQLExecute::exportData(const QString &tableName, const QList<int> &data)
{
    SQLExecute *pInstance = SQLExecute::getInstance();

    QSqlQuery query(*pInstance->db);

    query.exec(
                QString("CREATE TABLE IF NOT EXISTS '%1'(%2)") \
                .arg(tableName) \
                .arg(QString("_state INT2")) \
                );

    query.prepare(QString("INSERT INTO '%1' VALUES(?)").arg(tableName));

    for (int i = 0; i < data.count(); ++i)
    {
        query.bindValue(0, data.at(i));
        query.exec();
    }

    pInstance->db->commit();
}

//导入数据
QList<int> SQLExecute::importData(QString tableName)
{
    SQLExecute *pInstance = SQLExecute::getInstance();

    QSqlQuery query(*pInstance->db);

    query.exec(QString("SELECT * FROM '%1'").arg(tableName));

    QList<int> result;

    while (query.next())
    {
        result.append(query.value(QString("_state")).toInt());
    }

    return result;
}

//查询所有表名
QStringList SQLExecute::getAllTableName()
{
    SQLExecute *pInstance = SQLExecute::getInstance();

    QSqlQuery sqlquery(*pInstance->db);

    sqlquery.exec(QString("SELECT name FROM sqlite_master"));

    QStringList tableList;
    while (sqlquery.next())
        tableList.append(sqlquery.value(0).toString());

    return tableList;
}
