#ifndef RESTCLIENTMANAGER_H
#define RESTCLIENTMANAGER_H

#include "restclientinterface.h"
#include "telemetryjsonmanager.h"
#include <QTimer>
#include <memory>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QEventLoop>


namespace REST {

    namespace Client{

        class RESTClientManager: public RESTClientInterface {
            Q_OBJECT
        public:
            RESTClientManager(QObject* parent = nullptr);

            bool establishConnection(const QUrl& endAddress) override;
            void runGETRequests() final;
            void stopGETRequests() final;
            void setRequestsInterval(unsigned int peroid) override;

            //static QByteArray getRESTServerRequest(const QUrl& endpoint);
        private slots:
            void _requestFinished(QNetworkReply* reply);
            void _sslErrors      (QNetworkReply *reply, const QList<QSslError> &errors);
        private:
            void                   setConnections();
            QTimer*                _requestTimer;
            QNetworkAccessManager* _networkManager;
            QNetworkRequest        _networkRequest;
            QUrl                   _endpoint;
            unsigned int           _requestInterval;
            bool                   _connectionEstablished;
        };

    }

    namespace ClientAuthorization{

        class RESTAuthorizator: public QObject{
        public:
            RESTAuthorizator(QObject* parent = nullptr);

            static QByteArray getRESTServerRequest(const QUrl& endpoint);

        private:
            static std::unique_ptr<QNetworkAccessManager> authManager;
            static QByteArray authArray;
        };
    }
}
#endif // RESTCLIENTMANAGER_H
