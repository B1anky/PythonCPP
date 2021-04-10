#include "PythonInterpreter.h"
#include <QDebug>
#include <iostream>
#include <QPushButton>

PythonInterpreter::PythonInterpreter(const QString& pathToPythonFile){

    /*
     * Production::Note To allow debugger to work properly:
     * You must set in your environment variables on windows / linux for PYTHONHOME to be your python installation path
     * Additionally, you have to set your g++ kit up properly in QtCreator by going to:
     *   Tools -> Options -> Kits -> Select the kit you use (e.g. Desktop Qt5.15.0 MinGW64)
     *   Go down to the Environment row and click the "change" button on the right
     *   After a popup appears to set environment variables, add the line:
     *   PYTHONHOME=D:\\Python3-7-9 (or whatever your path is)
     *   Put your specific path you used for PYTHONHOME there, remember the double back slashes on Windows per directory
     *   This is necessary due to the fact that the compiler wants to source that particular variable for gdb and it overwrites ours,
     *   but we need it for the Python interpreter to work properly during runtime and debugging
     *
     */

    //Aids the program in looking at our local relative scripts folder for the .py files
    _putenv_s("PYTHONPATH", pathToPythonFile.toStdString().c_str());

    //Initialzes the python interpreter
    Py_Initialize();

}

PyObject* PythonInterpreter::createReusablePythonModule(const QString& pythonModuleFileName){

    //Formats the string for the .py file we want to load
    PyObject* pythonModuleString = PyUnicode_FromString(pythonModuleFileName.toStdString().c_str());

    //Loads the queryCLient.py file from the local relative scripts folder
    PyObject* pythonModule = PyImport_Import(pythonModuleString);

    return pythonModule;

}

bool PythonInterpreter::callPythonModuleFunction(PyObject* pythonModule, const QString& function, const QString& paramTypes, const QString& paramValues, std::string& output){

    bool successful = true;

    //pDict is a borrowed reference
    PyObject* pDict = PyModule_GetDict(pythonModule);

    //Get info from the python script
    PyObject* generateAllDataFromPythonFunc = PyDict_GetItemString(pDict, function.toStdString().c_str());

    PyObject* args = nullptr;

    if(PyCallable_Check(generateAllDataFromPythonFunc)){

        args = Py_BuildValue(paramTypes.toStdString().c_str(), paramValues.toStdString().c_str());

        PyObject* pythonReturnValue = PyObject_CallObject(generateAllDataFromPythonFunc, args);

        if(pythonReturnValue != nullptr){

            output = PyUnicode_AsUTF8(pythonReturnValue);

        }else{

            PyErr_Print();
            successful = false;

        }

    }else{

        PyErr_Print();
        successful = false;

    }

    return successful;

}

bool PythonInterpreter::callPythonModuleFunction(PyObject* pythonModule, const QString& function, PyObject* args, std::string& output){

    bool successful = true;

    //pDict is a borrowed reference
    PyObject* pDict = PyModule_GetDict(pythonModule);

    //Get info from the python script
    PyObject* generateAllDataFromPythonFunc = PyDict_GetItemString(pDict, function.toStdString().c_str());

    if(PyCallable_Check(generateAllDataFromPythonFunc)){

        PyObject* pythonReturnValue = PyObject_CallObject(generateAllDataFromPythonFunc, args);

        if(pythonReturnValue != nullptr){

            output = PyUnicode_AsUTF8(pythonReturnValue);

        }else{

            PyErr_Print();
            successful = false;

        }

    }else{

        PyErr_Print();
        successful = false;

    }

    return successful;

}

bool PythonInterpreter::callStandAloneFunction(const QString& pythonModuleFileName, const QString& function, const QString& paramTypes, const QString& paramValues, std::string& output){

    PyObject* pythonModule = createReusablePythonModule(pythonModuleFileName);

    return callPythonModuleFunction(pythonModule, function, paramTypes, paramValues, output);

}
