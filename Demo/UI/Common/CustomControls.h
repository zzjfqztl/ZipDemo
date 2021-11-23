/**
 * 自定义控件集合，此文件包含自定义的所以控件
 */

#ifndef CUSTOMCONTROLS_H
#define CUSTOMCONTROLS_H
#include "QFrame"
#include "QMap"
#include "QList"
#include <vector>
#include "UI/Define/EnumType.h"

class QComboBox;
class QLabel;
class QPushButton;
class QLineEdit;

/**
 * @brief QLabel + QComboBox 组合的自定义控件
 * QLabel 可在QComboBox 上方，也可在QComboBox的左边
*/
class ComboBoxFrame :public QFrame
{
	Q_OBJECT
public:

	/**
	 * @brief 
	*/
	/**
	 * @brief QLabel + QComboBox 组合的自定义控件 构造函数
	 * @param title QLabel内容
	 * @param parent 父窗体指针
	 * @param org QLabel与QComboBox 位置标识
	*/
	explicit ComboBoxFrame(const QString& title, QWidget* parent = nullptr, Qt::Orientation org = Qt::Orientation::Horizontal);

	/**
	 * @brief 初始化QComboBox显示的项列表信息
	 * @param itemList 显示的项列表(可国际化翻译)
	 * @param itemDataList 项列表对应的数据，不因国际化翻译而变化
	*/
	void InitData(const QStringList& itemList, const QStringList& itemDataList);
	
	/**
	 * @brief 获取QComboBox当前项对应的数据信息
	 * @return 返回QComboBox当前项对应唯一标识数据信息
	*/
	QString GetCurrentData() const;
	
	/**
	 * @brief 设置QComboBox当前项对应的唯一数据信息，从而设置当前项
	 * @param text QComboBox当前项对应唯一标识数据信息
	*/
	void SetCurrentData(const QString& text);
	
	/**
	 * @brief 设置QLabel文本对齐方式
	 * @param align 对齐方式
	*/
	void SetTitleLabelAlign(Qt::Alignment align);
signals:

	/**
	 * @brief QComboBox当前项变化后发出的信号
	 * @param QString 数据信息
	*/
	void currentTextChangedSgn(const QString&);
public slots:

	/**
	 * @brief QComboBox当前项变化后的操作
	 * @param nIndex 当前项的索引
	*/
	void onCurrentIndexChanged(int nIndex);
private:

	/**
	 * @brief ComboBoxFrame 界面信息
	*/
	void InitUI();
private:
	QLabel* titleLabel_ = nullptr;
	QComboBox* comboBox_ = nullptr;
	Qt::Orientation orientation_ = Qt::Orientation::Horizontal;
	QString titleContent_ = nullptr;
};

/**
 * @brief 文件或者文件夹选择 自定义控件
*/
class FileSelectFrame :public QFrame
{
	Q_OBJECT

public:

	/**
	 * @brief 文件或者文件夹选择自定义控件 构造函数
	 * @param title	标题
	 * @param bDir	false 选择文件 true 选择文件夹
	 * @param bMultSelect 是否支持多选 
	 * @param parent 父窗口指针 
	*/
	explicit FileSelectFrame(const QString& title, QWidget* parent = nullptr, bool bDir = false, bool bMultSelect =false);

	/**
	 * @brief 获取选择的文件列表
	 * @return 返回QStringList对象
	*/
	QStringList GetFileList() const;

	/**
	 * @brief 设置是否文件夹
	 * @param bDir true 文件夹 false 文件
	*/
	void SetDirFlag(bool bDir);

	/**
	 * @brief 设置是否多选文件
	 * @param bMultSelect true 多选 false 单选
	*/
	void SetMultSelect(bool bMultSelect);
signals:
	/**
	 * @brief 文件选择后发送出的信号
	 * @param filelist 选择的文件列表
	*/
	void selectFilesSgn(const QStringList& filelist);

public slots:
	/**
	 * @brief Select 操作
	*/
	void onSelectClick();
private:
	/**
	 * @brief FileSelectFrame 界面初始化
	*/
	void InitUI();
private:
	QLabel* titleLabel_ = nullptr;
	QLineEdit* lineEdit_ = nullptr;
	QPushButton* btnSelect_ = nullptr;
	QString titleContent_;
	bool bDir_ = false;
	bool bMultSelect_ = false;
};
#endif // CUSTOMCONTROLS_H