#pragma once
#include <qstring.h>
class Rate
{
private:
	QString id;
	QString news_id;
	QString user_id;
	QString rate;
public:
	Rate(QString id,
		QString news_id,
		QString user_id,
		QString rate);

	  QString getId();
	  QString getNewsId();
	  QString getUserId();
	  QString getRate();

	  void setId(QString id);
	  void setNewsId(QString news_id);
	  void setUserId(QString user_id);
	  void setRate(QString rate);
};

