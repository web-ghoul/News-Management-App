#pragma once

#include <QMainWindow>
#include "ui_Authentication.h"
#include "myApp.h"
#include "Image.h"
#include "User.h"
#include "HomePage.h"
#include <qinputdialog.h>

class Authentication : public QMainWindow
{
	Q_OBJECT

public:
	Authentication(QWidget *parent = nullptr);
	~Authentication();
	myApp app = new myApp();


private slots:
	void on_btn_login_clicked();
	void on_btn_register_clicked();
	void on_eye_pass_reg_toolBtn_clicked();
	void on_eye_conPass_reg_toolBtn_clicked();
	void on_eye_pass_login_toolBtn_clicked();
	void on_forgot_pass_btn_clicked();


private:
	Ui::AuthenticationClass ui;
	QInputDialog* getEmail;
	QInputDialog* getUsername;
	QInputDialog* newPassword;
	bool isPassRegHide, isConPassRegHide, isPassLogHide;
	QMap<QString, Image*> auth_imgs;
	QMap<QString, Image*>  getAuthImgsFromDB();
	QString getUserIdOfEmailAndUsername(QString email, QString username);
	bool confirmPassword(QString pass1, QString pass2);
	void AddNewUserData(QString username, QString email, QString password, QString gender, QString picture, QString pic_ext);
	void go_to_home(QString id);
	void loadImgs();
	void clearRegister();
	void clearLogin();
};
