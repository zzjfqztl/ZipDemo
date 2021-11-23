#include "GraphicWidget.h"
#include "qevent.h"
#include <iostream>
GraphicWidget::GraphicWidget(QWidget *parent) : QOpenGLWidget(parent)
{
	setMouseTracking(true);
	setFocusPolicy(Qt::FocusPolicy::StrongFocus);
}

void GraphicWidget::onSetDegree(DegreeType type)
{
	std::cout << "DegreeType:" << (int)type << std::endl;
}

void GraphicWidget::onSetMethod(MethodType type)
{
	std::cout << "MethodType:" << (int)type << std::endl;
}

void GraphicWidget::onSetKnotGeneration(KnotGenerationType type)
{
	std::cout << "KnotGenerationType:" << (int)type << std::endl;
}

void GraphicWidget::initializeGL()
{

}

void GraphicWidget::resizeGL(int w, int h)
{

}

void GraphicWidget::paintGL()
{

}

void GraphicWidget::mousePressEvent(QMouseEvent* e)
{

}

void GraphicWidget::mouseReleaseEvent(QMouseEvent* e)
{

}

void GraphicWidget::mouseMoveEvent(QMouseEvent* e)
{

}

void GraphicWidget::wheelEvent(QWheelEvent* e)
{

}

void GraphicWidget::keyPressEvent(QKeyEvent* e)
{

}

void GraphicWidget::keyReleaseEvent(QKeyEvent* e)
{

}
