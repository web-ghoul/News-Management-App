#include "myApp.h"
#include <QtWidgets/QApplication>
#include "Authentication.h"
#include "HomePage.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Authentication auth;
    auth.show();
    return a.exec();
}
