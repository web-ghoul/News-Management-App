#include "Rate.h"


Rate::Rate(QString id,
	QString news_id,
	QString user_id,
	QString rate) {
	this->id = id;
	this->news_id = news_id;
	this->user_id = user_id;
	this->rate = rate;
}

QString Rate::getId() {
	return id;
}
QString Rate::getNewsId() {
	return news_id;
}
QString Rate::getUserId() {
	return user_id;
}
QString Rate::getRate() {
	return rate;
}

void Rate::setId(QString id) {
	this->id = id;
}
void Rate::setNewsId(QString news_id) {
	this->news_id = news_id;
}
void Rate::setUserId(QString user_id) {
	this->user_id = user_id;
}
void Rate::setRate(QString rate) {
	this->rate = rate;
}