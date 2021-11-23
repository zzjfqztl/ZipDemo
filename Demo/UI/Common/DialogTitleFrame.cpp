#include "DialogTitleFrame.h"
#include "QBoxLayout"
#include "QLabel"
#include "QPushButton"

/// <summary>
/// 构造函数
/// </summary>
/// <param name="title">标题内容</param>
/// <param name="parent">父窗体指针</param>
/// <param name="align">标题是否居中表示</param>
DialogTitleFrame::DialogTitleFrame(const QString& title, QWidget* parent, Qt::Alignment align) : QFrame(parent),titleContent_(title), titleAlign_(align)
{
	initUI();
}

/// <summary>
/// 设置标题内容
/// </summary>
/// <param name="title"></param>
void DialogTitleFrame::setTitle(const QString& title)
{
	titleContent_ = title;
	titleLabel_->setText(titleContent_);
}

/// <summary>
/// 界面生成部分
/// </summary>
void DialogTitleFrame::initUI()
{
	QHBoxLayout* hLayout = new QHBoxLayout();
	hLayout->setSpacing(0);
	hLayout->setMargin(0);

	setLayout(hLayout);
	if (titleAlign_ == Qt::AlignCenter)
	{
		hLayout->addStretch();
	}

	titleLabel_ = new QLabel(this);
	titleLabel_->setObjectName("titleLabel");
	titleLabel_->setText(titleContent_);
	hLayout->addWidget(titleLabel_);
	hLayout->addStretch();

	btnClose_ = new QPushButton(this);
	btnClose_->setObjectName("btnClose");
	btnClose_->setToolTip(QObject::tr("Close"));
	btnClose_->setFocusPolicy(Qt::FocusPolicy::NoFocus);
	connect(btnClose_, &QPushButton::clicked, this,&DialogTitleFrame::closeSgn);
	hLayout->addWidget(btnClose_);
	hLayout->addSpacing(10);
}
