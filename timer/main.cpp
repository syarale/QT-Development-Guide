#include "timer.h"
#include <iostream>
#include <QApplication>

#pragma comment(lib, "user32.lib")


int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  Timer w;
  w.show();
  return a.exec();
}