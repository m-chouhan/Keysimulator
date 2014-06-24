
/****
  This application contains server code that will execute client commands
****/

#define _WIN32_WINNT 0x0500 //For INPUT class

#include <QApplication>
#include "Windows.h"
#include "Winuser.h"
#include "KeySimulatorServer.h"

using namespace std;

int main(int argv,char *argc[])
{
    QApplication app(argv,argc);
    KeySimulatorServer Lisa(QString("192.168.43.156"));
    Lisa.show();
    return app.exec();
}

