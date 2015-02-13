#ifndef MYOPTIONSWINDOW_H
#define MYOPTIONSWINDOW_H

#include <QWidget>
#include "Option.h"
#include <vector>
#include <QStandardItemModel>

class MyOptionsWindow : public QWidget
{
    Q_OBJECT
public:
    explicit MyOptionsWindow();
    void Update(vector<Option*>);
    ~MyOptionsWindow();
private:
    QStandardItemModel* _model;
signals:

public slots:
};

#endif // MYOPTIONSWINDOW_H
