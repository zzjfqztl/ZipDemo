#include "ZipOperator.h"
#include "quazip/quazip.h"
#include "quazip/quazipfile.h"

const QString EncryptKey_ = "ry1234";
ZipOperator::ZipOperator(QObject *parent) : QObject(parent)
{

}

void ZipOperator::setStop(bool bStop)
{
	bStop_ = bStop;
}

bool ZipOperator::copyData(QIODevice& inFile, QIODevice& outFile)
{
	while (!inFile.atEnd()) {
		if (bStop_)
		{
			return false;
		}
		char buf[4096];
		qint64 readLen = inFile.read(buf, 4096);
		if (readLen <= 0)
			return false;
		if (outFile.write(buf, readLen) != readLen)
			return false;
	}
	return true;
}


bool ZipOperator::compressSubDir(QuaZip* zip, QString dir, QString parentDir, bool recursive, QDir::Filters filters, bool bEncrypt)
{
	//�ж�Quazip��ģʽ
	if (!zip) return false;
	if (zip->getMode() != QuaZip::mdCreate &&
		zip->getMode() != QuaZip::mdAppend &&
		zip->getMode() != QuaZip::mdAdd) return false;

	// Controllo la cartella
	QDir directory(dir);
	if (!directory.exists()) return false;

	//��·��
	QDir origDirectory(parentDir);
	if (dir != parentDir) {
		QuaZipFile dirZipFile(zip);
		if (!dirZipFile.open(QIODevice::WriteOnly,
			QuaZipNewInfo(origDirectory.relativeFilePath(dir) + QLatin1String("/"), dir), bEncrypt ? EncryptKey_.toUtf8().constData() : nullptr, 0, 0)) {
			return false;
		}
		dirZipFile.close();
	}

	// �ݹ�ѹ����Ŀ¼�е��ļ�
	if (recursive) {
		// Per ogni sotto cartella
		QFileInfoList files = directory.entryInfoList(QDir::AllDirs | QDir::NoDotAndDotDot | filters);
		for (int index = 0; index < files.size(); ++index) {
			if (bStop_)
			{
				break;
			}
			const QFileInfo& file(files.at(index));
			if (!file.isDir()) // needed for Qt < 4.7 because it doesn't understand AllDirs
				continue;
			// Comprimo la sotto cartella
			if (!compressSubDir(zip, file.absoluteFilePath(), parentDir, recursive, filters,bEncrypt)) return false;
		}
	}

	// ѹ���ļ����е��ļ�
	QFileInfoList files = directory.entryInfoList(QDir::Files | filters);
	for (int index = 0; index < files.size(); ++index) {
		if (bStop_)
		{
			break;
		}
		const QFileInfo& file(files.at(index));
		// Se non e un file o e il file compresso che sto creando
		if (!file.isFile() || file.absoluteFilePath() == zip->getZipName()) continue;

		// Creo il nome relativo da usare all'interno del file compresso
		QString filename = origDirectory.relativeFilePath(file.absoluteFilePath());

		// Comprimo il file
		if (!compressFile(zip, file.absoluteFilePath(), filename,bEncrypt)) return false;
	}

	return true;
}

QStringList ZipOperator::extractDir(QuaZip& zip, const QString& dir, bool bEncrypt)
{
	bStop_ = false;
	if (!zip.open(QuaZip::mdUnzip)) {
		return QStringList();
	}
	QString cleanDir = QDir::cleanPath(dir);
	QDir directory(cleanDir);
	QString absCleanDir = directory.absolutePath();
	if (!absCleanDir.endsWith('/')) // It only ends with / if it's the FS root.
		absCleanDir += '/';
	QStringList extracted;
	if (!zip.goToFirstFile()) {
		return QStringList();
	}
	do {
		if (bStop_)
		{
			break;
		}
		QString name = zip.getCurrentFileName();
		QString absFilePath = directory.absoluteFilePath(name);
		QString absCleanPath = QDir::cleanPath(absFilePath);
		if (!absCleanPath.startsWith(absCleanDir))
			continue;
		if (!extractFile(&zip, QLatin1String(""), absFilePath,bEncrypt)) {
			removeFile(extracted);
			return QStringList();
		}
		extracted.append(absFilePath);
	} while (zip.goToNextFile());

	// Chiudo il file zip
	zip.close();
	if (zip.getZipError() != 0) {
		removeFile(extracted);
		return QStringList();
	}

	return extracted;
}

QStringList ZipOperator::extractDir(QString fileCompressed, QString dir /*= QString()*/, bool bEncrypt /*= false*/)
{
	return extractDir(fileCompressed, nullptr, dir, bEncrypt);
}

QStringList ZipOperator::extractDir(QString fileCompressed, QTextCodec* fileNameCodec, QString dir /*= QString()*/, bool bEncrypt /*= false*/)
{
	QuaZip zip(fileCompressed);
	if (fileNameCodec)
		zip.setFileNameCodec(fileNameCodec);
	return extractDir(zip, dir, bEncrypt);
}

QStringList ZipOperator::extractDir(QIODevice* ioDevice, QString dir /*= QString()*/, bool bEncrypt /*= false*/)
{
	return extractDir(ioDevice, nullptr, dir, bEncrypt);
}

QStringList ZipOperator::extractDir(QIODevice* ioDevice, QTextCodec* fileNameCodec, QString dir /*= QString()*/, bool bEncrypt)
{
	QuaZip zip(ioDevice);
	if (fileNameCodec)
		zip.setFileNameCodec(fileNameCodec);
	return extractDir(zip, dir, bEncrypt);
}

QStringList ZipOperator::getFileList(QuaZip* zip)
{
	if (!zip->open(QuaZip::mdUnzip)) {
		delete zip;
		return QStringList();
	}

	// Estraggo i nomi dei file
	QStringList lst;
	QuaZipFileInfo64 info;
	for (bool more = zip->goToFirstFile(); more; more = zip->goToNextFile()) {
		if (!zip->getCurrentFileInfo(&info)) {
			delete zip;
			return QStringList();
		}
		lst << info.name;
		//info.name.toLocal8Bit().constData()
	}

	// Chiudo il file zip
	zip->close();
	if (zip->getZipError() != 0) {
		delete zip;
		return QStringList();
	}
	delete zip;
	return lst;
}

QStringList ZipOperator::getFileList(QString fileCompressed)
{
	QuaZip* zip = new QuaZip(QFileInfo(fileCompressed).absoluteFilePath());
	return getFileList(zip);
}

QStringList ZipOperator::getFileList(QIODevice* ioDevice)
{
	QuaZip* zip = new QuaZip(ioDevice);
	return getFileList(zip);
}

QString ZipOperator::extractFile(QuaZip& zip, QString fileName, QString fileDest, bool bEncrypt)
{
	if (!zip.open(QuaZip::mdUnzip)) {
		return QString();
	}

	// Estraggo il file
	if (fileDest.isEmpty())
		fileDest = fileName;
	if (!extractFile(&zip, fileName, fileDest, bEncrypt)) {
		return QString();
	}

	// Chiudo il file zip
	zip.close();
	if (zip.getZipError() != 0) {
		removeFile(QStringList(fileDest));
		return QString();
	}
	return QFileInfo(fileDest).absoluteFilePath();
}

bool ZipOperator::extractFile(QuaZip* zip, QString fileName, QString fileDest, bool bEncrypt)
{
	//zip ��Ҫ��ѹ��ѹ���ļ�
	if (!zip) return false;
	if (zip->getMode() != QuaZip::mdUnzip) return false;

	// ��Ҫ��ѹ���ļ�
	if (!fileName.isEmpty())
		zip->setCurrentFile(fileName);
	QuaZipFile inFile(zip);
	if (!inFile.open(QIODevice::ReadOnly, bEncrypt ? EncryptKey_.toUtf8().constData() : nullptr ) || inFile.getZipError() != UNZ_OK) return false;

	// Controllo esistenza cartella file risultato
	//��ѹ���ļ��洢·��
	QDir curDir;
	if (fileDest.endsWith(QLatin1String("/"))) {
		if (!curDir.mkpath(fileDest)) {
			return false;
		}
	}
	else {
		if (!curDir.mkpath(QFileInfo(fileDest).absolutePath())) {
			return false;
		}
	}

	QuaZipFileInfo64 info;
	if (!zip->getCurrentFileInfo(&info))
		return false;

	QFile::Permissions srcPerm = info.getPermissions();
	if (fileDest.endsWith(QLatin1String("/")) && QFileInfo(fileDest).isDir()) {
		if (srcPerm != 0) {
			QFile(fileDest).setPermissions(srcPerm);
		}
		return true;
	}

	if (info.isSymbolicLink()) {
		QString target = QFile::decodeName(inFile.readAll());
		if (!QFile::link(target, fileDest))
			return false;
		return true;
	}

	// Apro il file risultato
	QFile outFile;
	outFile.setFileName(fileDest);
	if (!outFile.open(QIODevice::WriteOnly)) return false;

	// Copio i dati
	if (!copyData(inFile, outFile) || inFile.getZipError() != UNZ_OK) {
		outFile.close();
		removeFile(QStringList(fileDest));
		return false;
	}
	outFile.close();

	// Chiudo i file
	inFile.close();
	if (inFile.getZipError() != UNZ_OK) {
		removeFile(QStringList(fileDest));
		return false;
	}

	if (srcPerm != 0) {
		outFile.setPermissions(srcPerm);
	}
	return true;
}

QString ZipOperator::extractFile(QString fileCompressed, QString fileName, QString fileDest /*= QString()*/, bool bEncrypt)
{
	QuaZip zip(fileCompressed);
	return extractFile(zip, fileName, fileDest, bEncrypt);
}

QString ZipOperator::extractFile(QIODevice* ioDevice, QString fileName, QString fileDest /*= QString()*/, bool bEncrypt /*= false*/)
{
	QuaZip zip(ioDevice);
	return extractFile(zip, fileName, fileDest, bEncrypt);
}

QStringList ZipOperator::extractFiles(QuaZip& zip, const QStringList& files, const QString& dir, bool bEncrypt)
{
	bStop_ = false;
	if (!zip.open(QuaZip::mdUnzip)) {
		return QStringList();
	}

	// Estraggo i file
	QStringList extracted;
	for (int i = 0; i < files.count(); i++) {
		if (bStop_)
		{
			break;
		}
		QString absPath = QDir(dir).absoluteFilePath(files.at(i));
		if (!extractFile(&zip, files.at(i), absPath, bEncrypt)) {
			removeFile(extracted);
			return QStringList();
		}
		extracted.append(absPath);
	}

	// Chiudo il file zip
	zip.close();
	if (zip.getZipError() != 0) {
		removeFile(extracted);
		return QStringList();
	}

	return extracted;
}

QStringList ZipOperator::extractFiles(QString fileCompressed, QStringList files, QString dir /*= QString()*/, bool bEncrypt /*= false*/)
{
	QuaZip zip(fileCompressed);
	return extractFiles(zip, files, dir,bEncrypt);
}

QStringList ZipOperator::extractFiles(QIODevice* ioDevice, QStringList files, QString dir /*= QString()*/, bool bEncrypt /*= false*/)
{
	QuaZip zip(ioDevice);
	return extractFiles(zip, files, dir, bEncrypt);
}

bool ZipOperator::removeFile(QStringList listFile)
{
	bool ret = true;
	for (int i = 0; i < listFile.count(); i++) {
		ret = ret && QFile::remove(listFile.at(i));
	}
	return ret;
}

bool ZipOperator::bStop_ = false;

bool ZipOperator::compressFile(QString fileCompressed, QString file, bool bEncrypt /*= false*/)
{
	//����ѹ������ļ�����Quazip����
	QuaZip zip(fileCompressed);
	//����ѹ������ļ������ļ���
	QDir().mkpath(QFileInfo(fileCompressed).absolutePath());
	//�Դ�����ʽ��zip
	if (!zip.open(QuaZip::mdCreate)) {
		QFile::remove(fileCompressed);
		return false;
	}

	//ѹ������
	if (!compressFile(&zip, file, QFileInfo(file).fileName(),bEncrypt)) {
		QFile::remove(fileCompressed);
		return false;
	}

	//�ر�ѹ������ļ�
	zip.close();
	//ѹ��ʧ���Ƴ�ѹ������ļ�
	if (zip.getZipError() != 0) {
		QFile::remove(fileCompressed);
		return false;
	}

	return true;
}

bool ZipOperator::compressFile(QuaZip* zip, QString fileName, QString fileDest, bool bEncrypt)
{
	//�ж�Quazip��ģʽ
	if (!zip) return false;
	if (zip->getMode() != QuaZip::mdCreate &&
		zip->getMode() != QuaZip::mdAppend &&
		zip->getMode() != QuaZip::mdAdd) return false;


	//����Quazip����QuaZipFile����
	QuaZipFile outFile(zip);

	//��д��ķ�ʽ��QuaZipFile���˷����п������������
	//QuaZipNewInfo �ļ�����
	if (!outFile.open(QIODevice::WriteOnly, QuaZipNewInfo(fileDest, fileName), bEncrypt ? EncryptKey_.toUtf8().constData() : nullptr,0,8))
	{
		return false;
	}
	
	QFileInfo input(fileName);
	//�ж��Ƿ��ݷ�ʽ
	if (quazip_is_symlink(input)) {
		// Not sure if we should use any specialized codecs here.
		// After all, a symlink IS just a byte array. And
		// this is mostly for Linux, where UTF-8 is ubiquitous these days.
		QString path = quazip_symlink_target(input);
		QString relativePath = input.dir().relativeFilePath(path);
		outFile.write(QFile::encodeName(relativePath));
	}
	else {
		//����ѹ���ļ�д��ѹ������ļ�
		QFile inFile;
		inFile.setFileName(fileName);
		if (!inFile.open(QIODevice::ReadOnly))
			return false;
		if (!copyData(inFile, outFile) || outFile.getZipError() != UNZ_OK)
			return false;
		inFile.close();
	}

	outFile.close();
	if (outFile.getZipError() != UNZ_OK) return false;

	return true;
}

bool ZipOperator::compressFiles(QString fileCompressed, QStringList files, bool bEncrypt /*= false*/)
{
	bStop_ = false;
	//����ѹ������ļ�����Quazip����
	QuaZip zip(fileCompressed);
	//����ѹ������ļ������ļ���
	QDir().mkpath(QFileInfo(fileCompressed).absolutePath());
	//�Դ�����ʽ��zip
	if (!zip.open(QuaZip::mdCreate)) {
		QFile::remove(fileCompressed);
		return false;
	}

	//�����ļ��б�ѹ������
	QFileInfo info;
	for (int index = 0; index < files.size(); ++index) {
		if (bStop_)
		{
			break;
		}
		const QString& file(files.at(index));
		info.setFile(file);
		if (!info.exists() || !compressFile(&zip, file, info.fileName(),bEncrypt)) {
			QFile::remove(fileCompressed);
			return false;
		}
	}

	//�ر�ѹ������ļ�
	zip.close();
	//ѹ��ʧ���Ƴ�ѹ������ļ�
	if (zip.getZipError() != 0) {
		QFile::remove(fileCompressed);
		return false;
	}

	return true;
}

bool ZipOperator::compressDir(QString fileCompressed, QString dir /*= QString()*/, bool recursive /*= true*/, bool bEncrypt /*= false*/)
{
	return compressDir(fileCompressed, dir, recursive, QDir::Filters(), bEncrypt);
}

bool ZipOperator::compressDir(QString fileCompressed, QString dir, bool recursive, QDir::Filters filters, bool bEncrypt /*= false*/)
{
	bStop_ = false;
	// Creo lo zip
	QuaZip zip(fileCompressed);
	QDir().mkpath(QFileInfo(fileCompressed).absolutePath());
	if (!zip.open(QuaZip::mdCreate)) {
		QFile::remove(fileCompressed);
		return false;
	}

	// Aggiungo i file e le sotto cartelle
	if (!compressSubDir(&zip, dir, dir, recursive, filters,bEncrypt)) {
		QFile::remove(fileCompressed);
		return false;
	}

	// Chiudo il file zip
	zip.close();
	if (zip.getZipError() != 0) {
		QFile::remove(fileCompressed);
		return false;
	}

	return true;
}
