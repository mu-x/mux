#include <QBrush>

#include "Parser.h"



void Parser::put(const LexemList& list)
{
    current = &block; // Текущий узел
    QStringList tag;  // Содержимое тэга

    for (int i = 0; i < list.count(); i++)
    {
        Lexem lex = list[i];
        /**/ if ((lex.type == Lexem::TAG) && !tag.count()) // скобка вне тэга
        {
            if ((lex.text == "<") || (lex.text == "</"))
                tag.append(lex.text);
            else
                throw QString("Wrong tag opener `" + lex.text + "`");
        }
        else if ((lex.type == Lexem::TAG) && tag.count())  // скобка в тэге
        {
            if ((lex.text == ">") || (lex.text == "/>"))
                { put_tag(tag); tag.clear(); }
            else
                throw QString("Wrong tag closer `" + lex.text + "`");
        }
        else if ((lex.type == Lexem::TEXT) && !tag.count()) // текст вне тэга
        {
            if ((tags.length() == 1) && (tags[0] == "title"))
                title_ += (lex.text + " ");
            else
                current->add(new Text(lex.text, a, b, this->i, u));
        }
        else if ((lex.type == Lexem::TEXT) && tag.count())  // текст в тэге
        {
            tag.append(lex.text);
        }
    }

    if (title_ == "")
        title_ = "No Title";
}

void Parser::put_tag(QStringList& tag)
{
    if (tag.length() < 2)
        throw QString("Error too short tag");
    tag[1] = tag[1].toLower();

    // Декорация текста A,B,I,U
    /**/ if (tag[1] == "a") a = (tag[0] == "<");
    else if (tag[1] == "b") b = (tag[0] == "<");
    else if (tag[1] == "i") i = (tag[0] == "<");
    else if (tag[1] == "u") u = (tag[0] == "<");

    // Простые тэги     BR, IMG
    else if (tag[1] == "br") current->add(new Br());
    else if (tag[1] == "img") current->add(new Image(tag));

    // Бинарные тэги    ...
    else if (tag[1] == "html") {}
    else if (tag[1] == "head") {}
    else if (tag[1] == "body") {}
    else if (tag[1] == "title")
        push_tag(tag);
    else if (tag[1] == "div")
        current = (Block*) (push_tag(tag) ?
                  current->add(new Block(current)) :
                  current->parrent);

    // Список           UL, LI
    else if (tag[1] == "ul")
        if (push_tag(tag))
            current->add(new List(current));
        else {;}
    else if (tag[1] == "li")
        if (push_tag(tag))
        {
           if (tags.indexOf("ul") != tags.length() - 2)
                throw QString("Tag LI without UL error");
           List* list = (List*)current->items.back().data();
           current = new Block(current);
           list->items.append(BlockPtr(current));
        }
        else
           current = (Block*)current->parrent;

    // Таблица          TABLE, TR, TD
    else if (tag[1] == "table")
        if (push_tag(tag))
            current->add(new Grid(current));
        else {;}
    else if (tag[1] == "tr")
        if (push_tag(tag))
        {
            if (tags.indexOf("table") != tags.length() - 2)
                throw QString("Tag TR without TABLE error");
            ((Grid*)current->items.back().data())->
                cells.append(BlockList());
        }
        else {;}
    else if (tag[1] == "td")
        if (push_tag(tag))
        {
            if (tags.indexOf("tr") != tags.length() - 2)
                throw QString("Tag TD without TR error");
            Grid* grid = (Grid*)current->items.back().data();
            current = new Block(current);
            grid->cells.back().append(BlockPtr(current));
        }
        else
           current = (Block*)current->parrent;
}

bool Parser::push_tag(QStringList& tag)
{
    if (tag[0] == "<")
    {
        tags << tag[1];
        return true;
    }
    else
        if (tags.back() == tag[1])
        {
            tags.removeLast();
            return false;
        }
        else
            throw QString("Wrong close tag `" + tag[1] + "`");
}

QImage Parser::image()
{
    QImage image_(block.width(), block.height(), QImage::Format_ARGB32);
    QPainter field(&image_);
    field.setBackground(QBrush(QColor::fromRgb(255,255,255)));
    block.draw(field, 0, 0);
    return image_;
}
