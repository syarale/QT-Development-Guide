#include <iostream>
#include <QApplication>

#include "string_list_model_demo.h"

#pragma comment(lib, "user32.lib")

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  StringListModelDemo w;
  w.show();
  return a.exec();
}