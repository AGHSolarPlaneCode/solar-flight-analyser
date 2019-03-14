//#ifndef WEATHERDATA_H
//#define WEATHERDATA_H
//#include <QObject>
//#include <QTimer>
//#include <QString>
//#include "weatherdatastruct.h"


//class WeatherData: public QObject
//{
//    Q_OBJECT
//    Q_PROPERTY(int lon READ lon WRITE lon NOTIFY locationChanged)
//    Q_PROPERTY(int lat READ lat WRITE lat NOTIFY locationChanged)
//    Q_PROPERTY(int id READ id WRITE id NOTIFY weatherChanged)
//    Q_PROPERTY(QString main READ main WRITE main NOTIFY weatherChanged)
//    Q_PROPERTY(QString description READ description WRITE description NOTIFY weatherChanged)
//    Q_PROPERTY(QString icon READ icon WRITE icon NOTIFY weatherChanged)
//    Q_PROPERTY(int temp READ temp WRITE temp NOTIFY weatherChanged)
//    Q_PROPERTY(int pressure READ pressure WRITE pressure NOTIFY weatherChanged)
//    Q_PROPERTY(int humidity READ humidity WRITE humidity NOTIFY weatherChanged)
//    Q_PROPERTY(int temp_min READ temp_min WRITE temp_min NOTIFY weatherChanged)
//    Q_PROPERTY(int temp_max READ temp_max WRITE temp_max NOTIFY weatherChanged)
//    Q_PROPERTY(int visibility READ visibility WRITE visibility NOTIFY weatherChanged)
//    Q_PROPERTY(int speed READ speed WRITE speed NOTIFY weatherChanged)
//    Q_PROPERTY(int deg READ deg WRITE deg NOTIFY weatherChanged)
//    Q_PROPERTY(int all READ all WRITE all NOTIFY weatherChanged)
//    Q_PROPERTY(int dt READ dt WRITE dt NOTIFY weatherChanged)
//    Q_PROPERTY(QString country READ country WRITE country NOTIFY locationChanged)
//    Q_PROPERTY(QString name READ name WRITE name NOTIFY locationChanged)

//public:
//    explicit WeatherData(QObject* parent= nullptr);
//    void setWeatherData(Weather newWeather);

//    int lon() const;
//    int lat() const;
//    int id() const;
//    QString main() const;
//    QString description() const;
//    QString icon() const;
//    int temp() const;
//    int pressure() const;
//    int humidity() const;
//    int temp_min() const;
//    int temp_max() const;
//    int visibility() const;
//    int speed() const;
//    int deg() const;
//    int all() const;
//    int dt() const;
//    QString country() const;
//    QString name() const;

//signals:
//    void weatherDataChanged();

//public slots:
//    void weatherTimeout();
//private:
//    Weather data;
//    QTimer weatherTimer{this};
//};

//#endif // WEATHERDATA_H
