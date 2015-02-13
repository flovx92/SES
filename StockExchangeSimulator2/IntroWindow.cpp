#include "IntroWindow.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QGroupBox>
#include <QRadioButton>
#include <QObject>
#include <iostream>
#include "Window.h"
#include "Database.h"
#include "General.h"
using namespace std;

IntroWindow::IntroWindow() : QWidget()
{

    _rand = new QRadioButton("Random Agent");
    _company = new QRadioButton("Company Agent");
    _sharpe = new QRadioButton("Sharpe Agent");
    _bond = new QRadioButton("Bond Agent");
    _bs = new QRadioButton("Black Scholes Agent");
    _tree = new QRadioButton("Tree Agent");
    _submit = new QPushButton("ok");

    _rand->setChecked(true);

    _box = new QVBoxLayout;
    _box->addWidget(_rand);
    _box->addWidget(_company);
    _box->addWidget(_sharpe);
    _box->addWidget(_bond);
    _box->addWidget(_bs);
    _box->addWidget(_tree);
    _box->addWidget(_submit);

    QObject::connect(_submit, SIGNAL(clicked()), this, SLOT(OpenWindow()));

    this->setLayout(_box);



    this->show();


}



IntroWindow::~IntroWindow()
{

    delete _rand;
    delete _company;
    delete _sharpe;
    delete _bond;
    delete _bs;
    delete _submit;
    delete _box;

}

void IntroWindow::OpenWindow()
{
    int init;
    if(_rand->isChecked())
    {
        init=0;
    }
    if(_company->isChecked())
    {
        init=1;
    }
    if(_sharpe->isChecked())
    {
        init=2;
    }
    if(_bond->isChecked())
    {
        init=3;
    }
    if(_bs->isChecked())
    {
        init=4;
    }
    if(_tree->isChecked())
    {
        init=5;
    }
    this->hide();
    Database* pdata = Initialisation(init);
    Window* frame = new Window(pdata);
    frame->show();
    pdata->Simulation(frame);

}
