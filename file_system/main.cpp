#include <iostream>
#include <QApplication>
#include "file_system.h"

#pragma comment(lib, "user32.lib")

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  FileSystem w;
  w.show();
  return a.exec();
}