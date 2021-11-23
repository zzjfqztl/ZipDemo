#include "MainWindow.h"
#include "QBoxLayout"
#include "QPushButton"
#include "Common/CustomControls.h"
#include "QCheckBox"
#include <QTextEdit>
#include <QMessageBox>
#include "quazip/JlCompress.h"
#include "ZipOperation/ZipOperator.h"
#include <thread>
#include "Common/MaskWidget.h"
#include "Common/ProgressDialog.h"
#include "Common/ZipOperationThread.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
	InitUI();
	showMaximized();
}

void MainWindow::onCompressClick()
{
	if (fileSelectFrame_->GetFileList().count() <= 0)
	{
		QMessageBox::information(nullptr, QObject::tr("Information"), QObject::tr("Please choose files"));
		return;
	}
	
	ProgressDialog* dlg = new ProgressDialog(QObject::tr("Compress File"));
	MaskWidget::Instance()->setDialogNames(QStringList() << "progressDialog");
	MaskWidget::Instance()->setMainWidget(this);
	ZipOperationThread* zipThread = new ZipOperationThread();
	connect(zipThread, &ZipOperationThread::finishSgn, dlg, &ProgressDialog::onFinished);
	connect(zipThread, &ZipOperationThread::infoTextChangedSgn, dlg, &ProgressDialog::onInfoTextChanged);
	connect(zipThread, &ZipOperationThread::infoTextChangedSgn, this, [&](const QString& text) {
		textEdit_->append(text);
		});
	zipThread->compressOperator("d:/testData/test.zip", fileSelectFrame_->GetFileList(), ckbDir_->isChecked(), ckbEncrypt_->isChecked());
	textEdit_->append(QString("compress start time:") + QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss.zzz"));
	dlg->exec();
	delete dlg;
	dlg = nullptr;
	if (zipThread->isRunning())
	{
		zipThread->setStop();
		delete zipThread;
		zipThread = nullptr;
	}
	textEdit_->append(QString("compress end time:") + QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss.zzz"));
}

void MainWindow::onUnCompressClick()
{
	if (fileDirFrame_->GetFileList().count() <= 0)
	{
		QMessageBox::information(nullptr, QObject::tr("Information"), QObject::tr("Please choose files"));
		return;
	}

	ProgressDialog* dlg = new ProgressDialog(QObject::tr("Extract File"));
	MaskWidget::Instance()->setDialogNames(QStringList() << "progressDialog");
	MaskWidget::Instance()->setMainWidget(this);
	ZipOperationThread* zipThread = new ZipOperationThread();
	connect(zipThread, &ZipOperationThread::finishSgn, dlg, &ProgressDialog::onFinished);
	connect(zipThread, &ZipOperationThread::infoTextChangedSgn, dlg, &ProgressDialog::onInfoTextChanged);
	connect(zipThread, &ZipOperationThread::infoTextChangedSgn, this, [&](const QString& text) {
		textEdit_->append(text);
		});
	zipThread->unCompressOperator("d:/testData/test.zip", fileDirFrame_->GetFileList()[0], ckbEncrypt_->isChecked());
	textEdit_->append(QString("Extract start time:") + QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss.zzz"));
	dlg->exec();
	delete dlg;
	dlg = nullptr;
	if (zipThread->isRunning())
	{
		zipThread->setStop();
		delete zipThread;
		zipThread = nullptr;
	}
	textEdit_->append(QString("Extract end time:") + QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss.zzz"));
	
}

void MainWindow::onCheckDirClick()
{
	fileSelectFrame_->SetDirFlag(ckbDir_->isChecked());
	if (!ckbDir_->isChecked())
	{
		fileSelectFrame_->SetMultSelect(ckbMultSelect_->isChecked());
	}
	else
	{
		fileSelectFrame_->SetMultSelect(false);
	}
	ckbMultSelect_->setEnabled(!ckbDir_->isChecked());
}

void MainWindow::onCheckMultiSelectClick()
{
	fileSelectFrame_->SetDirFlag(ckbDir_->isChecked());
	if (!ckbDir_->isChecked())
	{
		fileSelectFrame_->SetMultSelect(ckbMultSelect_->isChecked());
	}
	else
	{
		fileSelectFrame_->SetMultSelect(false);
	}
	ckbMultSelect_->setEnabled(!ckbDir_->isChecked());
}

void MainWindow::InitUI()
{
	QWidget* centerWidget_ = new QWidget(this);
	centerWidget_->setObjectName("centerWidget");
	setCentralWidget(centerWidget_);

	QVBoxLayout* vLayout = new QVBoxLayout();
	vLayout->setSpacing(10);
	vLayout->setMargin(0);
	vLayout->setContentsMargins(20, 10, 20, 10);
	vLayout->setAlignment(Qt::AlignTop);

	centerWidget_->setLayout(vLayout);

	QHBoxLayout* hlayout = new QHBoxLayout();
	hlayout->setSpacing(20);
	hlayout->setMargin(0);
	vLayout->addLayout(hlayout);

	//文件选择
	fileSelectFrame_ = new FileSelectFrame(QObject::tr("Select Files"), this);
	hlayout->addWidget(fileSelectFrame_);

	//是否压缩文件夹
	ckbDir_ = new QCheckBox(this);
	ckbDir_->setObjectName("ckbDir");
	ckbDir_->setText(QObject::tr("Is Dir"));
	connect(ckbDir_, &QCheckBox::clicked, this, &MainWindow::onCheckDirClick);
	hlayout->addWidget(ckbDir_);

	//是否压缩多个文件
	ckbMultSelect_ = new QCheckBox(this);
	ckbMultSelect_->setObjectName("ckbMultSelect");
	ckbMultSelect_->setText(QObject::tr("Multi Select"));
	connect(ckbMultSelect_, &QCheckBox::clicked, this, &MainWindow::onCheckMultiSelectClick);
	hlayout->addWidget(ckbMultSelect_);

	//压缩按钮
	btnCompress_ = new QPushButton(this);
	btnCompress_->setObjectName("btnCompress");
	btnCompress_->setText(QObject::tr("Compress"));
	btnCompress_->setFocusPolicy(Qt::NoFocus);
	connect(btnCompress_, &QPushButton::clicked, this, &MainWindow::onCompressClick);
	hlayout->addWidget(btnCompress_);

	//解压后文件存储路径选择
	fileDirFrame_ = new FileSelectFrame(QObject::tr("Select Dir"), this,true);
	hlayout->addWidget(fileDirFrame_);

	//解压按钮
	btnUnCompress_ = new QPushButton(this);
	btnUnCompress_->setObjectName("btnUnCompress");
	btnUnCompress_->setText(QObject::tr("Extract"));
	btnUnCompress_->setFocusPolicy(Qt::NoFocus);
	connect(btnUnCompress_, &QPushButton::clicked, this, &MainWindow::onUnCompressClick);
	hlayout->addWidget(btnUnCompress_);

	ckbEncrypt_ = new QCheckBox(this);
	ckbEncrypt_->setObjectName("ckbEncrypt");
	ckbEncrypt_->setText(QObject::tr("Is Encrypt"));
	hlayout->addWidget(ckbEncrypt_);
	hlayout->addStretch();

	textEdit_ = new QTextEdit(this);
	textEdit_->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	textEdit_->setObjectName("textEdit");
	vLayout->addWidget(textEdit_);
}
