#define _USE_MATH_DEFINES

#include "ShaderWidget.h"
#include <qmessagebox.h>

void ShaderWidget::initializeGL()
{
  glClearColor(1.f, 1.f, 1.f, 1.f);
  QOpenGLShader vertexShader(QOpenGLShader::Vertex);
  vertexShader.compileSourceFile("raytracing.vert");
  QOpenGLShader fragmentShader(QOpenGLShader::Fragment);
  fragmentShader.compileSourceFile("raytracing.frag");
  m_program.addShader(&vertexShader);
  m_program.addShader(&fragmentShader);

  if (!m_program.link())
  {
    QMessageBox::warning(this, "Log programm", "Error link programm shader");
    qWarning("Error link programm shader");
    return;
  }
  vert_data_location = m_program.attributeLocation("vertex");
  qDebug() << QString("Log programm");
  qDebug() << m_program.log();

  if (!m_program.bind())
  {
    QMessageBox::warning(this, "Log programm", "Error bind programm shader");
    qWarning("Error bind programm shader");
  }
  
  m_program.setUniformValue("camera.position", QVector3D(0., 0., -10));
  m_program.setUniformValue("camera.view", QVector3D(0., 0., 1.));
  m_program.setUniformValue("camera.up", QVector3D(0., 1., 0.));
  m_program.setUniformValue("camera.side", QVector3D(1., 0., 0.));
  m_program.setUniformValue("scale", QVector2D(width(), height()));
  
  //left
  m_program.setUniformValue("triangles[0].vert1", QVector3D(-5, -5, -5));
  m_program.setUniformValue("triangles[0].vert2", QVector3D(-5, 5, -5));
  m_program.setUniformValue("triangles[0].vert3", QVector3D(-5, 5, 5));
  m_program.setUniformValue("triangles[0].color", QVector3D(1, 1, 0));
  m_program.setUniformValue("triangles[0].material_idx", 0);
  m_program.setUniformValue("triangles[1].vert1", QVector3D(-5, -5, -5));
  m_program.setUniformValue("triangles[1].vert2", QVector3D(-5, 5, 5));
  m_program.setUniformValue("triangles[1].vert3", QVector3D(-5, -5, 5));
  m_program.setUniformValue("triangles[1].color", QVector3D(1, 1, 0));
  m_program.setUniformValue("triangles[1].material_idx", 0);

  //right
  m_program.setUniformValue("triangles[2].vert1", QVector3D(5, -5, -5));
  m_program.setUniformValue("triangles[2].vert2", QVector3D(5, 5, 5));
  m_program.setUniformValue("triangles[2].vert3", QVector3D(5, 5, -5));
  m_program.setUniformValue("triangles[2].color", QVector3D(0, 1, 1));
  m_program.setUniformValue("triangles[2].material_idx", 0);
  m_program.setUniformValue("triangles[3].vert1", QVector3D(5, -5, -5));
  m_program.setUniformValue("triangles[3].vert2", QVector3D(5, -5, 5));
  m_program.setUniformValue("triangles[3].vert3", QVector3D(5, 5, 5));
  m_program.setUniformValue("triangles[3].color", QVector3D(0, 1, 1));
  m_program.setUniformValue("triangles[3].material_idx", 0);

  //down
  m_program.setUniformValue("triangles[4].vert1", QVector3D(-5, -5, -5));
  m_program.setUniformValue("triangles[4].vert2", QVector3D(-5, -5, 5));
  m_program.setUniformValue("triangles[4].vert3", QVector3D(5, -5, -5));
  m_program.setUniformValue("triangles[4].color", QVector3D(1, 0, 0));
  m_program.setUniformValue("triangles[4].material_idx", 0);
  m_program.setUniformValue("triangles[5].vert1", QVector3D(5, -5, 5));
  m_program.setUniformValue("triangles[5].vert2", QVector3D(5, -5, -5));
  m_program.setUniformValue("triangles[5].vert3", QVector3D(-5, -5, 5));
  m_program.setUniformValue("triangles[5].color", QVector3D(1, 0, 0));
  m_program.setUniformValue("triangles[5].material_idx", 0);
  
  //up
  m_program.setUniformValue("triangles[6].vert1", QVector3D(-5, 5, -5));
  m_program.setUniformValue("triangles[6].vert2", QVector3D(5, 5, -5));
  m_program.setUniformValue("triangles[6].vert3", QVector3D(-5, 5, 5));
  m_program.setUniformValue("triangles[6].color", QVector3D(0, 0, 1));
  m_program.setUniformValue("triangles[6].material_idx", 0);
  m_program.setUniformValue("triangles[7].vert1", QVector3D(5, 5, 5));
  m_program.setUniformValue("triangles[7].vert2", QVector3D(-5, 5, 5));
  m_program.setUniformValue("triangles[7].vert3", QVector3D(5, 5, -5));
  m_program.setUniformValue("triangles[7].color", QVector3D(0, 0, 1));
  m_program.setUniformValue("triangles[7].material_idx", 0);

  //end
  m_program.setUniformValue("triangles[8].vert1", QVector3D(-5, -5, 5));
  m_program.setUniformValue("triangles[8].vert2", QVector3D(-5, 5, 5));
  m_program.setUniformValue("triangles[8].vert3", QVector3D(5, -5, 5));
  m_program.setUniformValue("triangles[8].color", QVector3D(1, 1, 1));
  m_program.setUniformValue("triangles[8].material_idx", 0);
  m_program.setUniformValue("triangles[9].vert1", QVector3D(5, 5, 5));
  m_program.setUniformValue("triangles[9].vert2", QVector3D(5, -5, 5));
  m_program.setUniformValue("triangles[9].vert3", QVector3D(-5, 5, 5));
  m_program.setUniformValue("triangles[9].color", QVector3D(1, 1, 1));
  m_program.setUniformValue("triangles[9].material_idx", 0);

  m_program.release();
  /*
  QOpenGLFunctions_4_3_Core * functions = 0;
  functions = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctions_4_3_Core>();*/
  QOpenGLFunctions_3_0 * functions = QOpenGLContext::currentContext()->
    versionFunctions<QOpenGLFunctions_3_0>();
  GLuint ssbo = 0;
  functions->glGenBuffers(1, &ssbo);
  functions->glBindBuffer(GL_SHADER_STORAGE_BUFFER, ssbo);
  functions->glBufferData(GL_SHADER_STORAGE_BUFFER, count_of_spheres * sizeof(Sphere), 
    all_spheres, GL_DYNAMIC_COPY);
  functions->glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, ssbo);
}

void ShaderWidget::resizeGL(int nWidth, int nHeight)
{
  glViewport(0, 0, nWidth, nHeight);

  if (!m_program.bind())
  {
    QMessageBox::warning(this, "Log programm", "Error bind programm shader");
    qWarning("Error bind programm shader");
  }
  m_program.setUniformValue("scale", QVector2D(width(), height()));
  m_program.release();
}

void ShaderWidget::paintGL()
{
  glClear(GL_COLOR_BUFFER_BIT);

  if (!m_program.bind())
    return;

  m_program.enableAttributeArray(vert_data_location);
  m_program.setAttributeArray(vert_data_location, vert_data, 3);

  glDrawArrays(GL_QUADS, 0, 4);

  m_program.disableAttributeArray(vert_data_location);
  m_program.release();
}

ShaderWidget::ShaderWidget(QWidget * parent)
  : QOpenGLWidget(parent)
{
  vert_data = new GLfloat[12]
  { -1.f, -1.f, 0.f,
     1.f, -1.f, 0.f,
     1.f,  1.f, 0.f,
    -1.f,  1.f, 0.f
  };

  camera.position = QVector3D(0., 0., -10);
  camera.view = QVector3D(0., 0., 1.);
  camera.up = QVector3D(0., 1., 0.);
  camera.side = QVector3D(1., 0., 0.);

  all_spheres = new Sphere[count_of_spheres];

  all_spheres[0].position = QVector3D(1, 0, 3);
  all_spheres[0].radius = 2.;
  all_spheres[0].color = QVector3D(0.7, 0.7, 0);
  all_spheres[0].material_idx = 0;

  all_spheres[1].position = QVector3D(3, 0, 0);
  all_spheres[1].radius = 1.;
  all_spheres[1].color = QVector3D(0, 0.5, 0.5);
  all_spheres[1].material_idx = 0;

  all_spheres[2].position = QVector3D(-1, -2, 0);
  all_spheres[2].radius = 1.;
  all_spheres[2].color = QVector3D(1, 0, 1);
  all_spheres[2].material_idx = 0;
};

ShaderWidget::ShaderWidget()
{
  delete[] vert_data;
  delete[] all_spheres;
};

void ShaderWidget::keyPressEvent(QKeyEvent* event) 
{
  const float coef = 0.5;
  const float angle = M_PI / 180;
  float X, Y, Z;
  switch (event->nativeVirtualKey())
  {
  case Qt::Key_W:
    camera.position = camera.position + camera.view * coef;
    break;
  case Qt::Key_S:
    camera.position = camera.position - camera.view * coef;
    break;
  case Qt::Key_A:
    X = camera.view.x();
    Y = camera.view.y();
    Z = camera.view.z();
    camera.view = QVector3D(X * cos(angle) - Z * sin(angle), Y, X * sin(angle) + Z * cos(angle));
    camera.view.normalize();
    X = camera.side.x();
    Y = camera.side.y();
    Z = camera.side.z();
    camera.side = QVector3D(X * cos(angle) - Z * sin(angle), Y, X * sin(angle) + Z * cos(angle));
    camera.side.normalize();
    break;
  case Qt::Key_D:
    X = camera.view.x();
    Y = camera.view.y();
    Z = camera.view.z();
    camera.view = QVector3D(X * cos(angle) + Z * sin(angle), Y, Z * cos(angle) - X * sin(angle));
    camera.view.normalize();
    X = camera.side.x();
    Y = camera.side.y();
    Z = camera.side.z();
    camera.side = QVector3D(X * cos(angle) + Z * sin(angle), Y, Z * cos(angle) - X * sin(angle));
    camera.side.normalize();
    break;
  case Qt::Key_Q:
    X = camera.view.x();
    Y = camera.view.y();
    Z = camera.view.z();
    camera.view = QVector3D(X, Y * cos(angle) + Z * sin(angle), Z * cos(angle) - Y * sin(angle));
    camera.view.normalize();
    X = camera.up.x();
    Y = camera.up.y();
    Z = camera.up.z();
    camera.up = QVector3D(X, Y * cos(angle) + Z * sin(angle), Z * cos(angle) - Y * sin(angle));
    camera.up.normalize();
    break;
  case Qt::Key_E:
    X = camera.view.x();
    Y = camera.view.y();
    Z = camera.view.z();
    camera.view = QVector3D(X, Y * cos(angle) - Z * sin(angle), Y * sin(angle) + Z * cos(angle));
    camera.view.normalize();
    X = camera.up.x();
    Y = camera.up.y();
    Z = camera.up.z();
    camera.up = QVector3D(X, Y * cos(angle) - Z * sin(angle), Y * sin(angle) + Z * cos(angle));
    camera.up.normalize();
    break;
  default:
    break;
  }

  if (!m_program.bind())
  {
    QMessageBox::warning(this, "Log programm", "Error bind programm shader");
    qWarning("Error bind programm shader");
  }
  m_program.setUniformValue("camera.position", camera.position);
  m_program.setUniformValue("camera.view", camera.view);
  m_program.setUniformValue("camera.side", camera.side);
  m_program.setUniformValue("camera.up", camera.up);
  m_program.release();
  update();
}