#pragma once
#include <qstring.h>
class User
{
private:
	QString id;
	QString email;
	QString password;
	QString isAdmin;
	QString username;
	QString gender;
	QString image;
	QString image_ext;
	QString isVerify;

public:
	User(QString id,
		QString email,
		QString password,
		QString isAdmin,
		QString username,
		QString gender,
		QString image,
		QString image_ext,
		QString isVerify);


	QString getId();
	QString getEmail();
	QString getPassword();
	QString getIsAdmin();
	QString getUsername();
	QString getGender();
	QString getImage();
	QString getImageExt();
	QString getIsVerify();


	void setId(QString id);
	void setEmail(QString email);
	void setPassword(QString password);
	void setIsAdmin(QString isAdmin);
	void setUsername(QString username);
	void setGender(QString gender);
	void setImage(QString image);
	void setImageExt(QString image_ext);
	void setIsVerify(QString isVerify);
};

