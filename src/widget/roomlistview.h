#ifndef ROOMLISTVIEW_H
#define ROOMLISTVIEW_H

#include <QObject>

#include <QTreeView>

#include "src/model/roomlistmodel.h"

#include "src/spectralroom.h"

class RoomListView : public QTreeView {
  Q_OBJECT
 public:
  explicit RoomListView(RoomListModel* roomListModel,
                        QWidget* parent = nullptr);

 signals:
  void roomSelected(SpectralRoom* room);

 public slots:
  void rowSelected(const QModelIndex& index);

 private:
  RoomListModel* roomListModel;
};

#endif  // ROOMLISTVIEW_H
