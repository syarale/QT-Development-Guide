#ifndef MVC_PATTERN_VIEW_H_
#define MVC_PATTERN_VIEW_H_

#include <iostream>
#include <memory>

#include "observer.h"

class PersonView {
 public:
  virtual void PrintInfo(const DataInfo& info) = 0;
};
using PersonViewPtr = std::shared_ptr<PersonView>;

class StudentView : public PersonView {
 public:
  void PrintInfo(const DataInfo& info) override { PrintStudentInfo(info); }

 private:
  void PrintStudentInfo(const DataInfo& info) {
    std::cout << "[INFO] Student infomation, name: " << info.name
              << ", id: " << info.id << std::endl;
  }
};
using StudentViewPtr = std::shared_ptr<StudentView>;

class TeacherView : public PersonView {
 public:
  void PrintInfo(const DataInfo& info) override { PrintTeachertInfo(info); }

 private:
  void PrintTeachertInfo(const DataInfo& info) {
    std::cout << "[INFO] Teacher infomation, name: " << info.name
              << ", id: " << info.id << std::endl;
  }
};
using TeacherViewPtr = std::shared_ptr<TeacherView>;

#endif  // MVC_PATTERN_VIEW_H_
