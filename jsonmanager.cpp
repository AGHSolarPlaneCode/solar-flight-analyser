#include "jsonmanager.h"

JSONManager::JSONManager(QObject *parent) : QObject(parent), get(GET_STATE::WAITING)
  ,json_state(JSON_STATE::UNPARSED)
{

}
