#pragma once
#include <qstring.h>
class Category
{

private:
	QString id;
	QString category;
	QString date;
	QString admin_id;
	QString image;
	QString image_ext;
	QString active;
public:
	Category(QString id, QString category, QString date, QString admin_id, QString image, QString image_ext);
	QString getId();
	QString getCategory();
	QString getDate();
	QString getAdminId();
	QString getImage();
	QString getImageExt();
	QString getActive();



	void setId(QString id);
	void setCategory(QString category);
	void setDate(QString date);
	void setAdminId(QString admin_id);
	void setImage(QString image);
	void setImageExt(QString image_ext);
	void setActive(QString active);
};

