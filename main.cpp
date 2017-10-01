#include "graphwidget.h"
#include <QApplication>
#include <QTime>
#include <QMainWindow>
#include"mymap.h"
#include"newer.h"
using namespace std;
int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    QMainWindow mainWindow;
    newer * obj = new newer("mohamed");
    mainWindow.setCentralWidget(obj);
    mainWindow.setMinimumSize(1050,800);
    mainWindow.setMaximumWidth(1050);
    mainWindow.setMaximumHeight(800);
    mainWindow.setBaseSize(1050,800);
    mainWindow.raise();
    mainWindow.setWindowIconText("ShortestPath");
    mainWindow.setToolTip("this my first GUI program for getting the shortest Path");
    mainWindow.setToolTipDuration(3000);
    mainWindow.setWindowTitle("Mohamed_Mokhtar_Shortest_Path");
    QFont font("Arial",11,-1,false);
    font.setBold(true);
    font.setLetterSpacing(QFont::AbsoluteSpacing,2);
    font.setWordSpacing(2);
    mainWindow.setFont(font);
    mainWindow.setBackgroundRole(QPalette::Window);
    mainWindow.setWindowIcon(*(new QIcon("e.png")));
    mainWindow.move(480,0);
    mainWindow.show();
    return app.exec();
}
