#ifndef VIEW_H
#define VIEW_H

#include <QColorDialog>
#include <QFileDialog>
#include <QMainWindow>
#include <QMouseEvent>
#include <QSettings>
#include <memory>

#include "controller.h"
#include "gifcreator.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class View;
}
QT_END_NAMESPACE

namespace s21 {

class View : public QMainWindow {
  Q_OBJECT

 public:
  View(QWidget *parent = nullptr);
  ~View();

 private slots:
  void openFile_clicked();
  void getScreenshot_clicked();
  void createGIF_clicked();
  void resetParams_clicked();
  void resetGlSettings_clicked();
  void setBgColor_clicked();
  void setPolygonsColor_clicked();
  void setVerticesColor_clicked();
  void scale_valueChanged();
  void rotate_valueChanged();
  void move_valueChanged();
  void linesWidth_sliderMoved(int position);
  void sizeVertices_sliderMoved(int position);
  void polygonsType_toggled(bool checked);
  void verticesType_toggled();
  void projectionType_toggled(bool checked);

  // menu bar
  void on_actionOpen_triggered();
  void on_actionSave_as_triggered();

  // observer
 signals:
  void bgColorChanged(const QColor &color);
  void polygonsColorChanged(const QColor &color);
  void verticesColorChanged(const QColor &color);

 private:
  Ui::View *ui;
  Controller *controller;
  std::unique_ptr<QSettings> settings;
  QVector2D mousePos;
  bool fileOpened;

  void initializeUI();
  void saveSettings();
  void loadSettings();
  void setUISettings();

  void mousePressEvent(QMouseEvent *) override;
  void mouseReleaseEvent(QMouseEvent *) override;
  void mouseMoveEvent(QMouseEvent *) override;
  void wheelEvent(QWheelEvent *) override;
};

}  // namespace s21

#endif  // VIEW_H
