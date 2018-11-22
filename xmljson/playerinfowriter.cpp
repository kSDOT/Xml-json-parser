#include "playerinfowriter.h"
#include <QtDebug>
#include <QString>

PlayerInfoWriter::PlayerInfoWriter(QIODevice* qd, const PlayerInfo& p):mIndex{0}, mPinfo{p}
{

    mWriter.setDevice(qd);
    mWriter.setAutoFormatting(true);
    mWriter.setAutoFormattingIndent(2);
}

bool PlayerInfoWriter::Write()
{
    mWriter.writeStartDocument("1.0");
    mWriter.writeStartElement("PlayerInfo");
    WritePlayer();
    mWriter.writeEndElement();
    return 1;
}

QString PlayerInfoWriter::QstringFromType(InventoryItem::Type t)
{
    switch (t) {
        case InventoryItem::Weapon:
                return QString{"weapon"};
        case InventoryItem::Armor:
                return QString{"armor"};
        case InventoryItem::Gem:
                return QString{"gem"};
        case InventoryItem::Book:
                return QString{"book"};;
        case InventoryItem::Other:
                return QString{"other"};
        default:
             return QString{"UNKNOWN"};;
    }
}

bool PlayerInfoWriter::WritePlayer()
{
    mWriter.writeStartElement("Player");

    QXmlStreamAttributes q {};
    q.push_back({"hp",   QString::number(mPinfo.players.at(mIndex).hitPoints)});
    q.push_back({"exp",  QString::number(mPinfo.players.at(mIndex).experience)});
    mWriter.writeAttributes(q );

    WriteName();
    WritePassword();
    WriteInventory();
    WriteLocation();

    mWriter.writeEndElement();
    return 1;
}

bool PlayerInfoWriter::WriteName()
{
    mWriter.writeStartElement("Name");
    mWriter.writeCharacters(mPinfo.players.at(mIndex).name);
    mWriter.writeEndElement();
    return 1;
}

bool PlayerInfoWriter::WritePassword()
{
    mWriter.writeStartElement("Password");
    mWriter.writeCharacters(mPinfo.players.at(mIndex).password);
    mWriter.writeEndElement();
    return 1;
}

bool PlayerInfoWriter::WriteInventory ()
{
    mWriter.writeStartElement("Inventory");
    for(int i = 0; i < mPinfo.players.at(mIndex).inventory.size();++i)
        WriteInventoryItem(i);
    mWriter.writeEndElement();
    return 1;
}

bool PlayerInfoWriter::WriteInventoryItem (int i)
{
    mWriter.writeStartElement("InvItem");

    QXmlStreamAttributes q{};
    q.push_back ({"type",       QstringFromType(mPinfo.players.at(mIndex).inventory.at(i).type)});
    q.push_back ({"durability", QString::number(mPinfo.players.at(mIndex).inventory.at(i).durability)});
    mWriter.writeAttributes(q);

    if(mPinfo.players.at(mIndex).inventory.at(i).subType!=QString{})//if subtype is not empty
        WriteSubType(i);

    mWriter.writeEndElement();
    return 1;
}

bool PlayerInfoWriter::WriteSubType(int i)
{
    mWriter.writeStartElement("SubType");
    mWriter.writeCharacters(mPinfo.players.at(mIndex).inventory.at(i).subType);
    mWriter.writeEndElement();
    return 1;
}

bool PlayerInfoWriter::WriteLocation()
{
    mWriter.writeStartElement("Location");
    mWriter.writeAttribute({"name", mPinfo.players.at(mIndex).location});
    WritePosition();
    mWriter.writeEndElement();
    return 1;
}

bool PlayerInfoWriter::WritePosition()
{
    mWriter.writeStartElement("Position");

    QXmlStreamAttributes q{};
    q.push_back ({"x",       QString::number(mPinfo.players.at(mIndex).position.x())});
    q.push_back ({"y",       QString::number(mPinfo.players.at(mIndex).position.y())});
    mWriter.writeAttributes(q);

    mWriter.writeEndElement();
    return 1;
}

