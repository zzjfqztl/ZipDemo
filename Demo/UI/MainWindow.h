/**
 * �����岿��
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
     * @brief ѹ������
    */
    void onCompressClick();

    /**
     * @brief ��ѹ����
    */
    void onUnCompressClick();

    /**
     * @brief �Ƿ�ѡ���ļ���
    */
    void onCheckDirClick();

    /**
	 * @brief �Ƿ��ѡ�ļ�
	*/
    void onCheckMultiSelectClick();
private:
    /**
     * @brief �������ʼ��
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
