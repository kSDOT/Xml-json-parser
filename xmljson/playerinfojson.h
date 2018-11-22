#ifndef PLAYERINFOJSON_H
#define PLAYERINFOJSON_H

#include "playerinfo.h"
#include <QByteArray>
#include <QVariant>

class PlayerInfoJson{
 public:
    PlayerInfoJson(){}

    QByteArray WritePlayerInfo(const PlayerInfo&)  const;

    PlayerInfo readPlayerInfo (const QByteArray&)  const;
    PlayerInfo readPlayerInfo (const QJsonArray&)  const;

 private:
    //write to file
    QVariant toVariant (const PlayerInfo&)           const;
    QVariant toVariant (const Player&)               const;
    QVariant toVariant (const QList<InventoryItem>&) const;
    QVariant toVariant (const InventoryItem&)        const;

    //read from file
    Player               readPlayer     (const QJsonObject&) const;
    InventoryItem        readItem       (const QJsonObject&) const;
    QList<InventoryItem> readInventory  (const QJsonArray&)  const;
};



#endif // PLAYERINFOJSON_H
