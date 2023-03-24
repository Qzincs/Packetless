#include "listmodel.h"

/// <summary>
/// ��ȡ����
/// </summary>
int ListModel::rowCount(const QModelIndex& parent) const
{
	if (listData.size() > 0)
		return listData[row].size();
	else
		return 0;
}

/// <summary>
/// ��ȡ����
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
/// �������
/// </summary>
/// <param name="newData">Ҫ��ӵ�����</param>
void ListModel::addData(QVector<QString>& newData)
{
	listData.append(newData);
}

/// <summary>
/// ����б������
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
/// �����Ҫ��Ϣʱ��ʾ��Ӧԭʼ����
/// </summary>
/// <param name="index">����ı������</param>
void ListModel::onTableviewClicked(const QModelIndex& index)
{
	row = index.row();
	QModelIndex topLeft = createIndex(0, 1);
	QModelIndex bottomRight = createIndex(rowCount(), 1);
	//�������ݱ仯���źţ�����ʾ����ˢ��
	emit dataChanged(topLeft, bottomRight, { Qt::DisplayRole });
}
