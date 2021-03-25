#ifndef FRIENDMODEL_H
#define FRIENDMODEL_H

#include <QAbstractListModel>
#include "frienditem.h"

class FriendModel : public QAbstractListModel
{
  Q_OBJECT

public:
  explicit FriendModel(QObject* parent = nullptr);
  unsigned GetFirstFriendId() const;    //for loading on startup

  int rowCount(const QModelIndex &parent = QModelIndex()) const override;
  QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
  QHash<int, QByteArray> roleNames() const override;

  void AddFriendToList(FriendItem*);
  bool RemoveFriendFromList(FriendItem*);
  void RemoveAllFriendsFromList();
  FriendItem* FindFriendItem(quint32);
  void SetStatus(unsigned id, bool status);
  void AddUnreadMesg(unsigned id);
  void DeleteUnreadMesgs(unsigned id);

private:
  QList<FriendItem*> friends_list_;  //using QMap will be more comfortable
};
#endif // FRIENDMODEL_H
