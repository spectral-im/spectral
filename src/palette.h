#ifndef PALETTE_H
#define PALETTE_H

#include <QColor>

namespace MPalette {
static const QColor background = QColor("#263238");
static const QColor foreground = QColor("#CFD8DC");
static const QColor activated = QColor("#80CBC4");
static const QColor lighter = QColor("#546E7A");
static const QColor highlight = QColor("#AFBDC4");
static const QColor border = QColor("#536D79");
static const QColor disabled = QColor("#444444");
static const QColor handle = QColor("#37474F");

static QString generateStyleSheet(QString input) {
  QString inputText(input);

  inputText.replace("@background", background.name());
  inputText.replace("@foreground", foreground.name());
  inputText.replace("@activated", activated.name());
  inputText.replace("@lighter", lighter.name());
  inputText.replace("@highlight", highlight.name());
  inputText.replace("@border", border.name());
  inputText.replace("@disabled", disabled.name());
  inputText.replace("@handle", handle.name());

  return inputText;
}
}  // namespace MPalette

#endif  // PALETTE_H
