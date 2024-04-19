#ifndef MVC_PATTERN_OBSERVER_H_
#define MVC_PATTERN_OBSERVER_H_

#include <list>
#include <memory>
#include <string>

struct DataInfo {
  std::string name = "";
  int32_t id = 0;
  DataInfo(std::string str, uint32_t num) : name(str), id(num){};
};

class Observer {
 public:
  virtual void OnDataUpdate(const DataInfo& info) = 0;
};
using ObserverPtr = std::shared_ptr<Observer>;

class Observable {
 public:
  void Register(ObserverPtr observer) { observers_.push_back(observer); }

  void Unregister(ObserverPtr observer) {
    for (auto it = observers_.begin(); it != observers_.end(); it++) {
      ObserverPtr obs = (*it).lock();
      if (obs != nullptr && obs == observer) {
        observers_.erase(it);
        break;  // it has expired
      }
    }
    std::cout << "[INFO] Unregister observer successed." << std::endl;
  }

  void Notify(DataInfo info) {
    for (auto it = observers_.begin(); it != observers_.end(); it++) {
      ObserverPtr obs = (*it).lock();
      if (obs) {
        obs->OnDataUpdate(info);
      }
    }
  }

 private:
  std::list<std::weak_ptr<Observer>> observers_;
};

#endif  // MVC_PATTERN_OBSERVER_H_