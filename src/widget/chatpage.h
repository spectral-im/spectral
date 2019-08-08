#ifndef CHATPAGE_H
#define CHATPAGE_H

#include <QWidget>

#include <QHBoxLayout>

#include "src/controller.h"

class ChatPage : public QWidget {
  Q_OBJECT
 public:
  explicit ChatPage(Controller* controller, QWidget* parent = nullptr);

 signals:

 public slots:

 private:
  Controller* controller;
};

#endif  // CHATPAGE_H
