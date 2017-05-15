#pragma once
#pragma  execution_character_set("utf-8")

#include <QObject>
#include <QMutex>

QT_BEGIN_NAMESPACE

class QSqlDatabase;

class SQLExecute : public QObject
{
    Q_OBJECT
public:
    ~SQLExecute();

    //��������
	static void exportData(QString tableName, QMap<char, QList<qreal> * > *data);
    //��������
	static QMap<char, QList<qreal> * > importData(QString tableName);
	//��ѯ���б���
	static QStringList getAllTableName();

private:
    explicit SQLExecute(QObject *parent = 0);

    QSqlDatabase *db;

    static SQLExecute *getInstance();
    static SQLExecute *m_pInstance;
    static QMutex mutex;

signals:

public slots:
};

QT_END_NAMESPACE

