#ifndef MASKWIDGET_H
#define MASKWIDGET_H

/**
 * 弹窗遮罩层控件
 * 1. 可设置需要遮罩的主窗体，自动跟随主窗体位置显示遮罩面积。
 * 2. 只需要将弹窗窗体的名称一开始传入队列即可，足够简单。
 * 3. 可设置透明度。
 * 4. 可设置遮罩层颜色。
 * 5. 不阻塞消息循坏。
 */

#include <QWidget>

#ifdef quc
class Q_DECL_EXPORT MaskWidget : public QWidget
#else
class MaskWidget : public QWidget
#endif

{
    Q_OBJECT
public:
    /**
     * @brief 单例指针
    */
    static MaskWidget *Instance();
   
protected:
    /**
     * @brief 显示事件处理函数
     * @param  QShowEvent 指针
    */
    void showEvent(QShowEvent *event);

    /**
     * @brief 事件监控器，进行事件过滤
     * @param obj 监控对象
     * @param event 事件指针
     * @return true 不继续往下传递， false 继续向下传递
    */
    bool eventFilter(QObject *obj, QEvent *event);

private:
	/**
	 * @brief 私有够做函数
	 * @param parent 
	*/
	explicit MaskWidget(QWidget* parent = 0);

private:
    static QScopedPointer<MaskWidget> self;

    //需要遮罩的主窗体
    QWidget *mainWidget;
    //需要弹窗的窗体对象名称集合链表
    QStringList dialogNames;

public Q_SLOTS:
    /**
     * @brief 设置需要遮罩的主窗体
     * @param mainWidget 为空时，为遮罩当前桌面
    */
    void setMainWidget(QWidget *mainWidget);

    /**
     * @brief 设置需要弹窗的窗体对象名称集合链表,也即那些窗体显示在遮罩层上方，可操作的
     * @param dialogNames 体对象名称集合链表
    */
    void setDialogNames(const QStringList &dialogNames);

    /**
     * @brief 设置遮罩颜色
     * @param bgColor 遮罩颜色
    */
    void setBgColor(const QColor &bgColor);

    /**
     * @brief 设置颜色透明度
     * @param opacity 颜色透明度
    */
    void setOpacity(double opacity);
};

#endif // MASKWIDGET_H
