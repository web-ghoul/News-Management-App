#include "Image.h"


Image::Image(QString id,
	QString image_data,
	QString image_ext,
	QString image_name) {
	this->id = id;
	this->image_data = image_data;
	this->image_ext = image_ext;
	this->image_name = image_name;
}

QString Image::getId() {
	return id;
}
QString Image::getImageData() {
	return image_data;
}
QString Image::getImageExt() {
	return image_ext;
}
QString Image::getImageName() {
	return image_name;
}

void Image::setId(QString id) {
	this->id = id;
}
void Image::setImageData(QString image_data) {
	this->image_data = image_data;
}
void Image::setImageExt(QString image_ext) {
	this->image_ext = image_ext;
}
void Image::setImageName(QString image_name) {
	this->image_name = image_name;
}