#include "stdafx.h"

#include "sqlexecute.h"

SQLExecute *SQLExecute::m_pInstance = nullptr;

SQLExecute::SQLExecute(QObject *parent) : QObject(parent)
{
	db = new QSqlDatabase;
	db->addDatabase("QSQLITE");
	db->setDatabaseName("cows.db");

	query = new QSqlQuery(*db);
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
void SQLExecute::exportData(QString tableName, QMap<char, QList<qreal> * > *data)
{
	SQLExecute *pInstance = SQLExecute::getInstance();

	pInstance->query->exec(
		QString("CREATE TABLE IF NOT EXISTS '%1'(%2, %3, %4, %5)") \
		.arg(tableName) \
		.arg(QString("t REAL")) \
		.arg(QString("x REAL")) \
		.arg(QString("y REAL")) \
		.arg(QString("z REAL")) \
		);

	pInstance->query->prepare(QString("INSERT INTO %1 VALUES(?, ?, ?, ?)").arg(tableName));

	QList<qreal> *t = data->value('t');

	if (t)
	{
		for (int i = 0; i < t->count(); ++i)
		{
			pInstance->query->bindValue(0, t->at(i));
			pInstance->query->bindValue(1, data->value('x')->at(i));
			pInstance->query->bindValue(2, data->value('y')->at(i));
			pInstance->query->bindValue(3, data->value('z')->at(i));

			pInstance->query->exec();
		}
	}

	pInstance->db->commit();
}

//导入数据
QMap<char, QList<qreal> * > *SQLExecute::importData(QString tableName)
{
	SQLExecute *pInstance = SQLExecute::getInstance();

	pInstance->query->exec(QString("SELECT * FROM %1").arg(tableName));

	QList<qreal> *t = new QList<qreal>;
	QList<qreal> *x = new QList<qreal>;
	QList<qreal> *y = new QList<qreal>;
	QList<qreal> *z = new QList<qreal>;

	while (pInstance->query->next())
	{
		t->append(pInstance->query->value(QString('t')).toReal());
		x->append(pInstance->query->value(QString('x')).toReal());
		y->append(pInstance->query->value(QString('y')).toReal());
		z->append(pInstance->query->value(QString('z')).toReal());
	}

	QMap<char, QList<qreal> * > *result = new QMap<char, QList<qreal> * >;

	result->insert('t', t);
	result->insert('t', x);
	result->insert('t', y);
	result->insert('t', z);

	return result;
}

//查询所有表名
QStringList SQLExecute::getAllTableName()
{
	SQLExecute *pInstance = SQLExecute::getInstance();

	pInstance->query->exec(QString("SELECT name FROM sqlite_master WHERE 'table' order BY name"));

	QStringList tableList;
	while (pInstance->query->next())
		tableList.append(pInstance->query->value(0).toString());

	return tableList;
}