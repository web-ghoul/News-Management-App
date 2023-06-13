/********************************************************************************
** Form generated from reading UI file 'Authentication.ui'
**
** Created by: Qt User Interface Compiler version 6.4.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_AUTHENTICATION_H
#define UI_AUTHENTICATION_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AuthenticationClass
{
public:
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QVBoxLayout *verticalLayout_2;
    QTabWidget *tabWidget;
    QWidget *Register;
    QVBoxLayout *verticalLayout_5;
    QGroupBox *groupBox_4;
    QHBoxLayout *horizontalLayout_2;
    QLabel *l_logo_reg;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_3;
    QLineEdit *username_reg;
    QLineEdit *email_reg;
    QGroupBox *groupBox_2;
    QHBoxLayout *horizontalLayout;
    QRadioButton *male_radio_btn;
    QRadioButton *female_radio_btn;
    QGroupBox *groupBox_5;
    QHBoxLayout *horizontalLayout_3;
    QLineEdit *password_reg;
    QToolButton *eye_pass_reg_toolBtn;
    QGroupBox *groupBox_6;
    QHBoxLayout *horizontalLayout_4;
    QLineEdit *confirm_password;
    QToolButton *eye_conPass_reg_toolBtn;
    QGroupBox *groupBox_3;
    QVBoxLayout *verticalLayout_4;
    QPushButton *btn_register;
    QWidget *Login;
    QVBoxLayout *verticalLayout_7;
    QGroupBox *groupBox_7;
    QHBoxLayout *horizontalLayout_5;
    QLabel *l_logo_login;
    QGroupBox *groupBox_8;
    QVBoxLayout *verticalLayout_8;
    QGroupBox *groupBox_10;
    QHBoxLayout *horizontalLayout_7;
    QLineEdit *email_or_username_login;
    QGroupBox *groupBox_9;
    QVBoxLayout *verticalLayout_6;
    QGroupBox *groupBox_12;
    QHBoxLayout *horizontalLayout_6;
    QLineEdit *password_login;
    QToolButton *eye_pass_login_toolBtn;
    QPushButton *forgot_pass_btn;
    QGroupBox *groupBox_11;
    QHBoxLayout *horizontalLayout_8;
    QPushButton *btn_login;

    void setupUi(QMainWindow *AuthenticationClass)
    {
        if (AuthenticationClass->objectName().isEmpty())
            AuthenticationClass->setObjectName("AuthenticationClass");
        AuthenticationClass->resize(600, 650);
        AuthenticationClass->setMinimumSize(QSize(360, 600));
        AuthenticationClass->setMaximumSize(QSize(600, 650));
        AuthenticationClass->setCursor(QCursor(Qt::IBeamCursor));
        AuthenticationClass->setStyleSheet(QString::fromUtf8("*{\n"
"	outline:none;\n"
"	border:none;\n"
"	background-color:transparent;\n"
"	background-image:none;\n"
"}\n"
"\n"
"\n"
"QWidget{\n"
"	background-color:#333;\n"
"	color:#fff;\n"
"}\n"
"\n"
"QMenu::hover{\n"
"	background-color:#333;\n"
"}\n"
"\n"
"QLineEdit{\n"
"	background-color:#fff;	\n"
"	color:#037ef3;\n"
"	padding:5px 10px;\n"
"}\n"
"\n"
"QPushButton{\n"
"	background-color:#037ef3;\n"
"	color:#fff;\n"
"	border-radius:8px;\n"
"	padding:10px;\n"
"}\n"
"\n"
"\n"
"\n"
"QPushButton#delete_acc_btn{\n"
"	background-color:#ff7243;\n"
"}\n"
"\n"
"QPushButton#delete_acc_btn::hover{\n"
"	background-color:#fe5000;\n"
"}\n"
"\n"
"QPushButton::hover {\n"
"	background-color:#0099e5;\n"
"}\n"
"QPushButton#forgot_pass_btn{\n"
"	background-color:transparent;\n"
"padding :0px;\n"
"}\n"
"\n"
"\n"
"\n"
"QToolBar{\n"
"	border:4px solid;\n"
"	spacing:50px;\n"
"	padding:20px;\n"
"	color:#fff;\n"
"}\n"
"\n"
"QToolBar#controlToolBar,QToolBar#userToolBar,QToolBar#addNewsToolBar{\n"
"	border-right-color: #037ef3;\n"
"}\n"
"\n"
"QMe"
                        "nuBar::item:selected{\n"
"	background-color:#037ef3;\n"
"	color:#fff;\n"
"}\n"
"\n"
"QToolButton::hover{\n"
"	color:#037ef3;\n"
"}\n"
"\n"
"QGroupBox#searchGroup{\n"
"	border-bottom:4px solid #037ef3;\n"
"}\n"
"\n"
"QGroupBox#email_box,QGroupBox#gender_box{\n"
"	border:4px solid #037ef3;\n"
"	border-radius:10px;\n"
"}\n"
"\n"
"QLabel#avatar{\n"
"	border:4px solid transparent;\n"
"}\n"
"\n"
"QLabel#avatar::hover{\n"
"	border:4px solid #037ef3;\n"
"}\n"
"\n"
"QScrollBar::handle:vertical,QScrollBar::handle:horizontal{\n"
"	background-color:#037ef3;\n"
"}\n"
"\n"
"QScrollBar::handle:vertical:hover,QScrollBar::handle:horizontal:hover{\n"
"	background-color:#0099e5;\n"
"}\n"
"\n"
"QScrollBar:vertical {\n"
"    width: 15px;\n"
"    margin: 0px;\n"
"}\n"
"\n"
"QScrollBar:horizontal {\n"
"    height: 15px;\n"
"    margin: 0px;\n"
"}\n"
"\n"
"QScrollBar::add-page:vertical,\n"
"QScrollBar::sub-page:vertical,QScrollBar::add-page:horizontal,\n"
"QScrollBar::sub-page:horizontal {\n"
"    background-color: transparent;\n"
"}"
                        "\n"
"\n"
"QInputDialog ,QMessageBox{\n"
"	color:#fff;\n"
"	background-color:#333;\n"
"}\n"
"\n"
"QInputDialog QlineEdit{\n"
"	font-size:10px;\n"
"}\n"
"\n"
"QToolButton#eye_pass_reg_toolBtn ,QToolButton#eye_conPass_reg_toolBtn , QToolButton#eye_pass_login_toolBtn{\n"
"	background-color:#fff;\n"
"}\n"
"\n"
"\n"
"QLabel#pref{\n"
"	color:#fff;\n"
"}\n"
"\n"
"\n"
""));
        widget = new QWidget(AuthenticationClass);
        widget->setObjectName("widget");
        widget->setStyleSheet(QString::fromUtf8(""));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setSpacing(0);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        scrollArea = new QScrollArea(widget);
        scrollArea->setObjectName("scrollArea");
        scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName("scrollAreaWidgetContents");
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 600, 650));
        verticalLayout_2 = new QVBoxLayout(scrollAreaWidgetContents);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        tabWidget = new QTabWidget(scrollAreaWidgetContents);
        tabWidget->setObjectName("tabWidget");
        tabWidget->setMinimumSize(QSize(360, 600));
        tabWidget->setMaximumSize(QSize(600, 650));
        QFont font;
        font.setFamilies({QString::fromUtf8("Kozuka Gothic Pr6N B")});
        font.setPointSize(12);
        tabWidget->setFont(font);
        tabWidget->setCursor(QCursor(Qt::PointingHandCursor));
        tabWidget->setStyleSheet(QString::fromUtf8("color:#333;"));
        tabWidget->setIconSize(QSize(30, 30));
        tabWidget->setMovable(true);
        Register = new QWidget();
        Register->setObjectName("Register");
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Kozuka Gothic Pr6N B")});
        Register->setFont(font1);
        Register->setCursor(QCursor(Qt::ArrowCursor));
        Register->setLayoutDirection(Qt::LeftToRight);
        Register->setAutoFillBackground(false);
        Register->setStyleSheet(QString::fromUtf8(""));
        verticalLayout_5 = new QVBoxLayout(Register);
        verticalLayout_5->setSpacing(20);
        verticalLayout_5->setContentsMargins(11, 11, 11, 11);
        verticalLayout_5->setObjectName("verticalLayout_5");
        verticalLayout_5->setContentsMargins(20, 20, 20, 20);
        groupBox_4 = new QGroupBox(Register);
        groupBox_4->setObjectName("groupBox_4");
        groupBox_4->setMinimumSize(QSize(150, 150));
        horizontalLayout_2 = new QHBoxLayout(groupBox_4);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        l_logo_reg = new QLabel(groupBox_4);
        l_logo_reg->setObjectName("l_logo_reg");
        l_logo_reg->setMinimumSize(QSize(0, 0));
        l_logo_reg->setMaximumSize(QSize(150, 150));
        l_logo_reg->setScaledContents(true);

        horizontalLayout_2->addWidget(l_logo_reg);


        verticalLayout_5->addWidget(groupBox_4, 0, Qt::AlignHCenter);

        groupBox = new QGroupBox(Register);
        groupBox->setObjectName("groupBox");
        verticalLayout_3 = new QVBoxLayout(groupBox);
        verticalLayout_3->setSpacing(10);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName("verticalLayout_3");
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        username_reg = new QLineEdit(groupBox);
        username_reg->setObjectName("username_reg");
        username_reg->setMinimumSize(QSize(0, 50));
        QFont font2;
        font2.setFamilies({QString::fromUtf8("Kozuka Gothic Pr6N B")});
        font2.setPointSize(12);
        font2.setBold(true);
        username_reg->setFont(font2);

        verticalLayout_3->addWidget(username_reg);

        email_reg = new QLineEdit(groupBox);
        email_reg->setObjectName("email_reg");
        email_reg->setMinimumSize(QSize(0, 50));
        email_reg->setFont(font2);

        verticalLayout_3->addWidget(email_reg);

        groupBox_2 = new QGroupBox(groupBox);
        groupBox_2->setObjectName("groupBox_2");
        groupBox_2->setMinimumSize(QSize(0, 50));
        horizontalLayout = new QHBoxLayout(groupBox_2);
        horizontalLayout->setSpacing(20);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(20, 0, 20, 0);
        male_radio_btn = new QRadioButton(groupBox_2);
        male_radio_btn->setObjectName("male_radio_btn");
        male_radio_btn->setFont(font2);
        male_radio_btn->setCursor(QCursor(Qt::PointingHandCursor));
        male_radio_btn->setStyleSheet(QString::fromUtf8("color:#fff;"));

        horizontalLayout->addWidget(male_radio_btn, 0, Qt::AlignLeft);

        female_radio_btn = new QRadioButton(groupBox_2);
        female_radio_btn->setObjectName("female_radio_btn");
        female_radio_btn->setFont(font2);
        female_radio_btn->setCursor(QCursor(Qt::PointingHandCursor));
        female_radio_btn->setStyleSheet(QString::fromUtf8("color:#fff;"));

        horizontalLayout->addWidget(female_radio_btn, 0, Qt::AlignRight);


        verticalLayout_3->addWidget(groupBox_2);

        groupBox_5 = new QGroupBox(groupBox);
        groupBox_5->setObjectName("groupBox_5");
        horizontalLayout_3 = new QHBoxLayout(groupBox_5);
        horizontalLayout_3->setSpacing(0);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        password_reg = new QLineEdit(groupBox_5);
        password_reg->setObjectName("password_reg");
        password_reg->setMinimumSize(QSize(0, 50));
        password_reg->setFont(font2);
        password_reg->setEchoMode(QLineEdit::Password);

        horizontalLayout_3->addWidget(password_reg);

        eye_pass_reg_toolBtn = new QToolButton(groupBox_5);
        eye_pass_reg_toolBtn->setObjectName("eye_pass_reg_toolBtn");
        eye_pass_reg_toolBtn->setMinimumSize(QSize(50, 50));
        eye_pass_reg_toolBtn->setCursor(QCursor(Qt::PointingHandCursor));
        eye_pass_reg_toolBtn->setIconSize(QSize(30, 30));

        horizontalLayout_3->addWidget(eye_pass_reg_toolBtn);


        verticalLayout_3->addWidget(groupBox_5);

        groupBox_6 = new QGroupBox(groupBox);
        groupBox_6->setObjectName("groupBox_6");
        horizontalLayout_4 = new QHBoxLayout(groupBox_6);
        horizontalLayout_4->setSpacing(0);
        horizontalLayout_4->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        confirm_password = new QLineEdit(groupBox_6);
        confirm_password->setObjectName("confirm_password");
        confirm_password->setMinimumSize(QSize(0, 50));
        confirm_password->setFont(font2);
        confirm_password->setEchoMode(QLineEdit::Password);

        horizontalLayout_4->addWidget(confirm_password);

        eye_conPass_reg_toolBtn = new QToolButton(groupBox_6);
        eye_conPass_reg_toolBtn->setObjectName("eye_conPass_reg_toolBtn");
        eye_conPass_reg_toolBtn->setMinimumSize(QSize(50, 50));
        eye_conPass_reg_toolBtn->setCursor(QCursor(Qt::PointingHandCursor));
        eye_conPass_reg_toolBtn->setIconSize(QSize(30, 30));

        horizontalLayout_4->addWidget(eye_conPass_reg_toolBtn);


        verticalLayout_3->addWidget(groupBox_6);


        verticalLayout_5->addWidget(groupBox);

        groupBox_3 = new QGroupBox(Register);
        groupBox_3->setObjectName("groupBox_3");
        verticalLayout_4 = new QVBoxLayout(groupBox_3);
        verticalLayout_4->setSpacing(0);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName("verticalLayout_4");
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        btn_register = new QPushButton(groupBox_3);
        btn_register->setObjectName("btn_register");
        btn_register->setMinimumSize(QSize(250, 50));
        btn_register->setFont(font2);
        btn_register->setCursor(QCursor(Qt::PointingHandCursor));
        btn_register->setStyleSheet(QString::fromUtf8("color:#fff;"));

        verticalLayout_4->addWidget(btn_register, 0, Qt::AlignHCenter);


        verticalLayout_5->addWidget(groupBox_3);

        tabWidget->addTab(Register, QString());
        Login = new QWidget();
        Login->setObjectName("Login");
        Login->setFont(font1);
        Login->setCursor(QCursor(Qt::ArrowCursor));
        verticalLayout_7 = new QVBoxLayout(Login);
        verticalLayout_7->setSpacing(40);
        verticalLayout_7->setContentsMargins(11, 11, 11, 11);
        verticalLayout_7->setObjectName("verticalLayout_7");
        verticalLayout_7->setContentsMargins(20, 20, 20, 20);
        groupBox_7 = new QGroupBox(Login);
        groupBox_7->setObjectName("groupBox_7");
        groupBox_7->setMinimumSize(QSize(150, 150));
        horizontalLayout_5 = new QHBoxLayout(groupBox_7);
        horizontalLayout_5->setSpacing(0);
        horizontalLayout_5->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        horizontalLayout_5->setContentsMargins(10, 10, 10, 10);
        l_logo_login = new QLabel(groupBox_7);
        l_logo_login->setObjectName("l_logo_login");
        l_logo_login->setMaximumSize(QSize(150, 150));
        l_logo_login->setScaledContents(true);

        horizontalLayout_5->addWidget(l_logo_login, 0, Qt::AlignHCenter);


        verticalLayout_7->addWidget(groupBox_7);

        groupBox_8 = new QGroupBox(Login);
        groupBox_8->setObjectName("groupBox_8");
        verticalLayout_8 = new QVBoxLayout(groupBox_8);
        verticalLayout_8->setSpacing(20);
        verticalLayout_8->setContentsMargins(11, 11, 11, 11);
        verticalLayout_8->setObjectName("verticalLayout_8");
        verticalLayout_8->setContentsMargins(10, 10, 10, 10);
        groupBox_10 = new QGroupBox(groupBox_8);
        groupBox_10->setObjectName("groupBox_10");
        horizontalLayout_7 = new QHBoxLayout(groupBox_10);
        horizontalLayout_7->setSpacing(0);
        horizontalLayout_7->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_7->setObjectName("horizontalLayout_7");
        horizontalLayout_7->setContentsMargins(0, 0, 0, 0);
        email_or_username_login = new QLineEdit(groupBox_10);
        email_or_username_login->setObjectName("email_or_username_login");
        email_or_username_login->setMinimumSize(QSize(0, 50));
        email_or_username_login->setFont(font2);

        horizontalLayout_7->addWidget(email_or_username_login);


        verticalLayout_8->addWidget(groupBox_10);

        groupBox_9 = new QGroupBox(groupBox_8);
        groupBox_9->setObjectName("groupBox_9");
        verticalLayout_6 = new QVBoxLayout(groupBox_9);
        verticalLayout_6->setSpacing(0);
        verticalLayout_6->setContentsMargins(11, 11, 11, 11);
        verticalLayout_6->setObjectName("verticalLayout_6");
        verticalLayout_6->setContentsMargins(0, 0, 0, 0);
        groupBox_12 = new QGroupBox(groupBox_9);
        groupBox_12->setObjectName("groupBox_12");
        horizontalLayout_6 = new QHBoxLayout(groupBox_12);
        horizontalLayout_6->setSpacing(0);
        horizontalLayout_6->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        horizontalLayout_6->setContentsMargins(0, 0, 0, 0);
        password_login = new QLineEdit(groupBox_12);
        password_login->setObjectName("password_login");
        password_login->setMinimumSize(QSize(0, 50));
        password_login->setFont(font2);
        password_login->setEchoMode(QLineEdit::Password);

        horizontalLayout_6->addWidget(password_login);

        eye_pass_login_toolBtn = new QToolButton(groupBox_12);
        eye_pass_login_toolBtn->setObjectName("eye_pass_login_toolBtn");
        eye_pass_login_toolBtn->setMinimumSize(QSize(50, 50));
        eye_pass_login_toolBtn->setCursor(QCursor(Qt::PointingHandCursor));
        eye_pass_login_toolBtn->setIconSize(QSize(30, 30));

        horizontalLayout_6->addWidget(eye_pass_login_toolBtn);


        verticalLayout_6->addWidget(groupBox_12);

        forgot_pass_btn = new QPushButton(groupBox_9);
        forgot_pass_btn->setObjectName("forgot_pass_btn");
        forgot_pass_btn->setFont(font2);
        forgot_pass_btn->setCursor(QCursor(Qt::PointingHandCursor));
        forgot_pass_btn->setStyleSheet(QString::fromUtf8("QPushButton#forgot_pass_btn{\n"
"	color:#fff;\n"
"}\n"
"QPushButton#forgot_pass_btn::hover{\n"
"	color:#037ef3;\n"
"}\n"
""));

        verticalLayout_6->addWidget(forgot_pass_btn, 0, Qt::AlignRight);


        verticalLayout_8->addWidget(groupBox_9);


        verticalLayout_7->addWidget(groupBox_8);

        groupBox_11 = new QGroupBox(Login);
        groupBox_11->setObjectName("groupBox_11");
        horizontalLayout_8 = new QHBoxLayout(groupBox_11);
        horizontalLayout_8->setSpacing(10);
        horizontalLayout_8->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_8->setObjectName("horizontalLayout_8");
        horizontalLayout_8->setContentsMargins(10, 10, 10, 10);
        btn_login = new QPushButton(groupBox_11);
        btn_login->setObjectName("btn_login");
        btn_login->setMinimumSize(QSize(250, 50));
        btn_login->setFont(font2);
        btn_login->setCursor(QCursor(Qt::PointingHandCursor));
        btn_login->setStyleSheet(QString::fromUtf8("color:#fff;"));

        horizontalLayout_8->addWidget(btn_login, 0, Qt::AlignHCenter);


        verticalLayout_7->addWidget(groupBox_11, 0, Qt::AlignHCenter|Qt::AlignVCenter);

        tabWidget->addTab(Login, QString());

        verticalLayout_2->addWidget(tabWidget);

        scrollArea->setWidget(scrollAreaWidgetContents);

        verticalLayout->addWidget(scrollArea);

        AuthenticationClass->setCentralWidget(widget);

        retranslateUi(AuthenticationClass);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(AuthenticationClass);
    } // setupUi

    void retranslateUi(QMainWindow *AuthenticationClass)
    {
        AuthenticationClass->setWindowTitle(QCoreApplication::translate("AuthenticationClass", "Newspaper App", nullptr));
        groupBox_4->setTitle(QCoreApplication::translate("AuthenticationClass", "GroupBox", nullptr));
        l_logo_reg->setText(QString());
        groupBox->setTitle(QCoreApplication::translate("AuthenticationClass", "GroupBox", nullptr));
        username_reg->setText(QString());
        username_reg->setPlaceholderText(QCoreApplication::translate("AuthenticationClass", "Enter Username", nullptr));
        email_reg->setPlaceholderText(QCoreApplication::translate("AuthenticationClass", "Enter Email", nullptr));
        groupBox_2->setTitle(QString());
        male_radio_btn->setText(QCoreApplication::translate("AuthenticationClass", "Male", nullptr));
        female_radio_btn->setText(QCoreApplication::translate("AuthenticationClass", "Female", nullptr));
        groupBox_5->setTitle(QCoreApplication::translate("AuthenticationClass", "GroupBox", nullptr));
        password_reg->setPlaceholderText(QCoreApplication::translate("AuthenticationClass", "Enter Password", nullptr));
        eye_pass_reg_toolBtn->setText(QCoreApplication::translate("AuthenticationClass", "...", nullptr));
        groupBox_6->setTitle(QCoreApplication::translate("AuthenticationClass", "GroupBox", nullptr));
        confirm_password->setPlaceholderText(QCoreApplication::translate("AuthenticationClass", "Confirm Password", nullptr));
        eye_conPass_reg_toolBtn->setText(QCoreApplication::translate("AuthenticationClass", "...", nullptr));
        groupBox_3->setTitle(QString());
        btn_register->setText(QCoreApplication::translate("AuthenticationClass", "Register", nullptr));
#if QT_CONFIG(shortcut)
        btn_register->setShortcut(QCoreApplication::translate("AuthenticationClass", "Return", nullptr));
#endif // QT_CONFIG(shortcut)
        tabWidget->setTabText(tabWidget->indexOf(Register), QCoreApplication::translate("AuthenticationClass", "Register", nullptr));
        groupBox_7->setTitle(QCoreApplication::translate("AuthenticationClass", "GroupBox", nullptr));
        l_logo_login->setText(QString());
        groupBox_8->setTitle(QString());
        groupBox_10->setTitle(QString());
        email_or_username_login->setPlaceholderText(QCoreApplication::translate("AuthenticationClass", "Enter Username or Email", nullptr));
        groupBox_9->setTitle(QCoreApplication::translate("AuthenticationClass", "GroupBox", nullptr));
        groupBox_12->setTitle(QString());
        password_login->setPlaceholderText(QCoreApplication::translate("AuthenticationClass", "Enter Password", nullptr));
        eye_pass_login_toolBtn->setText(QCoreApplication::translate("AuthenticationClass", "...", nullptr));
        forgot_pass_btn->setText(QCoreApplication::translate("AuthenticationClass", "Forgot Password ?", nullptr));
        groupBox_11->setTitle(QString());
        btn_login->setText(QCoreApplication::translate("AuthenticationClass", "Login", nullptr));
#if QT_CONFIG(shortcut)
        btn_login->setShortcut(QCoreApplication::translate("AuthenticationClass", "Return", nullptr));
#endif // QT_CONFIG(shortcut)
        tabWidget->setTabText(tabWidget->indexOf(Login), QCoreApplication::translate("AuthenticationClass", "Login", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AuthenticationClass: public Ui_AuthenticationClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_AUTHENTICATION_H
