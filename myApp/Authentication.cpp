#include "Authentication.h"

Authentication::Authentication(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
    loadImgs();
    isPassRegHide = true;
    isConPassRegHide = true;
    isPassLogHide = true;
}

QMap<QString, Image*> Authentication::getAuthImgsFromDB() {
    if (auth_imgs.size() > 0) {
        return auth_imgs;
    }
    QMap<QString, Image*> images;
    app.DB.open();
    QSqlQuery query(app.DB);
    query.prepare("SELECT * FROM Auth_Images");
    if (query.exec()) {
        while (query.next()) {
            Image* image = new Image(query.value("id").toString(), query.value("image_data").toString(), query.value("image_ext").toString(), query.value("image_name").toString());
            images.insert(query.value("image_name").toString(), image);
        }
    }
    app.DB.close();
    return images;
}

void Authentication::loadImgs() {
    auth_imgs = getAuthImgsFromDB();
    ui.l_logo_login->setPixmap(app.convertImageDataToImageView(QByteArray::fromBase64(QVariant::fromValue(auth_imgs.value("login")->getImageData()).toByteArray()), auth_imgs.value("login")->getImageExt().toStdString().c_str()));

    ui.tabWidget->setTabIcon(1, QIcon(app.convertImageDataToImageView(QByteArray::fromBase64(QVariant::fromValue(auth_imgs.value("login")->getImageData()).toByteArray()), auth_imgs.value("login")->getImageExt().toStdString().c_str())));

    ui.l_logo_reg->setPixmap(app.convertImageDataToImageView(QByteArray::fromBase64(QVariant::fromValue(auth_imgs.value("register")->getImageData()).toByteArray()), auth_imgs.value("register")->getImageExt().toStdString().c_str()));

    ui.tabWidget->setTabIcon(0, QIcon(app.convertImageDataToImageView(QByteArray::fromBase64(QVariant::fromValue(auth_imgs.value("register")->getImageData()).toByteArray()), auth_imgs.value("register")->getImageExt().toStdString().c_str())));

    ui.eye_pass_login_toolBtn->setIcon(app.convertImageDataToImageView(QByteArray::fromBase64(QVariant::fromValue(auth_imgs.value("eye-open")->getImageData()).toByteArray()), auth_imgs.value("eye-open")->getImageExt().toStdString().c_str()));

    ui.eye_pass_reg_toolBtn->setIcon(app.convertImageDataToImageView(QByteArray::fromBase64(QVariant::fromValue(auth_imgs.value("eye-open")->getImageData()).toByteArray()), auth_imgs.value("eye-open")->getImageExt().toStdString().c_str()));

    ui.eye_conPass_reg_toolBtn->setIcon(app.convertImageDataToImageView(QByteArray::fromBase64(QVariant::fromValue(auth_imgs.value("eye-open")->getImageData()).toByteArray()), auth_imgs.value("eye-open")->getImageExt().toStdString().c_str()));

    setWindowIcon(app.convertImageDataToImageView(QByteArray::fromBase64(QVariant::fromValue(auth_imgs.value("logo")->getImageData()).toByteArray()), auth_imgs.value("logo")->getImageExt().toStdString().c_str()));
}

void Authentication::go_to_home(QString id) {
    HomePage* home = new HomePage(id);
    home->showMaximized();
    this->close();
}

QString Authentication::getUserIdOfEmailAndUsername(QString email, QString username) {
    app.DB.open();
    QSqlQuery query(app.DB);
    query.prepare("SELECT ID FROM USERS WHERE EMAIL = :EMAIL AND USERNAME = :USERNAME");
    query.bindValue(":EMAIL", email);
    query.bindValue(":USERNAME", username);
    if (query.exec()) {
        while (query.next()) {
            return query.value(0).toString();
        }
    }
    app.DB.close();
    return "-1";
}

bool Authentication::confirmPassword(QString pass1, QString pass2) {
    if (pass1 != pass2) {
        app.message("Error", "Password isn't Matched", "");
        return false;
    }
    return true;
}

void Authentication::AddNewUserData(QString username, QString email, QString password, QString gender, QString picture, QString pic_ext) {
    app.DB.open();
    QSqlDatabase::database().transaction();
    QSqlQuery query(app.DB);
    query.prepare("INSERT INTO USERS (id , username , email, password, picture , pic_ext, isAdmin,gender , isVerify) VALUES (:id,:username , :email  ,:password  ,  :picture  ,  :pic_ext , :isAdmin  ,:gender ,:isVerify)");
    query.bindValue(":username", username);
    query.bindValue(":email", email);
    query.bindValue(":password", password);
    query.bindValue(":picture", picture);
    query.bindValue(":pic_ext", pic_ext);
    query.bindValue(":isAdmin",0);
    query.bindValue(":gender", gender);
    query.bindValue(":isVerify", 0);
    query.exec();
    QSqlDatabase::database().commit();
    app.DB.close();
}

void Authentication::clearRegister() {
    ui.password_reg->setText("");
    ui.email_reg->setText("");
    ui.username_reg->setText("");
    ui.confirm_password->setText("");
    ui.male_radio_btn->setChecked(false);
    ui.female_radio_btn->setChecked(false);
}

void Authentication::clearLogin() {
    ui.email_or_username_login->setText("");
    ui.password_login->setText("");
}

void Authentication::on_eye_pass_reg_toolBtn_clicked() {
    if (isPassRegHide) {
        ui.eye_pass_reg_toolBtn->setIcon(app.convertImageDataToImageView(QByteArray::fromBase64(QVariant::fromValue(auth_imgs.value("eye-close")->getImageData()).toByteArray()), auth_imgs.value("eye-close")->getImageExt().toStdString().c_str()));
        ui.password_reg->setEchoMode(QLineEdit::Normal);
        isPassRegHide = false;
    }
    else {
        ui.eye_pass_reg_toolBtn->setIcon(app.convertImageDataToImageView(QByteArray::fromBase64(QVariant::fromValue(auth_imgs.value("eye-open")->getImageData()).toByteArray()), auth_imgs.value("eye-open")->getImageExt().toStdString().c_str()));
        ui.password_reg->setEchoMode(QLineEdit::Password);
        isPassRegHide = true;
    }
}

void Authentication::on_eye_conPass_reg_toolBtn_clicked() {
    if (isConPassRegHide) {
        ui.eye_conPass_reg_toolBtn->setIcon(app.convertImageDataToImageView(QByteArray::fromBase64(QVariant::fromValue(auth_imgs.value("eye-close")->getImageData()).toByteArray()), auth_imgs.value("eye-close")->getImageExt().toStdString().c_str()));
        ui.confirm_password->setEchoMode(QLineEdit::Normal);
        isConPassRegHide = false;
    }
    else {
        ui.eye_conPass_reg_toolBtn->setIcon(app.convertImageDataToImageView(QByteArray::fromBase64(QVariant::fromValue(auth_imgs.value("eye-open")->getImageData()).toByteArray()), auth_imgs.value("eye-open")->getImageExt().toStdString().c_str()));
        ui.confirm_password->setEchoMode(QLineEdit::Password);
        isConPassRegHide = true;
    }
}

void Authentication::on_eye_pass_login_toolBtn_clicked() {
    if (isPassLogHide) {
        ui.eye_pass_login_toolBtn->setIcon(app.convertImageDataToImageView(QByteArray::fromBase64(QVariant::fromValue(auth_imgs.value("eye-close")->getImageData()).toByteArray()), auth_imgs.value("eye-close")->getImageExt().toStdString().c_str()));
        ui.password_login->setEchoMode(QLineEdit::Normal);
        isPassLogHide = false;
    }
    else {
        ui.eye_pass_login_toolBtn->setIcon(app.convertImageDataToImageView(QByteArray::fromBase64(QVariant::fromValue(auth_imgs.value("eye-open")->getImageData()).toByteArray()), auth_imgs.value("eye-open")->getImageExt().toStdString().c_str()));
        ui.password_login->setEchoMode(QLineEdit::Password);
        isPassLogHide = true;
    }
}

void Authentication::on_btn_login_clicked() {
    QString emailOrUsername = ui.email_or_username_login->text();
    QString password = ui.password_login->text();
    if (emailOrUsername == "") {
        app.message("Error", "Please enter your Email or Username", "");
        return;
    }
    else if (password == "") {
        app.message("Error", "Please enter your Password", "");
        return;
    }
    bool exist = app.isUserExist(emailOrUsername);
    if (exist) {
        if (app.getPasswordByEmailOrUsername(emailOrUsername) != password) {
            ui.password_login->setText("");
            app.message("Error", "Password isn't correct", "");
        }
        else {
            QString id = app.getUserIdByEmailOrUsername(emailOrUsername);
            go_to_home(id);
        }
    }
    else {
        app.message("Error", "Email or Password is Incorrect", "");
    }
   
}

void Authentication::on_btn_register_clicked() {
    QString username = ui.username_reg->text();
    QString email = ui.email_reg->text();
    QString gender = ui.male_radio_btn->isChecked() ? "male" : ui.female_radio_btn->isChecked() ? "Female" : "";
    QString password = ui.password_reg->text();
    QString confirmPass = ui.confirm_password->text();
    QString picture;
    QString pic_ext;
    if (username == "") {
        app.message("Error", "Username isn't Validate", "Please Enter Your Username");
    }
    else if (email == "") {
        app.message("Error", "Email isn't Validate", "Please Enter Your Email");
    }
    else if (gender == "") {
        app.message("Error", "Gender isn't Validate", "Please Choose Your Gender");
    }
    else if (password == "") {
        app.message("Error", "Password isn't Validate", "Please Enter your Password");
    }
    else if (app.validateUsername(username) && app.validateEmail(email , true) && app.validatePassword(password) && confirmPassword(confirmPass, password)) {
        if (app.isUserExist(email)) {
            app.message("Error", "Email isn't Validate", "Email is Already Exist");
            return;
        }
        if (gender == "female") {
            picture = auth_imgs.value("girl")->getImageData();
            pic_ext = auth_imgs.value("girl")->getImageExt();
        }
        else {
            picture = auth_imgs.value("man")->getImageData();
            pic_ext = auth_imgs.value("man")->getImageExt();
        }
        AddNewUserData(username, email, password, gender, picture, pic_ext);
        clearRegister();
        clearLogin();
        ui.tabWidget->setCurrentIndex(1);
        app.message("Success", "Account is created succesfully", "");
    }
}

void Authentication::on_forgot_pass_btn_clicked() {
    bool ok;
    getEmail = new QInputDialog(this);
    getUsername = new QInputDialog(this);
    newPassword = new QInputDialog(this);
    QString email = getEmail->getText(this, "Enter your email",
        "The email:", QLineEdit::Normal,
        "", &ok);
    getEmail->setStyleSheet("QInputDialog{color:#fff;background-color:#333;}");
    if (!email.isEmpty()) {
        if (app.isUserExist(email)) {
            QString username = getUsername->getText(this, "Enter your username",
                "The username:", QLineEdit::Normal,
                "", &ok);
            getUsername->setStyleSheet("QInputDialog{color:#fff;background-color:#333;}");
            if (!username.isEmpty()) {
                QString id = getUserIdOfEmailAndUsername(email, username);
                if (id != "-1") {
                    QString newPass = newPassword->getText(this, "Enter New Password",
                        "New Password:", QLineEdit::Normal,
                        "", &ok);
                    newPassword->setStyleSheet("QInputDialog{color:#fff;background-color:#333;}");
                    if (!newPass.isEmpty()) {
                        app.changePasswaord(id, newPass);
                        app.message("Success", "Password is Updated Successfully", "");
                    }
                    else {
                        app.message("Error", "New Password is Empty", "Please Try Again");
                    }
                }
                else {
                    app.message("Error", "Username isn't Correct", "Please Try Again");
                }
            }
            else {
                app.message("Error", "Username is Empty", "Please Try Again");
            }
        }
        else {
            app.message("Error", "Email isn't Exist", "Please Try Again");
        }
    }
    else {
        app.message("Error", "Email is Empty", "Please Try Again");
    }
}

Authentication::~Authentication()
{}


