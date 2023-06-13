#include "News.h"


News::News(QString id,
	QString title,
	QString description,
	QString date,
	QString rates,
	QString spams,
	QString user_id,
	QString category_id,
	QString image_ext,
	QString image,
	QString likes, int count_users_rated) {
	this->id = id;
	this->title = title;
	this->description = description;
	this->date = date;
	this->rates = rates;
	this->spams = spams;
	this->likes = likes;
	this->user_id = user_id;
	this->category_id = category_id;
	this->image_ext = image_ext;
	this->image = image;
	this->count_users_rated = count_users_rated;
}


QString News::getId() {
	return id;
}
QString News::getTitle() {
	return title;
}
QString News::getDescription() {
	return description;
}
QString News::getDate() {
	return date;
}
QString News::getRates() {
	return rates;
}
QString News::getSpams() {
	return spams;
}
QString News::getUserId() {
	return user_id;
}
QString News::getCategoryId() {
	return category_id;
}
QString News::getImageExt() {
	return image_ext;
}
QString News::getImage() {
	return image;
}
QString News::getLikes() {
	return likes;
}
int News::getCountUsersRated() {
	return count_users_rated;
}

void News::setId(QString id) {
	this->id = id;
}
void News::setTitle(QString title) {
	this->title = title;
}
void News::setDescription(QString description) {
	this->description = description;
}
void News::setDate(QString date) {
	this->date = date;
}
void News::setRates(QString rates) {
	this->rates = rates;
}
void News::setSpams(QString spams) {
	this->spams = spams;
}
void News::setUserId(QString user_id) {
	this->user_id = user_id;
}
void News::setCategoryId(QString category_id) {
	this->category_id = category_id;
}
void News::setImageExt(QString image_ext) {
	this->image_ext = image_ext;
}
void News::setImage(QString image) {
	this->image = image;
}
void News::setLikes(QString likes) {
	this->likes = likes;
}

void News::setCountUsersRated(int count_users_rated) {
	this->count_users_rated = count_users_rated;
}
