#ifndef ROOMLISTPANEL_H
#define ROOMLISTPANEL_H

#include <QWidget>

#include "src/controller.h"
#include "src/spectralroom.h"

class RoomListPanel : public QWidget {
  Q_OBJECT
 public:
  explicit RoomListPanel(Controller* controller, QWidget* parent = nullptr);

 signals:
  void roomSelected(SpectralRoom* room);

 public slots:

 private:
  Controller* controller;
};

#endif  // ROOMLISTPANEL_H
