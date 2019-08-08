#include "roompanel.h"

#include <QHBoxLayout>
#include <QVBoxLayout>

#include "label.h"
#include "materialavatar.h"
#include "messagelistview.h"

#include "src/palette.h"

RoomPanelHeader::RoomPanelHeader(QWidget* parent) : QWidget(parent) {
  setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);

  setFixedHeight(64);

  auto layout = new QHBoxLayout(this);
  layout->setContentsMargins(12, 12, 12, 12);

  avatar = new MaterialAvatar(this);
  avatar->setFixedSize(40, 40);

  auto sub = new QWidget(this);

  auto subLayout = new QVBoxLayout(sub);
  subLayout->setContentsMargins(0, 0, 0, 0);
  subLayout->setSpacing(8);

  title = new Label(this);
  auto titleFont = title->font();
  titleFont.setPixelSize(16);
  title->setFont(titleFont);
  title->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);

  subTitle = new Label(this);
  auto subTitleFont = subTitle->font();
  subTitleFont.setPixelSize(13);
  subTitle->setFont(subTitleFont);
  auto subTitlePalette = subTitle->palette();
  subTitlePalette.setColor(subTitle->foregroundRole(), MPalette::foreground);
  subTitle->setPalette(subTitlePalette);
  subTitle->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);

  subLayout->addWidget(title);
  subLayout->addWidget(subTitle);

  layout->addWidget(avatar);
  layout->addWidget(sub);
}

void RoomPanelHeader::setRoom(SpectralRoom* room) {
  if (room == currentRoom) {
    return;
  }

  if (currentRoom) {
    currentRoom->disconnect(this);
  }

  if (room) {
    auto avatarSize = 40.0 * devicePixelRatio();

    if (!room->avatarMediaId().isEmpty()) {
      auto avatarPixmap = QPixmap::fromImage(room->avatar(avatarSize))
                              .scaled(avatarSize, avatarSize);
      avatar->setImage(room->avatar(40.0 * devicePixelRatio()));
    }

    avatar->setLetter(room->displayName().isEmpty()
                          ? ""
                          : QString(room->displayName().at(0)));
    title->setText(room->displayName().remove("\n"));
    subTitle->setText(room->topic().remove("\n"));

    connect(room, &Room::avatarChanged, this, [=] {
      auto as = 40.0 * devicePixelRatio();
      auto ap = room->avatar(as);

      avatar->setImage(ap);
    });
    connect(room, &Room::namesChanged, this, [=] {
      title->setText(room->displayName().remove("\n"));
      avatar->setLetter(room->displayName().isEmpty()
                            ? ""
                            : QString(room->displayName().at(0)));
    });
    connect(room, &Room::topicChanged, this,
            [=] { subTitle->setText(room->topic().remove("\n")); });
  } else {
    avatar->setLetter("");
    avatar->setImage({});
    title->clear();
    subTitle->clear();
  }
}

RoomPanel::RoomPanel(QWidget* parent) : QWidget(parent) {
  setMinimumWidth(480);

  auto layout = new QVBoxLayout(this);
  layout->setContentsMargins(0, 0, 0, 0);
  layout->setSpacing(0);

  auto roomPanelHeader = new RoomPanelHeader(this);

  connect(this, &RoomPanel::roomChanged, roomPanelHeader,
          [this, roomPanelHeader]() { roomPanelHeader->setRoom(currentRoom); });

  auto messageListView = new MessageListView(this);

  connect(this, &RoomPanel::roomChanged, messageListView,
          [this, messageListView]() { messageListView->setRoom(currentRoom); });

  layout->addWidget(roomPanelHeader, 0, Qt::AlignTop);
  layout->addWidget(messageListView);
}
