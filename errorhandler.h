#ifndef ErrorManager_H
#define ErrorManager_H

#include <QObject>
#include <QJsonParseError>
#include <QDebug>
#include <QSslError>
#include <QNetworkReply>

class ErrorHandler{
public:
    static int errorCtr;
    virtual void showErrorMessage() const = 0;                              // - qDebug error message | method of abstract class
    virtual void showErrorMessage(const QString& message) const = 0;
    virtual QString getErrorMessage() const = 0;                            // - return error message | method of abstract class
    virtual ~ErrorHandler(){}
};


class ErrorManager : public QObject, public ErrorHandler
{
    Q_OBJECT
public:
    enum class JSONErrors {EMPTY = 1, JSON, DEFAULT };                      // - default - no error occured
    enum class RequestErrors {REPLY = 1, SSL, DEFAULT};                     // - default - no error occured
public:
    explicit ErrorManager(JSONErrors state = JSONErrors::DEFAULT,RequestErrors req = RequestErrors::DEFAULT,
                          const QJsonParseError& err = QJsonParseError(),QNetworkReply* reply = nullptr,
                          QObject *parent = nullptr);


    void showErrorMessage() const override;
    void showErrorMessage(const QString& message) const override;           // - overload method
    QString getErrorMessage() const override;
    void errorJSONValidator(const ErrorManager::JSONErrors& type, const QJsonParseError& e);
    void errorRequestValidator(RequestErrors type, QNetworkReply* reply, const QList<QSslError>& list = QList<QSslError>());
    void setJsonParseError(const QJsonParseError& e);
    QVector<QString> listConverter();
    Q_INVOKABLE void ignoreRequestErrors();                                 // - ignore button action
signals:
    /* QML service not require */ void sendJSONErrors(const QString& err);
    /* QML service require     */ void sendRequestError(const QString& err);                          // - signal with error information to show in alerts box (send to frontend)
    /* QML service require     */ void sendSslVector(const QVector<QString>& data);                   // - signal with pack of ssl errors


private:
    QJsonParseError error;
    JSONErrors JStype;
    RequestErrors reType;
    QNetworkReply* rpl;
    QList<QSslError> sslList;
};

#endif // ErrorManager_H
