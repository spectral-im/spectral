#include "roomlistpanel.h"

#include <QLabel>
#include <QVBoxLayout>

#include "src/model/orderbytag.h"
#include "src/model/roomlistmodel.h"

#include "roomlistview.h"

RoomListPanel::RoomListPanel(Controller* controller, QWidget* parent)
    : QWidget(parent), controller(controller) {
  auto layout = new QVBoxLayout(this);

  auto roomListModel = new RoomListModel;
  roomListModel->setOrder<OrderByTag>();

  if (controller->connections().isEmpty()) {
    connect(controller, &Controller::connectionAdded, roomListModel,
            [=](Connection* c) { roomListModel->setConnection(c); });
  } else {
    roomListModel->setConnection(controller->connections()[0]);
  }

  auto roomListView = new RoomListView(roomListModel, this);
  roomListView->setMinimumWidth(180);

  connect(roomListView, &RoomListView::roomSelected, this,
          &RoomListPanel::roomSelected);

  auto roomListFooter = new QLabel("This is a label");

  layout->setContentsMargins(0, 0, 0, 0);
  layout->addWidget(roomListView);
  layout->addWidget(roomListFooter);
}
