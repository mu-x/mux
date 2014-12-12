#ifndef BROWSER_H
#define BROWSER_H

#include <QScrollArea>
#include <QLineEdit>



// Окно браузера
class Browser : public QWidget
{
    Q_OBJECT
    QLineEdit* path;
    QScrollArea* workspace;

public:
    explicit Browser(QWidget *parent = 0);

private slots:
    void reload();

};



#endif // BROWSER_H
