#ifndef MYOPENGLWIDGET_H
#define MYOPENGLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QColor>

class MyOpenGLWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT

public:
    explicit MyOpenGLWidget(QWidget *parent = nullptr);
	~MyOpenGLWidget();
    void changeBackgroundColor(QColor color);
	void changeTriangleColor(const QColor &color);

protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

private:
    QColor backgroundColor;
    QOpenGLShaderProgram *program;
    QOpenGLBuffer vbo;
    QOpenGLVertexArrayObject vao;
	QColor triangleColor;
	GLint colorLocation;
};

#endif // MYOPENGLWIDGET_H

