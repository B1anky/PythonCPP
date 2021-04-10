#include <QApplication>
#include "PythonInterface.h"

int main(int argc, char *argv[]){
    QApplication a(argc, argv);

    PythonInterface interfaceExample;

    return a.exec();
}
