#include "vns.h"
#include <algorithm>

void VNS::insert(const HostName& hostName, const IPAddress& ipAddress) {
  db.push_back(make_pair(hostName, ipAddress));
}

bool VNS::remove(const HostName& hostName) {
  auto end = db.end();
  auto index =
      find_if(db.begin(), end, [hostName](std::pair<HostName, IPAddress> p) {
        return p.first == hostName;
      });
  if (index == end) {
    return false;
  } else {
    db.erase(index);
    return true;
  }
}

IPAddress VNS::lookup(const HostName& hostName) const {
  auto begin = db.begin();
  auto end = db.end();
  auto index =
      find_if(begin, end, [hostName](std::pair<HostName, IPAddress> p) {
        return p.first == hostName;
      });
  if (index == end) {
    return NON_EXISTING_ADDRESS;
  } else {
    return db.at(distance(begin, index)).second;
  }
}
