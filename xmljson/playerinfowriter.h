#ifndef PLAYERINFOWRITER_H
#define PLAYERINFOWRITER_H

#include <QXmlStreamWriter>
#include "playerinfo.h"
#include <QSettings>

class PlayerInfoWriter{
 public:
    PlayerInfoWriter(QIODevice*, const PlayerInfo&);

    bool Write();
    QString QstringFromType(InventoryItem::Type);


 private:
    bool WritePlayer();
    bool WriteName();
    bool WritePassword();
    bool WriteInventory();
    bool WriteInventoryItem(int);
    bool WriteSubType(int);
    bool WriteLocation();
    bool WritePosition();
    int mIndex;
    QXmlStreamWriter mWriter;
    PlayerInfo mPinfo;
};












#endif // PLAYERINFOWRITER_H
