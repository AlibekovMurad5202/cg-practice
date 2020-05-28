#pragma once
#pragma comment(lib,"opengl32.lib")
#include <QOpenGLWidget>
#include <QOpenGLShaderProgram>
#include <QDebug>
#include <qopenglfunctions_3_0.h>
#include <QKeyEvent>
#include "math.h"

struct Sphere
{
  QVector3D position;
  float radius;
  QVector3D color;
  int material_idx;
};

struct Camera
{
  QVector3D position;
  QVector3D view;
  QVector3D up;
  QVector3D side;
};

class ShaderWidget : public QOpenGLWidget
{
private:
  QOpenGLShaderProgram m_program;
  GLfloat* vert_data;
  GLint vert_data_location;

  const GLuint count_of_spheres = 3;
  Sphere* all_spheres;

  Camera camera;

protected:
  void initializeGL() override;
  void resizeGL(int nWidth, int nHeight) override;
  void paintGL() override;

  void keyPressEvent(QKeyEvent* event);

public:
  ShaderWidget(QWidget *parent = nullptr);
  ShaderWidget();
};