/**
 * 对话框基类，包含标题栏部分，标题栏部分由标题及关闭按钮组成
 * 构造时需要传入标题文本内容
 */
#ifndef BASEDIALOG_H
#define BASEDIALOG_H

#include <QWidget>
#include "QDialog"

class DialogTitleFrame;
class BaseDialog : public QDialog
{
    Q_OBJECT
public:
	/// <summary>
    /// 构造函数
    /// </summary>
    /// <param name="title">标题文本</param>
    /// <param name="parent">父窗体指针</param>
    explicit BaseDialog(const QString& title, QWidget *parent = nullptr);

public slots:
    void onClose();
protected:
	/// <summary>
    /// 事件过滤器，主要用于拖动标题栏移动窗体
    /// </summary>
    /// <param name="watched"></param>
    /// <param name="event"></param>
    /// <returns></returns>
	bool eventFilter(QObject* watched, QEvent* event);
private:
    void InitUI();
private:
    DialogTitleFrame* titleFrame_ = nullptr;
    QString titleContent_;
};

#endif // BASEDIALOG_H
