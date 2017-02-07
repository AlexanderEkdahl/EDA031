#include "mns.h"
#include <algorithm>

void MNS::insert(const HostName& hostName, const IPAddress& ipAddress) {
  db.insert(make_pair(hostName, ipAddress));
}

bool MNS::remove(const HostName& hostName) {
  auto end = db.end();
  auto index = db.find(hostName);

  if (index == end) {
    return false;
  } else {
    db.erase(index);
    return true;
  }
}

IPAddress MNS::lookup(const HostName& hostName) const {
  auto index = db.find(hostName);

  if (index == db.end()) {
    return NON_EXISTING_ADDRESS;
  } else {
    return index->second;
  }
}
