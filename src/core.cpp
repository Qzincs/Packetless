#include "core.h"

/// <summary>
/// 构造函数，对软件进行初始化
/// </summary>
/// <param name="app">应用程序</param>
/// <param name="window">主窗口</param>
/// <param name="tran">翻译器</param>
Core::Core(QApplication* app, MainWindow* window, QTranslator* tran)
{
	this->app = app;
	this->window = window;
	this->translator = tran;
	
	//绘制主界面
	gui.setupUi(window);
	treeWidget = gui.treeWidget;

	//读取语言信息
	QSettings settings("lang.ini", QSettings::IniFormat);
	if (settings.value("lang") == "zh-CN")
	{
		translator->load("Translation_zh_Hans.qm");
		this->app->installTranslator(translator);
		gui.retranslateUi(window);
	}

	//绑定Model和View
	gui.setupView(tableModel, listModel);
	//连接信号槽
	connect();
	//将捕获业务对象移至子线程
	captureWork->moveToThread(captureThread);
	processWork->moveToThread(processThread);

	//注册信号槽自定参数类型
	qRegisterMetaType<Packet_Sniffer>("Packet_Sniffer");

	//查找捕获接口
	sniffer.set_devs();
	sniffer.set_sniffer_devs(captureInterfaceIndex);
	sender.fp = sniffer.fp;
}


/// <summary>
/// 连接信号槽
/// </summary>
void Core::connect()
{
	//点击Table更新Tree显示数据
	QObject::connect(gui.tableView, &QTableView::clicked, this, &Core::onTableviewClicked);
	QObject::connect(gui.tableView, &QTableView::clicked, &listModel, &ListModel::onTableviewClicked);

	//按钮点击
	QObject::connect(gui.actionStart, &QAction::triggered, this, &Core::startCapture);
	QObject::connect(gui.actionStop, &QAction::triggered, this, &Core::stopCapture);
	QObject::connect(gui.actionRestart, &QAction::triggered, this, &Core::restartCapture);
	QObject::connect(gui.actionOpen, &QAction::triggered, this, &Core::openFile);
	QObject::connect(gui.actionSave, &QAction::triggered, this, &Core::saveFile);
	QObject::connect(gui.actionSend, &QAction::triggered, this, &Core::sendDialog);
	QObject::connect(gui.actionQuit, &QAction::triggered, this, &Core::quit);
	QObject::connect(window, &MainWindow::close, this, &Core::quit);

	//设备选择
	QObject::connect(gui.actionSelectInterface, &QAction::triggered, this, &Core::interfaceSelectionDialog);
	QObject::connect(gui.actionAbout, &QAction::triggered, this, &Core::aboutDialog);

	//切换语言
	QObject::connect(gui.actionChinese, &QAction::triggered, this, &Core::changeToChinese);
	QObject::connect(gui.actionEnglish, &QAction::triggered, this, &Core::changeToEnglish);

	//过滤器相关
	QObject::connect(gui.inputFilter, &QLineEdit::editingFinished, this, &Core::applyFilter);
	QObject::connect(gui.buttonApply, &QPushButton::clicked, this, &Core::applyFilter);
	QObject::connect(gui.buttonClear, &QPushButton::clicked, this, &Core::clearFilter);

	//复制相关
	QObject::connect(gui.tableCopyAction, &QAction::triggered, this, &Core::tableDataCopy);
	QObject::connect(gui.listCopyAction, &QAction::triggered, this, &Core::listDataCopy);

	//线程相关
	QObject::connect(this, &Core::captureStarted, captureWork, &CaptureWork::run);
	QObject::connect(this, &Core::captureStarted, processWork, &ProcessWork::readyForNext);
	QObject::connect(this, &Core::processFinished, processWork, &ProcessWork::readyForNext);
	QObject::connect(processWork, &ProcessWork::next, this, &Core::onPacketCaptured);
}

/// <summary>
/// 添加详细数据
/// </summary>
void Core::addTreeData()
{
	//转换解析结果根节点
	QVector<string> parent = QVector<string>::fromStdVector(analyzer.tree_header);
	parent.pop_front();
	//转换解析结果子节点
	QVector<QVector<string>> children;
	for (int i = 0; i < analyzer.tree.size(); i++)
	{
		children.append(QVector<string>::fromStdVector(analyzer.tree.at(i)));
		if (children[i].size() > 0)
			children[i].pop_front();
	}
	children.pop_front();
	//将结果添加到tree
	TreeData data = TreeData(parent, children);
	treeData.append(data);
}


/// <summary>
/// 点击概要信息时显示对应详细信息
/// </summary>
/// <param name="index">点击的索引</param>
void Core::onTableviewClicked(const QModelIndex& index)
{
	lastViewedIndex = index.row();
	//清空显示的详细数据
	while (treeWidget->topLevelItemCount() > 0)
		treeWidget->takeTopLevelItem(0);
	//重新设置显示的数据
	TreeData data = treeData[index.row()];
	for (int i = 0; i < data.topNum; i++)
	{
		treeWidget->addTopLevelItem(data.top[i]);
		for (int j = 0; j < data.data[i].size(); j++)
		{
			data.top[i]->addChild(data.data[i][j]);
		}
	}
}

/// <summary>
/// 点击开始按钮的槽函数。改变按钮的可用性，开始捕获数据包。
/// </summary>
void Core::startCapture()
{
	//如果有未保存的数据包，提示用户保存
	if (!isSave && tableModel.rowCount() > 0)
	{
		int res = QMessageBox::warning(window, tr("Unsaved packets"),
			tr("Do you want to save the captured packets before startting a new capture?\nYour captured packets will be lost if you don't save them."),
			tr("Save"), tr("Discard"));
		if (res == 0 && !saveFile())
			return;
	}

	//如果临时文件夹不存在，则创建它
	QDir path(".\\temp");
	if (!path.exists())
	{
		path.mkpath("..\\temp");
	}
	//创建临时文件，用于暂存捕获到的数据包
	QString tempFileName = QDateTime::currentDateTime().toString("yyyyMMddhhmmss");
	tempFileName.append(".pcap").push_front(".\\temp\\temp");
	tempFile.setFileName(tempFileName);
	sniffer.file = tempFileName.toStdString();
	sniffer.set_openfile();


	//启用和禁用按钮
	gui.actionStop->setEnabled(true);
	gui.actionRestart->setEnabled(true);
	gui.actionStart->setEnabled(false);
	gui.actionOpen->setEnabled(false);
	gui.actionSave->setEnabled(false);
	gui.actionSelectInterface->setEnabled(false);
	gui.actionSend->setEnabled(false);
	gui.buttonApply->setEnabled(false);
	gui.buttonClear->setEnabled(false);

	//清除上次捕获的数据
	packetsRaw.clear();
	packetsStr.clear();
	newPacketRaw = nullptr;
	newPacketRawLength = 0;

	sniffer.caplen.clear();
	sniffer.pkt_data.clear();
	sniffer.time_stamp.clear();
	processIndex = 0;
	stat.fill(0);

	tableModel.clear();
	listModel.clear();
	treeData.clear();
	while (treeWidget->topLevelItemCount() > 0)
		treeWidget->takeTopLevelItem(0);

	//状态设为未保存
	isSave = false;

	//启动捕获和解析子线程
	captureThread->start();
	processThread->start();

	//发送信号，开始捕获数据包
	emit captureStarted(&sniffer, false);
}

/// <summary>
/// 点击停止按钮的槽函数。改变按钮的可用性，开始捕获数据包。
/// </summary>
void Core::stopCapture()
{
	//启用和禁用按钮
	gui.actionStop->setEnabled(false);
	gui.actionRestart->setEnabled(false);
	gui.actionStart->setEnabled(true);
	gui.actionOpen->setEnabled(true);
	gui.actionSave->setEnabled(true);
	gui.actionSelectInterface->setEnabled(true);
	gui.actionSend->setEnabled(true);
	gui.buttonApply->setEnabled(true);
	gui.buttonClear->setEnabled(true);


	//结束捕获子线程
	captureWork->stop();
	captureThread->quit();
	captureThread->wait();
	//关闭临时文件
	sniffer.close_file();
}

/// <summary>
/// 点击重新开始按钮的槽函数。
/// </summary>
void Core::restartCapture()
{
	//如果有未保存的数据包，提示用户保存
	if (!isSave && tableModel.rowCount() > 0)
	{
		int res = QMessageBox::warning(window, tr("Unsaved packets"),
			tr("Do you want to save the captured packets before startting a new capture?\nYour captured packets will be lost if you don't save them."),
			tr("Save"), tr("Discard"));
		if (res == 0 && !saveFile())
			return;
	}
	//状态设为已保存
	isSave = true;
	//重新开始即为先停止再开始
	stopCapture();
	startCapture();
}


/// <summary>
/// 打开捕获文件
/// </summary>
void Core::openFile()
{
	//如果有未保存的数据包，提示用户保存
	if (!isSave && tableModel.rowCount() > 0)
	{
		int res = QMessageBox::warning(window, tr("Unsaved packets"),
			tr("Do you want to save the captured packets before opening another file?\nYour captured packets will be lost if you don't save them."),
			tr("Save"), tr("Discard"));
		if (res == 0 && !saveFile())
			return;
	}
	//打开文件对话框
	QString fileName = QFileDialog::getOpenFileName(window, tr("Open Capture File"), ".", tr("Capture files(*.pcap)"));

	if (QFile::exists(fileName))
	{
		//清除上次的数据
		packetsRaw.clear();
		packetsStr.clear();
		newPacketRaw = nullptr;
		newPacketRawLength = 0;
		tableModel.clear();
		listModel.clear();
		treeData.clear();
		sniffer.caplen.clear();
		sniffer.pkt_data.clear();
		sniffer.time_stamp.clear();
		processIndex = 0;
		stat.fill(0);

		//如果打不开文件，提示用户
		bool res = sniffer.open_file(fileName.toStdString().c_str());
		if (!res)
		{
			QMessageBox::critical(window, tr("Error"), tr("Failed to read file. The capture file may be corrupt."), QMessageBox::Ok);
		}
		//解析文件
		while (processIndex < sniffer.pkt_data.size())
		{
			onPacketCaptured();
		}
	}
}

/// <summary>
/// 点击保存按钮的槽函数。
/// </summary>
/// <returns>若成功保存，返回true，否则返回false</returns>
bool Core::saveFile()
{
	//打开保存对话框
	QString fileName = QFileDialog::getSaveFileName(window, tr("Save Capture File"), ".", tr("Capture files(*.pcap)"));

	if (!fileName.isEmpty())
	{
		//如果存在同名文件则进行替换
		if (QFile::exists(fileName))
		{
			//如果文件被占用则提示用户
			if (!QFile::remove(fileName))
			{
				QMessageBox::critical(window, tr("Error"), tr("Failed to save capture file. Please try another file name."));
			}
		}
		tempFile.copy(fileName);
		isSave = true;
	}
	return isSave;
}

/// <summary>
/// 对捕获的原始数据进行处理。
/// </summary>
void Core::onPacketCaptured()
{
	if (sniffer.pkt_data.size() > 0 && processIndex < sniffer.pkt_data.size())
	{
		newPacketRaw = sniffer.pkt_data[processIndex];	//获取原始数据
		newPacketRawLength = sniffer.caplen[processIndex];	//获取数据长度

		//将数据包比特流转换为十六进制和Ascii码
		QString str;
		QString ascii;
		QVector<QString> packetStr;
		//添加行号
		str.append(QString("%1  ").arg(0, 4, 16, QLatin1Char('0')));
		for (int i = 0; i < newPacketRawLength; i++)
		{

			//将数据转换为十六进制
			str.append(QString("%1 ").arg(newPacketRaw[i], 2, 16, QLatin1Char('0')));
			//将数据转换为Ascii码
			if (isprint(newPacketRaw[i]))
			{
				ascii.append(QString(newPacketRaw[i]).toLatin1());
			}
			else
			{
				ascii.append(".");
			}
			//格式化
			if (i != 0 && (i + 1) % 16 == 0 || i == newPacketRawLength - 1)
			{
				str = str.leftJustified(55, ' ');
				str.append("  " + ascii);
				packetStr.append(str);
				ascii.clear();
				str.clear();
				str.append(QString("%1  ").arg(i + 1, 4, 16, QLatin1Char('0')));
				continue;
			}
			if (i != 0 && (i + 1) % 8 == 0)
			{
				str.append(" ");
				ascii.append(" ");
			}
		}
		packetsStr.append(packetStr);

		//解析数据包
		analyzer.Analyze(newPacketRawLength, newPacketRaw);
		analyzer.ParseMACPacket();
		//数据包的简要信息
		QVector<QString> info;

		for (int i = 0; i < analyzer.info.size(); i++)
		{
			info.append(QString::fromStdString(analyzer.info[i]));
		}
		//添加时间戳
		info[0] = QString::number(sniffer.time_stamp[processIndex].tv_sec - sniffer.time_stamp[0].tv_sec +
			(sniffer.time_stamp[processIndex].tv_usec - sniffer.time_stamp[0].tv_usec) * 1e-6, 'f', 6);
		//添加简要信息到table
		tableModel.addRow(info, newPacketRawLength);
		//添加十六进制和Ascii码到list
		listModel.addData(packetStr);
		//添加详细信息到tree
		addTreeData();

		//根据解析出的协议类型进行统计
		stat[0]++;
		if (info[3] == "ARP")
			stat[1]++;
		else if (info[3] == "ICMP" || info[3] == "ICMPv6")
			stat[2]++;
		else if (info[3] == "IGMP")
			stat[3]++;
		else if (info[3] == "UDP")
			stat[4]++;
		else if (info[3] == "TCP")
			stat[5]++;
		else if (info[3] == "HTTP")
			stat[6]++;

		QString statStr = QString("Packets: %0, ARP: %1, ICMP: %2 IGMP: %3 UDP: %4 TCP: %5").arg(stat[0]).arg(stat[1]).arg(stat[2]).arg(stat[3]).arg(stat[4]).arg(stat[5]).arg(stat[6]);
		gui.labelStat->setText(statStr);

		processIndex++;
	}

	//如果解析的数量大于等于目前捕获到的数据，则返回等待。
	if (processIndex > sniffer.pkt_data.size())
		return;

	//发送本次解析完成信号
	emit processFinished();
}

/// <summary>
/// 退出应用程序
/// </summary>
void Core::quit()
{
	//如果有未保存的数据包，提示用户保存
	if (!isSave && tableModel.rowCount() > 0)
	{
		int res = QMessageBox::warning(window, tr("Unsaved packets"),
			tr("Do you want to save the captured packets before quitting?\nYour captured packets will be lost if you don't save them."),
			tr("Save"), tr("Discard"));
		if (res == 0 && !saveFile())
			return;
	}

	//删除临时文件
	QDir path(".\\temp");
	if (path.exists())
	{
		path.removeRecursively();
		path.mkpath("..\\temp");
	}
	//退出程序
	app->quit();
}

/// <summary>
/// 网络接口选择对话框
/// </summary>	
void Core::interfaceSelectionDialog()
{
	//设置对话框界面
	QDialog* dialog = new QDialog(window);
	Ui::InterfaceSelectionUI ui;
	ui.setupUi(dialog);
	dialog->setAttribute(Qt::WA_DeleteOnClose);

	//添加菜单项
	for (int i = 0; i < sniffer.devs_name.size(); i++)
	{
		ui.deviceMenu->addItem(QString::fromStdString(sniffer.devs_name[i]));
	}
	ui.deviceMenu->setCurrentIndex(captureInterfaceIndex);
	ui.deviceDescription->setText(QString::fromStdString(sniffer.devs_description[captureInterfaceIndex]));

	//接口描述随用户选择更新
	QObject::connect(ui.deviceMenu, QOverload<int>::of(&QComboBox::activated),
		[=](int i) {ui.deviceDescription->setText(QString::fromStdString(sniffer.devs_description[i])); });
	//点击确认和取消按钮关闭对话框
	QObject::connect(ui.okButton, &QPushButton::clicked, dialog, &QDialog::accept);
	QObject::connect(ui.cancelButton, &QPushButton::clicked, dialog, &QDialog::reject);
	//点击确认按钮设置捕获接口
	QObject::connect(dialog, &QDialog::accepted, [=]() {
		captureInterfaceIndex = ui.deviceMenu->currentIndex();
		sniffer.set_sniffer_devs(captureInterfaceIndex);
		sender.fp = sniffer.fp; });
	//显示对话框
	dialog->exec();
}

/// <summary>
/// 发送数据包对话框
/// </summary>
void Core::sendDialog()
{
	//设置对话框界面
	QDialog* dialog = new QDialog(window);
	Ui::SendUI ui;
	ui.setupUi(dialog);
	dialog->setAttribute(Qt::WA_DeleteOnClose);

	//设置协议类型单选按钮
	QObject::connect(ui.MAC, &QRadioButton::clicked, [=]() {
		sendType = 0;
		ui.ipBox->setEnabled(false);
		ui.arpBox->setEnabled(false);
		ui.icmpBox->setEnabled(false);
		ui.udpBox->setEnabled(false);
		ui.tcpBox->setEnabled(false); });
	QObject::connect(ui.IPv4, &QRadioButton::clicked, [=]() {
		sendType = 1;
		ui.ipBox->setEnabled(true);
		ui.arpBox->setEnabled(false);
		ui.icmpBox->setEnabled(false);
		ui.udpBox->setEnabled(false);
		ui.tcpBox->setEnabled(false); });
	QObject::connect(ui.ARP, &QRadioButton::clicked, [=]() {
		sendType = 2;
		ui.ipBox->setEnabled(false);
		ui.arpBox->setEnabled(true);
		ui.icmpBox->setEnabled(false);
		ui.udpBox->setEnabled(false);
		ui.tcpBox->setEnabled(false); });
	QObject::connect(ui.ICMP, &QRadioButton::clicked, [=]() {
		sendType = 3;
		ui.ipBox->setEnabled(true);
		ui.arpBox->setEnabled(false);
		ui.icmpBox->setEnabled(true);
		ui.udpBox->setEnabled(false);
		ui.tcpBox->setEnabled(false); });
	QObject::connect(ui.UDP, &QRadioButton::clicked, [=]() {
		sendType = 4;
		ui.ipBox->setEnabled(true);
		ui.arpBox->setEnabled(false);
		ui.icmpBox->setEnabled(false);
		ui.udpBox->setEnabled(true);
		ui.tcpBox->setEnabled(false); });
	QObject::connect(ui.TCP, &QRadioButton::clicked, [=]() {
		sendType = 5;
		ui.ipBox->setEnabled(true);
		ui.arpBox->setEnabled(false);
		ui.icmpBox->setEnabled(false);
		ui.udpBox->setEnabled(false);
		ui.tcpBox->setEnabled(true); });
	ui.MAC->click();

	//限制输入
	QRegExp macRx("^[0-9a-fA-F]{12}$");
	QRegExpValidator* macValidator = new QRegExpValidator(macRx);
	ui.macSrc->setValidator(macValidator);
	ui.macDst->setValidator(macValidator);
	ui.arpSrcMac->setValidator(macValidator);
	ui.arpDstMac->setValidator(macValidator);
	QRegExp ipRx(R"(^((2(5[0-5]|[0-4]\d))|[0-1]?\d{1,2})(\.((2(5[0-5]|[0-4]\d))|[0-1]?\d{1,2})){3}$)");
	QRegExpValidator* ipValidator = new QRegExpValidator(ipRx);
	ui.ipSrc->setValidator(ipValidator);
	ui.ipDst->setValidator(ipValidator);
	ui.arpSrcIp->setValidator(ipValidator);
	ui.arpDstIp->setValidator(ipValidator);
	QRegExp portRx(R"(^[0-9]$|(^[1-9][0-9]$)|(^[1-9][0-9][0-9]$)|(^[1-9][0-9][0-9][0-9]$)|(^[1-9][0-9][0-9][0-9][0-9]$)|^6[0-5][0-5][0-3][0-5]$)");
	QRegExpValidator* portValidator = new QRegExpValidator(portRx);
	ui.udpSrcPort->setValidator(portValidator);
	ui.udpDstPort->setValidator(portValidator);
	ui.tcpSrcPort->setValidator(portValidator);
	ui.tcpDstPort->setValidator(portValidator);
	ui.tcpWindow->setValidator(portValidator);
	ui.tcpUgPointer->setValidator(portValidator);
	ui.ipId->setValidator(portValidator);
	ui.icmpSeq->setValidator(portValidator);
	ui.icmpId->setValidator(portValidator);
	QRegExp twoBitRx("[0123]{1}");
	QRegExpValidator* twoBitValidator = new QRegExpValidator(twoBitRx);
	ui.ipEcn->setValidator(twoBitValidator);
	QRegExp fiveBitRx("^[0-9]$|^[1-5][0-9]$|^6[0-3]$");
	QRegExpValidator* fiveBitValidator = new QRegExpValidator(fiveBitRx);
	ui.ipDscp->setValidator(fiveBitValidator);
	QRegExp eightBitRx(R"(^\d{1,2}|[1]\d{2}|2[0-4]\d|25[0-5]$)");
	QRegExpValidator* eightBitValidator = new QRegExpValidator(eightBitRx);
	ui.ipTtl->setValidator(eightBitValidator);
	ui.icmpType->setValidator(eightBitValidator);
	ui.icmpCode->setValidator(eightBitValidator);
	QRegExp opCodeRx("[0-4]{1}");
	QRegExpValidator* arpOpCodeValidator = new QRegExpValidator(opCodeRx);
	ui.arpOpCode->setValidator(arpOpCodeValidator);
	QIntValidator* ipOffsetValidator = new QIntValidator(0, 8191);
	ui.ipOffset->setValidator(ipOffsetValidator);
	QIntValidator* tcpOffsetValidator = new QIntValidator(5, 15);
	ui.tcpOffset->setValidator(tcpOffsetValidator);

	//将输入框存入向量，便于下面引用
	QVector<QLineEdit*> inputs = { ui.macSrc, ui.macDst,ui.ipSrc,ui.ipDst,ui.ipDscp,ui.ipEcn,ui.ipTtl,ui.ipOffset,ui.ipId,
		ui.arpSrcMac,ui.arpDstMac,ui.arpSrcIp,ui.arpDstIp,ui.icmpType,ui.icmpCode,ui.icmpId,ui.icmpSeq,ui.udpSrcPort,ui.udpDstPort,
		ui.tcpSrcPort,ui.tcpDstPort,ui.tcpSeq,ui.tcpAck,ui.tcpOffset,ui.tcpWindow,ui.tcpUgPointer };

	//点击发送按钮的事件
	QObject::connect(ui.sendButton, &QPushButton::clicked, [=] {
		//检验输入合法性
		bool isError = false;
		for (auto input : inputs)
		{
			if (!input->isEnabled())
			{
				continue;
			}
			QString str = input->text();
			int pos = 0;
			if (input->validator())
			{
				if (input->validator()->validate(str, pos) == QValidator::Acceptable)
				{
					input->setStyleSheet("background-color:rgb(255, 255, 255)");
				}
				else
				{
					isError = true;
					input->setStyleSheet("background-color:rgb(255, 175, 175)");
				}
			}
		}
		//如果输入有误，提示用户
		if (isError)
		{
			QMessageBox::critical(dialog, tr("Error"), tr("Invalid input. Hover over the red input boxes for tips."));
			return;
		}

		//处理数据字段
		QString dataStr = ui.data->toPlainText();
		//奇数个字符的输入，补一个0使其变为偶数个
		if (dataStr.length() % 2 == 1)
		{
			dataStr.append("0");
		}
		sender.userpack = new int[dataStr.length() / 2];
		//字符串转换为十六进制数字
		for (int i = 0; i < dataStr.length() / 2; i++)
		{
			sender.userpack[i] = dataStr.mid(i * 2, 2).toInt(nullptr, 16);
		}

		//构造数据包
		switch (sendType)
		{
			//MAC
		case 0:
			for (int i = 0; i < 6; i++)
			{
				sender.mac.hostmac[i] = ui.macSrc->text().mid(i * 2, 2).toInt(nullptr, 16);
			}
			for (int i = 0; i < 6; i++)
			{
				sender.mac.dstmac[i] = ui.macDst->text().mid(i * 2, 2).toInt(nullptr, 16);
			}
			sender.mac.type[0] = 0;
			sender.mac.type[1] = 0;
			sender.len = dataStr.length() / 2 + 14;
			break;
		case 2:
			for (int i = 0; i < 6; i++)
			{
				sender.mac.hostmac[i] = ui.macSrc->text().mid(i * 2, 2).toInt(nullptr, 16);
			}
			for (int i = 0; i < 6; i++)
			{
				sender.mac.dstmac[i] = ui.macDst->text().mid(i * 2, 2).toInt(nullptr, 16);
			}
			sender.arp.op = ui.arpOpCode->text().toInt(nullptr, 10);
			for (int i = 0; i < 6; i++)
			{
				sender.arp.hostmac[i] = ui.arpSrcMac->text().mid(i * 2, 2).toInt(nullptr, 16);
			}
			for (int i = 0; i < 6; i++)
			{
				sender.arp.dstmac[i] = ui.arpDstMac->text().mid(i * 2, 2).toInt(nullptr, 16);
			}
			for (int i = 0; i < 4; i++)
			{
				sender.arp.hostip[i] = ui.arpSrcIp->text().split(".")[i].toInt(nullptr, 10);
			}
			for (int i = 0; i < 4; i++)
			{
				sender.arp.dstip[i] = ui.arpDstIp->text().split(".")[i].toInt(nullptr, 10);
			}
			sender.len = 42;
			break;
			//IPv4及以上
		default:
			for (int i = 0; i < 6; i++)
			{
				sender.mac.hostmac[i] = ui.macSrc->text().mid(i * 2, 2).toInt(nullptr, 16);
			}
			for (int i = 0; i < 6; i++)
			{
				sender.mac.dstmac[i] = ui.macDst->text().mid(i * 2, 2).toInt(nullptr, 16);
			}
			sender.ip4.dscp = ui.ipDscp->text().toInt(nullptr, 10);
			sender.ip4.ecn = ui.ipEcn->text().toInt(nullptr, 10);
			sender.ip4.id = ui.ipId->text().toInt(nullptr, 10);
			sender.ip4.depart = ui.reserved->isChecked() ? 4 : 0;
			sender.ip4.depart += ui.df->isChecked() ? 2 : 0;
			sender.ip4.depart += ui.mf->isChecked() ? 1 : 0;
			sender.ip4.offset = ui.ipOffset->text().toInt(nullptr, 10);
			sender.ip4.ttl = ui.ipTtl->text().toInt(nullptr, 10);
			sender.ip4.ptc = 253;
			for (int i = 0; i < 4; i++)
			{
				sender.ip4.hostip[i] = ui.ipSrc->text().split(".")[i].toInt(nullptr, 10);
			}
			for (int i = 0; i < 4; i++)
			{
				sender.ip4.dstip[i] = ui.ipDst->text().split(".")[i].toInt(nullptr, 10);
			}

			//IPv4
			if (sendType == 1)
			{
				sender.len = dataStr.length() / 2 + 34;
			}
			//ICMP
			else if (sendType == 3)
			{
				sender.icp.type = ui.icmpType->text().toInt(nullptr, 10);
				sender.icp.code = ui.icmpCode->text().toInt(nullptr, 10);
				sender.icp.id = ui.icmpId->text().toInt(nullptr, 10);
				sender.icp.seq = ui.icmpSeq->text().toInt(nullptr, 10);
				sender.len = dataStr.length() / 2 + 42;
			}
			//UDP
			else if (sendType == 4)
			{
				sender.udp.hostport = ui.udpSrcPort->text().toInt(nullptr, 10);
				sender.udp.dstport = ui.udpDstPort->text().toInt(nullptr, 10);
				sender.len = dataStr.length() / 2 + 42;
			}
			//TCP
			else
			{
				sender.tcp.hostport = ui.tcpSrcPort->text().toInt(nullptr, 10);
				sender.tcp.dstport = ui.tcpDstPort->text().toInt(nullptr, 10);
				sender.tcp.seq = ui.tcpSeq->text().toUInt(nullptr, 10);
				sender.tcp.conf = ui.tcpAck->text().toUInt(nullptr, 10);
				sender.tcp.offset = ui.tcpOffset->text().toInt(nullptr, 10);
				sender.tcp.aec = ui.AEC->isChecked() ? 1 : 0;
				sender.tcp.cwr = ui.CWR->isChecked() ? 1 : 0;
				sender.tcp.ece = ui.ECE->isChecked() ? 1 : 0;
				sender.tcp.urg = ui.URG->isChecked() ? 1 : 0;
				sender.tcp.ack = ui.ACK->isChecked() ? 1 : 0;
				sender.tcp.psh = ui.PSH->isChecked() ? 1 : 0;
				sender.tcp.rst = ui.RST->isChecked() ? 1 : 0;
				sender.tcp.syn = ui.SYN->isChecked() ? 1 : 0;
				sender.tcp.fin = ui.FIN->isChecked() ? 1 : 0;
				sender.tcp.win = ui.tcpWindow->text().toInt(nullptr, 10);
				sender.tcp.up = ui.tcpUgPointer->text().toInt(nullptr, 10);
				sender.tcp.op = new u_int8_t[sender.tcp.offset * 4 - 20];

				QString optionStr = ui.tcpOptions->text();

				optionStr.resize((sender.tcp.offset * 4 - 20) * 2, '0');
				//option字段的输入转换为十六进制
				for (int i = 0; i < optionStr.length() / 2; i++)
				{
					sender.tcp.op[i] = optionStr.mid(i * 2, 2).toInt(nullptr, 16);
				}
				sender.len = dataStr.length() / 2 + sender.tcp.offset * 4 + 34;
			}
		}
		//发送数据包
		sender.packetype = sendType;
		int res = sender.senduser(ui.times->value());
		//根据发送的结果，弹出对话框告知用户
		if (res == 0)
		{
			QMessageBox::information(dialog, tr("Infomation"), tr("Packets are sent successfully."));
		}
		else if (res == -1)
		{
			QMessageBox::critical(dialog, tr("Error"), tr("Failed to send packets."));
		}
		else
		{
			QMessageBox::critical(dialog, tr("Error"), tr("Failed to construct packets. Please check your input."));
		}
		});
	
	//从文件发送数据包
	QObject::connect(ui.fileButton, &QPushButton::clicked, [=]() {
		QString fileName = QFileDialog::getOpenFileName(window, tr("Open Capture File"), ".", tr("Capture files(*.pcap)"));
		if (!QFile::exists(fileName))
		{
			return;
		}
		sender.file = fileName.toStdString();
		//根据发送的结果，弹出对话框告知用户
		int res = sender.sendfile(0);
		if (res == 0)
		{
			QMessageBox::information(dialog, tr("Infomation"), tr("Packets are sent successfully."));
		}
		else if (res == -1)
		{
			QMessageBox::critical(window, tr("Error"), tr("Failed to read file. The capture file may be corrupt."));
		}
		else
		{
			QMessageBox::warning(dialog, tr("Warning"), tr("Some packets are failed to send. Please try again."));
		}
		});

	dialog->exec();
}

/// <summary>
/// 将语言切换到中文
/// </summary>
void Core::changeToChinese()
{
	translator->load("Translation_zh_Hans.qm");
	app->installTranslator(translator);
	gui.retranslateUi(window);
	//将语言设置保存到配置文件
	QSettings settings("./lang.ini", QSettings::IniFormat);
	settings.setValue("lang", "zh-CN");
}

/// <summary>
/// 将语言切换到英文
/// </summary>
void Core::changeToEnglish()
{
	app->removeTranslator(translator);
	gui.retranslateUi(window);
	//将语言设置保存到配置文件
	QSettings settings("./lang.ini", QSettings::IniFormat);
	settings.setValue("lang", "en-US");
}

/// <summary>
/// 打开关于对话框
/// </summary>
void Core::aboutDialog()
{
	QDialog* dialog = new QDialog(window);
	Ui::AboutUI ui;
	ui.setupUi(dialog);
	dialog->setAttribute(Qt::WA_DeleteOnClose);

	dialog->show();
}

/// <summary>
/// 应用捕获过滤器
/// </summary>
void Core::applyFilter()
{
	//如果过滤表达式语法正确，输入框变为绿色。若错误，输入框变为红色并弹窗提示
	switch (sniffer.set_filter(gui.inputFilter->text().toStdString()))
	{
	case -1:
		gui.inputFilter->setStyleSheet("background-color:rgb(255, 175, 175)");
		QMessageBox::critical(window, tr("Error"), tr("Failed to set the filter: syntax error."));
		break;
	case -2:
		gui.inputFilter->setStyleSheet("background-color:rgb(255, 175, 175)");
		QMessageBox::critical(window, tr("Error"), tr("Failed to set the filter."));
		break;
	default:
		gui.inputFilter->setStyleSheet("background-color:rgb(175, 255, 175)");
		break;
	}
}

/// <summary>
/// 清除捕获过滤器
/// </summary>
void Core::clearFilter()
{
	//清除
	gui.inputFilter->clear();
	sniffer.set_filter("");
	//输入框恢复白色
	gui.inputFilter->setStyleSheet("background-color:rgb(255, 255, 255)");
}

/// <summary>
/// 复制简要信息
/// </summary>
void Core::tableDataCopy()
{
	int index = gui.tableView->currentIndex().row();
	if (index < 0)
		return;
	QString data = QString();
	for (int i = 0; i < tableModel.tableData.at(index).size(); i++)
	{
		data.append(tableModel.tableData.at(index).at(i));
		data.append("\t");
	}
	data.truncate(data.size() - 1);
	clipboard->setText(data);
}

/// <summary>
/// 复制十六进制和Ascii码
/// </summary>
void Core::listDataCopy()
{
	int index = gui.tableView->currentIndex().row();
	if (index < 0)
		return;
	QString data = "Hex Dump:\n";
	for (int i = 0; i < listModel.listData.at(index).size(); i++)
	{
		data.append(listModel.listData.at(index).at(i).mid(6, 49));
		data.append("\n");
	}
	data.append("\nAscii Dump:\n");
	for (int i = 0; i < listModel.listData.at(index).size(); i++)
	{
		data.append(listModel.listData.at(index).at(i).mid(57, 17));
		data.append("\n");
	}
	clipboard->setText(data);
}