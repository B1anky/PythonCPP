#include "PythonInterface.h"
#include <iostream>

PythonInterface::PythonInterface(){

    //Makes an instance of an interpreter (e.g. with the specified folder as the taregt directory, so pointing to your __init__.py)
    m_pythonInterpreter = new PythonInterpreter("./pythonFiles/");

    //This is how you would make an instance for a particular file / module
    m_pythonModule = m_pythonInterpreter->createReusablePythonModule("numbers");

    std::string getNumberAsStdString("");
    int val(0);
    bool getNumberSuccessful = m_pythonInterpreter->callPythonModuleFunction(m_pythonModule, "getInstanceValue", Py_BuildValue("()"), getNumberAsStdString);

    if(getNumberSuccessful){

       std::cout << "numbers.py::getInstanceValue() = " << getNumberAsStdString << std::endl;
       val = std::stoi(getNumberAsStdString);

    }else{

        std::cerr << "Error. Call to python module failed." << std::endl;

    }

    std::string voidRet("");
    m_pythonInterpreter->callPythonModuleFunction(m_pythonModule, "addToInstance", Py_BuildValue("(i)", 20), voidRet);

    std::string getNumberAsStdStringAfterAddNumber("");
    getNumberSuccessful = m_pythonInterpreter->callPythonModuleFunction(m_pythonModule, "getInstanceValue", Py_BuildValue("()"), getNumberAsStdStringAfterAddNumber);

    if(getNumberSuccessful){

       std::cout << "numbers.py::getInstanceValue() = " << getNumberAsStdStringAfterAddNumber << std::endl;
       val += std::stoi(getNumberAsStdStringAfterAddNumber);

    }else{

        std::cerr << "Error. Call to python module failed." << std::endl;

    }

    std::cout << val << std::endl;

}
