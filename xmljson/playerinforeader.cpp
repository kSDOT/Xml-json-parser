#include "playerinforeader.h"
#include <QtDebug>

PlayerInfoReader::PlayerInfoReader(QIODevice *device) {
    reader.setDevice(device);
}

PlayerInfoReader::Token PlayerInfoReader::tokenByName(const QStringRef &r) {
    static QStringList tokenList = QStringList() << "PlayerInfo" << "Player"
                                                 << "Name" << "Password"
                                                 << "Inventory" << "Location"
                                                 << "Position" << "InvItem";
    int idx = tokenList.indexOf(r.toString());
    return (Token)idx;
}

bool PlayerInfoReader::read() {
    m_pinfo = PlayerInfo();
    if(reader.readNextStartElement() && tokenByName(reader.name()) == T_PlayerInfo) {
        return readPlayerInfo();
    } else {
        return false;
    }
}

bool PlayerInfoReader::readPlayerInfo() {
    if(tokenByName(reader.name()) != T_PlayerInfo)
        return false;
    while(reader.readNextStartElement()) {
        if(tokenByName(reader.name()) == T_Player) {
            Player p = readPlayer();
            m_pinfo.players.append(p);
        } else
            reader.skipCurrentElement();
    }
    return true;
}

Player PlayerInfoReader::readPlayer() {
    if(tokenByName(reader.name()) != T_Player) return Player();
    Player p;
    const QXmlStreamAttributes& playerAttrs = reader.attributes();
    p.hitPoints = playerAttrs.value("hp").toString().toInt();
    p.experience = playerAttrs.value("exp").toString().toInt();
    while(reader.readNextStartElement()) {
        Token t = tokenByName(reader.name());
        switch(t) {
        case T_Name: p.name = reader.readElementText(); break;
        case T_Password: p.password = reader.readElementText(); break;
        case T_Inventory: p.inventory = readInventory(); break;
        case T_Location: {
            p.location = reader.attributes().value("name").toString();
            while(reader.readNextStartElement()) {
                if(tokenByName(reader.name()) == T_Position) {
                    const QXmlStreamAttributes& attrs = reader.attributes();
                    p.position.setX(attrs.value("x").toString().toInt());
                    p.position.setY(attrs.value("y").toString().toInt());
                    reader.skipCurrentElement();
                } else
                    reader.skipCurrentElement();
            }
        }; break;
        default:
            reader.skipCurrentElement();
        }
    }
    return p;
}

QList<InventoryItem> PlayerInfoReader::readInventory() {
    QList<InventoryItem> inventory;
    while(reader.readNextStartElement()) {
        if(tokenByName(reader.name()) != T_InvItem) {
            reader.skipCurrentElement();
            continue;
        }
        InventoryItem item;
        const QXmlStreamAttributes& attrs = reader.attributes();
        item.durability = attrs.value("durability").toString().toInt();
        QStringRef typeRef = attrs.value("type");
        if(typeRef == "weapon") {
            item.type = InventoryItem::Weapon;
        } else if(typeRef == "armor") {
            item.type = InventoryItem::Armor;
        } else if(typeRef == "gem") {
            item.type = InventoryItem::Gem;
        } else if(typeRef == "book") {
            item.type = InventoryItem::Book;
        } else item.type = InventoryItem::Other;
        while(reader.readNextStartElement()) {
            if(reader.name() == "SubType")
                item.subType = reader.readElementText();
            else
                reader.skipCurrentElement();
        }
        inventory << item;
    }

    return inventory;
}
