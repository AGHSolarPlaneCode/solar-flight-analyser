#ifndef FILGHTDATAGENERATOR_H
#define FILGHTDATAGENERATOR_H
#include <QGeoCoordinate>
#include <QObject>

namespace FlightData{
    namespace Data{
        struct FlyData{
            QGeoCoordinate lastPosition;
            QGeoCoordinate startPoint, endPoint;
            double alt;
            double speed;
        };

        struct WeatherData{
            int iconID;
            double temp;
        };

    }

    namespace Generator{
        class FlightDataGenerator : public QObject
        {
            Q_OBJECT
            Q_PROPERTY(QGeoCoordinate lastPoint READ getPoint WRITE setPoint NOTIFY movePosition)
            Q_PROPERTY(QGeoCoordinate startPoint READ getStartPos)
            Q_PROPERTY(QGeoCoordinate endPoint READ getLastPos)

            Q_PROPERTY(double lat READ getLat NOTIFY movePosition)
            Q_PROPERTY(double lon READ getLon NOTIFY movePosition)
            Q_PROPERTY(double speed READ getSpeed NOTIFY movePosition)
        public:
            // default constructor with 'Cracow' -> 'Gdansk' coordinates
            FlightDataGenerator(const QGeoCoordinate& firstPosition = QGeoCoordinate(50.0619474,19.9368564),
            const QGeoCoordinate& lastPosition = QGeoCoordinate(54.347628,18.6452029), QObject* parent = nullptr);

            double getLat()   { return flyData.lastPosition.latitude();  }
            double getLon()   { return flyData.lastPosition.longitude(); }
            double getAlt()   { return flyData.alt;   }
            double getSpeed() { return flyData.speed; }
            // main setter
            void setPoint(const QGeoCoordinate& point);
            // getters
            inline QGeoCoordinate getPoint()    { return flyData.lastPosition; }
            inline QGeoCoordinate getStartPos() { return flyData.startPoint;   }
            inline QGeoCoordinate getLastPos()  { return flyData.endPoint;     }

        signals:
            void movePosition();
        public slots:

        private:
            // method to generate
            void generateData();
            Data::FlyData flyData;
            Data::WeatherData weatherData;
        };

    }
}
#endif // FILGHTDATAGENERATOR_H
