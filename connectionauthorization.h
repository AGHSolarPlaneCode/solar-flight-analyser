#ifndef CONNECTIONAUTHORIZATION_H
#define CONNECTIONAUTHORIZATION_H
#include <QUrl>

namespace {
    struct Authorization{
        QUrl address = QUrl();
        bool connectionState = false;
        bool dataValidation = false;
    };
}

#endif // CONNECTIONAUTHORIZATION_H
