#ifndef ZIPOPERATIONTHREAD_H
#define ZIPOPERATIONTHREAD_H

#include <QObject>
#include <QThread>
/**
 * @brief ѹ�����ѹ�ļ��߳�
*/
class ZipOperationThread : public QThread
{
    Q_OBJECT
public:
    /**
     * @brief ���캯��
    */
    explicit ZipOperationThread(QObject *parent = nullptr);

    /**
     * ��������
     */
    ~ZipOperationThread();

    /**
     * @brief �߳���ֹ
    */
    void setStop();

    /**
     * @brief ѹ���ļ�����Ĳ�����ѹ���߳̿�ʼ
     * @param fileCompressed ѹ������ļ�
     * @param files ��ѹ�����ļ��б�
     * @param bDir �Ƿ��ļ���
     * @param bEncrypt �Ƿ���Ҫ����
    */
    void compressOperator(const QString& fileCompressed, const QStringList& files, bool bDir, bool bEncrypt);
    
    /**
     * @brief ��ѹ�ļ�
     * @param fileCompressed ����ѹ���ļ�
     * @param strDir ��ѹ���ļ���ŵ�Ŀ¼
     * @param bEncrypt �Ƿ���Ҫ��ѹ����
    */
    void unCompressOperator(const QString& fileCompressed, const QString& strDir, bool bEncrypt);
signals:
    /**
     * @brief �߳̽����ź�
    */
    void finishSgn(bool);

    /**
     * @brief �߳�ִ�й�������Ҫ��ӡ����Ϣ
     * @param  ��ӡ����Ϣ
    */
    void infoTextChangedSgn(const QString&);

private:
    /**
     * @brief ѹ������ļ���һ���ļ�
     * @param fileCompressed ѹ������ļ�
     * @param files ��ѹ�����ļ��б�
     * @param bEncrypt �Ƿ���Ҫѹ������
     * @return true �ɹ� false ʧ��
    */
    bool compressFiles(QString fileCompressed, QStringList files, bool bEncrypt);

    /**
     * @brief ѹ��һ���ļ��г�һ���ļ�
     * @param fileCompressed ѹ������ļ�
     * @param dir ��ѹ�����ļ���
     * @param bEncrypt �Ƿ���Ҫѹ������
     * @return true �ɹ� false ʧ��
    */
    bool compressDir(QString fileCompressed, QString dir, bool bEncrypt);

	/**
	 * @brief ��ѹָ���ļ���ָ���ļ���
	 * @param fileCompressed ����ѹ���ļ�
	 * @param dir ��Ž�ѹ����ļ���·��
	 * @param bEncrypt �Ƿ���Ҫ��ѹ����
	 * @return true �ɹ� false ʧ��
	*/
	bool extractDir(QString fileCompressed, QString dir, bool bEncrypt);

protected:
    /**
     * @brief �߳�ִ�к���
    */
    virtual void run();
private:
    QString fileCompressed_;
    QStringList compressedFileList_;
    QString dirPath_;
    bool bDir_;
    bool bEncrypt_;
    bool bCompressing_;
    bool bStop_ = false;
};

#endif // ZIPOPERATIONTHREAD_H
