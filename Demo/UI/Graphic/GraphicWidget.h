/**
 * ��Ⱦ���ڣ�����ͼԪչʾ�򹴻�
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
     * @brief ��Ⱦ���ڹ��캯��
    */
    explicit GraphicWidget(QWidget *parent = nullptr);

public slots:
	/**
	 * @brief ����Degree������
	 * @param type �����DegreeType ����ֵ
	*/
	void onSetDegree(DegreeType type);

	/**
	 * @brief ����Method������
	 * @param type �����MethodType ����ֵ
	*/
	void onSetMethod(MethodType type);

	/**
	 * @brief ����Knot Generation ������ֵ
	 * @param type ����KnotGenerationType����ֵ
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
