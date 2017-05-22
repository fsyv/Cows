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
void SQLExecute::exportData(QString tableName, const QMap<char, QList<qreal> * > data)
{
	SQLExecute *pInstance = SQLExecute::getInstance();

	QSqlQuery query(*pInstance->db);

	query.exec(
		QString("CREATE TABLE IF NOT EXISTS '%1'(%2, %3, %4, %5)") \
		.arg(tableName) \
		.arg(QString("t REAL")) \
		.arg(QString("x REAL")) \
		.arg(QString("y REAL")) \
		.arg(QString("z REAL")) \
		);

	query.prepare(QString("INSERT INTO '%1' VALUES(?, ?, ?, ?)").arg(tableName));

    QList<qreal> *t = data.value('t');

	if (t)
	{
		for (int i = 0; i < t->count(); ++i)
		{
			query.bindValue(0, t->at(i));
            query.bindValue(1, data.value('x')->at(i));
            query.bindValue(2, data.value('y')->at(i));
            query.bindValue(3, data.value('z')->at(i));

			query.exec();
		}
	}

	pInstance->db->commit();
}

//导入数据
QMap<char, QList<qreal> * > SQLExecute::importData(QString tableName)
{
	SQLExecute *pInstance = SQLExecute::getInstance();

	QSqlQuery query(*pInstance->db);

	query.exec(QString("SELECT * FROM '%1'").arg(tableName));

	QList<qreal> *t = new QList<qreal>;
	QList<qreal> *x = new QList<qreal>;
	QList<qreal> *y = new QList<qreal>;
	QList<qreal> *z = new QList<qreal>;

	while (query.next())
	{
		t->append(query.value(QString('t')).toReal());
		x->append(query.value(QString('x')).toReal());
		y->append(query.value(QString('y')).toReal());
		z->append(query.value(QString('z')).toReal());
	}

	QMap<char, QList<qreal> * > result;

	result.insert('t', t);
	result.insert('x', x);
	result.insert('y', y);
	result.insert('z', z);

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
