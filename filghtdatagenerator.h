#ifndef FILGHTDATAGENERATOR_H
#define FILGHTDATAGENERATOR_H
#include <QGeoCoordinate>
#include <QRandomGenerator>
#include <QDateTime>
#include <QObject>
#include <QtDebug>
#include <algorithm>
#include <QTimer>

namespace FlightData{

    namespace Data{
        struct FlyData{
            QGeoCoordinate lastPosition;
            QGeoCoordinate startPoint, endPoint;
            double alt;
            double speed;
            double distanceToGoal;
        };

        struct WeatherData{
            int iconID;
            double temp;
            double humidity;
            double windSpeed;
            QString description;
        };

        struct Param{
            static constexpr int KM = 1000;
        };

    }

    namespace Generator{
        class FlightDataGenerator : public QObject
        {
            Q_OBJECT

            Q_PROPERTY(QGeoCoordinate lastPoint READ getPoint WRITE setPoint NOTIFY movePosition)   // main property which reacts for changes

            Q_PROPERTY(QGeoCoordinate startPoint READ getStartPos)
            Q_PROPERTY(QGeoCoordinate endPoint READ getLastPos)

            // property for weather
            Q_PROPERTY(double lat READ getLat NOTIFY movePosition)
            Q_PROPERTY(double lon READ getLon NOTIFY movePosition)
            Q_PROPERTY(double speed READ getSpeed NOTIFY movePosition)
            Q_PROPERTY(double distance READ getDistanceToEnd NOTIFY movePosition)
            Q_PROPERTY(double constDistance READ getDistanceToEnd)

            // property for weather
            Q_PROPERTY(int id READ getIconID NOTIFY weatherSignal)
            Q_PROPERTY(double temp READ getTemp NOTIFY weatherSignal)
            Q_PROPERTY(double hum READ getHumidity NOTIFY weatherSignal)
            Q_PROPERTY(QString desc READ getDescript NOTIFY weatherSignal)
            Q_PROPERTY(double wspeed READ getWindSpeed NOTIFY weatherSignal)

        public:
            // default constructor with 'Cracow' -> 'Gdansk' coordinates
            FlightDataGenerator(const QGeoCoordinate& firstPosition = QGeoCoordinate(50.0619474,19.9368564),
            const QGeoCoordinate& lastPosition = QGeoCoordinate(54.347628,18.6452029), QObject* parent = nullptr);
            // flyData getters
            double getLat() const { return flyData.lastPosition.latitude();  }
            double getLon() const { return flyData.lastPosition.longitude(); }
            double getAlt() const { return flyData.alt; }
            double getSpeed() const { return flyData.speed; }
            double getDistanceToEnd() const { return flyData.distanceToGoal; }
            // weather getters
            int getIconID() const { return weatherData.iconID; }
            double getTemp() const { return weatherData.temp; }
            double getHumidity() const { return weatherData.humidity; }
            QString getDescript() const { return weatherData.description; }
            double getWindSpeed() const { return weatherData.windSpeed; }
            // main setters
            void setPoint(const QGeoCoordinate& point);
            void setDistanceToPoint(const QGeoCoordinate& point);
            // getters
            inline QGeoCoordinate getPoint()    { return flyData.lastPosition; }
            inline QGeoCoordinate getStartPos() { return flyData.startPoint;   }
            inline QGeoCoordinate getLastPos()  { return flyData.endPoint;     }
        signals:
            void movePosition();
            void weatherSignal();
        public slots:
            void weatherDataGenerator();
        private:
            Data::FlyData flyData;
            Data::WeatherData weatherData;
            QTimer* weatherTimer;
        };

    }
}
#endif // FILGHTDATAGENERATOR_H
