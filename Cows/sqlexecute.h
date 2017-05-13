#ifndef SQLEXECUTE_H
#define SQLEXECUTE_H

#include <QObject>
#include <QMutex>

QT_BEGIN_NAMESPACE

class QSqlDatabase;

class SQLExecute : public QObject
{
    Q_OBJECT
public:
    ~SQLExecute();

    //导出数据
	static void exportData(QString tableName, QMap<char, QList<qreal> * > *data);
    //导入数据
	static QMap<char, QList<qreal> * > *importData(QString tableName);
	//查询所有表名
	static QStringList getAllTableName();

private:
    explicit SQLExecute(QObject *parent = 0);

    QSqlDatabase *db;

    SQLExecute *getInstance();
    SQLExecute *m_pInstance = nullptr;
    QMutex mutex;

signals:

public slots:
};

QT_END_NAMESPACE

#endif // SQLEXECUTE_H
