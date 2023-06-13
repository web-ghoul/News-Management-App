#include "Spam.h"

Spam::Spam(QString id,
	QString news_id,
	QString user_id,
	QString isSpam) {
	this->id = id;
	this->news_id = news_id;
	this->user_id = user_id;
	this->isSpam = isSpam;
}

QString Spam::getId() {
	return id;
}
QString Spam::getNewsId() {
	return news_id;
}
QString Spam::getUserId() {
	return user_id;
}
QString Spam::getIsSpam() {
	return isSpam;
}

void Spam::setId(QString id) {
	this->id = id;
}
void Spam::setNewsId(QString news_id) {
	this->news_id = news_id;
}
void Spam::setUserId(QString user_id) {
	this->user_id = user_id;
}
void Spam::setIsSpam(QString isSpam) {
	this->isSpam = isSpam;
}