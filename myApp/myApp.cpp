#include "myApp.h"

myApp::myApp(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    DB = QSqlDatabase::addDatabase("QSQLITE");
    DB.setDatabaseName("./database/db.sqlite");
    if (!DB.open()) {
        QMessageBox::information(this, "Not Connection", "Database is not Connected");
    }
    gen_imgs = getGeneralImagesFromDB();
}

QMap<QString, Image*> myApp::getGeneralImagesFromDB() {
    if (gen_imgs.size() > 0) {
        return gen_imgs;
    }
    QMap<QString, Image*> images;
    DB.open();
    QSqlQuery query(DB);
    query.prepare("SELECT * FROM GENERAL_IMGS");
    if (query.exec()) {
        while (query.next()) {
            Image* image = new Image(query.value("id").toString(), query.value("image_data").toString(), query.value("image_ext").toString(), query.value("image_name").toString());
            images.insert(query.value("image_name").toString(), image);
        }
    }
    DB.close();
    return images;
}

bool myApp::isUserExist(QString emailOrUsername) {
    DB.open();
    QSqlQuery query(DB);
    if (validateEmail(emailOrUsername)) {
        query.prepare("SELECT EMAIL FROM USERS WHERE EMAIL = :EMAIL");
        query.bindValue(":EMAIL", emailOrUsername);
    }
    else {
        query.prepare("SELECT USERNAME FROM USERS WHERE USERNAME = :USERNAME");
        query.bindValue(":USERNAME", emailOrUsername);
    }
    if (query.exec()) {
        while (query.next()) {
            return true;
        }
    }
    DB.close();
    return false;
}

QString myApp::getPasswordByEmailOrUsername(QString emailOrUsername) {
    DB.open();
    QSqlQuery query(DB);
    QString password = "";
    if (validateEmail(emailOrUsername)) {
        query.prepare("SELECT PASSWORD FROM USERS WHERE EMAIL = :EMAIL");
        query.bindValue(":EMAIL", emailOrUsername);
    }
    else {
        query.prepare("SELECT PASSWORD FROM USERS WHERE USERNAME = :USERNAME");
        query.bindValue(":USERNAME", emailOrUsername);
    }
    if (query.exec()) {
        while (query.next()) {
            password = query.value(0).toString();
            return password;
        }
    }
    DB.close();
    return password;
}

QString myApp::getUserIdByEmailOrUsername(QString emailOrUsername) {
    DB.open();
    QSqlQuery query(DB);
    QString id = "";
    if (validateEmail(emailOrUsername)) {
        query.prepare("SELECT ID FROM USERS WHERE EMAIL = :EMAIL");
        query.bindValue(":EMAIL", emailOrUsername);
    }
    else {
        query.prepare("SELECT ID FROM USERS WHERE USERNAME = :USERNAME");
        query.bindValue(":USERNAME", emailOrUsername);
    }
    if (query.exec()) {
        while (query.next()) {
            id = query.value(0).toString();
            return id;
        }
    }
    DB.close();
    return id;
}

void myApp::changePasswaord(QString id, QString newPass) {
    DB.open();
    QSqlQuery query(DB);
    query.prepare("UPDATE USERS SET PASSWORD = :NEWPASSWORD WHERE ID = :ID");
    query.bindValue(":NEWPASSWORD", newPass);
    query.bindValue(":ID", id);
    query.exec();
    DB.close();
}

bool myApp::validateUsername(QString username) {
    if (isUserExist(username)) {
        message("Error", "Username isn't Validate", "Username is already Token");
        return false;
    }
    return true;
}

bool myApp::validateEmail(QString email , bool msg) {
    const regex pattern(
        "(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+");
    bool valid = regex_match(email.toStdString(), pattern);
    if (!valid && msg) {
        message("Error", "Email isn't Validate", "Please Enter Correct Email");
    }
    return valid;
}

bool myApp::validatePassword(QString password) {
    if (password == "") {
        message("Error", "Password isn't Validate", "Please Enter your Password");
        return false;
    }
    if (password.length() < 8) {
        message("Error", "Password isn't Validate", "Password is 8 Character at Least");
        return false;
    }
    return true;
}

QString myApp::openBrowser() {
    QString imagePath = QFileDialog::getOpenFileName(this, tr("Select Image"), QCoreApplication::applicationDirPath(), tr("*.JPG , *.PNG , *.JFIF ,*.GIF ,*.SVG"));
    return imagePath;
}

int myApp::message(string title, string text, string infoText) {
    QPixmap icon;
    if (title == "Success") {
        icon = convertImageDataToImageView(QByteArray::fromBase64(QVariant::fromValue(gen_imgs.value("success")->getImageData()).toByteArray()), gen_imgs.value("success")->getImageExt().toStdString().c_str());
    }
    else if (title == "Error") {
        icon = convertImageDataToImageView(QByteArray::fromBase64(QVariant::fromValue(gen_imgs.value("error")->getImageData()).toByteArray()), gen_imgs.value("error")->getImageExt().toStdString().c_str());
    }
    else {
        icon = convertImageDataToImageView(QByteArray::fromBase64(QVariant::fromValue(gen_imgs.value("question")->getImageData()).toByteArray()), gen_imgs.value("question")->getImageExt().toStdString().c_str());
    }
    QMessageBox msg;
    msg.setWindowTitle(QString::fromStdString("Newspaper Message"));
    msg.setText(QString::fromStdString(text));
    msg.setInformativeText(QString::fromStdString(infoText));
    msg.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    msg.setDefaultButton(QMessageBox::Ok);
    msg.setWindowIcon(convertImageDataToImageView(QByteArray::fromBase64(QVariant::fromValue(gen_imgs.value("logo")->getImageData()).toByteArray()), gen_imgs.value("logo")->getImageExt().toStdString().c_str()));
    msg.setIconPixmap(icon.scaled(25, 25));
    msg.setFont(QFont("Tahoma"));
    msg.setStyleSheet("QMessageBox{background-color:#333;color:#fff;} QMessageBox QLabel{color:#fff;} QPushButton{background-color:#037ef3;color:#fff;border-radius:8px;padding:10px;}QPushButton::hover{background-color:#0099e5;}");
    return msg.exec();
}

QPixmap myApp::convertImageDataToImageView(QByteArray imageData, const char* format) {
    QPixmap imageView;
    imageView.loadFromData(imageData, format);
    return imageView;
}

QByteArray myApp::convertImageViewToImageData(QString imagePath) {
    QFileInfo fi(imagePath);
    string ext = fi.completeSuffix().toStdString();
    for (int i = 0; i < ext.length(); i++) {
        ext[i] = toupper(ext[i]);
    }
    const char* format = ext.c_str();
    QPixmap image(imagePath);
    QBuffer imageBufferData;
    if (imageBufferData.open(QIODevice::ReadWrite)) {
        image.save(&imageBufferData, format);
    }
    QByteArray finaleDataToSave = imageBufferData.buffer().toBase64();
    return finaleDataToSave;
}




myApp::~myApp()
{}
