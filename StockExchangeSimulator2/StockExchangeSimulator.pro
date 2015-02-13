#-------------------------------------------------
#
# Project created by QtCreator 2015-01-27T12:05:39
#
#-------------------------------------------------

QT       += core gui

#ligne mac
QMAKE_MACOSX_DEPLOYMENT_TARGET = 10.9
#INCLUDEPATH += <boost_install_path>
#LIBS += -L<boost_install_path>/stage/lib


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = StockExchangeSimulator
TEMPLATE = app



SOURCES += main.cpp\
    Agent.cpp\
    Bond.cpp\
    Company.cpp\
    Database.cpp\
    General.cpp\
    Option.cpp\
    Order.cpp\
    Portfolio.cpp\
    RandomAgent.cpp\
    StockExchange.cpp\
    StockExchangeFunctions.cpp\
    TreeAgent.cpp \
    Stock.cpp \
    Stat.cpp \
    Window.cpp \
    StockWindow.cpp \
    PortfolioWindow.cpp \
    OrderWindow.cpp \
    MyOptionStoreWindow.cpp \
    MyOptionsWindow.cpp \
    OptionsStoreWindow.cpp \
    BondWindow.cpp \
    SharpeAgent.cpp \
    BondAgent.cpp \
    CompanyAgent.cpp \
    BlackScholesAgent.cpp \
    Treasure.cpp \
    IntroWindow.cpp


HEADERS  += Agent.h\
    Bond.h\
    Company.h\
    Database.h\
    General.h\
    Option.h\
    Order.h\
    Portfolio.h\
    RandomAgent.h\
    StockExchange.h\
    StockExchangeFunctions.h\
    TreeAgent.h \
    Stock.h \
    Stat.h \
    Window.h \
    StockWindow.h \
    PortfolioWindow.h \
    OrderWindow.h \
    MyOptionStoreWindow.h \
    MyOptionsWindow.h \
    OptionsStoreWindow.h \
    BondWindow.h \
    SharpeAgent.h \
    BondAgent.h \
    CompanyAgent.h \
    BlackScholesAgent.h \
    Treasure.h \
    IntroWindow.h



FORMS    +=
