#include "Category.h"

Category::Category(QString id, QString category, QString date, QString admin_id, QString image, QString image_ext) {
	this->id = id;
	this->category = category;
	this->date = date;
	this->admin_id = admin_id;
	this->image = image;
	this->image_ext = image_ext;
	this->active = "0";
}

QString Category::getId() {
	return id;
}
QString Category::getCategory() {
	return category;
}
QString Category::getDate() {
	return date;
}
QString Category::getAdminId() {
	return admin_id;
}
QString Category::getImage() {
	return image;
}
QString Category::getImageExt() {
	return image_ext;
}
QString Category::getActive() {
	return active;
}


void Category::setId(QString id) {
	this->id = id;
}
void Category::setCategory(QString category) {
	this->category = category;
}
void Category::setDate(QString date) {
	this->date = date;
}
void Category::setAdminId(QString admin_id) {
	this->admin_id = admin_id;
}
void Category::setImage(QString image) {
	this->image = image;
}
void Category::setImageExt(QString image_ext) {
	this->image_ext = image_ext;
}
void Category::setActive(QString active) {
	this->active = active;
}