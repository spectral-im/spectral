#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "controller.h"

class MainWindow : public QMainWindow {
  Q_OBJECT
 public:
  explicit MainWindow(QWidget* parent = nullptr);

 signals:

 public slots:

 private:
  Controller* controller;
};

#endif  // MAINWINDOW_H
