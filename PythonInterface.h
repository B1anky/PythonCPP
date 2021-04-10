#ifndef PYTHONINTERFACE_H
#define PYTHONINTERFACE_H

#include "PythonInterpreter.h"
#include <QPointer>

class PythonInterface{

public:

    PythonInterface();

    PythonInterpreter* m_pythonInterpreter;
    PyObject*          m_pythonModule;

};

#endif // PYTHONINTERFACE_H
