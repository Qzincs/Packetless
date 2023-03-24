#pragma once
#include <QVector>
#include <QTreeWidgetItem>
#include <string>

/// <summary>
/// ��״�ڵ������
/// </summary>
class TreeData
{
public:	
	TreeData(QVector<std::string> parent, QVector<QVector<std::string>> children);

	//����ڵ�����
	int topNum;
	//����ڵ�����
	QVector<QTreeWidgetItem*> top;
	//�ӽ�����ݡ�����ڵ����ӽ��������������Ŷ�Ӧ��
	QVector<QVector<QTreeWidgetItem*>> data;


};