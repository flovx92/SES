#ifndef MYOPTIONSTOREWINDOW_H
#define MYOPTIONSTOREWINDOW_H

#include <QWidget>
#include "Option.h"
#include <vector>
#include <QStandardItemModel>

class MyOptionStoreWindow : public QWidget
{
    Q_OBJECT
public:
    explicit MyOptionStoreWindow();
    void Update(vector<Option*>);
    ~MyOptionStoreWindow();
private:
    QStandardItemModel* _model;
signals:

public slots:
};

#endif // MYOPTIONSTOREWINDOW_H
