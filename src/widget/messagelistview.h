#ifndef MESSAGELISTVIEW_H
#define MESSAGELISTVIEW_H

#include <QScrollArea>
#include <QWidget>

#include "connection.h"

#include "src/spectralroom.h"

class MessageListView : public QWidget {
  Q_OBJECT
  Q_PROPERTY(SpectralRoom* room READ room WRITE setRoom NOTIFY roomChanged)

 public:
  MessageListView(QWidget* parent = nullptr);

  SpectralRoom* room() { return currentRoom; }
  void setRoom(SpectralRoom* room);

 signals:
  void roomChanged();

 private:
  void beginInsertRows(int first, int last);
  void endInsertRows();

  bool hasPendingRows = false;
  int firstInsertedRows = 0;
  int lastInsertedRows = 0;

  SpectralRoom* currentRoom = nullptr;
};

#endif  // MESSAGELISTVIEW_H
