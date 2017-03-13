#include <QFont>

#include "Items.h"



void Text::draw(QPainter& field, int x, int y)
{
    QFont font("Courier", FONT_H, FONT_W);
    field.setPen(a ? QColor::fromRgb(0,0,255) :
                     QColor::fromRgb(0,0,0));

    font.setBold(b);
    font.setItalic(i);
    font.setUnderline(u);

    field.setFont(font);
    field.drawText(x, y, width(), height(),
        Qt::TextJustificationForced, text);
}



Image::Image(const QStringList& attr)
{
    QString path;
    for (int i = 2; i < attr.count(); i++)
    {
        QStringList cur = attr[i].split("=");
        if ((cur.length() == 2) && (cur[0] == "src"))
            path = cur[1];
    }
    if (!path.isEmpty())
        image =  QImage(path);
}

void Image::draw(QPainter& field, int x, int y)
{
    field.drawImage(x, y, image);
}



int Block::width()
{
    int size = 0, total = 0;
    for (int i = 0; i < items.count(); i++)
    {
        if (items[i]->newline())
            size = 0;
        size += items[i]->width();
        if (total < size)
            total = size;
    }
    return total;
}

int Block::height()
{
    int size = 0, total = 0;
    for (int i = 0; i < items.count(); i++)
    {
        if (items[i]->newline())
        {
            total += (size + MARG_H);
            size = 0;
        }
        if (size < items[i]->height())
            size = items[i]->height();
    }
    return total + size;
}

void Block::draw(QPainter& field, int x, int y)
{
    int size = 0, base = x;
    for (int i = 0; i < items.count(); i++)
    {
        if (items[i]->newline())
        {
            y += size + MARG_H;
            size = 0;
            x = base;
        }
        items[i]->draw(field, x, y);
        x += (items[i]->width() + MARG_W);
        if (size < items[i]->height())
            size = items[i]->height();
    }
}



int List::width()
{
    int size = 0, buf;
    for (int i = 0; i < items.count(); i++)
        if ((buf = items[i]->width()) > size)
            size = buf;
    return FONT_W + MARG_W + size;
}

int List::height()
{
    int size = 0;
    for (int i = 0; i < items.count(); i++)
        size += (items[i]->height() + MARG_H);
    return size;
}

void List::draw(QPainter& field, int x, int y)
{
    for (int i = 0; i < items.count(); i++)
    {
        field.drawText(x, y, FONT_W, FONT_H, 0, QString("*"));
        field.drawText(x, y, FONT_W, FONT_H, 0, QString("^"));
        items[i]->draw(field, x + FONT_W + MARG_W, y);
        y += (items[i]->height() + MARG_H);
    }
}



int Grid::width()
{
    int size_one = 0, buf, count = 0;
    for (int i = 0; i < cells.count(); i++)
    {
        if (count < cells[i].count())
            count = cells[i].count();
        for (int j = 0; j < cells[i].count(); j++)
            if ((buf = cells[i][j]->width()) > size_one);
                size_one = buf;
    }
    return count * (size_one + MARG_H);
}

int Grid::height()
{
    int size_one = 0, buf;
    for (int i = 0; i < cells.count(); i++)
        for (int j = 0; j < cells[i].count(); j++)
            if ((buf = cells[i][j]->height()) > size_one);
                size_one = buf;
    return cells.count() * size_one;
}

void Grid::draw(QPainter& field, int x, int y)
{
    int height_one = height() / cells.count();
    for (int i = 0; i < cells.count(); ++i)
    {
        int width_one = width() / cells[i].count();
        for (int j = 0; j < cells[i].count(); j++)
            cells[i][j]->draw(field, x + width_one * j, y + height_one * i);
    }
}
