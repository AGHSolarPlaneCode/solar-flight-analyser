#ifndef JSONERROR_H
#define JSONERROR_H

#include <QObject>
#include <QJsonParseError>
#include <QDebug>

class ErrorHandler{
private:
    static int errorCtr;
public:
    virtual void showErrorMessage() const = 0;                              // - qDebug error message | method of abstract class
    virtual void showErrorMessage(const QString& message) const = 0;
    virtual QString getErrorMessage() const = 0;                            // - return error message | method of abstract class
    virtual ~ErrorHandler(){}
};

class JsonError : public QObject, public ErrorHandler
{
    Q_OBJECT
    //Q_DISABLE_COPY(JsonError)
public:
    enum class Errors {EMPTY = 1, JSON, DEFAULT };                          // - default - no error occured
public:
    explicit JsonError(Errors state = Errors::DEFAULT, const QJsonParseError& err = QJsonParseError(), QObject *parent = nullptr);
    JsonError(const JsonError& err);
    JsonError& operator=(JsonError&& err);
    void showErrorMessage() const override;
    void showErrorMessage(const QString& message) const override;           // - overload method
    QString getErrorMessage() const override;
    void errorValidator() const;
signals:
    void sendToFrontend(const QString& err) const;                          // - signal with error information to show in alerts box (send to frontend)
private:
    QJsonParseError error;
    Errors type;
};

#endif // JSONERROR_H
