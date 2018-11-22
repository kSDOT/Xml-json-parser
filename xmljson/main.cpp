#include "playerinforeader.h"
#include "playerinfowriter.h"
#include "playerinfojson.h"
#include <QCoreApplication>
#include <QFile>
#include <QtDebug>
#include <QByteArray>
#include <QSettings>
#include <QStandardPaths>
#include <QJsonDocument>
int main(int argc, char **argv) {
    PlayerInfo playerInfo;

//XML
    //READ FROM XML
    QFile file( "..\\xmljson\\playerinfo.xml" );
    file.open(QFile::ReadOnly|QFile::Text);
    PlayerInfoReader reader(&file);

    if(reader.read()) {
        playerInfo = reader.result();
        qDebug() << "Count:" << playerInfo.players.count();
        qDebug() << "Size of inventory:" << playerInfo.players.first().inventory.size();
        qDebug() << "Room: " << playerInfo.players.first().location << playerInfo.players.first().position;
    }
    file.close();

    //WRITE TO XML
    QFile filewr( "..\\xmljson\\playerinfowr.xml" );
    filewr.open(QFile::WriteOnly|QFile::Text);
    PlayerInfoWriter writer (&filewr, playerInfo);
    writer.Write();
    filewr.close();

  //JSON
    //WRITE TO JSON
    QFile filej( "..\\xmljson\\playerinfojson.json" );
    filej.open(QFile::WriteOnly|QFile::Text);
    PlayerInfoJson js {};
    QByteArray result{js.WritePlayerInfo(playerInfo)};//write from previously created playerInfo to js
    filej.write(result);
    filej.close();

    //READ FROM JSON
    filej.open(QFile::ReadOnly|QFile::Text);
    PlayerInfoJson jsReadFile{};
    PlayerInfo playerInfo2{ jsReadFile.readPlayerInfo(filej.readAll())};
    if(!playerInfo2.players.isEmpty())
        qDebug() << js.WritePlayerInfo(playerInfo2);
    filej.close();

    return 0;
}
