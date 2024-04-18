#ifndef MVC_PATTERN_MODEL_H_
#define MVC_PATTERN_MODEL_H_

#include <memory>
#include <string>

#include "observer.h"

class PersonModel : public Observable {
 public:
  PersonModel(std::string name = "Lucy", uint32_t id = 101)
      : name_(name), id_(id) {}

  void SetInfo(DataInfo info) {
    name_ = info.name;
    id_ = info.id;
    Notify({name_, id_});
  }

 private:
  std::string name_;
  uint32_t id_;
};
using PersonModelPtr = std::shared_ptr<PersonModel>;

#endif  // MVC_PATTERN_MODEL_H_