#include "myopenglwidget.h"
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>


static const char *vertexShaderSource =
    "#version 330\n"
	"layout (location = 0) in vec3 aPos;\n"
    "void main() {\n"
	"gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);"
    "}";

static const char *fragmentShaderSource =
    "#version 330 core\n"
    "out vec4 FragColor;\n"
    "uniform vec4 ourColor;\n"		
    "void main() {\n"
    "   FragColor = ourColor;\n"
    "}";	

MyOpenGLWidget::MyOpenGLWidget(QWidget *parent)
    : QOpenGLWidget(parent), backgroundColor(Qt::black)
{
}

MyOpenGLWidget::~MyOpenGLWidget()
{
    makeCurrent();
    vao.destroy();
    vbo.destroy();
    doneCurrent();
}


void MyOpenGLWidget::changeBackgroundColor(QColor color)
{
    // Change the background color
    backgroundColor = color; 
    update(); // Trigger a repaint
}

void MyOpenGLWidget::initializeGL()
{
    initializeOpenGLFunctions();
    glClearColor(backgroundColor.redF(), backgroundColor.greenF(), backgroundColor.blueF(), 1.0f);

    // Shader program
    program = new QOpenGLShaderProgram(this);
	
	program->addShaderFromSourceCode(QOpenGLShader::Vertex, vertexShaderSource); 
	program->addShaderFromSourceCode(QOpenGLShader::Fragment,fragmentShaderSource);
									
    program->link();
    program->bind();
	
    // Get the uniform for color "ourColor"
	changeTriangleColor(QColor::fromRgb(180, 190, 0));
    colorLocation = program->uniformLocation("ourColor");

    // Vertex data
    GLfloat vertices[] = {
        0.0f,  0.5f, 0.0f,
       -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f
    };

    vao.create();
    vao.bind();

    vbo.create();
    vbo.bind();
    vbo.allocate(vertices, sizeof(vertices));

    program->enableAttributeArray(0);
    program->setAttributeBuffer(0, GL_FLOAT, 0, 3);

    vbo.release();
    vao.release();
    program->release();
}

void MyOpenGLWidget::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
}

void MyOpenGLWidget::paintGL()
{
    glClearColor(backgroundColor.redF(), backgroundColor.greenF(), backgroundColor.blueF(), 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    program->bind();
    vao.bind();
	
    // Set the color for GLint colorLocation which is used by the shader
    glUniform4f(colorLocation, triangleColor.redF(), triangleColor.greenF(), triangleColor.blueF(), 1.0f);

    glDrawArrays(GL_TRIANGLES, 0, 3);

    vao.release();
    program->release();
}

void MyOpenGLWidget::changeTriangleColor(const QColor &color)
{
    triangleColor = color;
    update();
}



