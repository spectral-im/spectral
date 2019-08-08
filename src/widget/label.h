#ifndef LABEL_H
#define LABEL_H

#include <QLabel>

// MIT - Yash : Speedovation.com [ Picked from internet and modified. if owner
// needs to add or change license do let me know.]

class Label : public QLabel {
  Q_OBJECT
 public:
  using QLabel::QLabel;
  QString text() const { return m_text; }
  void setText(const QString& text);

  QSize sizeHint() const override;
  QSize minimumSizeHint() const override;

 protected:
  void paintEvent(QPaintEvent* e) override;
  void resizeEvent(QResizeEvent* e) override;

 private:
  void updateCachedTexts();

 private:
  QString m_elidedText;
  QString m_text;
};

#endif  // ELIDEDLABEL_HPP
