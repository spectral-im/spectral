#include "materialavatar.h"

#include <QPainter>
#include <QtDebug>

MaterialAvatar::MaterialAvatar(QWidget* parent) : QWidget(parent) {
  m_avatarType = AvatarType::Letter;
  m_letter = "H";

  QFont f(font());
  f.setPixelSize(20);
  setFont(f);

  QSizePolicy policy(QSizePolicy::MinimumExpanding,
                     QSizePolicy::MinimumExpanding);
  setSizePolicy(policy);
}

QColor MaterialAvatar::textColor() const {
  if (!m_textColor.isValid())
    return Qt::white;

  return m_textColor;
}

QColor MaterialAvatar::backgroundColor() const {
  if (!m_backgroundColor.isValid())
    return QColor("#2196F3");

  return m_backgroundColor;
}

QSize MaterialAvatar::sizeHint() const {
  return {0, 0};
}

void MaterialAvatar::setTextColor(const QColor& color) {
  m_textColor = color;
}

void MaterialAvatar::setBackgroundColor(const QColor& color) {
  m_backgroundColor = color;
}

void MaterialAvatar::setLetter(const QString& letter) {
  m_letter = letter;
  if (m_image.isNull() && m_icon.isNull()) {
    m_avatarType = AvatarType::Letter;
  }
  update();
}

void MaterialAvatar::setImage(const QImage& image) {
  m_image = image;
  if (!image.isNull()) {
    m_avatarType = AvatarType::Image;
    auto size =
        std::min(width() * devicePixelRatio(), height() * devicePixelRatio());
    m_pixmap = QPixmap::fromImage(image).scaled(
        size, size, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);
  } else {
    if (m_icon.isNull()) {
      m_avatarType = AvatarType::Letter;
    } else {
      m_avatarType = AvatarType::Icon;
    }
  }

  update();
}

void MaterialAvatar::setIcon(const QIcon& icon) {
  m_icon = icon;

  if (!icon.isNull()) {
    if (m_image.isNull()) {
      m_avatarType = AvatarType::Icon;
    }
  } else {
    m_avatarType = AvatarType::Letter;
  }
  update();
}

void MaterialAvatar::paintEvent(QPaintEvent*) {
  QPainter painter(this);
  painter.setRenderHint(QPainter::Antialiasing);

  QRect r = rect();
  auto size = std::min(width() - 1, height() - 1);
  const int hs = size / 2;

  if (m_avatarType != AvatarType::Image) {
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(backgroundColor());

    painter.setPen(Qt::NoPen);
    painter.setBrush(brush);
    painter.drawEllipse(r.center(), hs, hs);
  }

  switch (m_avatarType) {
    case AvatarType::Icon: {
      m_icon.paint(&painter,
                   QRect((width() - hs) / 2, (height() - hs) / 2, hs, hs),
                   Qt::AlignCenter, QIcon::Normal);
      break;
    }
    case AvatarType::Image: {
      QPainterPath ppath;
      ppath.addEllipse(width() / 2 - hs, height() / 2 - hs, size, size);
      painter.setClipPath(ppath);
      painter.drawPixmap(QRect(width() / 2 - hs, height() / 2 - hs, size, size),
                         m_pixmap);
      break;
    }
    case AvatarType::Letter: {
      painter.setPen(textColor());
      painter.setBrush(Qt::NoBrush);
      painter.drawText(r.translated(0, -1), Qt::AlignCenter, m_letter);
      break;
    }
    default:
      break;
  }
}
