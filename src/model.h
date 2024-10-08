#ifndef MODEL_H
#define MODEL_H

#include <QFile>
#include <QOpenGLWidget>
#include <QTextStream>
#include <QVector3D>

namespace s21 {

class Model {
 public:
  static Model* Instance();

  void parseFile(QString& path);
  QVector<QVector3D>* getVertices();
  QVector<GLuint>* getIndices();
  int getCountVertices();
  int getCountIndices();

 private:
  Model() = default;
  Model(const Model&) = delete;
  Model& operator=(const Model&) = delete;

  QVector<QVector3D> vertices;
  QVector<GLuint> indices;

  void parseVertice(QStringList& line);
  void parseFace(QStringList& line);
  void transformIndex(GLint& index);
  void centerModel();
};

}  // namespace s21

#endif  // MODEL_H
