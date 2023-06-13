#pragma once
#include <qstring.h>
class News
{
private:
	QString id;
	QString title;
	QString description;
	QString date;
	QString rates;
	QString spams;
	QString user_id;
	QString category_id;
	QString image_ext;
	QString image;
	QString likes;
	int count_users_rated;
public:
	News(QString id,
		QString title,
		QString description,
		QString date,
		QString rates,
		QString spams,
		QString user_id,
		QString category_id,
		QString image_ext,
		QString image,
		QString likes,
		int count_users_rated);


	QString getId();
	QString getTitle();
	QString getDescription();
	QString getDate();
	QString getRates();
	QString getSpams();
	QString getUserId();
	QString getCategoryId();
	QString getImageExt();
	QString getImage();
	QString getLikes();
	int getCountUsersRated();


	void setId(QString id);
	void setTitle(QString title);
	void setDescription(QString description);
	void setDate(QString date);
	void setRates(QString rates);
	void setSpams(QString spams);
	void setUserId(QString user_id);
	void setCategoryId(QString category_id);
	void setImageExt(QString image_ext);
	void setImage(QString image);
	void setLikes(QString likes);
	void setCountUsersRated(int count_users_rated);
};

