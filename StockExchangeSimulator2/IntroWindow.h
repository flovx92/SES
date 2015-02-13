#ifndef INTROWINDOW_H
#define INTROWINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QRadioButton>
#include <QObject>

class IntroWindow : public QWidget
{
    Q_OBJECT

public:
    explicit IntroWindow();
    ~IntroWindow();
public slots:
    void OpenWindow();
private:
    QVBoxLayout* _box;
    QRadioButton* _rand;
    QRadioButton* _company;
    QRadioButton* _sharpe;
    QRadioButton* _bond;
    QRadioButton* _bs;
    QRadioButton* _tree;
    QPushButton* _submit;

};

#endif // INTROWINDOW_H
