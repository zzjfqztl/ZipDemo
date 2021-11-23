/**
 * 渲染窗口，用于图元展示或勾画
 */

#ifndef GRAPHICWIDGET_H
#define GRAPHICWIDGET_H

#include <QWidget>
#include <QOpenGLWidget>
#include "Define/EnumType.h"

class GraphicWidget : public QOpenGLWidget
{
    Q_OBJECT
public:
    /**
     * @brief 渲染窗口构造函数
    */
    explicit GraphicWidget(QWidget *parent = nullptr);

public slots:
	/**
	 * @brief 设置Degree的类型
	 * @param type 传入的DegreeType 类型值
	*/
	void onSetDegree(DegreeType type);

	/**
	 * @brief 设置Method的类型
	 * @param type 传入的MethodType 类型值
	*/
	void onSetMethod(MethodType type);

	/**
	 * @brief 设置Knot Generation 的类型值
	 * @param type 传入KnotGenerationType类型值
	*/
	void onSetKnotGeneration(KnotGenerationType type);
signals:

protected:
	virtual void initializeGL() override;
	virtual void resizeGL(int w, int h) override;
	virtual void paintGL() override;

	void mousePressEvent(QMouseEvent* e) override;
	void mouseReleaseEvent(QMouseEvent* e) override;
	void mouseMoveEvent(QMouseEvent* e) override;
	void wheelEvent(QWheelEvent* e) override;
	void keyPressEvent(QKeyEvent* e) override;
	void keyReleaseEvent(QKeyEvent* e) override;

private:

};

#endif // GRAPHICWIDGET_H
