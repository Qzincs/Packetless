#pragma once
#include <QAbstractListModel>
#include <QAction>
#include <QVector>
#include <QFont>

/// <summary>
/// 列表的数据模型
/// </summary>
class ListModel : public QAbstractListModel
{
public:
	int rowCount(const QModelIndex& parent = QModelIndex()) const override;
	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
	void addData(QVector<QString>& newData);
	void clear();

	int row = 0;
	QVector<QVector<QString>> listData;

public slots:
	void onTableviewClicked(const QModelIndex& index);
};
