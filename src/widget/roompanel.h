#ifndef ROOMPANEL_H
#define ROOMPANEL_H

#include <QLabel>
#include <QWidget>

#include "room.h"

#include "src/spectralroom.h"

#include "label.h"
#include "materialavatar.h"

class RoomPanelHeader : public QWidget {
  Q_OBJECT
  Q_PROPERTY(SpectralRoom* room READ room WRITE setRoom NOTIFY roomChanged)
 public:
  explicit RoomPanelHeader(QWidget* parent = nullptr);

  SpectralRoom* room() { return currentRoom; }
  void setRoom(SpectralRoom* room);

 signals:
  void roomChanged();

 public slots:

 private:
  SpectralRoom* currentRoom = nullptr;

  MaterialAvatar* avatar;
  Label* title;
  Label* subTitle;

 private slots:
};

class RoomPanel : public QWidget {
  Q_OBJECT
  Q_PROPERTY(SpectralRoom* room READ room WRITE setRoom NOTIFY roomChanged)
 public:
  explicit RoomPanel(QWidget* parent = nullptr);

  SpectralRoom* room() { return currentRoom; }
  void setRoom(SpectralRoom* room) {
    if (room == currentRoom) {
      return;
    }

    currentRoom = room;
    emit roomChanged();
  }

 signals:
  void roomChanged();

 public slots:

 private:
  SpectralRoom* currentRoom;
};

#endif  // ROOMPANEL_H
