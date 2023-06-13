#pragma once
#include <qstring.h>
class Spam
{
private:
	QString id;
	QString news_id;
	QString user_id;
	QString isSpam;
public:
	Spam(QString id,
		QString news_id,
		QString user_id,
		QString isSpam);

	QString getId();
	QString getNewsId();
	QString getUserId();
	QString getIsSpam();

	void setId(QString id);
	void setNewsId(QString news_id);
	void setUserId(QString user_id);
	void setIsSpam(QString isSpam);
};

