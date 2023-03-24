#include "listmodel.h"

/// <summary>
/// 获取行数
/// </summary>
int ListModel::rowCount(const QModelIndex& parent) const
{
	if (listData.size() > 0)
		return listData[row].size();
	else
		return 0;
}

/// <summary>
/// 获取数据
/// </summary>
QVariant ListModel::data(const QModelIndex& index, int role) const
{
	if (role == Qt::DisplayRole&&index.row() >= 0 && index.row()<rowCount())//&&listData.size()>0)
		return listData[row][index.row()];
	if (role == Qt::FontRole)
		return QFont("Consolas", 11);
	return QVariant();
}

/// <summary>
/// 添加数据
/// </summary>
/// <param name="newData">要添加的数据</param>
void ListModel::addData(QVector<QString>& newData)
{
	listData.append(newData);
}

/// <summary>
/// 清除列表的数据
/// </summary>
void ListModel::clear()
{
	if (rowCount() == 0)
		return;
	beginRemoveRows(QModelIndex(), 0, rowCount() - 1);
	listData.clear();
	endRemoveRows();
}

/// <summary>
/// 点击概要信息时显示对应原始数据
/// </summary>
/// <param name="index">点击的表格索引</param>
void ListModel::onTableviewClicked(const QModelIndex& index)
{
	row = index.row();
	QModelIndex topLeft = createIndex(0, 1);
	QModelIndex bottomRight = createIndex(rowCount(), 1);
	//发送数据变化的信号，让显示内容刷新
	emit dataChanged(topLeft, bottomRight, { Qt::DisplayRole });
}
