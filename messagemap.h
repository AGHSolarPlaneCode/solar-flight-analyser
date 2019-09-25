#ifndef MESSAGEMAP_H
#define MESSAGEMAP_H

#include <QDebug>
#include <map>
#include <QString>
#include "notifyenums.h"

// # TODO LIST #
// 1. QSingleShot to erase deprecated alerts
// 2. Method to store actual number how many given type messages are there
// 3. Own for_each friend function to send data


namespace IDGenerator{ // generate unique ID for erasing objects
    QByteArray generateUniqueID(){
        return QByteArray();
    }
}

template<typename MType, typename MAlert>
class MessageMap
{
public:
    using messPair = std::pair<MType, MAlert>;
    using initList = std::initializer_list<std::pair<const MType, MAlert>>;
    using mapIter  = typename std::multimap<MType,MAlert>::iterator;

    MessageMap() {}
    MessageMap(const std::multimap<MType, MAlert>& cpyMessage): messages(cpyMessage) {}
    MessageMap(const initList& initMessages): messages(initMessages) {}
    MessageMap(const mapIter& first, const mapIter& last): messages(first, last) {}

    MessageMap(const MessageMap<MType, MAlert>& mMap): messages(mMap.messages) {}
    MessageMap<MType, MAlert>& operator=(const MessageMap<MType, MAlert>& mMap);

    mapIter insertMessage(const messPair& mPair);  // give unique ID to del
    mapIter insertMessage(const MType& fType, const MAlert& mAlert);

    bool   contains(const messPair& conMessage);
    bool   contains(const MType& fType, const MAlert& mAlert);

    mapIter findByKey(const MType& key);
    mapIter findByValue(const MAlert& value);
    mapIter findByMessage(const messPair& message);

    size_t  uniqueKeyCount(const MType& key);   // how many massages of given 'key' are contained
    size_t  size() const;

    //MAlert& operator[](const MType& key);

    friend QDebug operator<<(QDebug debug, const MessageMap& mMap);

private:
    std::multimap<MType, MAlert> messages;
};

template<typename MType, typename MAlert>
MessageMap<MType, MAlert>& MessageMap<MType, MAlert>::operator=(const MessageMap<MType, MAlert>& mMap){
    if(this == &mMap)
        return *this;

    // send deprecated datas to frontend
    messages.clear();
    messages = mMap.messages;

    return *this;
}




#endif // MESSAGEMAP_H
