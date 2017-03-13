#ifndef LEXER_H
#define LEXER_H

#include <QString>
#include <QList>



// Лексема (мин единица кода)
struct Lexem
{
    enum LT { TAG, SPACE, TEXT }; // Типы лексем
    static LT getType(char char_); // Определение типа по символу

    LT      type; // Тип
    QString text; // Содержимое

    Lexem(char char_); // Создание по первому символу
};

// Список
typedef QList<Lexem> LexemList;



// Лерсер (разбиение текста на лексемы)
class Lexer
{
    enum LS { WAIT, MAKE }; // Состояния лексера

    LS        state; // Текущее
    LexemList list;  // Список лексем

public:

    Lexer() : state(WAIT) {}
    LexemList& lexemList() { return list; }
    void put(char char_); // Новый символ

};

#endif // LEXER_H
