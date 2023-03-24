#include "tablemodel.h"
#include <algorithm>
#include <QDebug>

/// <summary>
/// 获取表格行数
/// </summary>
/// <returns>返回表格的行数</returns>
int TableModel::rowCount(const QModelIndex& parent) const
{
	return tableData.size();
}

/// <summary>
/// 获取表格列数
/// </summary>
/// <returns>返回表格的列数</returns>
int TableModel::columnCount(const QModelIndex& parent) const
{
	return 7;
}

/// <summary>
/// 获取数据
/// </summary>
/// <param name="index">表格索引</param>
/// <param name="role">角色</param>
/// <returns>索引对应的数据</returns>
QVariant TableModel::data(const QModelIndex& index, int role) const
{
    //获取数据
    if (role == Qt::DisplayRole)
        return tableData[index.row()][index.column()];
    //设置字体
    if (role == Qt::FontRole)
        return QFont("Consolas", 11);
    //根据不同协议设置条目背景色
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
/// 设置列标题
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
/// 插入行
/// </summary>
/// <param name="row">插入的位置</param>
/// <param name="count">插入的行数</param>
bool TableModel::insertRows(int row, int count, const QModelIndex& parent)
{
    beginInsertRows(parent, row, row+count-1);
    tableData.append(newData);
    endInsertRows();
	return true;
}

/// <summary>
/// 设置新数据
/// </summary>
/// <param name="time">时间戳</param>
/// <param name="src">源地址</param>
/// <param name="des">目的地址</param>
/// <param name="protocol">协议类型</param>
/// <param name="length">报文长度</param>
/// <param name="info">报文信息</param>
void TableModel::setNewData(QString time, QString src, QString des, QString protocol, int length, QString info)
{
    int num = tableData.size() + 1;
    newData = {QString::number(num), time, src, des, protocol, QString::number(length),info };
}

/// <summary>
/// 设置新数据。类似于上面的重载函数。只是将除报文长度外的信息构成了向量
/// </summary>
/// <param name="info"></param>
/// <param name="length">报文长度</param>
void TableModel::setNewData(QVector<QString> info, int length)
{
    int num = tableData.size() + 1;
    newData = { QString::number(num), info[0], info[1], info[2], info[3], QString::number(length), info[5]};
}

//// <summary>
/// 在末尾添加新行
/// </summary>
void TableModel::addRow(QString time, QString src, QString des, QString protocol, int length, QString info)
{
    setNewData(time, src, des, protocol, length, info);
    insertRows(rowCount(), 1);
}

//// <summary>
/// 在末尾添加新行
/// </summary>
void TableModel::addRow(QVector<QString> info, int length)
{
    setNewData(info, length);
    insertRows(rowCount(), 1);
}

/// <summary>
/// 清除表格的数据
/// </summary>
void TableModel::clear()
{
    if (rowCount() == 0)
        return;
    beginRemoveRows(QModelIndex(), 0, rowCount() - 1);
    tableData.clear();
    endRemoveRows();
}


