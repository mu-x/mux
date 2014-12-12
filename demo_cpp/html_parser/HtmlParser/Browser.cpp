#include "Browser.h"

#include <QFile>
#include <QPixmap>
#include <QPainter>

#include <QLabel>
#include <QVBoxLayout>
#include <QMessageBox>


#include "Lexer.h"
#include "Parser.h"



Browser::Browser(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout* box = new QVBoxLayout();
    box->addWidget(path = new QLineEdit("TestPage.html"));
    box->addWidget(workspace = new QScrollArea);

    connect(path, SIGNAL(returnPressed()), SLOT(reload()));
    setLayout(box);
    resize(800, 600);
    reload();
}

void Browser::reload()
{
    try
    {
        QFile file(path->text());
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
            throw QString("File `" + path->text() + "` can't be found!");

        // Разбиение на лексемы
        Lexer lexer;
        while (!file.atEnd())
        {
            char char_;
            file.getChar(&char_);
            lexer.put(char_);
        }

        // Парсирование лексем
        Parser parser;
        parser.put(lexer.lexemList());

        // Вывод полученого изображения
        QLabel* label = new QLabel();
        label->setPixmap(QPixmap::fromImage(parser.image()));
        workspace->setWidget(label);
        setWindowTitle(parser.title() + " - Html Parser");
    }
    catch (const QString& error)
    {
        QMessageBox::warning(0, "Error", error);
    }
}
