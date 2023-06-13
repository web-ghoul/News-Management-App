#include "Comment.h"

Comment::Comment(QString id, QString comment, QString date, QString user_id, QString news_id) {
	this->id = id;
	this->comment = comment;
	this->date = date;
	this->user_id = user_id;
	this->news_id = news_id;
}

QString Comment::getId() {
	return id;
}
QString Comment::getComment() {
	return comment;
}
QString Comment::getDate() {
	return date;
}
QString Comment::getUserId() {
	return user_id;
}
QString Comment::getNewsId() {
	return news_id;
}

void Comment::setId(QString id) {
	this->id = id;
}
void Comment::setComment(QString comment) {
	this->comment = comment;
}
void Comment::setDate(QString date) {
	this->date = date;
}
void Comment::setUserId(QString user_id) {
	this->user_id = user_id;
}
void Comment::setNewsId(QString news_id) {
	this->news_id = news_id;
}
