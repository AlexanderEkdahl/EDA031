#include "hns.h"
#include "iostream"

HNS::HNS(int size) { db.resize(size); }

void HNS::insert(const HostName& hostName, const IPAddress& ipAddress) {
  std::pair<HostName, IPAddress> p = std::make_pair(hostName, ipAddress);

  // Rehash all contents
  if (++nbr_of_elements >= db.size() / 2) {
    std::vector<std::vector<std::pair<HostName, IPAddress>>> new_db;
    new_db.resize(2 * db.size());
    for (auto vector : db) {
      for (auto pair : vector) {
        new_db[hasher(pair.first) % new_db.size()].push_back(pair);
      }
    }
    db = new_db;
  }

  db[hasher(p.first) % db.size()].push_back(p);
}

bool HNS::remove(const HostName& hostName) {
  size_t index = hasher(hostName) % db.size();
  auto& vector = db[index];

  auto it = std::find_if(vector.begin(), vector.end(),
                         [hostName](std::pair<HostName, IPAddress> p) {
                           return p.first == hostName;
                         });
  if (it != vector.end()) {
    vector.erase(it);
    nbr_of_elements--;
    return true;
  } else {
    return false;
  }
}

IPAddress HNS::lookup(const HostName& hostName) const {
  size_t index = hasher(hostName) % db.size();
  auto vector = db[index];
  auto begin = vector.begin();
  auto end = vector.end();
  auto it =
      std::find_if(begin, end, [hostName](std::pair<HostName, IPAddress> p) {
        return p.first == hostName;
      });
  if (it != end) {
    return vector[std::distance(begin, it)].second;
  } else {
    return NON_EXISTING_ADDRESS;
  }
}
