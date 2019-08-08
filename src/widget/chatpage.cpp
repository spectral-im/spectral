#include "chatpage.h"

#include <QLabel>
#include <QSplitter>

#include <QHBoxLayout>
#include <QVBoxLayout>

#include "roomlistpanel.h"
#include "roompanel.h"

#include "src/model/orderbytag.h"
#include "src/model/roomlistmodel.h"

ChatPage::ChatPage(Controller* controller, QWidget* parent)
    : QWidget(parent), controller(controller) {
  setContentsMargins(0, 0, 0, 0);

  auto layout = new QHBoxLayout(this);
  layout->setContentsMargins(0, 0, 0, 0);

  auto splitter = new QSplitter(this);
  splitter->setHandleWidth(4);

  auto roomListPanel = new RoomListPanel(controller, this);

  auto roomPanel = new RoomPanel(this);

  connect(roomListPanel, &RoomListPanel::roomSelected, roomPanel,
          [=](SpectralRoom* room) { roomPanel->setRoom(room); });

  splitter->setContentsMargins(0, 0, 0, 0);
  splitter->addWidget(roomListPanel);
  splitter->addWidget(roomPanel);

  layout->addWidget(splitter);
}
