#include "roomlistview.h"

#include <QApplication>
#include <QPainter>
#include <QStringListModel>
#include <QAbstractItemDelegate>

#include "src/palette.h"

class RoomListViewDelegate : public QAbstractItemDelegate {
 public:
  explicit RoomListViewDelegate(QWidget* parent = nullptr)
      : QAbstractItemDelegate(parent) {}

  void paint(QPainter* painter,
             const QStyleOptionViewItem& option,
             const QModelIndex& index) const override;
  QSize sizeHint(const QStyleOptionViewItem& option,
                 const QModelIndex& index) const override;

  QWidget* createEditor(QWidget* parent,
                        const QStyleOptionViewItem& option,
                        const QModelIndex& index) const override;
};

QSize RoomListViewDelegate::sizeHint(const QStyleOptionViewItem& /*option*/,
                                     const QModelIndex& index) const {
  if (index.parent().isValid()) {
    return {0, 64};
  }
  return {0, 24};
}

void RoomListViewDelegate::paint(QPainter* painter,
                                 const QStyleOptionViewItem& option,
                                 const QModelIndex& index) const {
  painter->setRenderHint(QPainter::Antialiasing);

  if (!index.parent().isValid()) {  // If it is section header
    QFont font = QApplication::font();
    font.setBold(true);
    font.setPixelSize(12);
    QFontMetrics fontMetrics(font);

    QString headerText =
        index.data(RoomListModel::SectionRole).value<QString>();

    QRect headerRect = option.rect;

    headerRect.setTopLeft({option.rect.left() + 16, option.rect.top() + 4});
    headerRect.setBottomRight(
        {option.rect.right() - 4, option.rect.bottom() - 4});

    if (option.state & QStyle::State_Open) {
      painter->setPen(MPalette::activated);
    } else if (option.state & QStyle::State_MouseOver) {
      painter->setPen(MPalette::foreground);
    } else {
      painter->setPen(MPalette::lighter);
    }

    painter->setFont(font);
    painter->drawText(headerRect,
                      fontMetrics.elidedText(headerText, Qt::ElideRight,
                                             headerRect.width() - 4));
  } else {
    QFont font = QApplication::font();
    QFont subFont = QApplication::font();
    font.setPixelSize(16);
    subFont.setPixelSize(13);

    QFontMetrics fontMetrics(font);
    QFontMetrics subFontMetrics(subFont);

    QImage avatar = index.data(RoomListModel::AvatarRole).value<QImage>();
    QString headerText = index.data(RoomListModel::NameRole).value<QString>();
    QString subText = index.data(RoomListModel::TopicRole).value<QString>();

    QRect headerRect = option.rect;
    QRect subheaderRect = option.rect;
    QRect iconRect = subheaderRect;

    QPoint topLeft{option.rect.left() + 12, option.rect.top() + 12};
    QPoint bottomRight{option.rect.right() - 12, option.rect.bottom() - 12};

    iconRect.setTopLeft(topLeft);
    iconRect.setSize({40, 40});

    headerRect.setTopLeft({iconRect.right() + 12, topLeft.y()});
    headerRect.setBottomRight(
        {bottomRight.x(), topLeft.y() + fontMetrics.height() + 5});

    subheaderRect.setTopLeft({iconRect.right() + 12, headerRect.bottom() + 12});
    subheaderRect.setRight(bottomRight.x());

    if (avatar.isNull()) {
      painter->save();
      painter->setBrush(QColor("#2196F3"));
      painter->setPen(Qt::NoPen);
      painter->drawEllipse(iconRect);
      painter->setPen(Qt::white);
      painter->setFont(QFont(font.family(), 20));
      painter->drawText(iconRect, Qt::AlignCenter, headerText.isEmpty() ? 'H' : headerText.at(0).toUpper());
      painter->restore();
    } else {
      painter->save();

      QPainterPath ppath;
      ppath.addEllipse(iconRect.topLeft().x(), iconRect.topLeft().y(),
                       iconRect.width(), iconRect.height());
      painter->setClipPath(ppath);
      painter->drawImage(iconRect, avatar);

      painter->restore();
    }

    if (option.state & QStyle::State_Selected) {
      painter->setPen(MPalette::activated);
    } else if (option.state & QStyle::State_MouseOver) {
      painter->setPen(MPalette::foreground);
    } else {
      painter->setPen(MPalette::lighter);
    }

    painter->setFont(font);
    painter->drawText(
        headerRect,
        fontMetrics.elidedText(headerText, Qt::ElideRight, headerRect.width()));

    painter->setFont(subFont);
    painter->drawText(subheaderRect.left(), subheaderRect.top(),
                      subFontMetrics.elidedText(subText, Qt::ElideRight,
                                                subheaderRect.width()));
  }
}

QWidget* RoomListViewDelegate::createEditor(
    QWidget* /*parent*/,
    const QStyleOptionViewItem& /*option*/,
    const QModelIndex& /*index*/) const {
  return nullptr;
}

RoomListView::RoomListView(RoomListModel* roomListModel, QWidget* parent)
    : QTreeView(parent), roomListModel(roomListModel) {
  setHeaderHidden(true);
  setIndentation(0);
  setRootIsDecorated(false);
  setAnimated(true);

  connect(this, &QTreeView::activated, this, &RoomListView::rowSelected);
  connect(this, &QTreeView::clicked, this, &RoomListView::rowSelected);

  setModel(roomListModel);
  setItemDelegate(new RoomListViewDelegate(this));
}

void RoomListView::rowSelected(const QModelIndex& index) {
  if (roomListModel->isValidRoomIndex(index)) {
    emit roomSelected(roomListModel->roomAt(index));
  }
}
