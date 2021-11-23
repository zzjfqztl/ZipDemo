/**
 * 主窗体部分
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class ComboBoxFrame;
class QTextEdit;
class QCheckBox;
class QPushButton;
class FileSelectFrame;
class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);

public slots:

    /**
     * @brief 压缩操作
    */
    void onCompressClick();

    /**
     * @brief 解压操作
    */
    void onUnCompressClick();

    /**
     * @brief 是否选择文件夹
    */
    void onCheckDirClick();

    /**
	 * @brief 是否多选文件
	*/
    void onCheckMultiSelectClick();
private:
    /**
     * @brief 主界面初始化
    */
    void InitUI();

private:
    FileSelectFrame* fileSelectFrame_ = nullptr;
	QCheckBox* ckbDir_ = nullptr;
	QCheckBox* ckbMultSelect_ = nullptr;
    QPushButton* btnCompress_ = nullptr;
    FileSelectFrame* fileDirFrame_ = nullptr;
    QPushButton* btnUnCompress_ = nullptr;
    QCheckBox* ckbEncrypt_ = nullptr;
    QTextEdit* textEdit_ = nullptr;
    
};

#endif // MAINWINDOW_H
