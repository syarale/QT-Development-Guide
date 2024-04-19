#include <iostream>
#include <memory>

#include "controller.h"
#include "observer.h"
#include "model.h"
#include "view.h"

int main() {
  std::cout << "hello..." << std::endl;
  StudentViewPtr student_view = std::make_shared<StudentView>();
  TeacherViewPtr teacher_view = std::make_shared<TeacherView>();
  PersonModelPtr person_model = std::make_shared<PersonModel>("Tom", 1999);

  ControllerPtr student_controller(new Controller(person_model, student_view));
  ControllerPtr teacher_controller(new Controller(person_model, teacher_view));

  person_model->Register(student_controller);
  person_model->Register(teacher_controller);

  student_controller->SetDataInfo({"LingLing", 20});
  std::cout << "------------------------\n" << std::endl;

  teacher_controller->SetDataInfo({"DaMing", 30});
  std::cout << "------------------------\n" << std::endl;

  person_model->SetInfo({"Lucy", 33});
  std::cout << "------------------------\n" << std::endl;

  person_model->SetInfo({"Tom", 99});
  std::cout << "------------------------\n" << std::endl;

  person_model->Unregister(student_controller);
  person_model->Unregister(teacher_controller);
  person_model->SetInfo({"Jack", 39});
  std::cout << "*******************************\n" << std::endl;

  return 0;
}