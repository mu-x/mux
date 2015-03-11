#include <QApplication>
#include <QTextCodec>

#include <Browser.h>


int main(int argc, char* argv[])
{
    QTextCodec* codec =
    QTextCodec::codecForName("UTF8");
    QTextCodec::setCodecForTr(codec);

    QApplication app(argc, argv);
    Browser browser;
    browser.show();
    return app.exec();
}
