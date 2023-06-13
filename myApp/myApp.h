#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_myApp.h"
#include <qsqldatabase.h>
#include <qsqlquery.h>
#include <qsql.h>
#include <vector>
#include <qpair.h>
#include<qvector.h>
#include <qmessagebox.h>
#include <regex>
#include <qdebug.h>
#include <string>
#include <qbuffer.h>
#include<qdatetime.h>
#include <qbytearray.h>
#include<qmap.h>
#include<qstack.h>
#include<qlabel.h>
#include<qframe.h>
#include<qfont.h>
#include<qgroupbox.h>
#include<qpushbutton.h>
#include<qgraphicseffect.h>
#include <qfile.h>
#include <qfileinfo.h>
#include <qtimer.h>
#include <qelapsedtimer.h>
#include "Image.h"
#include <qfiledialog.h>
using namespace std;

class myApp : public QMainWindow
{
    Q_OBJECT

public:
    myApp(QWidget *parent = nullptr);
    ~myApp();
    QSqlDatabase DB;
    QMap<QString, Image*> gen_imgs;
    QPixmap convertImageDataToImageView(QByteArray imageData, const char* format);
    QByteArray convertImageViewToImageData(QString imagePath);
    bool isUserExist(QString emailOrUsername);
    bool validateEmail(QString email , bool msg = false);
    bool validatePassword(QString password);
    QString getPasswordByEmailOrUsername(QString emailOrUsername);
    int message(string title, string text, string infoText);
    QMap<QString, Image*> getGeneralImagesFromDB();
    void changePasswaord(QString id, QString newPass);
    QString openBrowser();
    bool validateUsername(QString username);

    QString getUserIdByEmailOrUsername(QString emailOrUsername);
private:
    Ui::myAppClass ui;
};
