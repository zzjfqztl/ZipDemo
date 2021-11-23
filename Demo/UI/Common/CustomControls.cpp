#include "CustomControls.h"
#include "QBoxLayout"
#include "QCheckBox"
#include "QComboBox"
#include "QLabel"
#include <QListView>
#include <QLineEdit>
#include <QPushButton>
#include <QFileDialog>

ComboBoxFrame::ComboBoxFrame(const QString& title, QWidget* parent /*= nullptr*/, Qt::Orientation org /*= Qt::Orientation::Horizontal*/)
	: QFrame(parent), titleContent_(title), orientation_(org)
{
	InitUI();
}

void ComboBoxFrame::InitData(const QStringList& itemList, const QStringList& itemDataList)
{
	if (itemList.count() != itemDataList.count())
	{
		return;
	}
	comboBox_->clear();
	for (int iLoop=0; iLoop < itemList.count(); iLoop++)
	{
		comboBox_->addItem(itemList[iLoop], itemDataList[iLoop]);
	}
}

QString ComboBoxFrame::GetCurrentData() const
{
	return comboBox_->currentData().toString();
}

void ComboBoxFrame::SetCurrentData(const QString& text)
{
	for (int iLoop = 0; iLoop < comboBox_->count(); iLoop++)
	{
		if (comboBox_->itemData(iLoop).toString() == text)
		{
			comboBox_->setCurrentIndex(iLoop);
			break;
		}
	}
}

void ComboBoxFrame::SetTitleLabelAlign(Qt::Alignment align)
{
	titleLabel_->setAlignment(align);
}

void ComboBoxFrame::onCurrentIndexChanged(int nIndex)
{
	emit currentTextChangedSgn(comboBox_->itemData(nIndex).toString());
}

void ComboBoxFrame::InitUI()
{
	setFrameShape(QFrame::Shape::NoFrame);
	QLayout* mainLayout = nullptr;
	if (orientation_ == Qt::Orientation::Horizontal)
	{
		mainLayout = new QHBoxLayout();
		mainLayout->setSpacing(10);
		mainLayout->setMargin(0);
	}
	else
	{
		mainLayout = new QVBoxLayout();
		mainLayout->setSpacing(3);
		mainLayout->setMargin(0);
	}
	setLayout(mainLayout);

	titleLabel_ = new QLabel(this);
	titleLabel_->setObjectName("titleLabel");
	titleLabel_->setText(titleContent_);
	mainLayout->addWidget(titleLabel_);
	/*if (orientation_ == Qt::Orientation::Horizontal)
	{
		(qobject_cast<QHBoxLayout*>(mainLayout))->addStretch();
	}*/
	comboBox_ = new QComboBox(this);
	comboBox_->setObjectName("comboBox");
	comboBox_->setView(new QListView());
	connect(comboBox_, SIGNAL(currentIndexChanged(int)), this, SLOT(onCurrentIndexChanged(int)));
	mainLayout->addWidget(comboBox_);
}

FileSelectFrame::FileSelectFrame(const QString& title, QWidget* parent /*= nullptr*/, bool bDir /*= false*/, bool bMultSelect /*=false*/ )
	:QFrame(parent), titleContent_(title), bDir_(bDir), bMultSelect_(bMultSelect)
{
	InitUI();
}

QStringList FileSelectFrame::GetFileList() const
{
	QStringList fileList;
	QString strText = lineEdit_->text().trimmed();
	fileList = strText.split(";");
	return fileList;
}


void FileSelectFrame::SetDirFlag(bool bDir)
{
	bDir_ = bDir;
}


void FileSelectFrame::SetMultSelect(bool bMultSelect)
{
	bMultSelect_ = bMultSelect;
}

void FileSelectFrame::onSelectClick()
{
	QFileDialog dlg;
	QStringList strFileList;
	if (bDir_)
	{
		//选择文件夹
		QString strDir = dlg.getExistingDirectory(nullptr, QObject::tr("Open File"), QObject::tr("./"));
		if (!strDir.isEmpty())
		{
			emit selectFilesSgn(strFileList << strDir);
		}
	}
	else
	{
		
		if (bMultSelect_)
		{
			strFileList = dlg.getOpenFileNames(nullptr, QObject::tr("Open File"), QObject::tr("./"));
			if (strFileList.count() > 0)
			{
				emit selectFilesSgn(strFileList);
			}
		}
		else
		{
			QString strName = dlg.getOpenFileName(nullptr, QObject::tr("Open File"), QObject::tr("./"));
			if (!strName.isEmpty())
			{
				emit selectFilesSgn(strFileList << strName);
			}
		}
	}
	if (strFileList.count() > 0)
	{
		lineEdit_->setText(strFileList.join(";"));
	}
	else
	{
		lineEdit_->setText("");
	}
	
}

void FileSelectFrame::InitUI()
{
	setFrameShape(QFrame::Shape::NoFrame);
	//控件水平布局
	QHBoxLayout* mainLayout = new QHBoxLayout();
	mainLayout->setSpacing(6);
	mainLayout->setMargin(0);
	setLayout(mainLayout);

	//标题
	titleLabel_ = new QLabel(this);
	titleLabel_->setObjectName("titleLabel");
	titleLabel_->setText(titleContent_);
	mainLayout->addWidget(titleLabel_);

	//选择好的文件或文件夹展示区域
	lineEdit_ = new QLineEdit(this);
	lineEdit_->setObjectName("lineEdit");
	lineEdit_->clear();
	mainLayout->addWidget(lineEdit_);

	//浏览选择按钮
	btnSelect_ = new QPushButton(this);
	btnSelect_->setObjectName("btnSelect");
	btnSelect_->setText(QObject::tr("Select"));
	btnSelect_->setFocusPolicy(Qt::NoFocus);
	connect(btnSelect_, &QPushButton::clicked, this, &FileSelectFrame::onSelectClick);
	mainLayout->addWidget(btnSelect_);
}
