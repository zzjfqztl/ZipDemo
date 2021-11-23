#ifndef PROGRESSDIALOG_H
#define PROGRESSDIALOG_H

#include <QWidget>
#include <QDialog>
#include "BaseDialog.h"

class QProgressBar;
class QLabel;

/**
 * @brief ��ʾ���ȵĶԻ���
*/
class ProgressDialog : public BaseDialog
{
    Q_OBJECT
public:
    /**
     * @brief ��ʾ���ȵĶԻ���
    */
    explicit ProgressDialog(const QString& title, QWidget *parent = nullptr);

signals:

public slots:
    /**
     * @brief ʵʱ��ʾ����Ϣ
    */
    void onInfoTextChanged(const QString& text);

    /**
     * @brief ���������Ĳ���
    */
    void onFinished();
private:
    /**
     * @brief ��ʼ������
    */
    void initUI();
private:
    QProgressBar* progressBar_ = nullptr;
    QLabel* infoLabel_ = nullptr;
};

#endif // PROGRESSDIALOG_H
