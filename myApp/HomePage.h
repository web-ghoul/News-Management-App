#pragma once

#include <QMainWindow>
#include "ui_HomePage.h"
#include "Image.h"
#include "myApp.h"
#include "Authentication.h"
#include "Category.h"
#include "News.h"
#include "Rate.h"
#include "Like.h"
#include "Comment.h"
#include "Spam.h"
#include <qinputdialog.h>
#include <qlabel.h>

class HomePage : public QMainWindow
{
	Q_OBJECT

public:
	HomePage(QString id , QWidget *parent = nullptr);
	~HomePage();
	myApp app = new myApp();


private slots:
	void on_actionLog_Out_triggered();
	void on_actionProfile_triggered();
	void on_actionHome_triggered();
	void on_actionuser_triggered();
	void on_actionAdd_News_triggered();
	void on_actionAdd_Category_triggered();
	void on_add_news_clear_btn_clicked();
	void on_add_cat_clear_btn_clicked();
	void on_categoriesToolBtn_clicked();
	void on_close_Alert_btn_clicked();
	void on_close_Error_btn_clicked();
	void on_reset_filter_news_btn_clicked();
	void on_actionUser_triggered();
	void on_change_pic_btn_clicked();
	void on_edit_username_btn_clicked();
	void on_edit_email_btn_clicked();
	void on_edit_gender_btn_clicked();
	void on_change_pass_btn_clicked();
	void on_delete_acc_btn_clicked();
	void on_add_news_upload_img_btn_clicked();
	void on_add_news_btn_clicked();
	void on_add_cat_upload_img_btn_clicked();
	void on_add_new_cat_btn_clicked();
	void on_star1_clicked();
	void on_star2_clicked();
	void on_star3_clicked();
	void on_star4_clicked();
	void on_star5_clicked();
	void on_news_btn_clicked();
	void on_likeBtn_clicked();
	void on_sendCommentBtn_clicked();
	void on_comment_btn_clicked();
	void on_report_btn_clicked();
	void on_edit_news_cover_img_btn_clicked();
	void on_edit_news_title_btn_clicked();
	void on_edit_news_desc_btn_clicked();
	void on_delete_news_btn_clicked();
	void on_searchBtn_clicked();
	void on_searchInput_textChanged(const QString& arg1);

private:
	Ui::HomePageClass ui;
	bool isSearch;
	QString current_cat_id;
	QInputDialog* updateUsernameDialog;
	QInputDialog* updateEmailDialog;
	QInputDialog* updatePassDialog;
	QInputDialog* checkPassDialog;
	QInputDialog* updateNewsTitleDialog;
	QInputDialog* updateNewsDescDialog;
	QStack<QGroupBox*> commentGroups;
	QTimer* timer = new QTimer(this);
	bool isCategoriesOpen;
	User* current_user;
	News* current_news;
	QMap<QString, Image*> home_imgs;
	QMap<QString, Category*> categories;
	void loadImgs();
	void loadCats();
	void loadNews(QString id = "0" , QString arg = "");
	bool isNewsTitleExist(QString title);
	QMap<QString, QVector<Spam*>> getSpamsFromDB();
	bool addNewNews(QString title, QString description, QString imagePath, int category);
	bool addNewCategory(QString categoryTitle, QString imagePath);
	bool isCatTitleExist(QString title);
	QString getCatTitleById(QString id);
	QString getCurrentDateAndTime();
	void deleteNews(QString news_id);
	bool isNewsDescExist(QString desc);
	QMap<QString, Image*> getHomeImgsFromDB();
	void updateNewsDesc(QString newDesc);
	void addNewComment(QString comment);
	void addNewSpam(QString spam, QString news_id, QString user_id);
	QGroupBox* buildCategoriesInHomePage(QString id, QString title, QString image, QString image_ext);
	QFrame* buildNews(QString title, QString description, QString date, QString image, QString id, QString image_ext);
	void changeNewsImage();
	void updateNewsTitle(QString newTitle);
	QGroupBox* buildComment (QString id, QString commentDesc, User* user);
	QStack<Comment*> getCommentsByNewsId(QString news_id);
	void handleCommentsOfNews(QString news_id);
	void toggleAdminOperations(bool isAdmin);
	void updateNewsLike(QString id);
	bool isUserLikedNews(QString news_id);
	void buildStarsOfRate(QString rate);
	QVector<QToolButton*> buildRate(QString rate);
	bool isUserAdmin(QString user_id);
	void deleteComment(QString comment_id);
	void buildComments();
	QString getRatesOfNews(QString news_id);
	News* getNewsById(QString id);
	QString getNumberOfUserIsRated(QString news_id);
	Category* getCatById(QString cat_id);
	User* getUserById(QString user_id);
	QPair<bool, Rate*> getRateOfUser(QString news_id, QString user_id);
	QPair<bool, Like*> getLikeOfUser(QString news_id, QString user_id);
	QString getRateOfNewsByUser(QString user_id, QString news_id);
	void updateRateOfUser(QString rate, QString news_id, QString user_id);
	void updateNewsRate(QString rate, QString id);
	void updateRatesOfNews(QString rates, QString news_id);
	void addNewRate(QString rate, QString news_id, QString user_id);
	void addNewLike(QString like, QString news_id, QString user_id);
	void updateLikesRate(QString like, QString news_id);
	void updateLikeOfNews(QString like, QString news_id, QString user_id);
	void activateNews(QString news_id);
	void getCurrentUserFromDB(QString id);
	void handleProfile();
	void deleteAccount();
	void closeComment();
	void handleCategoriesInComboBox();
	void deleteCategory(QString id);
	void openAlert(QString message);
	void openError(QString message);
	void filterByCat(QString id);
};
