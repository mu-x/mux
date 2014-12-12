#ifndef PARSER_H
#define PARSER_H

#include <QImage>
#include <QStringList>

#include "Lexer.h"
#include "Items.h"



class Parser
{
    QStringList tags;    // Стэк тэгов
    Block       block;   // Дерево HTML
    QString     title_;  // Заголовок
    bool        a, b, i, u;
    Block*      current; // Текущая

public:
    Parser() : block(0), a(0), b(0), i(0), u(0) {}
    void put(const LexemList& list);  // Загрузка лексем
    QString title() { return title_; }
    QImage image(); // Вывод изображения

private:
    void put_tag(QStringList& tag); // Обработка тэга
    bool push_tag(QStringList& tag); // Контроль вложения
};

#endif // PARSER_H
