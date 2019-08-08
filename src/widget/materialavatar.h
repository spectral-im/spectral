#ifndef MATERIALAVATAR_H
#define MATERIALAVATAR_H

#include <QIcon>
#include <QWidget>

enum AvatarType {
  Letter = 0,
  Image,
  Icon,
};

class MaterialAvatar : public QWidget {
  Q_OBJECT
 public:
  explicit MaterialAvatar(QWidget* parent = nullptr);

  void setBackgroundColor(const QColor& color);
  void setIcon(const QIcon& icon);
  void setImage(const QImage& image);
  void setLetter(const QString& letter);
  void setTextColor(const QColor& color);

  QColor backgroundColor() const;
  QColor textColor() const;

  QSize sizeHint() const override;

 protected:
  void paintEvent(QPaintEvent* event) override;

 private:
  void init();

  AvatarType m_avatarType;
  QString m_letter;
  QColor m_backgroundColor;
  QColor m_textColor;
  QIcon m_icon;
  QImage m_image;
  QPixmap m_pixmap;
};

#endif  // MATERIALAVATAR_H
