#pragma once
#include <QAbstractTableModel>
#include <QVector>
#include <QFont>
#include <QBrush>
#include <QColor>

/// <summary>
/// 表格的数据模型
/// </summary>
class TableModel :public QAbstractTableModel
{
public:
	int rowCount(const QModelIndex& parent = QModelIndex()) const override;
	int columnCount(const QModelIndex& parent = QModelIndex()) const override;
	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
	QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
	bool insertRows(int row, int count, const QModelIndex& parent = QModelIndex()) override;
	void setNewData(QString time, QString src, QString des, QString protocol, int length, QString info);
	void setNewData(QVector<QString> info, int length);
	void addRow(QString time, QString src, QString des, QString protocol, int length, QString info);
	void addRow(QVector<QString> info, int length);
	void clear();

	QVector<QVector<QString>> tableData;
	QVector<QString> newData;

};
