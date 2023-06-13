#pragma once
#include <qstring.h>
class Image
{
private:
	QString id;
	QString image_data;
	QString image_ext;
	QString image_name;
public:
	Image(QString id,
		QString image_data,
		QString image_ext,
		QString image_name);

	QString getId();
	QString getImageData();
	QString getImageExt();
	QString getImageName();

	void setId(QString id);
	void setImageData(QString image_data);
	void setImageExt(QString image_ext);
	void setImageName(QString image_name);
};

