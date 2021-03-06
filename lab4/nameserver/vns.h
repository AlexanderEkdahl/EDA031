#include <vector>
#include "nameserverinterface.h"

class VNS : public NameServerInterface {
 public:
  virtual void insert(const HostName&, const IPAddress&);
  virtual bool remove(const HostName&);
  virtual IPAddress lookup(const HostName&) const;

 private:
  std::vector<std::pair<HostName, IPAddress>> db;
};
