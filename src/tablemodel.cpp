#include "tablemodel.h"
#include <algorithm>
#include <QDebug>

/// <summary>
/// ��ȡ�������
/// </summary>
/// <returns>���ر�������</returns>
int TableModel::rowCount(const QModelIndex& parent) const
{
	return tableData.size();
}

/// <summary>
/// ��ȡ�������
/// </summary>
/// <returns>���ر�������</returns>
int TableModel::columnCount(const QModelIndex& parent) const
{
	return 7;
}

/// <summary>
/// ��ȡ����
/// </summary>
/// <param name="index">�������</param>
/// <param name="role">��ɫ</param>
/// <returns>������Ӧ������</returns>
QVariant TableModel::data(const QModelIndex& index, int role) const
{
    //��ȡ����
    if (role == Qt::DisplayRole)
        return tableData[index.row()][index.column()];
    //��������
    if (role == Qt::FontRole)
        return QFont("Consolas", 11);
    //���ݲ�ͬЭ��������Ŀ����ɫ
    if (role == Qt::BackgroundRole)
    {
        QString protocol = tableData[index.row()][4];
        if(protocol=="ARP")
        { 
            return QBrush(QColor("#faf0d7"));
        }
        else if(protocol=="ICMP" || protocol=="ICMPv6")
        {
            return QBrush(QColor("#fce0ff"));
        }
        else if (protocol == "IGMP")
        {
            return QBrush(QColor("#fff3d6"));
        }
        else if (protocol == "UDP")
        {
            return QBrush(QColor("#daeeff"));
        }
        else if (protocol == "TCP")
        {
            return QBrush(QColor("#e7e6ff"));
        }
        else if (protocol == "HTTP")
        {
            return QBrush(QColor("#e4ffc7"));
        }
    }
	return QVariant();
}

/// <summary>
/// �����б���
/// </summary>
QVariant TableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
        switch (section) {
        case 0:
            return QString(tr("No."));
        case 1:
            return QString(tr("Time"));
        case 2:
            return QString(tr("Source"));
        case 3:
            return QString(tr("Destination"));
        case 4:
            return QString(tr("Protocol"));
        case 5:
            return QString(tr("Length"));
        case 6:
            return QString(tr("Info"));
        }
    }
    return QVariant();
}

/// <summary>
/// ������
/// </summary>
/// <param name="row">�����λ��</param>
/// <param name="count">���������</param>
bool TableModel::insertRows(int row, int count, const QModelIndex& parent)
{
    beginInsertRows(parent, row, row+count-1);
    tableData.append(newData);
    endInsertRows();
	return true;
}

/// <summary>
/// ����������
/// </summary>
/// <param name="time">ʱ���</param>
/// <param name="src">Դ��ַ</param>
/// <param name="des">Ŀ�ĵ�ַ</param>
/// <param name="protocol">Э������</param>
/// <param name="length">���ĳ���</param>
/// <param name="info">������Ϣ</param>
void TableModel::setNewData(QString time, QString src, QString des, QString protocol, int length, QString info)
{
    int num = tableData.size() + 1;
    newData = {QString::number(num), time, src, des, protocol, QString::number(length),info };
}

/// <summary>
/// ���������ݡ���������������غ�����ֻ�ǽ������ĳ��������Ϣ����������
/// </summary>
/// <param name="info"></param>
/// <param name="length">���ĳ���</param>
void TableModel::setNewData(QVector<QString> info, int length)
{
    int num = tableData.size() + 1;
    newData = { QString::number(num), info[0], info[1], info[2], info[3], QString::number(length), info[5]};
}

//// <summary>
/// ��ĩβ�������
/// </summary>
void TableModel::addRow(QString time, QString src, QString des, QString protocol, int length, QString info)
{
    setNewData(time, src, des, protocol, length, info);
    insertRows(rowCount(), 1);
}

//// <summary>
/// ��ĩβ�������
/// </summary>
void TableModel::addRow(QVector<QString> info, int length)
{
    setNewData(info, length);
    insertRows(rowCount(), 1);
}

/// <summary>
/// �����������
/// </summary>
void TableModel::clear()
{
    if (rowCount() == 0)
        return;
    beginRemoveRows(QModelIndex(), 0, rowCount() - 1);
    tableData.clear();
    endRemoveRows();
}


