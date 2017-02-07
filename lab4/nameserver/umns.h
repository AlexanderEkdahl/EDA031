#include <unordered_map>
#include "nameserverinterface.h"

class UMNS : public NameServerInterface {
 public:
  virtual void insert(const HostName&, const IPAddress&);
  virtual bool remove(const HostName&);
  virtual IPAddress lookup(const HostName&) const;

 private:
  std::unordered_map<HostName, IPAddress> db;
};
