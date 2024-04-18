#ifndef MVC_PATTERN_CONTROLLER_H_
#define MVC_PATTERN_CONTROLLER_H_

#include <memory>

#include "observer.h"
#include "model.h"
#include "view.h"

class Controller : public Observer {
 public:
  Controller(PersonModelPtr model, PersonViewPtr view)
      : person_model_(model), person_view_(view) {}

  void OnDataUpdate(const DataInfo& info) { person_view_->PrintInfo(info); }
  void SetDataInfo(const DataInfo& info) { person_model_->SetInfo(info); }

 private:
  PersonModelPtr person_model_;
  PersonViewPtr person_view_;
};
using ControllerPtr = std::shared_ptr<Controller>;

#endif  // MVC_PATTERN_CONTROLLER_H_