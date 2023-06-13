#include "User.h"


User::User(QString id,
	QString email,
	QString password,
	QString isAdmin,
	QString username,
	QString gender,
	QString image,
	QString image_ext,
	QString isVerify) {
	this->id = id;
	this->email = email;
	this->password = password;
	this->isAdmin = isAdmin;
	this->username = username;
	this->gender = gender;
	this->image = image;
	this->image_ext = image_ext;
	this->isVerify = isVerify;
}


QString User::getId() {
	return id;
}
QString User::getEmail() {
	return email;
}
QString User::getPassword() {
	return password;
}
QString User::getIsAdmin() {
	return  isAdmin;
}
QString User::getUsername() {
	return username;
}
QString User::getGender() {
	return gender;
}
QString User::getImage() {
	return image;
}
QString User::getImageExt() {
	return image_ext;
}
QString User::getIsVerify() {
	return isVerify;
}


void User::setId(QString id) {
	this->id = id;
}
void User::setEmail(QString email) {
	this->email = email;
}
void User::setPassword(QString password) {
	this->password = password;
}
void User::setIsAdmin(QString isAdmin) {
	this->isAdmin = isAdmin;
}
void User::setUsername(QString username) {
	this->username = username;
}
void User::setGender(QString gender) {
	this->gender = gender;
}
void User::setImage(QString image) {
	this->image = image;
}
void User::setImageExt(QString image_ext) {
	this->image_ext = image_ext;
}
void User::setIsVerify(QString isVerify) {
	this->isVerify = isVerify;
}