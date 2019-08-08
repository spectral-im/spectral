#include "mainwindow.h"

#include "connection.h"

#include "spectralroom.h"
#include "spectraluser.h"

#include "widget/chatpage.h"

using namespace QMatrixClient;

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), controller(new Controller(this)) {
  setMinimumSize({720, 480});

  setContentsMargins(0, 0, 0, 0);

  auto chatPage = new ChatPage(controller, this);
  setCentralWidget(chatPage);
}
