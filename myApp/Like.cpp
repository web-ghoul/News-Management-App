#include "Like.h"


Like::Like(QString id,
	QString news_id,
	QString user_id,
	QString isLiked) {
	this->id = id;
	this->news_id = news_id;
	this->user_id = user_id;
	this->isLiked = isLiked;
}

QString Like::getId() {
	return id;
}
QString Like::getNewsId() {
	return news_id;
}
QString Like::getUserId() {
	return user_id;
}
QString Like::getIsLiked() {
	return isLiked;
}

void Like::setId(QString id) {
	this->id = id;
}
void Like::setNewsId(QString news_id) {
	this->news_id = news_id;
}
void Like::setUserId(QString user_id) {
	this->user_id = user_id;
}
void Like::setIsLiked(QString isLiked) {
	this->isLiked = isLiked;
}