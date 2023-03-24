#include "treedata.h"

TreeData::TreeData(QVector<std::string> parent, QVector<QVector<std::string>> children)
{
	//设置父节点数量
	topNum = parent.size();
	//创建树形项目，并设置父节点和子节点
	for (int i = 0; i < topNum; i++)
	{
		QTreeWidgetItem* item = new QTreeWidgetItem();
		item->setData(0, Qt::DisplayRole, QString::fromStdString(parent[i]));
		top.append(item);
		QVector<QTreeWidgetItem*> sub;
		for (int j = 0; j < children[i].size(); j++)
		{
			QTreeWidgetItem* childItem = new QTreeWidgetItem();
			childItem->setData(0, Qt::DisplayRole, QString::fromStdString(children[i][j]));
			sub.append(childItem);
		}
		data.append(sub);
	}
}