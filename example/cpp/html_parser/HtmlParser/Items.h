#ifndef ITEMS_H
#define ITEMS_H

#include <QPair>
#include <QList>
#include <QSharedPointer>

#include <QImage>
#include <QPainter>

#include "Lexer.h"



// Разраяженность
const int MARG_W = 3, MARG_H = 5;  // Отступы
const int FONT_W = 11, FONT_H = 10; // Шрифты



// Элемент HTML
struct Item
{
    Item* parrent; // Родительский узел

    virtual int width() = 0; // Ширина
    virtual int height() = 0; // Высота
    virtual void draw(QPainter& field, int x, int y) = 0; // Отрисовка
    virtual bool newline() = 0; // С новой строки
};

typedef QSharedPointer<Item> ItemPtr;
typedef QList<ItemPtr> ItemList;


struct Br : public Item
{
    virtual int width() { return MARG_W; }
    virtual int height() { return FONT_H + MARG_H; }
    virtual void draw(QPainter& field, int x, int y) {}
    virtual bool newline() { return true; }
};


// Текст HTML
struct Text : public Item
{
    QString text;
    bool a, b, i, u;

    virtual int width() { return text.length() * FONT_W; }
    virtual int height() { return FONT_H + MARG_H; }
    virtual void draw(QPainter& field, int x, int y);
    virtual bool newline() { return false; };

    Text(const QString& t = "",
         bool a_ = 0, bool b_ = 0, bool i_ = 0, bool u_ = 0)
        : text(t), a(a_), b(b_), i(i_), u(u_)  {}
};



// Тэг IMG
struct Image : public Item
{
    QImage image;

    virtual int width() { image.width(); }
    virtual int height() { image.height(); }
    virtual void draw(QPainter& field, int x, int y);
    virtual bool newline() { return false; };

    Image(const QStringList& attr);
};



// Тэг DIV, LI, TD
struct Block : public Item
{
    ItemList items;

    virtual int width();
    virtual int height();
    virtual void draw(QPainter& field, int x, int y);
    virtual bool newline() { return true; };

    Item* add(Item* item) { items.append(ItemPtr(item)); return item; }
    Block(Item* p) { parrent = p; }
};

typedef QSharedPointer<Block> BlockPtr;
typedef QList<BlockPtr> BlockList;
typedef QList<BlockList> BlockGrid;



// Tэг Ul
struct List : public Item
{
    BlockList items;

    virtual int width();
    virtual int height();
    virtual void draw(QPainter& field, int x, int y);
    virtual bool newline() { return true; };

    List(Item* p) { parrent = p; }
};



// Тэг TABLE +TD
struct Grid : public Item
{
    BlockGrid cells;

    virtual int width();
    virtual int height();
    virtual void draw(QPainter& field, int x, int y);
    virtual bool newline() { return true; };

    Grid(Item* p) { parrent = p; }
};


#endif // ITEMS_H
