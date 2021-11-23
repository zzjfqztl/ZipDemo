#ifndef PROGRESSDIALOG_H
#define PROGRESSDIALOG_H

#include <QWidget>
#include <QDialog>
#include "BaseDialog.h"

class QProgressBar;
class QLabel;

/**
 * @brief 显示进度的对话框
*/
class ProgressDialog : public BaseDialog
{
    Q_OBJECT
public:
    /**
     * @brief 显示进度的对话框
    */
    explicit ProgressDialog(const QString& title, QWidget *parent = nullptr);

signals:

public slots:
    /**
     * @brief 实时显示的信息
    */
    void onInfoTextChanged(const QString& text);

    /**
     * @brief 结束后做的操作
    */
    void onFinished();
private:
    /**
     * @brief 初始化界面
    */
    void initUI();
private:
    QProgressBar* progressBar_ = nullptr;
    QLabel* infoLabel_ = nullptr;
};

#endif // PROGRESSDIALOG_H
