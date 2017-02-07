#include <map>
#include "nameserverinterface.h"

class MNS : public NameServerInterface {
 public:
  virtual void insert(const HostName&, const IPAddress&);
  virtual bool remove(const HostName&);
  virtual IPAddress lookup(const HostName&) const;

 private:
  std::map<HostName, IPAddress> db;
};
