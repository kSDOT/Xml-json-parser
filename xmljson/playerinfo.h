#ifndef PLAYERDATA_H
#define PLAYERDATA_H

#include <QString>
#include <QList>
#include <QPoint>
#include <QObject>
struct InventoryItem {
  enum Type { Weapon, Armor, Gem, Book, Other } type;
  QString subType;
  int durability;
};

struct Player {
  QString name;
  QString password;
  int experience;
  int hitPoints;
  QList<InventoryItem> inventory;
  QString location;
  QPoint position;
};

struct PlayerInfo {
  QList<Player> players;
};

#endif // PLAYERDATA_H

