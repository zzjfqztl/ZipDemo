/**
 * 文件或文件夹解压缩操作
 * 可以有加密解压操作
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
	 * @brief 设置压缩或者解压是否终止
	 * @param bStop true 终止 false 继续
	*/
	static void setStop(bool bStop);
    /**
     * @brief 压缩单个文件
     * @param fileCompressed 压缩后的文件
     * @param file 待压缩的文件
     * @param bEncrypt 是否加密
     * @return true 成功 false 失败
    */
    static bool compressFile(QString fileCompressed, QString file, bool bEncrypt = false);

    /**
     * @brief 将多个文件压缩成一个文件
     * @param fileCompressed 压缩后的文件
     * @param files 待压缩的文件列表
     * @param bEncrypt 是否加密
     * @return  true 成功 false 失败
    */
    static bool compressFiles(QString fileCompressed, QStringList files, bool bEncrypt = false);

    /**
     * @brief 压缩整个文件夹
     * @param fileCompressed 压缩后的文件
     * @param dir 待压缩的文件夹
	 * @param recursive 是否递归打包子目录，或普通文件
     * @param bEncrypt 是否使用加密
     * @return true 成功 false 失败
    */
    static bool compressDir(QString fileCompressed, QString dir = QString(), bool recursive = true, bool bEncrypt = false);

	/**
	 * @brief 压缩整个文件夹
	 * @param fileCompressed 压缩后的文件
	 * @param dir 待压缩的文件夹
	 * @param recursive 是否递归打包子目录，还是普通文件
	 * @param filters 文件筛选器，要打包什么，过滤器在搜索或子目录(如果递归打包)和寻找要打包的文件时都被应用
	 * @param bEncrypt 是否使用加密
	 * @return true 成功 false 失败
	*/
	static bool compressDir(QString fileCompressed, QString dir, bool recursive, QDir::Filters filters, bool bEncrypt = false);

	/**
	 * @brief 解压指定文件，并返回解压后文件所在的路径
	 * @param fileCompressed 压缩文件
	 * @param fileName 待解压的文件
	 * @param fileDest 解压后的文件
	 * @param bEncrypt 是否需要加密密码
	 * @return QString 解压后文件所在的路径
	*/
	static QString extractFile(QString fileCompressed, QString fileName, QString fileDest = QString(), bool bEncrypt = false);

	/**
	 * @brief 解压指定列表文件，并返回解压后文件路径列表
	 * @param fileCompressed 压缩文件
	 * @param files 待解压的文件列表
	 * @param dir 解压后的文件存放路径，如果为空，为当前路径
	 * @param bEncrypt 是否需要加密密码
	 * @return QStringList 解压后文件路径列表
	*/
	static QStringList extractFiles(QString fileCompressed, QStringList files, QString dir = QString(), bool bEncrypt = false);

	/**
	 * @brief 解压文件，并返回解压后的文件路径列表
	 * @param fileCompressed 待解压缩文件
	 * @param dir 解压后的文件存放路径，如果为空，为当前路径
	 * @param bEncrypt 是否需要加密密码
	 * @return QStringList 解压后文件路径列表
	*/
	static QStringList extractDir(QString fileCompressed, QString dir = QString(), bool bEncrypt = false);

	/**
	 * @brief 解压文件，并返回解压后的文件路径列表
	 * @param fileCompressed 待解压缩文件
	 * @param fileNameCodec 解压后的文件名字采用编码方式
	 * @param dir 解压后的文件存放路径，如果为空，为当前路径
	 * @param bEncrypt 是否需要加密密码
	 * @return 解压后文件路径列表
	*/
	static QStringList extractDir(QString fileCompressed, QTextCodec* fileNameCodec, QString dir = QString(), bool bEncrypt = false);

	/**
	 * @brief 获取压缩文件中文件列表，包括文件及子文件夹
	 * @param fileCompressed 指定压缩文件
	 * @return QStringList 压缩文件中文件列表，包括文件及子文件夹
	*/
	static QStringList getFileList(QString fileCompressed);

	/**
	 * @brief 解压指定文件，并返回解压后文件路径
	 * @param ioDevice 压缩文件的指针
	 * @param fileName 指定的待解压文件
	 * @param fileDest 解压后的文件
	 * @param bEncrypt 是否需要加密密码
	 * @return QString 解压后文件路径
	*/
	static QString extractFile(QIODevice* ioDevice, QString fileName, QString fileDest = QString(), bool bEncrypt = false);

	/**
	 * @brief 解压指定列表的文件，并返回解压后列表文件路径
	 * @param ioDevice 压缩文件的指针
	 * @param files 指定的待解压文件列表
	 * @param dir 解压后的文件存放路径，为空，则为当前目录
	 * @param bEncrypt 是否需要加密密码
	 * @return QStringList 解压后的列表文件路径
	*/
	static QStringList extractFiles(QIODevice* ioDevice, QStringList files, QString dir = QString(), bool bEncrypt = false);

	/**
	 * @brief 解压指定文件，并返回解压后文件路径列表
	 * @param ioDevice 压缩文件的指针
	 * @param dir 解压后的文件存放路径，为空，则为当前目录
	 * @param bEncrypt 是否需要加密密码
	 * @return QStringList 解压后的列表文件路径
	*/
	static QStringList extractDir(QIODevice* ioDevice, QString dir = QString(), bool bEncrypt = false);

	/**
	 * @brief 解压文件，并返回解压后的文件路径列表
	 * @param ioDevice 待解压缩文件QIODevice指针
	 * @param fileNameCodec 解压后的文件名字采用编码方式
	 * @param dir 解压后的文件存放路径，如果为空，为当前路径
	 * @param bEncrypt 是否需要加密密码
	 * @return 解压后文件路径列表
	*/
	static QStringList extractDir(QIODevice* ioDevice, QTextCodec* fileNameCodec, QString dir = QString(), bool bEncrypt = false);

	/**
	 * @brief 获取压缩文件中文件列表，包括文件及子文件夹
	 * @param ioDevice 指定压缩文件QIODevice指针
	 * @return QStringList 压缩文件中文件列表，包括文件及子文件夹
	*/
	static QStringList getFileList(QIODevice* ioDevice);

private:
    
	 /**
	 * @brief 压缩单个文件
	 * @param zip fileCompressed 压缩后的文件
	 * @param fileName 待压缩的文件
	 * @param fileDest 压缩后的文件中显示的文件名称
	 * @param bEncrypt 是否加密码压缩
	 * @return true 成功 false 失败
	  */
	static bool compressFile(QuaZip* zip, QString fileName, QString fileDest, bool bEncrypt);

    /**
     * @brief 复制文件内容，将一个文件的内容复制到另一个文件中
     * @param inFile 待复制的文件
     * @param outFile 复制后的文件
     * @return true 成功 false 失败
    */
    static bool copyData(QIODevice& inFile, QIODevice& outFile);

	/**
	 * @brief 压缩子文件夹.
	 * @param parentZip 包含父目录的QuaZip对象指针
	 * @param dir 要压缩的目录的完整路径
	 * @param parentDir 到ZIP根目录对应的全路径 
	 * @param recursive 是否也打包子目录，还是只打包文件
	 * @param filters 文件筛选器，要打包什么，过滤器在搜索或子目录(如果递归打包)和寻找要打包的文件时都被应用
	 * @param bEncrypt 是否加密码压缩
	 * @return true 成功 false 失败
	*/
	static bool compressSubDir(QuaZip* parentZip, QString dir, QString parentDir, bool recursive,
		QDir::Filters filters, bool bEncrypt);

	/**
	 * @brief 将压缩文件解压到指定文件夹中
	 * @param zip 待解压的文件
	 * @param dir 存放解压后的文件所在路径
	 * @param bEncrypt 是否需要加密密码
	 * @return QStringList 返回解压后的文件列表
	*/
	static QStringList extractDir(QuaZip& zip, const QString& dir, bool bEncrypt);

	/**
	 * @brief 获取压缩文件中的文件列表
	 * @param zip 压缩文件
	 * @return QStringList 压缩文件中的文件列表
	*/
	static QStringList getFileList(QuaZip* zip);

	/**
	 * @brief 解压指定文件，并返回解压后文件所在的路径
	 * @param zip 压缩文件
	 * @param fileName 待解压的文件
	 * @param fileDest 解压后的文件
	 * @param bEncrypt 是否需要加密密码
	 * @return QString 解压后文件所在的路径
	*/
	static QString extractFile(QuaZip& zip, QString fileName, QString fileDest, bool bEncrypt);

	/**
	 * @brief 解压指定的文件列表，并返回解压后文件列表
	 * @param zip 压缩文件
	 * @param files 待解压的文件列表
	 * @param dir 解压后文件存放的路径
	 * @param bEncrypt 是否需要加密密码
	 * @return QStringList 解压后文件列表
	*/
	static QStringList extractFiles(QuaZip& zip, const QStringList& files, const QString& dir, bool bEncrypt);
   
	/**
	 * @brief 解压指定文件
	 * @param zip 压缩文件
	 * @param fileName 待解压的文件
	 * @param fileDest 解压后的文件
	 * @param bEncrypt 是否需要加密密码
	 * @return true 成功 false 失败
	*/
	static bool extractFile(QuaZip* zip, QString fileName, QString fileDest, bool bEncrypt);

	/**
	 * @brief 删除文件
	 * @param listFile 删除的文件列表
	 * @return true 成功 false 失败 
	*/
	static bool removeFile(QStringList listFile);
	static bool bStop_;
};

#endif // ZIPOPERATOR_H
