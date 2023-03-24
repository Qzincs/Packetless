#pragma once
#include <QVector>
#include <QTreeWidgetItem>
#include <string>

/// <summary>
/// 树状节点的数据
/// </summary>
class TreeData
{
public:	
	TreeData(QVector<std::string> parent, QVector<QVector<std::string>> children);

	//顶层节点数量
	int topNum;
	//顶层节点数据
	QVector<QTreeWidgetItem*> top;
	//子结点数据。顶层节点与子结点数据向量的序号对应。
	QVector<QVector<QTreeWidgetItem*>> data;


};