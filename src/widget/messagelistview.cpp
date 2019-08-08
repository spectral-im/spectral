#include "messagelistview.h"

#include <QScrollArea>
#include <QVBoxLayout>

#include <QtDebug>

#include "room.h"

MessageListView::MessageListView(QWidget* parent) : QWidget(parent) {
  auto topLayout = new QVBoxLayout(this);
  topLayout->setMargin(0);
  topLayout->setSpacing(0);

  auto scrollArea = new QScrollArea(this);
  scrollArea->setWidgetResizable(true);
  scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

  auto scrollWidget = new QWidget(this);

  auto scrollLayout = new QVBoxLayout(scrollWidget);
  scrollLayout->setContentsMargins(0, 0, 0, 0);
  scrollLayout->setSpacing(0);

  scrollArea->setWidget(scrollWidget);
  scrollArea->setAlignment(Qt::AlignBottom);

  topLayout->addWidget(scrollArea);

  setContentsMargins(0, 0, 0, 0);
}

void MessageListView::setRoom(SpectralRoom* room) {
  if (currentRoom == room) {
    return;
  }

  if (currentRoom) {
    currentRoom->disconnect(this);
  }

  currentRoom = room;

  if (currentRoom) {
      connect(currentRoom, &Room::addedMessages, this, [=](int lowest, int biggest) {
      });
  }
}

void MessageListView::beginInsertRows(int first, int last) {
    firstInsertedRows = first;
    lastInsertedRows = last;
    hasPendingRows = true;
}

void MessageListView::endInsertRows() {
    if (!hasPendingRows) {
        return;
    }

    hasPendingRows = false;


}
