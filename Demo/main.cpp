
#include <QDir>
#include <QProcess>
#include <QApplication>
#include <QStandardPaths>
#include <QSplashScreen>
#include <QJsonDocument>
#include <QJsonObject>

#include <QLibraryInfo>
#include <String.h>
#include <windows.h>
#include <iostream>
#include <winuser.h>
#include "glog/logging.h"
#include "MainWindow.h"

#include <QTranslator>
#include "QGuiApplication"

#if _MSC_VER >= 1600  
#pragma execution_character_set("utf-8")
#endif

/// <summary>
/// 读取样式表信息，并返回样式表内容
/// </summary>
/// <param name="sheetName">样式表名称链表</param>
/// <returns></returns>
QString loadStyleSheet(const QStringList& sheetName)
{
	QString styleSheet;
	for (auto& itr : sheetName)
	{
		//QFile file("D:/workspace/ASTM/Demo/Resources/ry_systle.css");
        QFile file(":/css/ry_systle.css");
		bool b = file.open(QFile::ReadOnly);
		if (file.isOpen())
		{
			styleSheet += QString(file.readAll()) + "";

		}
	}
	return styleSheet;
}
void initGoogleLog() {
	google::InitGoogleLogging("ASTM_Demo");
	FLAGS_alsologtostderr = true;
	FLAGS_colorlogtostderr = true;   
}


void initApplication() {
	initGoogleLog();
}

int main(int argc, char* argv[])
{
	initApplication();
	QApplication a(argc, argv);
	QStringList cssFiles;
	cssFiles << "ry_systle";
	a.setStyleSheet(loadStyleSheet(cssFiles));
	DLOG(INFO) << "test";
	//QTranslator tsor; //全局显示中文
	////创建翻译器
	//bool bret = tsor.load(":/Translator/RY3D_ASTN_CN.qm");    //加载语言包
	//
	//qApp->installTranslator(&tsor); //安装翻译器

	
	MainWindow w;
	w.show();
	return a.exec();
   
}
