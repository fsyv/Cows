#include "stdafx.h"

#include "sqlexecute.h"

SQLExecute::SQLExecute(QObject *parent) : QObject(parent)
{
    db = new QSqlDatabase;
    db->addDatabase("QSQLITE");
    db->setDatabaseName("cows.db");
}

SQLExecute::~SQLExecute()
{
    db->close();
    delete db;
}

SQLExecute *SQLExecute::getInstance()
{
    if(m_pInstance == nullptr)
    {
        mutex.lock();
        if(m_pInstance == nullptr)
        {
            m_pInstance = new SQLExecute;
        }
        mutex.unlock();
    }

    return m_pInstance;
}

//导出数据
void SQLExecute::exportData(QString tableName, QMap<char, QList<qreal> * > *data)
{

}

//导入数据
QMap<char, QList<qreal> * > *SQLExecute::importData(QString tableName)
{

}

//查询所有表名
QStringList SQLExecute::getAllTableName()
{

}