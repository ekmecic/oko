#include "src/oko.h"
#include <QApplication>

int main(int argc, char* argv[]) {
  QApplication a(argc, argv);
  oko   w;
  w.show();

  return a.exec();
}
