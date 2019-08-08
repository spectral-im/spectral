#include "label.h"

#include <QPaintEvent>
#include <QResizeEvent>
#include <QtDebug>

void Label::setText(const QString& text) {
  if (m_text == text) {
    return;
  }

  m_text = text;
  updateCachedTexts();
  update();
}

void Label::resizeEvent(QResizeEvent* e) {
  QLabel::resizeEvent(e);
}

void Label::paintEvent(QPaintEvent* e) {
  updateCachedTexts();
  QLabel::setText(m_elidedText);
  QLabel::paintEvent(e);
}

void Label::updateCachedTexts() {
  const QFontMetrics fm(fontMetrics());
  m_elidedText =
      fm.elidedText(m_text, Qt::ElideRight, width(), Qt::TextShowMnemonic);
  // make sure to show at least the first character
  if (!m_text.isEmpty()) {
    const QString showFirstCharacter = m_text.at(0) + QStringLiteral("...");
    setMinimumWidth(fm.horizontalAdvance(showFirstCharacter) + 1);
  }
}

QSize Label::sizeHint() const {
  return {0, QLabel::sizeHint().height()};
}

QSize Label::minimumSizeHint() const {
  return {0, QLabel::minimumSizeHint().height()};
}
