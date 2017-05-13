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

//��������
void SQLExecute::exportData(QString tableName, QMap<char, QList<qreal> * > *data)
{

}

//��������
QMap<char, QList<qreal> * > *SQLExecute::importData(QString tableName)
{

}

//��ѯ���б���
QStringList SQLExecute::getAllTableName()
{

}