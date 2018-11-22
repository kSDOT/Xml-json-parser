#ifndef PLAYERINFOREADER_H
#define PLAYERINFOREADER_H

#include <QXmlStreamReader>
#include "playerinfo.h"
#include <QSettings>
class PlayerInfoReader {
public:
    PlayerInfoReader(QIODevice *);
    inline const PlayerInfo& result() const { return m_pinfo; }

    enum Token {
    T_Invalid = -1,
          T_PlayerInfo, 					/* root tag */
          T_Player, 						/* in PlayerInfo */
          T_Name, T_Password, T_Inventory, T_Location,	/* in Player */
          T_Position,						/* in Location */
          T_InvItem						/* in Inventory */
    };

    static Token tokenByName(const QStringRef &r);
    bool read();

protected:
    bool readPlayerInfo();
    Player readPlayer();
    QList<InventoryItem> readInventory();
private:
    QXmlStreamReader reader;
    PlayerInfo m_pinfo;
};

#endif // PLAYERINFOREADER_H
