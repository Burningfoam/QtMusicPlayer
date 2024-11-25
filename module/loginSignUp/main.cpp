#include "loginsignup.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    loginSignUp w;
    w.show();

    return a.exec();
}
