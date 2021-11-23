#include "ZipOperationThread.h"
#include "ZipOperation/ZipOperator.h"
#include "quazip/quazip.h"

ZipOperationThread::ZipOperationThread(QObject *parent) : QThread(parent)
{
	fileCompressed_.clear();
	compressedFileList_.clear();
	bDir_ = false;
	bEncrypt_ = false;
	bCompressing_ = true;
	bStop_ = false;
}

ZipOperationThread::~ZipOperationThread()
{
	if (isRunning())
	{
		bStop_ = true;
		ZipOperator::setStop(bStop_);
		requestInterruption();
		quit();
		wait();
	}
	
}

void ZipOperationThread::setStop()
{
	bStop_ = true;
	ZipOperator::setStop(bStop_);
	requestInterruption();
	quit();
	wait();
}

void ZipOperationThread::compressOperator(const QString& fileCompressed, const QStringList& files, bool bDir, bool bEncrypt)
{
	fileCompressed_ = fileCompressed;
	compressedFileList_ = files;
	bDir_ = bDir;
	if (bDir_)
	{
		dirPath_ = files[0];
	}
	bEncrypt_ = bEncrypt;
	bCompressing_ = true;
	bStop_ = false;
	start();
}

void ZipOperationThread::unCompressOperator(const QString& fileCompressed, const QString& strDir, bool bEncrypt)
{
	fileCompressed_ = fileCompressed;
	dirPath_ = strDir;
	bEncrypt_ = bEncrypt;
	bCompressing_ = false;
	bStop_ = false;
	start();
}

bool ZipOperationThread::compressFiles(QString fileCompressed, QStringList files, bool bEncrypt)
{
	emit infoTextChangedSgn(QStringLiteral("Compressing Files: %1 ").arg(files.join(" ; ")));
	bool b = ZipOperator::compressFiles(fileCompressed, files, bEncrypt);
	emit infoTextChangedSgn(QStringLiteral("Compressing Files: %1 ").arg(b ? "success" : "failed"));
	return b;
}

bool ZipOperationThread::compressDir(QString fileCompressed, QString dir, bool bEncrypt)
{
	emit infoTextChangedSgn(QStringLiteral("Compressing Directory: %1 ").arg(dir));
	bool b = ZipOperator::compressDir(fileCompressed, dir, bEncrypt);
	emit infoTextChangedSgn(QStringLiteral("Compressing Directory: %1 ").arg(b ? "success" : "failed"));
	return b;
}

bool ZipOperationThread::extractDir(QString fileCompressed, QString dir, bool bEncrypt)
{
	emit infoTextChangedSgn(QStringLiteral("Extract file [ %1 ] to %2").arg(fileCompressed).arg(dir));
	QStringList strList = ZipOperator::extractDir(fileCompressed, dir, bEncrypt);
	emit infoTextChangedSgn(QStringLiteral("Extract file list [ %1 ]").arg(fileCompressed));
	return true;
}

void ZipOperationThread::run()
{
	while (!bStop_)
	{
		if (bCompressing_)
		{
			if (bDir_)
			{
				compressDir(fileCompressed_, dirPath_, bEncrypt_);
			}
			else
			{
				compressFiles(fileCompressed_, compressedFileList_, bEncrypt_);
			}
		}
		else
		{
			extractDir(fileCompressed_, dirPath_, bEncrypt_);
		}
		bStop_ = true;
	}
	emit finishSgn(true);
}
