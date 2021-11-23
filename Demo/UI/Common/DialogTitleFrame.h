/**
 * 标题栏自定义控件，包含标题内容和关闭按钮，以及标题是否居中
 */

#ifndef DIALOGTITLEFRAME_H
#define DIALOGTITLEFRAME_H

#include <QWidget>
#include "QFrame"

class QLabel;
class QPushButton;
class DialogTitleFrame : public QFrame
{
    Q_OBJECT
public:
	/// <summary>
	/// 构造函数
	/// </summary>
	/// <param name="title">标题内容</param>
	/// <param name="parent">父窗体指针</param>
	/// <param name="align">标题是否居中表示,默认居中</param>
    explicit DialogTitleFrame(const QString& title,QWidget *parent = nullptr, Qt::Alignment align = Qt::AlignCenter);
	
	/// <summary>
	/// 设置标题内容
	/// </summary>
	/// <param name="title"></param>
	void setTitle(const QString& title);
signals:
	void closeSgn();
private:
	void initUI();
private:
	QLabel* titleLabel_ = nullptr;
	QPushButton* btnClose_ = nullptr;
	QString titleContent_;
	Qt::Alignment titleAlign_ = Qt::AlignCenter;
};

#endif // DIALOGTITLEFRAME_H
