#ifndef MEMENTO_H
#define MEMENTO_H

#include <QColor>

class Memento {
 private:
  QColor bgColor;
  QColor pColor;
  QColor vColor;
  int linesWidth;
  int verticesSize;
  int verticesType;
  bool stippleLines;
  bool orthoProjection;

 public:
  Memento(QColor bgColor, QColor pColor, QColor vColor, int linesWidth,
          int verticesSize, int verticesType, bool stippleLines,
          bool orthoProjection)
      : bgColor(bgColor),
        pColor(pColor),
        vColor(vColor),
        linesWidth(linesWidth),
        verticesSize(verticesSize),
        verticesType(verticesType),
        stippleLines(stippleLines),
        orthoProjection(orthoProjection) {}

  QColor getBgColor() const { return bgColor; }
  QColor getPolygonsColor() const { return pColor; }
  QColor getVerticesColor() const { return vColor; }
  int getLinesWidth() const { return linesWidth; }
  int getVerticesSize() const { return verticesSize; }
  int getVerticesType() const { return verticesType; }
  bool getStippleLines() const { return stippleLines; }
  bool getOrthoProjection() const { return orthoProjection; }
};

#endif  // MEMENTO_H
