#include "Lexer.h"



Lexem::LT Lexem::getType(char char_)
{
    switch (char_)
    {
    case '<':
    case '>':
    case '/':
        return TAG;

    case ' ':
    case '\t':
    case '\n':
        return SPACE;

    default:
        return TEXT;
    }
}

Lexem::Lexem(char char_)
    : type(getType(char_))
    , text(QString(char_))
{
}



void Lexer::put(char char_)
{
    Lexem::LT type = Lexem::getType(char_);
    if (type == Lexem::SPACE)
    {
        state = WAIT;
        return;
    }

    switch (state)
    {

    case WAIT: // Ожидание
        list.append(Lexem(char_));
        state = MAKE;
        return;

    case MAKE: // Генерация
        if (type == list.back().type)
            list.back().text.append(char_);
        else {
            state = WAIT;
            put(char_);
        } return;

    }
};
