#pragma once
#include <qstring.h>
class Like
{
private:
	QString id;
	QString news_id;
	QString user_id;
	QString isLiked;
public:
	Like(QString id,
		QString news_id,
		QString user_id,
		QString isLiked);

	QString getId();
	QString getNewsId();
	QString getUserId();
	QString getIsLiked();

	void setId(QString id);
	void setNewsId(QString news_id);
	void setUserId(QString user_id);
	void setIsLiked(QString isLiked);
};

