#include "widget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // 注册 SongInfo 和 QList<SongInfo> 类型
    qRegisterMetaType<SongInfo>("SongInfo");
    qRegisterMetaType<QList<SongInfo>>("QList<SongInfo>");

    Widget w;
    w.show();
    return a.exec();
}
