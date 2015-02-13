#ifndef OPTIONSSTOREWINDOW_H
#define OPTIONSSTOREWINDOW_H

#include <QWidget>
#include "Option.h"
#include <vector>
#include <QStandardItemModel>

class OptionsStoreWindow : public QWidget
{
    Q_OBJECT
public:
    explicit OptionsStoreWindow();
    void Update(vector<Option*>);
    ~OptionsStoreWindow();

signals:

private :
    QStandardItemModel* _model;
public slots:
};

#endif // OPTIONSSTOREWINDOW_H
