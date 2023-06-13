#pragma once
#include <qstring.h>
class Comment
{
private:
	QString id;
	QString comment;
	QString date;
	QString user_id;
	QString news_id;
public:
	Comment(QString id, QString comment, QString date, QString user_id, QString news_id);
	QString getId();
	QString getComment();
	QString getDate();
	QString getUserId();
	QString getNewsId();

	void setId(QString id);
	void setComment(QString comment);
	void setDate(QString date);
	void setUserId(QString user_id);
	void setNewsId(QString news_id);
};

