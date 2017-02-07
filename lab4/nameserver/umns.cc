#include "umns.h"
#include <utility>
#include <algorithm>

void UMNS::insert(const HostName& hostName, const IPAddress& ipAddress) {
  db.insert(make_pair(hostName, ipAddress));
}

bool UMNS::remove(const HostName& hostName) {
  auto end = db.end();
  auto index = db.find(hostName);
  if (index == end) {
    return false;
  } else {
    db.erase(index);
    return true;
  }
}

IPAddress UMNS::lookup(const HostName& hostName) const {
  auto index = db.find(hostName);
  if (index == db.end()) {
    return NON_EXISTING_ADDRESS;
  } else {
    return index->second;
  }
}
