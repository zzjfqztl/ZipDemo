#ifndef ZIPOPERATIONTHREAD_H
#define ZIPOPERATIONTHREAD_H

#include <QObject>
#include <QThread>
/**
 * @brief 压缩或解压文件线程
*/
class ZipOperationThread : public QThread
{
    Q_OBJECT
public:
    /**
     * @brief 构造函数
    */
    explicit ZipOperationThread(QObject *parent = nullptr);

    /**
     * 析构函数
     */
    ~ZipOperationThread();

    /**
     * @brief 线程终止
    */
    void setStop();

    /**
     * @brief 压缩文件传入的参数，压缩线程开始
     * @param fileCompressed 压缩后的文件
     * @param files 待压缩的文件列表
     * @param bDir 是否文件夹
     * @param bEncrypt 是否需要加密
    */
    void compressOperator(const QString& fileCompressed, const QStringList& files, bool bDir, bool bEncrypt);
    
    /**
     * @brief 解压文件
     * @param fileCompressed 待解压的文件
     * @param strDir 解压后文件存放的目录
     * @param bEncrypt 是否需要解压密码
    */
    void unCompressOperator(const QString& fileCompressed, const QString& strDir, bool bEncrypt);
signals:
    /**
     * @brief 线程结束信号
    */
    void finishSgn(bool);

    /**
     * @brief 线程执行过程中需要打印的信息
     * @param  打印的信息
    */
    void infoTextChangedSgn(const QString&);

private:
    /**
     * @brief 压缩多个文件成一个文件
     * @param fileCompressed 压缩后的文件
     * @param files 待压缩的文件列表
     * @param bEncrypt 是否需要压缩密码
     * @return true 成功 false 失败
    */
    bool compressFiles(QString fileCompressed, QStringList files, bool bEncrypt);

    /**
     * @brief 压缩一个文件夹成一个文件
     * @param fileCompressed 压缩后的文件
     * @param dir 待压缩的文件夹
     * @param bEncrypt 是否需要压缩密码
     * @return true 成功 false 失败
    */
    bool compressDir(QString fileCompressed, QString dir, bool bEncrypt);

	/**
	 * @brief 解压指定文件到指定文件夹
	 * @param fileCompressed 待解压的文件
	 * @param dir 存放解压后的文件的路径
	 * @param bEncrypt 是否需要解压密码
	 * @return true 成功 false 失败
	*/
	bool extractDir(QString fileCompressed, QString dir, bool bEncrypt);

protected:
    /**
     * @brief 线程执行函数
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
