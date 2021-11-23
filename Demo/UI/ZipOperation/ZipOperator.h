/**
 * �ļ����ļ��н�ѹ������
 * �����м��ܽ�ѹ����
 */

#ifndef ZIPOPERATOR_H
#define ZIPOPERATOR_H

#include <QObject>
#include "QDir"

class QuaZip;
class QIODevice;
class ZipOperator : public QObject
{
    Q_OBJECT
public:
    explicit ZipOperator(QObject *parent = nullptr);

	/**
	 * @brief ����ѹ�����߽�ѹ�Ƿ���ֹ
	 * @param bStop true ��ֹ false ����
	*/
	static void setStop(bool bStop);
    /**
     * @brief ѹ�������ļ�
     * @param fileCompressed ѹ������ļ�
     * @param file ��ѹ�����ļ�
     * @param bEncrypt �Ƿ����
     * @return true �ɹ� false ʧ��
    */
    static bool compressFile(QString fileCompressed, QString file, bool bEncrypt = false);

    /**
     * @brief ������ļ�ѹ����һ���ļ�
     * @param fileCompressed ѹ������ļ�
     * @param files ��ѹ�����ļ��б�
     * @param bEncrypt �Ƿ����
     * @return  true �ɹ� false ʧ��
    */
    static bool compressFiles(QString fileCompressed, QStringList files, bool bEncrypt = false);

    /**
     * @brief ѹ�������ļ���
     * @param fileCompressed ѹ������ļ�
     * @param dir ��ѹ�����ļ���
	 * @param recursive �Ƿ�ݹ�����Ŀ¼������ͨ�ļ�
     * @param bEncrypt �Ƿ�ʹ�ü���
     * @return true �ɹ� false ʧ��
    */
    static bool compressDir(QString fileCompressed, QString dir = QString(), bool recursive = true, bool bEncrypt = false);

	/**
	 * @brief ѹ�������ļ���
	 * @param fileCompressed ѹ������ļ�
	 * @param dir ��ѹ�����ļ���
	 * @param recursive �Ƿ�ݹ�����Ŀ¼��������ͨ�ļ�
	 * @param filters �ļ�ɸѡ����Ҫ���ʲô������������������Ŀ¼(����ݹ���)��Ѱ��Ҫ������ļ�ʱ����Ӧ��
	 * @param bEncrypt �Ƿ�ʹ�ü���
	 * @return true �ɹ� false ʧ��
	*/
	static bool compressDir(QString fileCompressed, QString dir, bool recursive, QDir::Filters filters, bool bEncrypt = false);

	/**
	 * @brief ��ѹָ���ļ��������ؽ�ѹ���ļ����ڵ�·��
	 * @param fileCompressed ѹ���ļ�
	 * @param fileName ����ѹ���ļ�
	 * @param fileDest ��ѹ����ļ�
	 * @param bEncrypt �Ƿ���Ҫ��������
	 * @return QString ��ѹ���ļ����ڵ�·��
	*/
	static QString extractFile(QString fileCompressed, QString fileName, QString fileDest = QString(), bool bEncrypt = false);

	/**
	 * @brief ��ѹָ���б��ļ��������ؽ�ѹ���ļ�·���б�
	 * @param fileCompressed ѹ���ļ�
	 * @param files ����ѹ���ļ��б�
	 * @param dir ��ѹ����ļ����·�������Ϊ�գ�Ϊ��ǰ·��
	 * @param bEncrypt �Ƿ���Ҫ��������
	 * @return QStringList ��ѹ���ļ�·���б�
	*/
	static QStringList extractFiles(QString fileCompressed, QStringList files, QString dir = QString(), bool bEncrypt = false);

	/**
	 * @brief ��ѹ�ļ��������ؽ�ѹ����ļ�·���б�
	 * @param fileCompressed ����ѹ���ļ�
	 * @param dir ��ѹ����ļ����·�������Ϊ�գ�Ϊ��ǰ·��
	 * @param bEncrypt �Ƿ���Ҫ��������
	 * @return QStringList ��ѹ���ļ�·���б�
	*/
	static QStringList extractDir(QString fileCompressed, QString dir = QString(), bool bEncrypt = false);

	/**
	 * @brief ��ѹ�ļ��������ؽ�ѹ����ļ�·���б�
	 * @param fileCompressed ����ѹ���ļ�
	 * @param fileNameCodec ��ѹ����ļ����ֲ��ñ��뷽ʽ
	 * @param dir ��ѹ����ļ����·�������Ϊ�գ�Ϊ��ǰ·��
	 * @param bEncrypt �Ƿ���Ҫ��������
	 * @return ��ѹ���ļ�·���б�
	*/
	static QStringList extractDir(QString fileCompressed, QTextCodec* fileNameCodec, QString dir = QString(), bool bEncrypt = false);

	/**
	 * @brief ��ȡѹ���ļ����ļ��б������ļ������ļ���
	 * @param fileCompressed ָ��ѹ���ļ�
	 * @return QStringList ѹ���ļ����ļ��б������ļ������ļ���
	*/
	static QStringList getFileList(QString fileCompressed);

	/**
	 * @brief ��ѹָ���ļ��������ؽ�ѹ���ļ�·��
	 * @param ioDevice ѹ���ļ���ָ��
	 * @param fileName ָ���Ĵ���ѹ�ļ�
	 * @param fileDest ��ѹ����ļ�
	 * @param bEncrypt �Ƿ���Ҫ��������
	 * @return QString ��ѹ���ļ�·��
	*/
	static QString extractFile(QIODevice* ioDevice, QString fileName, QString fileDest = QString(), bool bEncrypt = false);

	/**
	 * @brief ��ѹָ���б���ļ��������ؽ�ѹ���б��ļ�·��
	 * @param ioDevice ѹ���ļ���ָ��
	 * @param files ָ���Ĵ���ѹ�ļ��б�
	 * @param dir ��ѹ����ļ����·����Ϊ�գ���Ϊ��ǰĿ¼
	 * @param bEncrypt �Ƿ���Ҫ��������
	 * @return QStringList ��ѹ����б��ļ�·��
	*/
	static QStringList extractFiles(QIODevice* ioDevice, QStringList files, QString dir = QString(), bool bEncrypt = false);

	/**
	 * @brief ��ѹָ���ļ��������ؽ�ѹ���ļ�·���б�
	 * @param ioDevice ѹ���ļ���ָ��
	 * @param dir ��ѹ����ļ����·����Ϊ�գ���Ϊ��ǰĿ¼
	 * @param bEncrypt �Ƿ���Ҫ��������
	 * @return QStringList ��ѹ����б��ļ�·��
	*/
	static QStringList extractDir(QIODevice* ioDevice, QString dir = QString(), bool bEncrypt = false);

	/**
	 * @brief ��ѹ�ļ��������ؽ�ѹ����ļ�·���б�
	 * @param ioDevice ����ѹ���ļ�QIODeviceָ��
	 * @param fileNameCodec ��ѹ����ļ����ֲ��ñ��뷽ʽ
	 * @param dir ��ѹ����ļ����·�������Ϊ�գ�Ϊ��ǰ·��
	 * @param bEncrypt �Ƿ���Ҫ��������
	 * @return ��ѹ���ļ�·���б�
	*/
	static QStringList extractDir(QIODevice* ioDevice, QTextCodec* fileNameCodec, QString dir = QString(), bool bEncrypt = false);

	/**
	 * @brief ��ȡѹ���ļ����ļ��б������ļ������ļ���
	 * @param ioDevice ָ��ѹ���ļ�QIODeviceָ��
	 * @return QStringList ѹ���ļ����ļ��б������ļ������ļ���
	*/
	static QStringList getFileList(QIODevice* ioDevice);

private:
    
	 /**
	 * @brief ѹ�������ļ�
	 * @param zip fileCompressed ѹ������ļ�
	 * @param fileName ��ѹ�����ļ�
	 * @param fileDest ѹ������ļ�����ʾ���ļ�����
	 * @param bEncrypt �Ƿ������ѹ��
	 * @return true �ɹ� false ʧ��
	  */
	static bool compressFile(QuaZip* zip, QString fileName, QString fileDest, bool bEncrypt);

    /**
     * @brief �����ļ����ݣ���һ���ļ������ݸ��Ƶ���һ���ļ���
     * @param inFile �����Ƶ��ļ�
     * @param outFile ���ƺ���ļ�
     * @return true �ɹ� false ʧ��
    */
    static bool copyData(QIODevice& inFile, QIODevice& outFile);

	/**
	 * @brief ѹ�����ļ���.
	 * @param parentZip ������Ŀ¼��QuaZip����ָ��
	 * @param dir Ҫѹ����Ŀ¼������·��
	 * @param parentDir ��ZIP��Ŀ¼��Ӧ��ȫ·�� 
	 * @param recursive �Ƿ�Ҳ�����Ŀ¼������ֻ����ļ�
	 * @param filters �ļ�ɸѡ����Ҫ���ʲô������������������Ŀ¼(����ݹ���)��Ѱ��Ҫ������ļ�ʱ����Ӧ��
	 * @param bEncrypt �Ƿ������ѹ��
	 * @return true �ɹ� false ʧ��
	*/
	static bool compressSubDir(QuaZip* parentZip, QString dir, QString parentDir, bool recursive,
		QDir::Filters filters, bool bEncrypt);

	/**
	 * @brief ��ѹ���ļ���ѹ��ָ���ļ�����
	 * @param zip ����ѹ���ļ�
	 * @param dir ��Ž�ѹ����ļ�����·��
	 * @param bEncrypt �Ƿ���Ҫ��������
	 * @return QStringList ���ؽ�ѹ����ļ��б�
	*/
	static QStringList extractDir(QuaZip& zip, const QString& dir, bool bEncrypt);

	/**
	 * @brief ��ȡѹ���ļ��е��ļ��б�
	 * @param zip ѹ���ļ�
	 * @return QStringList ѹ���ļ��е��ļ��б�
	*/
	static QStringList getFileList(QuaZip* zip);

	/**
	 * @brief ��ѹָ���ļ��������ؽ�ѹ���ļ����ڵ�·��
	 * @param zip ѹ���ļ�
	 * @param fileName ����ѹ���ļ�
	 * @param fileDest ��ѹ����ļ�
	 * @param bEncrypt �Ƿ���Ҫ��������
	 * @return QString ��ѹ���ļ����ڵ�·��
	*/
	static QString extractFile(QuaZip& zip, QString fileName, QString fileDest, bool bEncrypt);

	/**
	 * @brief ��ѹָ�����ļ��б������ؽ�ѹ���ļ��б�
	 * @param zip ѹ���ļ�
	 * @param files ����ѹ���ļ��б�
	 * @param dir ��ѹ���ļ���ŵ�·��
	 * @param bEncrypt �Ƿ���Ҫ��������
	 * @return QStringList ��ѹ���ļ��б�
	*/
	static QStringList extractFiles(QuaZip& zip, const QStringList& files, const QString& dir, bool bEncrypt);
   
	/**
	 * @brief ��ѹָ���ļ�
	 * @param zip ѹ���ļ�
	 * @param fileName ����ѹ���ļ�
	 * @param fileDest ��ѹ����ļ�
	 * @param bEncrypt �Ƿ���Ҫ��������
	 * @return true �ɹ� false ʧ��
	*/
	static bool extractFile(QuaZip* zip, QString fileName, QString fileDest, bool bEncrypt);

	/**
	 * @brief ɾ���ļ�
	 * @param listFile ɾ�����ļ��б�
	 * @return true �ɹ� false ʧ�� 
	*/
	static bool removeFile(QStringList listFile);
	static bool bStop_;
};

#endif // ZIPOPERATOR_H
