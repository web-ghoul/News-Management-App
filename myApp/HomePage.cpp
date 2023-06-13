#include "HomePage.h"

HomePage::HomePage(QString id,QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	getCurrentUserFromDB(id);
	isSearch = false;
	current_cat_id = "0";
	loadImgs();
	isCategoriesOpen = false;
	loadNews("0");
	loadCats();
	handleProfile();
}

QMap<QString, Image*> HomePage::getHomeImgsFromDB() {
	if (home_imgs.size() > 0) {
		return home_imgs;
	}
	QMap<QString, Image*> images;
	app.DB.open();
	QSqlQuery query(app.DB);
	query.prepare("SELECT * FROM Home_Images");
	if (query.exec()) {
		while (query.next()) {
			Image* image = new Image(query.value("id").toString(), query.value("image_data").toString(), query.value("image_ext").toString(), query.value("image_name").toString());
			images.insert(query.value("image_name").toString(), image);
		}
	}
	app.DB.close();
	return images;
}

QString HomePage::getCatTitleById(QString id) {
	if (id == "0") {
		return "Latest";
	}
	app.DB.open();
	QSqlQuery q(app.DB);
	q.prepare("SELECT CATEGORY FROM CATEGORIES WHERE ID = :ID");
	q.bindValue(":ID", id);
	if (q.exec()) {
		while (q.next()) {
			return q.value(0).toString();
		}
	}
	app.DB.close();
	return "";
}

QString HomePage::getCurrentDateAndTime() {
	time_t     now = time(0);
	struct tm  tstruct;
	char       buf[80];
	tstruct = *localtime(&now);
	strftime(buf, sizeof(buf), "%Y-%m-%d %X", &tstruct);
	return buf;
}

void HomePage::getCurrentUserFromDB( QString id){
	app.DB.open();
	QSqlQuery query(app.DB);
	query.prepare("SELECT * FROM USERS WHERE ID = :ID");
	query.bindValue(":ID" , id);
	if (query.exec()) {
		while (query.next()) {
			current_user = new User(query.value("id").toString(), query.value("email").toString(), query.value("password").toString(), query.value("isAdmin").toString(), query.value("username").toString(), query.value("gender").toString(), query.value("picture").toString(), query.value("pic_ext").toString(), query.value("isVerify").toString());
		}
	}
	app.DB.close();
}

News* HomePage::getNewsById(QString id) {
	News* news;
	app.DB.open();
	QSqlQuery query(app.DB);
	query.prepare("SELECT * FROM NEWS WHERE ID = :ID");
	query.bindValue(":ID", id);
	if (query.exec()) {
		while (query.next()) {
			news = new News(query.value("id").toString(), query.value("title").toString(), query.value("description").toString(), query.value("date").toString(), query.value("rates").toString(), query.value("spams").toString(), query.value("user_id").toString(), query.value("category_id").toString(), query.value("image_ext").toString(), query.value("image").toString(), query.value("likes").toString(), 0);
		}
	}
	app.DB.close();
	return news;
}

QMap<QString, QVector<Spam*>> HomePage::getSpamsFromDB() {
	QMap<QString, QVector<Spam*>> spams;
	app.DB.open();
	QSqlQuery query(app.DB);
	query.prepare("SELECT * FROM SPAM");
	if (query.exec()) {
		while (query.next()) {
			Spam* spam = new Spam(query.value("id").toString(), query.value("news_id").toString(), query.value("user_id").toString(), query.value("isSpam").toString());
			if (spam->getIsSpam() == "1") {
				if (spams.value(spam->getNewsId()).size() == 0) {
					spams.insert(spam->getNewsId(), {spam});
				}
				else {
					spams[spam->getNewsId()].push_back(spam);
				}
			}
		}
	}
	app.DB.close();
	return spams;
}

QString HomePage::getRateOfNewsByUser(QString user_id, QString news_id) {
	app.DB.open();
	QSqlQuery query(app.DB);
	query.prepare("SELECT RATE FROM RATE WHERE NEWS_ID = :NEWS_ID AND USER_ID = :USER_ID");
	query.bindValue(":NEWS_ID", news_id);
	query.bindValue(":USER_ID", user_id);
	if (query.exec()) {
		while (query.next()) {
			return query.value(0).toString();
		}
	}
	app.DB.close();
	return "0";
}

User* HomePage::getUserById(QString user_id) {
	User* user;
	app.DB.open();
	QSqlQuery query(app.DB);
	query.prepare("SELECT * FROM USERS WHERE ID = :ID");
	query.bindValue(":ID", user_id);
	if (query.exec()) {
		while (query.next()) {
			user = new User(query.value("id").toString(), query.value("email").toString(), query.value("password").toString(), query.value("isAdmin").toString(), query.value("username").toString(), query.value("gender").toString(), query.value("picture").toString(), query.value("pic_ext").toString(), query.value("isVerify").toString());
		}
	}
	app.DB.close();
	return user;
}

QString HomePage::getNumberOfUserIsRated(QString news_id) {
	int num = 0;
	app.DB.open();
	QSqlQuery query(app.DB);
	query.prepare("SELECT * FROM RATE WHERE NEWS_ID = :NEWS_ID");
	query.bindValue(":NEWS_ID", news_id);
	if (query.exec()) {
		while (query.next()) {
			num++;
		}
	}
	app.DB.close();
	return QString::number(num);
}

Category* HomePage::getCatById(QString cat_id) {
	Category* cat;
	app.DB.open();
	QSqlQuery query(app.DB);
	query.prepare("SELECT * FROM CATEGORIES WHERE ID = :ID");
	query.bindValue(":ID", cat_id);
	if (query.exec()) {
		while (query.next()) {
			cat = new Category(query.value("id").toString(), query.value("category").toString(), query.value("date").toString(), query.value("admin_id").toString(), query.value("image").toString(), query.value("image_ext").toString());
		}
	}
	app.DB.close();
	return cat;
}

void HomePage::activateNews(QString news_id) {
	User* user;
	Category* cat;
	QMap<QString, QVector<Spam*>> spams = getSpamsFromDB();
	ui.spam_num_label->setText(QString::number(spams.value(news_id).size()));

	current_news = getNewsById(news_id);

	user = getUserById(current_news->getUserId());

	cat = getCatById(current_news->getCategoryId());

	buildStarsOfRate(getRateOfNewsByUser(current_user->getId(), current_news->getId()));

	current_news->setCountUsersRated(getNumberOfUserIsRated(current_news->getId()).toInt());

	ui.coverImg->setPixmap(app.convertImageDataToImageView(QByteArray::fromBase64(QVariant::fromValue(current_news->getImage()).toByteArray()), current_news->getImageExt().toStdString().c_str()));
	ui.news_title->setText(current_news->getTitle());
	ui.news_date->setText(current_news->getDate());
	ui.news_description->setText(current_news->getDescription());
	ui.creator->setText(user->getUsername());
	ui.categoryLabel->setText(cat->getCategory());
	ui.likes_count->setText(current_news->getLikes());

	if (current_news->getCountUsersRated() == 0) {
		ui.average_rate_num->setText("0");
	}
	else {
		ui.average_rate_num->setText(QString::number(current_news->getRates().toInt() / current_news->getCountUsersRated()));
	}

	if (isUserLikedNews(news_id)) {
		ui.likeBtn->setIcon(app.convertImageDataToImageView(QByteArray::fromBase64(QVariant::fromValue(home_imgs.value("love-filled")->getImageData()).toByteArray()), home_imgs.value("love-filled")->getImageExt().toStdString().c_str()));
	}
	else {
		ui.likeBtn->setIcon(app.convertImageDataToImageView(QByteArray::fromBase64(QVariant::fromValue(home_imgs.value("love")->getImageData()).toByteArray()), home_imgs.value("love")->getImageExt().toStdString().c_str()));
	}
	closeComment();
	handleCommentsOfNews(news_id);
	ui.stackedWidget->setCurrentIndex(2);
}

bool HomePage::isUserLikedNews(QString news_id) {
	bool liked = false;
	app.DB.open();
	QSqlQuery query(app.DB);
	query.prepare("SELECT * FROM LIKE WHERE NEWS_ID = :NEWS_ID AND USER_ID = :USER_ID");
	query.bindValue(":NEWS_ID", news_id);
	query.bindValue(":USER_ID", current_user->getId());
	if (query.exec()) {
		while (query.next()) {
			if (query.value("ISLIKED") == "0") {
				liked = false;
			}
			else {
				liked = true;
			}
		}
	}
	app.DB.close();
	return liked;
}

void HomePage::openAlert(QString message) {
	on_close_Error_btn_clicked();
	ui.Alert_message->setText(message);
	ui.Alert->setMinimumHeight(50);
	ui.Alert->setMaximumHeight(1000000000);
	QTimer::singleShot(5000, this, [this]() {on_close_Alert_btn_clicked(); });
}

void HomePage::openError(QString message) {
	on_close_Alert_btn_clicked();
	ui.Error_message->setText(message);
	ui.Error->setMinimumHeight(50);
	ui.Error->setMaximumHeight(1000000000);
	QTimer::singleShot(5000, this, [this]() {on_close_Error_btn_clicked(); });
}

void HomePage::deleteCategory(QString id) {
	app.DB.open();
	QSqlQuery query(app.DB);
	query.prepare("DELETE FROM CATEGORIES WHERE ID = :ID");
	query.bindValue(":ID", id);
	query.exec();
	app.DB.close();
	openAlert("Category is deleted Successfully");
	loadCats();
}

QStack<Comment*> HomePage::getCommentsByNewsId(QString news_id) {
	QStack<Comment*> comments;
	app.DB.open();
	QSqlQuery query(app.DB);
	query.prepare("SELECT * FROM COMMENTS WHERE NEWS_ID = :NEWS_ID");
	query.bindValue(":NEWS_ID" , news_id);
	if (query.exec()) {
		while (query.next()) {
			Comment* comment = new Comment(query.value("id").toString(), query.value("comment").toString(), query.value("date").toString(), query.value("user_id").toString(), query.value("news_id").toString());
			comments.push(comment);
		}
	}
	app.DB.close();
	return comments;
}

void HomePage::handleCommentsOfNews(QString news_id) {
	QStack<Comment*> comments = getCommentsByNewsId(news_id);
	commentGroups.clear();
	while (comments.size() > 0) {
		User* user = getUserById(comments.top()->getUserId());
		QGroupBox* commentGroup = buildComment(comments.top()->getId() , comments.top()->getComment(), user);
		commentGroups.push(commentGroup);
		comments.pop();
	}
	//ui.comment_num->setText(QString::number(commentGroups.size()));
	buildComments();
}

bool HomePage::isUserAdmin(QString user_id) {
	User* user = getUserById(user_id);
	if (user->getIsAdmin() == "1") {
		return true;
	}
	return false;
}

QGroupBox* HomePage::buildCategoriesInHomePage(QString id,QString title , QString image, QString image_ext) {
	QToolButton* catBtn = new QToolButton();
	QGroupBox* catBox = new QGroupBox();
	QPushButton* delBtn = new QPushButton();
	QVBoxLayout* vLayout = new QVBoxLayout(catBox);
	catBtn->setObjectName(title);
	catBtn->setCursor(QCursor(Qt::PointingHandCursor));
	QIcon icon;
	const char* format = image_ext.toStdString().c_str();
	QByteArray imageData = QByteArray::fromBase64(QVariant::fromValue(image).toByteArray());
	icon.addPixmap(app.convertImageDataToImageView(imageData, format));
	catBtn->setIcon(icon);
	catBtn->setText(title);
	catBtn->setIconSize(QSize(50, 50));
	catBtn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
	catBtn->setObjectName("cat_btn");
	if (current_user->getIsAdmin() == "1") {
		delBtn->setIcon(app.convertImageDataToImageView(QByteArray::fromBase64(QVariant::fromValue(home_imgs.value("delete-white")->getImageData()).toByteArray()), home_imgs.value("delete-white")->getImageExt().toStdString().c_str()));
		delBtn->setObjectName("del_btn");
		delBtn->setCursor(Qt::PointingHandCursor);
		delBtn->setMaximumSize(30, 30);
		connect(delBtn, &QPushButton::clicked, this, [=]() {deleteCategory(id); });
		vLayout->addWidget(delBtn);
	}
	vLayout->setContentsMargins(0, 0, 0, 0);
	vLayout->setAlignment(Qt::AlignCenter);
	vLayout->addWidget(catBtn);
	catBox->setObjectName("cat_box");
	catBox->setLayout(vLayout);
	connect(catBtn, &QToolButton::clicked, this, [=]() {loadNews(id); current_cat_id = id; });
	return catBox;
}

QFrame* HomePage::buildNews(QString title, QString description, QString date, QString image, QString id, QString image_ext) {
	QFrame* news_frame;
	QLabel* post_title;
	QPushButton* view_more_btn;
	QLabel* post_date;
	//QLabel* post_image;
	QGroupBox* groupBox_11;
	QGroupBox* groupBox_10;
	QVBoxLayout* verticalLayout_4;
	QGroupBox* groupBox_9;
	QHBoxLayout* horizontalLayout_15;
	QHBoxLayout* horizontalLayout_16;
	QHBoxLayout* horizontalLayout_17;
	QFont font;
	auto effect = new QGraphicsDropShadowEffect();
	QString title_handled;
	for (int i = 0; i < title.size(); i++) {
		title_handled += title[i];
		if (i > 25) {
			title_handled += "...";
			break;
		}
	}
	title = title_handled;
	effect->setBlurRadius(20);
	effect->setOffset(0.f);
	effect->setColor(Qt::black);
	font.setFamilies({ QString::fromUtf8("Segoe UI Semibold") });
	font.setPointSize(10);
	font.setBold(false);
	news_frame = new QFrame();
	news_frame->setObjectName("news_frame");
	news_frame->setMinimumSize(QSize(315, 135));
	news_frame->setFrameShape(QFrame::NoFrame);
	news_frame->setFrameShadow(QFrame::Plain);
	news_frame->setLineWidth(1);
	news_frame->setGraphicsEffect(effect);
	verticalLayout_4 = new QVBoxLayout(news_frame);
	verticalLayout_4->setSpacing(10);
	verticalLayout_4->setObjectName("verticalLayout_4");
	verticalLayout_4->setContentsMargins(0, 0, 0, 0);
	groupBox_9 = new QGroupBox(news_frame);
	groupBox_9->setObjectName("groupBox_9");
	/*horizontalLayout_15 = new QHBoxLayout(groupBox_9);
	horizontalLayout_15->setSpacing(0);
	horizontalLayout_15->setObjectName("horizontalLayout_15");
	horizontalLayout_15->setContentsMargins(0, 0, 0, 0);
	post_image = new QLabel(groupBox_9);
	post_image->setObjectName("label");
	post_image->setPixmap(app.convertImageDataToImageView(QByteArray::fromBase64(QVariant::fromValue(image).toByteArray()), image_ext.toStdString().c_str()));
	post_image->setScaledContents(true);
	post_image->setMaximumHeight(200);
	horizontalLayout_15->addWidget(post_image);*/
	verticalLayout_4->addWidget(groupBox_9);
	groupBox_10 = new QGroupBox(news_frame);
	groupBox_10->setObjectName("groupBox_10");
	horizontalLayout_16 = new QHBoxLayout(groupBox_10);
	horizontalLayout_16->setSpacing(0);
	horizontalLayout_16->setObjectName("horizontalLayout_16");
	horizontalLayout_16->setContentsMargins(10, 10, 10, 10);
	post_title = new QLabel(groupBox_10);
	post_title->setObjectName("post_title");
	QFont font5;
	font5.setFamilies({ QString::fromUtf8("Segoe UI Semibold") });
	font5.setPointSize(14);
	post_title->setFont(font5);
	horizontalLayout_16->addWidget(post_title);
	verticalLayout_4->addWidget(groupBox_10);
	groupBox_11 = new QGroupBox(news_frame);
	groupBox_11->setObjectName("groupBox_11");
	horizontalLayout_17 = new QHBoxLayout(groupBox_11);
	horizontalLayout_17->setSpacing(20);
	horizontalLayout_17->setObjectName("horizontalLayout_17");
	horizontalLayout_17->setContentsMargins(10, 10, 10, 10);
	view_more_btn = new QPushButton(groupBox_11);
	view_more_btn->setObjectName("view_more_btn");
	view_more_btn->setMinimumSize(QSize(0, 0));
	view_more_btn->setMaximumSize(QSize(150, 16777215));
	view_more_btn->setFont(font);
	horizontalLayout_17->addWidget(view_more_btn, 0, Qt::AlignLeft);
	post_date = new QLabel(groupBox_11);
	post_date->setObjectName("post_date");
	QFont font6;
	font6.setFamilies({ QString::fromUtf8("Segoe UI Semibold") });
	font6.setBold(false);
	post_date->setFont(font6);
	horizontalLayout_17->addWidget(post_date, 0, Qt::AlignRight);
	verticalLayout_4->addWidget(groupBox_11);
	groupBox_9->setTitle(QString());
	groupBox_10->setTitle(QString());
	post_title->setText(title);
	groupBox_11->setTitle(QString());
	view_more_btn->setText("View More");
	view_more_btn->setCursor(Qt::PointingHandCursor);
	connect(view_more_btn, &QPushButton::clicked, this, [=]() { activateNews(id); });
	post_date->setText(date);
	return news_frame;
}

QGroupBox* HomePage::buildComment (QString id ,QString commentDesc,User* user) {
	QGroupBox* commentGroup;
	QHBoxLayout* commentGroup_h_layout;
	QHBoxLayout* username_h_layout;
	QLabel* avatarComment;
	QGroupBox* commentGroupBox;
	QVBoxLayout* commentData_v_layout;
	QLabel* userComment;
	QLabel* comment;
	QToolButton* delete_btn;
	QLabel* adminIcon;
	commentGroup = new QGroupBox();
	commentGroup->setObjectName("commentGroup");
	commentGroup_h_layout = new QHBoxLayout(commentGroup);
	commentGroup_h_layout->setSpacing(0);
	commentGroup_h_layout->setObjectName("horizontalLayout_21");
	commentGroup_h_layout->setContentsMargins(0, 0, 0, 0);
	commentGroup_h_layout->setSpacing(10);
	avatarComment = new QLabel(commentGroup);
	avatarComment->setObjectName("avatarComment");
	avatarComment->setMaximumSize(QSize(50, 50));
	avatarComment->setPixmap(app.convertImageDataToImageView(QByteArray::fromBase64(QVariant::fromValue(user->getImage()).toByteArray()), user->getImageExt().toStdString().c_str()));
	avatarComment->setScaledContents(true);

	commentGroup_h_layout->addWidget(avatarComment, 0, Qt::AlignTop);

	commentGroupBox = new QGroupBox(commentGroup);
	commentGroupBox->setObjectName("commentGroupBox");
	commentGroupBox->setStyleSheet(QString::fromUtf8("background-color:#444 ; border-radius:10px"));
	commentData_v_layout = new QVBoxLayout(commentGroupBox);
	username_h_layout = new QHBoxLayout();
	commentData_v_layout->setSpacing(10);
	commentData_v_layout->setContentsMargins(10, 10, 10, 10);
	commentData_v_layout->setObjectName("verticalLayout_24");



	userComment = new QLabel(commentGroupBox);
	userComment->setObjectName("userComment");
	QFont font13;
	font13.setFamilies({ QString::fromUtf8("Kozuka Gothic Pr6N B") });
	font13.setPointSize(12);
	font13.setBold(true);
	userComment->setFont(font13);
	username_h_layout->addWidget(userComment, 0, Qt::AlignLeft);
	if (user->getIsAdmin() == "1") {
		adminIcon = new QLabel(commentGroupBox);
		adminIcon->setPixmap(app.convertImageDataToImageView(QByteArray::fromBase64(QVariant::fromValue(home_imgs.value("admin")->getImageData()).toByteArray()), home_imgs.value("admin")->getImageExt().toStdString().c_str()));
		adminIcon->setScaledContents(true);
		adminIcon->setMaximumSize(20, 20);
		username_h_layout->addWidget(adminIcon, 1, Qt::AlignLeft);
		username_h_layout->setSpacing(5);
	}
	commentData_v_layout->addLayout(username_h_layout);
	comment = new QLabel(commentGroupBox);
	comment->setObjectName("comment");
	comment->setScaledContents(true);
	QFont font14;
	font14.setFamilies({ QString::fromUtf8("Kozuka Gothic Pr6N B") });
	font14.setPointSize(10);
	font14.setBold(false);
	font14.setItalic(false);
	font14.setUnderline(false);
	commentData_v_layout->addWidget(comment);
	if (current_user->getIsAdmin() == "1" || current_user->getId() == user->getId()) {
		if (!(user->getIsAdmin() == "1" && current_user->getId() != user->getId())) {
			delete_btn = new QToolButton(commentGroupBox);
			delete_btn->setIcon(app.convertImageDataToImageView(QByteArray::fromBase64(QVariant::fromValue(home_imgs.value("delete-red")->getImageData()).toByteArray()), home_imgs.value("delete-red")->getImageExt().toStdString().c_str()));
			delete_btn->setCursor(Qt::PointingHandCursor);
			delete_btn->setIconSize(QSize(20, 20));
			connect(delete_btn, &QToolButton::clicked, this, [=]() {deleteComment(id); });
			commentData_v_layout->addWidget(delete_btn, 0, Qt::AlignRight);
		}
	}
	commentGroup_h_layout->addWidget(commentGroupBox);
	commentGroup->setTitle(QString());
	avatarComment->setText(QString());
	commentGroupBox->setTitle(QString());
	userComment->setText(user->getUsername());
	comment->setText(commentDesc);
	comment->setWordWrap(true);
	comment->setFont(font14);
	comment->setAlignment(Qt::AlignLeft | Qt::AlignTop);
	commentGroup->setMinimumSize(comment->width(), 0);
	return commentGroup;
}

void HomePage::buildComments() {
	int n = ui.comments_v_layout->count();
	for (int i = 0; i < n; i++) {
		ui.comments_v_layout->takeAt(0)->widget()->deleteLater();
	}
	while (!commentGroups.isEmpty()) {
		ui.comments_v_layout->addWidget(commentGroups.top());
		commentGroups.pop();
	}
	ui.comment_num->setText(QString::number(ui.comments_v_layout->count()));
	if (ui.comments_v_layout->count() == 0) {
		QLabel* l = new QLabel("No Comments Found...");
		l->setObjectName("no_comments_label");
		l->setAlignment(Qt::AlignCenter);
		l->setMaximumSize(300, 100);
		ui.comments_v_layout->addWidget(l);
		ui.comments_v_layout->setAlignment(Qt::AlignCenter);
	}
}

void HomePage::deleteComment(QString comment_id) {
	app.DB.open();
	QSqlQuery query(app.DB);
	QSqlDatabase::database().transaction();
	query.prepare("DELETE FROM COMMENTS WHERE ID = :ID");
	query.bindValue(":ID", comment_id);
	query.exec();
	QSqlDatabase::database().commit();
	app.DB.close();
	openAlert("Comment is deleted Successfully");
	handleCommentsOfNews(current_news->getId());
}

void HomePage::closeComment() {
	ui.commentsgroup->setMinimumHeight(0);
	ui.commentsgroup->setMaximumSize(0, 0);
	ui.comment_btn->setIcon(app.convertImageDataToImageView(QByteArray::fromBase64(QVariant::fromValue(home_imgs.value("comment")->getImageData()).toByteArray()), home_imgs.value("comment")->getImageExt().toStdString().c_str()));
}

QVector<QToolButton*> HomePage::buildRate(QString rate) {
	QToolButton* star1 = new QToolButton();
	star1->setObjectName("star1");
	QToolButton* star2 = new QToolButton();
	star2->setObjectName("star2");
	QToolButton* star3 = new QToolButton();
	star3->setObjectName("star3");
	QToolButton* star4 = new QToolButton();
	star4->setObjectName("star4");
	QToolButton* star5 = new QToolButton();
	star5->setObjectName("star5");
	QVector<QToolButton*> stars = { star1,star2,star3,star4,star5 };
	for (int i = 0; i < stars.size(); i++)
	{
		QIcon icon;
		stars[i]->setCursor(QCursor(Qt::PointingHandCursor));
		stars[i]->setIconSize(QSize(30, 30));
		if (i < rate.toInt()) {
			icon.addPixmap(app.convertImageDataToImageView(QByteArray::fromBase64(QVariant::fromValue(home_imgs.value("star-filled")->getImageData()).toByteArray()), home_imgs.value("star-filled")->getImageExt().toStdString().c_str()));
			stars[i]->setIcon(icon);
		}
		else {
			icon.addPixmap(app.convertImageDataToImageView(QByteArray::fromBase64(QVariant::fromValue(home_imgs.value("star")->getImageData()).toByteArray()), home_imgs.value("star")->getImageExt().toStdString().c_str()));
			stars[i]->setIcon(icon);
		}
	}
	return stars;
}

void HomePage::buildStarsOfRate(QString rate) {
	for (int i = 0; i < 5; i++) {
		ui.horizontalLayout_9->takeAt(0)->widget()->deleteLater();
	}
	QVector<QToolButton*> stars = buildRate(rate);
	ui.horizontalLayout_9->addWidget(stars[0]);
	connect(stars[0], SIGNAL(clicked()), this, SLOT(on_star1_clicked()));
	ui.horizontalLayout_9->addWidget(stars[1]);
	connect(stars[1], SIGNAL(clicked()), this, SLOT(on_star2_clicked()));
	ui.horizontalLayout_9->addWidget(stars[2]);
	connect(stars[2], SIGNAL(clicked()), this, SLOT(on_star3_clicked()));
	ui.horizontalLayout_9->addWidget(stars[3]);
	connect(stars[3], SIGNAL(clicked()), this, SLOT(on_star4_clicked()));
	ui.horizontalLayout_9->addWidget(stars[4]);
	connect(stars[4], SIGNAL(clicked()), this, SLOT(on_star5_clicked()));
}

void HomePage::loadImgs() {
	home_imgs = getHomeImgsFromDB();

	ui.searchBtn->setIcon(app.convertImageDataToImageView(QByteArray::fromBase64(QVariant::fromValue(home_imgs.value("search")->getImageData()).toByteArray()), home_imgs.value("search")->getImageExt().toStdString().c_str()));

	ui.actionUser->setIcon(app.convertImageDataToImageView(QByteArray::fromBase64(QVariant::fromValue(current_user->getImage()).toByteArray()), current_user->getImageExt().toStdString().c_str()));

	ui.actionProfile->setIcon(app.convertImageDataToImageView(QByteArray::fromBase64(QVariant::fromValue(home_imgs.value("profile")->getImageData()).toByteArray()), home_imgs.value("profile")->getImageExt().toStdString().c_str()));

	ui.actionLog_Out->setIcon(app.convertImageDataToImageView(QByteArray::fromBase64(QVariant::fromValue(home_imgs.value("logout")->getImageData()).toByteArray()), home_imgs.value("logout")->getImageExt().toStdString().c_str()));

	ui.actionHome->setIcon(app.convertImageDataToImageView(QByteArray::fromBase64(QVariant::fromValue(home_imgs.value("home")->getImageData()).toByteArray()), home_imgs.value("home")->getImageExt().toStdString().c_str()));

	ui.add_cat_icon->setPixmap(app.convertImageDataToImageView(QByteArray::fromBase64(QVariant::fromValue(home_imgs.value("add-category")->getImageData()).toByteArray()), home_imgs.value("add-category")->getImageExt().toStdString().c_str()));

	ui.actionAdd_Category->setIcon(app.convertImageDataToImageView(QByteArray::fromBase64(QVariant::fromValue(home_imgs.value("add-category")->getImageData()).toByteArray()), home_imgs.value("add-category")->getImageExt().toStdString().c_str()));

	ui.actionAdd_News->setIcon(app.convertImageDataToImageView(QByteArray::fromBase64(QVariant::fromValue(home_imgs.value("add-news")->getImageData()).toByteArray()), home_imgs.value("add-news")->getImageExt().toStdString().c_str()));

	ui.add_news_icon->setPixmap(app.convertImageDataToImageView(QByteArray::fromBase64(QVariant::fromValue(home_imgs.value("add-news")->getImageData()).toByteArray()), home_imgs.value("add-news")->getImageExt().toStdString().c_str()));

	ui.close_Alert_btn->setIcon(app.convertImageDataToImageView(QByteArray::fromBase64(QVariant::fromValue(home_imgs.value("close-alert")->getImageData()).toByteArray()), home_imgs.value("close-alert")->getImageExt().toStdString().c_str()));

	ui.close_Error_btn->setIcon(app.convertImageDataToImageView(QByteArray::fromBase64(QVariant::fromValue(home_imgs.value("close-alert")->getImageData()).toByteArray()), home_imgs.value("close-alert")->getImageExt().toStdString().c_str()));

	ui.categoriesToolBtn->setIcon(app.convertImageDataToImageView(QByteArray::fromBase64(QVariant::fromValue(home_imgs.value("up-arrow")->getImageData()).toByteArray()), home_imgs.value("up-arrow")->getImageExt().toStdString().c_str()));

	ui.change_pic_btn->setIcon(app.convertImageDataToImageView(QByteArray::fromBase64(QVariant::fromValue(home_imgs.value("edit")->getImageData()).toByteArray()), home_imgs.value("edit")->getImageExt().toStdString().c_str()));

	ui.edit_username_btn->setIcon(app.convertImageDataToImageView(QByteArray::fromBase64(QVariant::fromValue(home_imgs.value("edit")->getImageData()).toByteArray()), home_imgs.value("edit")->getImageExt().toStdString().c_str()));

	ui.edit_email_btn->setIcon(app.convertImageDataToImageView(QByteArray::fromBase64(QVariant::fromValue(home_imgs.value("edit")->getImageData()).toByteArray()), home_imgs.value("edit")->getImageExt().toStdString().c_str()));

	ui.edit_gender_btn->setIcon(app.convertImageDataToImageView(QByteArray::fromBase64(QVariant::fromValue(home_imgs.value("edit")->getImageData()).toByteArray()), home_imgs.value("edit")->getImageExt().toStdString().c_str()));

	ui.edit_news_cover_img_btn->setIcon(app.convertImageDataToImageView(QByteArray::fromBase64(QVariant::fromValue(home_imgs.value("edit")->getImageData()).toByteArray()), home_imgs.value("edit")->getImageExt().toStdString().c_str()));

	ui.edit_news_title_btn->setIcon(app.convertImageDataToImageView(QByteArray::fromBase64(QVariant::fromValue(home_imgs.value("edit")->getImageData()).toByteArray()), home_imgs.value("edit")->getImageExt().toStdString().c_str()));

	ui.edit_news_desc_btn->setIcon(app.convertImageDataToImageView(QByteArray::fromBase64(QVariant::fromValue(home_imgs.value("edit")->getImageData()).toByteArray()), home_imgs.value("edit")->getImageExt().toStdString().c_str()));

	ui.change_pass_btn->setIcon(app.convertImageDataToImageView(QByteArray::fromBase64(QVariant::fromValue(home_imgs.value("edit")->getImageData()).toByteArray()), home_imgs.value("edit")->getImageExt().toStdString().c_str()));

	ui.stars->setPixmap(app.convertImageDataToImageView(QByteArray::fromBase64(QVariant::fromValue(home_imgs.value("star-filled")->getImageData()).toByteArray()), home_imgs.value("star-filled")->getImageExt().toStdString().c_str()));

	ui.spams->setPixmap(app.convertImageDataToImageView(QByteArray::fromBase64(QVariant::fromValue(home_imgs.value("spam-red")->getImageData()).toByteArray()), home_imgs.value("spam-red")->getImageExt().toStdString().c_str()));

	ui.report_btn->setIcon(app.convertImageDataToImageView(QByteArray::fromBase64(QVariant::fromValue(home_imgs.value("spam-white")->getImageData()).toByteArray()), home_imgs.value("spam-white")->getImageExt().toStdString().c_str()));

	ui.arrowIcon->setPixmap(app.convertImageDataToImageView(QByteArray::fromBase64(QVariant::fromValue(home_imgs.value("up-arrow")->getImageData()).toByteArray()), home_imgs.value("up-arrow")->getImageExt().toStdString().c_str()));

	ui.delete_acc_btn->setIcon(app.convertImageDataToImageView(QByteArray::fromBase64(QVariant::fromValue(home_imgs.value("delete-white")->getImageData()).toByteArray()), home_imgs.value("delete-white")->getImageExt().toStdString().c_str()));

	ui.delete_news_btn->setIcon(app.convertImageDataToImageView(QByteArray::fromBase64(QVariant::fromValue(home_imgs.value("delete-white")->getImageData()).toByteArray()), home_imgs.value("delete-white")->getImageExt().toStdString().c_str()));

	ui.add_news_upload_img_btn->setIcon(app.convertImageDataToImageView(QByteArray::fromBase64(QVariant::fromValue(home_imgs.value("upload")->getImageData()).toByteArray()), home_imgs.value("upload")->getImageExt().toStdString().c_str()));

	ui.add_cat_upload_img_btn->setIcon(app.convertImageDataToImageView(QByteArray::fromBase64(QVariant::fromValue(home_imgs.value("upload")->getImageData()).toByteArray()), home_imgs.value("upload")->getImageExt().toStdString().c_str()));

	ui.done_btn->setIcon(app.convertImageDataToImageView(QByteArray::fromBase64(QVariant::fromValue(home_imgs.value("done")->getImageData()).toByteArray()), home_imgs.value("done")->getImageExt().toStdString().c_str()));

	setWindowIcon(app.convertImageDataToImageView(QByteArray::fromBase64(QVariant::fromValue(home_imgs.value("logo")->getImageData()).toByteArray()), home_imgs.value("logo")->getImageExt().toStdString().c_str()));

	ui.comment_btn->setIcon(app.convertImageDataToImageView(QByteArray::fromBase64(QVariant::fromValue(home_imgs.value("comment")->getImageData()).toByteArray()), home_imgs.value("comment")->getImageExt().toStdString().c_str()));

	ui.reset_filter_news_btn->setIcon(app.convertImageDataToImageView(QByteArray::fromBase64(QVariant::fromValue(home_imgs.value("error")->getImageData()).toByteArray()), home_imgs.value("error")->getImageExt().toStdString().c_str()));
	ui.star1->setIcon(app.convertImageDataToImageView(QByteArray::fromBase64(QVariant::fromValue(home_imgs.value("star")->getImageData()).toByteArray()), home_imgs.value("star")->getImageExt().toStdString().c_str()));
	ui.star2->setIcon(app.convertImageDataToImageView(QByteArray::fromBase64(QVariant::fromValue(home_imgs.value("star")->getImageData()).toByteArray()), home_imgs.value("star")->getImageExt().toStdString().c_str()));
	ui.star3->setIcon(app.convertImageDataToImageView(QByteArray::fromBase64(QVariant::fromValue(home_imgs.value("star")->getImageData()).toByteArray()), home_imgs.value("star")->getImageExt().toStdString().c_str()));
	ui.star4->setIcon(app.convertImageDataToImageView(QByteArray::fromBase64(QVariant::fromValue(home_imgs.value("star")->getImageData()).toByteArray()), home_imgs.value("star")->getImageExt().toStdString().c_str()));
	ui.star5->setIcon(app.convertImageDataToImageView(QByteArray::fromBase64(QVariant::fromValue(home_imgs.value("star")->getImageData()).toByteArray()), home_imgs.value("star")->getImageExt().toStdString().c_str()));
	ui.sendCommentBtn->setIcon(app.convertImageDataToImageView(QByteArray::fromBase64(QVariant::fromValue(home_imgs.value("readySend")->getImageData()).toByteArray()), home_imgs.value("readySend")->getImageExt().toStdString().c_str()));
}

void HomePage::loadCats() {
	int num = ui.layoutCats->count();
	for (int i = 0; i < num; i++) {
		ui.layoutCats->takeAt(0)->widget()->deleteLater();
	}
	int r = 0;
	int c = 0;
	app.DB.open();
	QSqlQuery getCats(app.DB);
	getCats.prepare("SELECT * FROM CATEGORIES");
	if (getCats.exec()) {
		while (getCats.next()) {
			ui.layoutCats->addWidget(buildCategoriesInHomePage(getCats.value("id").toString(),getCats.value("category").toString(), getCats.value("image").toString(),getCats.value("image_ext").toString()), r, c, 1, 1, Qt::AlignCenter);
			c++;
			if (c % 10 == 0) {
				r++;
				c = 0;
			}
		}
	}
	app.DB.close();
	if (ui.layoutCats->count() == 0) {
		QLabel* l = new QLabel("No Categories Found...");
		l->setObjectName("no_categories_label");
		l->setAlignment(Qt::AlignCenter);
		l->setMaximumSize(300, 100);
		l->setStyleSheet("font-size:20px;");
		ui.layoutCats->addWidget(l);
		ui.layoutCats->setAlignment(Qt::AlignCenter);
	}
}

void HomePage::loadNews(QString id , QString arg) {
	QMap<QString, QVector<Spam*>> spams = getSpamsFromDB();
	QString title;
	if (id != "0") {
		title = getCatTitleById(id);
	}
	int num = ui.gridLayout->count();
	for (int i = 0; i < num; i++) {
		ui.gridLayout->takeAt(0)->widget()->deleteLater();
	}
	int r = 0;
	int c = 0;
	QMap<QString, News*> allNews;
	app.DB.open();
	QSqlQuery query(app.DB);
	if (id == "0") {
		query.prepare("SELECT * FROM NEWS ORDER BY ID DESC");
	}
	else {
		query.prepare("SELECT * FROM NEWS WHERE CATEGORY_ID = :ID ORDER BY ID DESC");
		query.bindValue(":ID", id);
	}
	if (query.exec()) {
		while (query.next()) {
			if (c > 0 && c % 4 == 0) {
				r++;
				c = 0;
			}
			bool isSpam = false;
			QVector<Spam*> spam = spams.value(query.value("id").toString());
			for (int i = 0; i < spam.size(); i++) {
				if (spam[i]->getUserId() == current_user->getId()) {
					isSpam = true;
					break;
				}
			}
			if (spam.size() >= 3 || isSpam) {
				continue;
			}
			if (arg.length() > 0) {
				const char* found = strstr(query.value("title").toString().toStdString().c_str(), arg.toStdString().c_str());
				if (!found) {
					continue;
				}
			}
			QFrame* news_frame = buildNews(query.value("title").toString(), query.value("description").toString(), query.value("date").toString(), query.value("image").toString(), query.value("id").toString(), query.value("image_ext").toString());
			ui.gridLayout->addWidget(news_frame, r, c, 1, 1, Qt::AlignTop | Qt::AlignLeft);
			c++;
		}
	}
	app.DB.close();
	if (id == "0") {
		ui.reset_filter_news_box->setMaximumWidth(0);
		ui.cat_type_label->setStyleSheet("color:#fff");
		ui.cat_type_label->setText("Latest");
	}
	else {
		ui.reset_filter_news_box->setMaximumWidth(100000000);
		ui.cat_type_label->setStyleSheet("color:#037ef3");
		ui.cat_type_label->setText(title);
	}
	if (ui.gridLayout->count() == 0) {
		QLabel* l = new QLabel("No News Found...");
		l->setObjectName("no_news_label");
		ui.gridLayout->addWidget(l, 0, 2, Qt::AlignVCenter | Qt::AlignHCenter);
		ui.news_count->setText("0");
	}
	else {
		ui.news_count->setText(QString::number(ui.gridLayout->count()));
	}
}

void HomePage::handleCategoriesInComboBox() {
	int num = ui.add_news_cat->count();
	for (int i = 0; i < num; i++) {
		ui.add_news_cat->removeItem(0);
	}
	app.DB.open();
	QSqlQuery query(app.DB);
	query.prepare("SELECT * FROM CATEGORIES");
	if (query.exec()) {
		while (query.next()) {
			const char* format = query.value("image_ext").toString().toStdString().c_str();
			QByteArray imageData = QByteArray::fromBase64(QVariant::fromValue(query.value("image").toString()).toByteArray());
			ui.add_news_cat->addItem(QIcon(QPixmap(app.convertImageDataToImageView(imageData, format))), query.value("category").toString());
		}
	}
	app.DB.close();
}

void HomePage::handleProfile() {
	ui.actionUser->setText(current_user->getUsername());
	ui.username->setText(current_user->getUsername());
	ui.email->setText(current_user->getEmail());
	ui.gender_icon->setPixmap(current_user->getGender() == "male" ? app.convertImageDataToImageView(QByteArray::fromBase64(QVariant::fromValue(home_imgs.value("male")->getImageData()).toByteArray()), home_imgs.value("male")->getImageExt().toStdString().c_str()) : app.convertImageDataToImageView(QByteArray::fromBase64(QVariant::fromValue(home_imgs.value("female")->getImageData()).toByteArray()), home_imgs.value("female")->getImageExt().toStdString().c_str()));
	current_user->getIsAdmin() == "1" ? toggleAdminOperations(true) : toggleAdminOperations(false);
	ui.avatar->setPixmap(app.convertImageDataToImageView(QByteArray::fromBase64(QVariant::fromValue(current_user->getImage()).toByteArray()), current_user->getImageExt().toStdString().c_str()));
	ui.actionUser->setIcon(QIcon(app.convertImageDataToImageView(QByteArray::fromBase64(QVariant::fromValue(current_user->getImage()).toByteArray()), current_user->getImageExt().toStdString().c_str())));
	ui.commentLine->setPlaceholderText("comment as " + current_user->getUsername()+"...");
}

void HomePage::toggleAdminOperations(bool isAdmin) {
	if (isAdmin) {
		ui.addNewsToolBar->show();
		ui.edit_news_desc_btn->show();
		ui.delete_news_btn->show();
		ui.edit_news_title_btn->show();
		ui.edit_news_cover_img_btn->show();
	}
	else {
		ui.addNewsToolBar->hide();
		ui.edit_news_desc_btn->hide();
		ui.delete_news_btn->hide();
		ui.edit_news_title_btn->hide();
		ui.edit_news_cover_img_btn->hide();
	}
}

void HomePage::deleteAccount() {
	app.DB.open();
	QSqlQuery query(app.DB);
	QSqlDatabase::database().transaction();
	query.prepare("DELETE FROM USERS WHERE ID = :ID");
	query.bindValue(":ID", current_user->getId());
	query.exec();
	query.prepare("DELETE FROM RATE WHERE USER_ID = :ID");
	query.bindValue(":ID", current_user->getId());
	query.exec();
	query.prepare("DELETE FROM LIKE WHERE USER_ID = :ID");
	query.bindValue(":ID", current_user->getId());
	query.exec();
	query.prepare("DELETE FROM SPAM WHERE USER_ID = :ID");
	query.bindValue(":ID", current_user->getId());
	query.exec();
	query.prepare("DELETE FROM NEWS WHERE USER_ID = :ID");
	query.bindValue(":ID", current_user->getId());
	query.exec();
	query.prepare("DELETE FROM COMMENTS WHERE USER_ID = :ID");
	query.bindValue(":ID", current_user->getId());
	query.exec();
	QSqlDatabase::database().commit();
	app.DB.close();
	on_actionLog_Out_triggered();
}

bool HomePage::addNewNews(QString title , QString description, QString imagePath, int category) {
	QFileInfo fi(imagePath);
	const char* format = fi.completeSuffix().toUpper().toStdString().c_str();
	QString imageData = QString::fromUtf8(app.convertImageViewToImageData(imagePath));
	if (imageData == "") {
		openError("The Image Isn't Uploaded");
		return false;
	}
	app.DB.open();
	QSqlDatabase::database().transaction();
	QSqlQuery query(app.DB);
	query.prepare("INSERT INTO NEWS(title , description , date , rates , image, image_ext ,spams,likes,user_id,category_id) VALUES(:title , :description , :date , :rates , :image, :image_ext ,:spams,:likes ,:user_id,:category_id)");
	query.bindValue(":title", title);
	query.bindValue(":description", description);
	query.bindValue(":date", getCurrentDateAndTime());
	query.bindValue(":rates", "0");
	query.bindValue(":image", imageData);
	query.bindValue(":image_ext", format);
	query.bindValue(":spams","0");
	query.bindValue(":likes", "0");
	query.bindValue(":user_id",current_user->getId());
	query.bindValue(":category_id", category);
	query.exec();
	QSqlDatabase::database().commit();
	app.DB.close();
	on_add_news_clear_btn_clicked();
	return true;
}

bool HomePage::addNewCategory(QString categoryTitle, QString imagePath) {
	QFileInfo fi(imagePath);
	string ext = fi.completeSuffix().toStdString();
	for (int i = 0; i < ext.length(); i++) {
		ext[i] = toupper(ext[i]);
	}
	const char* format = ext.c_str();
	QByteArray imageData = app.convertImageViewToImageData(imagePath);
	if (imageData == "") {
		openError("Image isn't Uploaded");
		return false;
	}
	app.DB.open();
	QSqlDatabase::database().transaction();
	QSqlQuery query(app.DB);
	query.prepare("INSERT INTO CATEGORIES(category , image , date , admin_id ,image_ext) VALUES(:category , :image , :date , :admin_id ,:image_ext)");
	query.bindValue(":category", categoryTitle);
	query.bindValue(":image", imageData);
	query.bindValue(":date", getCurrentDateAndTime());
	query.bindValue(":admin_id", current_user->getId());
	query.bindValue(":image_ext", format);
	query.exec();
	QSqlDatabase::database().commit();
	app.DB.close();
	on_add_cat_clear_btn_clicked();
	return true;
}

void HomePage::addNewComment(QString comment) {
	app.DB.open();
	QSqlDatabase::database().transaction();
	QSqlQuery query(app.DB);
	query.prepare("INSERT INTO COMMENTS(COMMENT , NEWS_ID , USER_ID , DATE) VALUES(:COMMENT , :NEWS_ID , :USER_ID , :DATE)");
	query.bindValue(":COMMENT", comment);
	query.bindValue(":NEWS_ID", current_news->getId());
	query.bindValue(":USER_ID", current_user->getId());
	query.bindValue(":DATE", getCurrentDateAndTime());
	query.exec();
	QSqlDatabase::database().commit();
	app.DB.close();
}

void HomePage::updateRateOfUser(QString rate , QString news_id , QString user_id) {
	app.DB.open();
	QSqlDatabase::database().transaction();
	QSqlQuery query(app.DB);
	query.prepare("UPDATE RATE SET RATE = :RATE WHERE USER_ID = :USER_ID AND NEWS_ID = :NEWS_ID");
	query.bindValue(":NEWS_ID", news_id);
	query.bindValue(":USER_ID", user_id);
	query.bindValue(":RATE", rate);
	query.exec();
	QSqlDatabase::database().commit();
	app.DB.close();
}

QString HomePage::getRatesOfNews(QString news_id) {
	QString rates;
	app.DB.open();
	QSqlQuery query(app.DB);
	query.prepare("SELECT RATES FROM NEWS WHERE  NEWS_ID = :NEWS_ID");
	query.bindValue(":NEWS_ID", news_id);
	if (query.exec()) {
		while (query.next()) {
			rates = query.value(0).toString();
		}
	}
	QSqlDatabase::database().commit();
	app.DB.close();
	return rates;
}

void HomePage::updateRatesOfNews(QString rates, QString news_id) {
	app.DB.open();
	QSqlQuery query(app.DB);
	query.prepare("UPDATE NEWS SET RATES = :RATES WHERE ID = :ID");
	query.bindValue(":RATES", rates);
	query.bindValue(":ID", news_id);
	query.exec();
	app.DB.close();
}

void HomePage::addNewRate(QString rate, QString news_id , QString user_id) {
	app.DB.open();
	QSqlQuery query(app.DB);
	QSqlDatabase::database().transaction();
	query.prepare("INSERT INTO RATE (user_id , news_id , rate) VALUES(:user_id ,:news_id , :rate)");
	query.bindValue(":user_id", user_id);
	query.bindValue(":news_id", news_id);
	query.bindValue(":rate", rate);
	query.exec();
	QSqlDatabase::database().commit();
	app.DB.close();
}

QPair<bool,Rate*> HomePage::getRateOfUser(QString news_id, QString user_id) {
	Rate* rate;
	bool isExist = false;
	app.DB.open();
	QSqlQuery query(app.DB);
	query.prepare("SELECT * FROM RATE WHERE USER_ID = :USER_ID AND NEWS_ID = :NEWS_ID");
	query.bindValue(":USER_ID", user_id);
	query.bindValue(":NEWS_ID", news_id);
	if (query.exec()) {
		while (query.next()) {
			rate = new Rate(query.value("id").toString(), query.value("news_id").toString(), query.value("user_id").toString(), query.value("rate").toString());
			isExist = true;
		}
	}
	app.DB.close();
	return { isExist, rate };
}

void HomePage::updateNewsRate(QString rate, QString id) {
	QPair<bool,Rate*> p = getRateOfUser(id, current_user->getId());
	Rate* current_rate = p.second;
	if (p.first) {
		updateRateOfUser(rate, current_news->getId(), current_user->getId());
		current_news->setRates(QString::number(current_news->getRates().toInt() + rate.toInt() - current_rate->getRate().toInt()));
		updateRatesOfNews(current_news->getRates(), current_news->getId());
	}
	else {
		addNewRate(rate, current_news->getId(), current_user->getId());
		current_news->setRates(QString::number(current_news->getRates().toInt() + rate.toInt()));
		updateRatesOfNews(current_news->getRates(), current_news->getId());
	}
}

QPair<bool, Like*> HomePage::getLikeOfUser(QString news_id, QString user_id) {
	Like* like;
	bool isExist = false;
	app.DB.open();
	QSqlQuery query(app.DB);
	query.prepare("SELECT * FROM LIKE WHERE USER_ID = :USER_ID AND NEWS_ID = :NEWS_ID");
	query.bindValue(":USER_ID", user_id);
	query.bindValue(":NEWS_ID", news_id);
	if (query.exec()) {
		while (query.next()) {
			like = new Like(query.value("id").toString(), query.value("news_id").toString(), query.value("user_id").toString(), query.value("isLiked").toString());
			isExist = true;
		}
	}
	app.DB.close();
	return { isExist, like };
}

void HomePage::addNewLike(QString like,QString news_id, QString user_id) {
	app.DB.open();
	QSqlQuery query(app.DB);
	QSqlDatabase::database().transaction();
	query.prepare("INSERT INTO LIKE (user_id , news_id , ISLIKED) VALUES(:user_id ,:news_id , :ISLIKED)");
	query.bindValue(":user_id", user_id);
	query.bindValue(":news_id", news_id);
	query.bindValue(":ISLIKED", like);
	query.exec();
	QSqlDatabase::database().commit();
	app.DB.close();
}

void HomePage::addNewSpam(QString spam, QString news_id, QString user_id) {
	app.DB.open();
	QSqlQuery query(app.DB);
	QSqlDatabase::database().transaction();
	query.prepare("INSERT INTO SPAM (user_id , news_id , ISSPAM) VALUES(:user_id ,:news_id , :ISSPAM)");
	query.bindValue(":user_id", user_id);
	query.bindValue(":news_id", news_id);
	query.bindValue(":ISSPAM", spam);
	query.exec();
	QSqlDatabase::database().commit();
	app.DB.close();
}

void HomePage::updateLikeOfNews(QString like, QString news_id , QString user_id) {
	app.DB.open();
	QSqlQuery query(app.DB);
	query.prepare("UPDATE LIKE SET ISLIKED = :ISLIKED WHERE NEWS_ID = :NEWS_ID AND USER_ID = :USER_ID");
	query.bindValue(":ISLIKED", like);
	query.bindValue(":NEWS_ID", news_id);
	query.bindValue(":USER_ID", user_id);
	query.exec();
	app.DB.close();
}

void HomePage::updateLikesRate(QString like, QString news_id) {
	QString likes = current_news->getLikes();
	if (like == "1") {
		likes = QString::number(likes.toInt() + 1);
	}
	else {
		likes = QString::number(likes.toInt() - 1);
	}
	app.DB.open();
	QSqlDatabase::database().transaction();
	QSqlQuery query(app.DB);
	query.prepare("UPDATE NEWS SET LIKES = :LIKES WHERE ID = :ID");
	query.bindValue(":LIKES", likes);
	query.bindValue(":ID", news_id);
	query.exec();
	QSqlDatabase::database().commit();
	app.DB.close();
}

void HomePage::updateNewsLike(QString news_id) {
	QPair<bool, Like*> p = getLikeOfUser(news_id, current_user->getId());
	Like* like = p.second;
	if (p.first) {
		if (like->getIsLiked() == "1") {
			updateLikeOfNews("0", news_id, current_user->getId());
			updateLikesRate("0" , news_id);
			current_news->setLikes(QString::number(current_news->getLikes().toInt() - 1));
			ui.likeBtn->setIcon(app.convertImageDataToImageView(QByteArray::fromBase64(QVariant::fromValue(home_imgs.value("love")->getImageData()).toByteArray()), home_imgs.value("love")->getImageExt().toStdString().c_str()));
		}
		else {
			updateLikeOfNews("1", news_id, current_user->getId());
			updateLikesRate("1", news_id);
			current_news->setLikes(QString::number(current_news->getLikes().toInt()+1));
			ui.likeBtn->setIcon(app.convertImageDataToImageView(QByteArray::fromBase64(QVariant::fromValue(home_imgs.value("love-filled")->getImageData()).toByteArray()), home_imgs.value("love-filled")->getImageExt().toStdString().c_str()));
		}
	}
	else {
		updateLikesRate("1", news_id);
		addNewLike("1", current_news->getId(), current_user->getId());
		current_news->setLikes(QString::number(current_news->getLikes().toInt() + 1));
		ui.likeBtn->setIcon(app.convertImageDataToImageView(QByteArray::fromBase64(QVariant::fromValue(home_imgs.value("love-filled")->getImageData()).toByteArray()), home_imgs.value("love-filled")->getImageExt().toStdString().c_str()));
	}
}

bool HomePage::isCatTitleExist(QString title) {
	app.DB.open();
	QSqlQuery query(app.DB);
	bool exist = false;
	query.prepare("SELECT CATEGORY FROM CATEGORIES WHERE CATEGORY = :CATEGORY");
	query.bindValue(":CATEGORY", title);
	if (query.exec()) {
		while (query.next()) {
			exist = true;
		}
	}
	app.DB.close();
	return exist;
}

bool HomePage::isNewsTitleExist(QString title) {
	app.DB.open();
	QSqlQuery query(app.DB);
	bool exist = false;
	query.prepare("SELECT TITLE FROM NEWS WHERE TITLE = :TITLE");
	query.bindValue(":TITLE", title);
	if (query.exec()) {
		while (query.next()) {
			exist = true;
		}
	}
	app.DB.close();
	return exist;
}

bool HomePage::isNewsDescExist(QString desc) {
	app.DB.open();
	QSqlQuery query(app.DB);
	bool exist = false;
	query.prepare("SELECT DESCRIPTION FROM NEWS WHERE DESCRIPTION = :DESCRIPTION");
	query.bindValue(":DESCRIPTION", desc);
	if (query.exec()) {
		while (query.next()) {
			exist = true;
		}
	}
	app.DB.close();
	return exist;
}

void HomePage::deleteNews(QString news_id) {
	app.DB.open();
	QSqlQuery query(app.DB);
	bool exist = false;
	query.prepare("DELETE FROM NEWS WHERE ID = :ID");
	query.bindValue(":ID", news_id);
	query.exec();
	app.DB.close();
}

void HomePage::updateNewsDesc(QString newDesc) {
	app.DB.open();
	QSqlQuery query(app.DB);
	bool exist = false;
	query.prepare("UPDATE NEWS SET DESCRIPTION = :DESCRIPTION WHERE ID = :ID");
	query.bindValue(":DESCRIPTION", newDesc);
	query.bindValue(":ID", current_news->getId());
	query.exec();
	app.DB.close();
}

void HomePage::updateNewsTitle(QString newTitle) {
	app.DB.open();
	QSqlQuery query(app.DB);
	bool exist = false;
	query.prepare("UPDATE NEWS SET TITLE = :TITLE WHERE ID = :ID");
	query.bindValue(":TITLE", newTitle);
	query.bindValue(":ID", current_news->getId());
	query.exec();
	app.DB.close();
}





void HomePage::on_searchInput_textChanged(const QString& arg1) {
	loadNews(current_cat_id, arg1);
}

void HomePage::on_searchBtn_clicked() {
	if (isSearch) {
		QPixmap icon = app.convertImageDataToImageView(QByteArray::fromBase64(QVariant::fromValue(home_imgs.value("search")->getImageData()).toByteArray()), home_imgs.value("search")->getImageExt().toStdString().c_str());
		ui.searchInput->setMaximumWidth(0);
		ui.searchInput->setMinimumWidth(0);
		ui.searchInput->setText("");
		ui.searchBtn->setIcon(icon);
		isSearch = !isSearch;
	}
	else {
		QPixmap icon = app.convertImageDataToImageView(QByteArray::fromBase64(QVariant::fromValue(home_imgs.value("close-search")->getImageData()).toByteArray()), home_imgs.value("close-search")->getImageExt().toStdString().c_str());
		ui.searchInput->setMaximumWidth(10000000);
		ui.searchInput->setMinimumWidth(500);
		ui.searchBtn->setIcon(icon);
		isSearch = !isSearch;
	}
}

void HomePage::on_actionHome_triggered() {
	loadNews("0");
	ui.stackedWidget->setCurrentIndex(0);
}

void HomePage::on_categoriesToolBtn_clicked() {
	if (isCategoriesOpen) {
		ui.catsGroup->setMinimumSize(0, 0);
		ui.catsGroup->setMaximumSize(0, 0);
		isCategoriesOpen = false;
		ui.categoriesToolBtn->setIcon(app.convertImageDataToImageView(QByteArray::fromBase64(QVariant::fromValue(home_imgs.value("up-arrow")->getImageData()).toByteArray()), home_imgs.value("up-arrow")->getImageExt().toStdString().c_str()));
	}
	else {
		ui.catsGroup->setMinimumSize(0, 100);
		ui.catsGroup->setMaximumSize(1000000, 10000000);
		ui.categoriesToolBtn->setIcon(app.convertImageDataToImageView(QByteArray::fromBase64(QVariant::fromValue(home_imgs.value("down-arrow")->getImageData()).toByteArray()), home_imgs.value("down-arrow")->getImageExt().toStdString().c_str()));
		isCategoriesOpen = true;
	}
}

void HomePage::on_actionLog_Out_triggered() {
	this->close();
	Authentication* authPage = new Authentication();
	authPage->show();
}

void HomePage::on_actionProfile_triggered() {
	ui.stackedWidget->setCurrentIndex(1);
}

void HomePage::on_actionuser_triggered() {
	ui.stackedWidget->setCurrentIndex(1);
}

void HomePage::on_actionAdd_News_triggered() {
	handleCategoriesInComboBox();
	on_add_news_clear_btn_clicked();
	ui.stackedWidget->setCurrentIndex(3);
}

void HomePage::on_actionAdd_Category_triggered() {
	on_add_cat_clear_btn_clicked();
	ui.stackedWidget->setCurrentIndex(4);
}

void HomePage::on_actionUser_triggered() {
	handleProfile();
	ui.stackedWidget->setCurrentIndex(1);
}

void HomePage::on_add_news_btn_clicked() {
	if (ui.add_news_image_name->text() == "") {
		openError("News Image is empty");
	}
	else if (ui.add_news_title->text() == "") {
		openError("Title is empty");
	}
	else if (ui.add_news_des->toPlainText() == "") {
		openError("Description is empty");
	}
	else if (ui.add_news_cat->currentIndex() == -1) {
		openError("Category is empty");
	}
	else if (isNewsTitleExist(ui.add_news_title->text())) {
		openError("News title is Already Exist");
	}
	else {
		if (addNewNews(ui.add_news_title->text(),ui.add_news_des->toPlainText(), ui.add_news_image_name->text(), ui.add_news_cat->currentIndex() + 1)) {
			loadNews("0");
			ui.stackedWidget->setCurrentIndex(0);
			openAlert("News is Added Successfully");
		}
	}
}

void HomePage::on_add_news_upload_img_btn_clicked() {
	ui.add_news_image_name->setText(app.openBrowser());
}

void HomePage::on_add_news_clear_btn_clicked() {
	ui.add_news_image_name->setText("");
	ui.add_news_title->setText("");
	ui.add_news_des->setText("");
	ui.add_news_cat->setCurrentIndex(-1);
}

void HomePage::on_add_cat_upload_img_btn_clicked() {
	ui.add_cat_image_name->setText(app.openBrowser());
}

void HomePage::on_add_new_cat_btn_clicked() {
	if (ui.add_cat_image_name->text() == "") {
		openError("Category Image is empty");
	}
	else if (ui.add_category_title->text() == "") {
		openError("Title is empty");
	}
	else if (isCatTitleExist(ui.add_category_title->text())) {
		openError("Category title is Already Exist");
	}
	else {
		if (addNewCategory(ui.add_category_title->text(), ui.add_cat_image_name->text())) {
			loadCats();
			ui.stackedWidget->setCurrentIndex(0);
			openAlert("Category is Added Successfully");
		}
	}
}

void HomePage::on_add_cat_clear_btn_clicked() {
	ui.add_cat_image_name->setText("");
	ui.add_category_title->setText("");
}

void HomePage::on_change_pic_btn_clicked() {
	QString imagePath = app.openBrowser();
	QFileInfo fi(imagePath);
	string ext = fi.completeSuffix().toStdString();
	for (int i = 0; i < ext.length(); i++) {
		ext[i] = toupper(ext[i]);
	}
	const char* format = ext.c_str();
	QByteArray finaleDataToSave = app.convertImageViewToImageData(imagePath);
	if (finaleDataToSave == "") {
		openError("The Image Isn't Uploaded");
		return;
	}
	current_user->setImage(QString::fromUtf8(finaleDataToSave));
	current_user->setImageExt(format);
	openAlert("Avatar is Updataed Successfully");
	app.DB.open();
	QSqlQuery query(app.DB);
	query.prepare("UPDATE USERS SET PICTURE = :PICTURE , PIC_EXT = :PIC_EXT WHERE ID = :ID");
	query.bindValue(":PICTURE", finaleDataToSave);
	query.bindValue(":PIC_EXT", format);
	query.bindValue(":ID", current_user->getId());
	query.exec();
	app.DB.close();
	ui.avatar->setPixmap(app.convertImageDataToImageView(QByteArray::fromBase64(QVariant::fromValue(current_user->getImage()).toByteArray()), current_user->getImageExt().toStdString().c_str()));
	ui.actionUser->setIcon(QIcon(app.convertImageDataToImageView(QByteArray::fromBase64(QVariant::fromValue(current_user->getImage()).toByteArray()), current_user->getImageExt().toStdString().c_str())));
}

void HomePage::on_edit_username_btn_clicked() {
	bool ok;
	updateUsernameDialog = new QInputDialog(this);
	QString newUsername = updateUsernameDialog->getText(this, "Update username",
		"new username:", QLineEdit::Normal,
		"", &ok);
	updateUsernameDialog->setStyleSheet("QInputDialog{color:#fff;background-color:#333;}");
	if (!newUsername.isEmpty()) {
		if (!app.isUserExist(newUsername)) {
			current_user->setUsername(newUsername);
			ui.username->setText(newUsername);
			openAlert("Username is Updataed Successfully");
			app.DB.open();
			QSqlQuery query(app.DB);
			query.prepare("UPDATE USERS SET USERNAME = :USERNAME WHERE ID = :ID");
			query.bindValue(":USERNAME", newUsername);
			query.bindValue(":ID", current_user->getId());
			query.exec();
			app.DB.close();
		}
		else {
			openError("Username isn't Available");
			on_edit_username_btn_clicked();
		}
	}
}

void HomePage::on_edit_email_btn_clicked() {
	bool ok;
	updateEmailDialog = new QInputDialog(this);
	QString newEmail = updateEmailDialog->getText(this, "Update email",
		"new email:", QLineEdit::Normal,
		"", &ok);
	updateEmailDialog->setStyleSheet("QInputDialog{color:#fff;background-color:#333;}");
	if (!newEmail.isEmpty()) {
		if (!app.isUserExist(newEmail)) {
			if (app.validateEmail(newEmail)) {
				current_user->setEmail(newEmail);
				ui.email->setText(newEmail);
				openAlert("Email is Updataed Successfully");
				app.DB.open();
				QSqlQuery query(app.DB);
				query.prepare("UPDATE USERS SET EMAIL = :EMAIL WHERE ID = :ID");
				query.bindValue(":EMAIL", newEmail);
				query.bindValue(":ID", current_user->getId());
				query.exec();
				app.DB.close();
			}
		}
		else {
			openError("Email is already exist");
			on_edit_email_btn_clicked();
		}
	}
}

void HomePage::on_edit_gender_btn_clicked() {
	QString g = current_user->getGender() == "male" ? "female" : "male";
	current_user->setGender(g);
	ui.gender_icon->setPixmap(current_user->getGender() == "male" ? app.convertImageDataToImageView(QByteArray::fromBase64(QVariant::fromValue(home_imgs.value("male")->getImageData()).toByteArray()), home_imgs.value("male")->getImageExt().toStdString().c_str()) : app.convertImageDataToImageView(QByteArray::fromBase64(QVariant::fromValue(home_imgs.value("female")->getImageData()).toByteArray()), home_imgs.value("female")->getImageExt().toStdString().c_str()));

	ui.gender_icon->setPixmap(g == "male" ? app.convertImageDataToImageView(QByteArray::fromBase64(QVariant::fromValue(home_imgs.value("male")->getImageData()).toByteArray()), home_imgs.value("male")->getImageExt().toStdString().c_str()) : app.convertImageDataToImageView(QByteArray::fromBase64(QVariant::fromValue(home_imgs.value("female")->getImageData()).toByteArray()), home_imgs.value("female")->getImageExt().toStdString().c_str()));
	app.DB.open();
	QSqlQuery query(app.DB);
	query.prepare("UPDATE USERS SET GENDER = :GENDER WHERE ID = :ID");
	query.bindValue(":GENDER", g);
	query.bindValue(":ID", current_user->getId());
	query.exec();
	app.DB.close();
}

void HomePage::on_delete_acc_btn_clicked() {
	bool ok;
	int ans;
	checkPassDialog = new QInputDialog(this);
	QString pass = checkPassDialog->getText(this, "Delete Account",
		"Enter your Password:", QLineEdit::Normal,
		"", &ok);
	if (pass != current_user->getPassword()) {
		openError("Password isn't Correct");
	}
	else {
		ans = app.message("Question", "Are you sure About Deleting your account ?", "");
		if (ans == 4194304) {
			return;
		}
		if (ans == 1024) {
			deleteAccount();
		}
	}
}

void HomePage::on_change_pass_btn_clicked() {
	bool ok;
	updatePassDialog = new QInputDialog(this);
	QString oldPass = updatePassDialog->getText(this, "Update Password",
		"old password:", QLineEdit::Normal,
		"", &ok);
	if (oldPass != current_user->getPassword()) {
		openError("Password isn't Correct");
		return;
	}
	QString newPass = updatePassDialog->getText(this, "",
		"new password:", QLineEdit::Normal,
		"", &ok);
	updatePassDialog->setStyleSheet("QInputDialog{color:#fff;background-color:#333;}");
	if (!newPass.isEmpty()) {
		if (app.validatePassword(newPass)) {
			current_user->setPassword(newPass);
			openAlert("Password is Updataed Successfully");
			app.DB.open();
			QSqlQuery query(app.DB);
			query.prepare("UPDATE USERS SET PASSWORD = :PASSWORD WHERE ID = :ID");
			query.bindValue(":PASSWORD", newPass);
			query.bindValue(":ID", current_user->getId());
			query.exec();
			app.DB.close();
		}
	}
}

void HomePage::on_close_Alert_btn_clicked() {
	ui.Alert->setMinimumHeight(0);
	ui.Alert->setMaximumHeight(0);
}

void HomePage::on_close_Error_btn_clicked() {
	ui.Error->setMinimumHeight(0);
	ui.Error->setMaximumHeight(0);
}

void HomePage::on_reset_filter_news_btn_clicked() {
	ui.reset_filter_news_box->setMaximumWidth(0);
	loadNews("0");
	current_cat_id = "0";
	ui.cat_type_label->setStyleSheet("color:#fff");
	ui.cat_type_label->setText("Latest");
}

void HomePage::on_star1_clicked() {
	buildStarsOfRate("1");
	updateNewsRate("1", current_news->getId());
}

void HomePage::on_star2_clicked() {
	buildStarsOfRate("2");
	updateNewsRate("2", current_news->getId());
}

void HomePage::on_star3_clicked() {
	buildStarsOfRate("3");
	updateNewsRate("3", current_news->getId());
}

void HomePage::on_star4_clicked() {
	buildStarsOfRate("4");
	updateNewsRate("4", current_news->getId());
}

void HomePage::on_star5_clicked() {
	buildStarsOfRate("5");
	updateNewsRate("5", current_news->getId());
}

void HomePage::on_news_btn_clicked() {
	loadNews("0");
	ui.stackedWidget->setCurrentIndex(0);
}

void HomePage::on_likeBtn_clicked() {
	updateNewsLike(current_news->getId());
	ui.likes_count->setText(current_news->getLikes());
}

void HomePage::on_sendCommentBtn_clicked() {
	addNewComment(ui.commentLine->text());
	ui.commentLine->clear();
	handleCommentsOfNews(current_news->getId());
}

void HomePage::on_comment_btn_clicked() {
	if (ui.commentsgroup->minimumHeight() == 0) {
		ui.commentsgroup->setMinimumHeight(500);
		ui.commentsgroup->setMaximumSize(10000000, 10000000);
		ui.comment_btn->setIcon(app.convertImageDataToImageView(QByteArray::fromBase64(QVariant::fromValue(home_imgs.value("close-comment")->getImageData()).toByteArray()), home_imgs.value("close-comment")->getImageExt().toStdString().c_str()));
		handleCommentsOfNews(current_news->getId());
	}
	else {
		ui.commentsgroup->setMinimumHeight(0);
		ui.commentsgroup->setMaximumSize(0, 0);
		ui.comment_btn->setIcon(app.convertImageDataToImageView(QByteArray::fromBase64(QVariant::fromValue(home_imgs.value("comment")->getImageData()).toByteArray()), home_imgs.value("comment")->getImageExt().toStdString().c_str()));
	}
}

void HomePage::on_report_btn_clicked() {
	int answer = app.message("Question", "This News Delete For You", "Are yousure ?");
	if (answer == 1024) {
		addNewSpam("1" , current_news->getId() , current_user->getId());
		loadNews("0");
		on_actionHome_triggered();
	}
}

void HomePage::on_edit_news_cover_img_btn_clicked() {
	QString imagePath = app.openBrowser();
	QFileInfo fi(imagePath);
	string ext = fi.completeSuffix().toStdString();
	for (int i = 0; i < ext.length(); i++) {
		ext[i] = toupper(ext[i]);
	}
	const char* format = ext.c_str();
	QByteArray finaleDataToSave = app.convertImageViewToImageData(imagePath);
	if (finaleDataToSave == "") {
		openError("The Image Isn't Uploaded");
		return;
	}
	current_news->setImage(QString::fromUtf8(finaleDataToSave));
	current_news->setImageExt(format);
	openAlert("The News Image is Updataed Successfully");
	app.DB.open();
	QSqlQuery query(app.DB);
	query.prepare("UPDATE NEWS SET IMAGE = :IMAGE , IMAGE_EXT = :IMAGE_EXT WHERE ID = :ID");
	query.bindValue(":IMAGE", finaleDataToSave);
	query.bindValue(":IMAGE_EXT", format);
	query.bindValue(":ID", current_news->getId());
	query.exec();
	app.DB.close();
	ui.coverImg->setPixmap(app.convertImageDataToImageView(QByteArray::fromBase64(QVariant::fromValue(current_news->getImage()).toByteArray()), current_news->getImageExt().toStdString().c_str()));
}

void HomePage::on_edit_news_title_btn_clicked() {
	bool ok;
	updateNewsTitleDialog = new QInputDialog(this);
	QString newTitle = updateNewsTitleDialog->getText(this, "Update News Title",
		"new title:", QLineEdit::Normal,
		"", &ok);
	updateNewsTitleDialog->setStyleSheet("QInputDialog{color:#fff;background-color:#333;}");
	if (!newTitle.isEmpty()) {
		if (!isNewsTitleExist(newTitle)) {
			updateNewsTitle(newTitle);
			ui.news_title->setText(newTitle);
			openAlert("Title is Updataed Successfully");
		}
		else {
			openError("Title isn't Available");
			on_edit_news_title_btn_clicked();
		}
	}
}

void HomePage::on_edit_news_desc_btn_clicked() {
	bool ok;
	updateNewsDescDialog = new QInputDialog(this);
	QString newDesc = updateNewsDescDialog->getMultiLineText(this, "Update News Description",
		"new description:", "", &ok);
	updateNewsDescDialog->setStyleSheet("QInputDialog{color:#fff;background-color:#333;}");
	if (!newDesc.isEmpty()) {
		if (!isNewsTitleExist(newDesc)) {
			updateNewsDesc(newDesc);
			ui.news_description->setText(newDesc);
			openAlert("Description is Updataed Successfully");
		}
		else {
			openError("Description isn't Available");
		}
	}
}

void HomePage::on_delete_news_btn_clicked() {
	bool ok;
	int ans;
	checkPassDialog = new QInputDialog(this);
	QString pass = checkPassDialog->getText(this, "Delete News",
		"Enter your Password:", QLineEdit::Normal,
		"", &ok);
	if (pass != current_user->getPassword()) {
		openError("Password isn't Correct");
	}
	else {
		ans = app.message("Question", "Are you sure About Deleting This News ?", "");
		if (ans == 4194304) {
			return;
		}
		if (ans == 1024) {
			deleteNews(current_news->getId());
			loadNews("0");
			on_actionHome_triggered();
			openAlert("News is Deleted Successfully");
		}
	}
}

HomePage::~HomePage()
{}
