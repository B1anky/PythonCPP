#ifndef PYTHONINTERPRETER_H
#define PYTHONINTERPRETER_H

#include <QObject>
#include <Python.h>

class PythonInterpreter : public QObject{

    Q_OBJECT

public:

    /*
     * This will setup the Python interprer to look at a certain folder path (i.e. ./scripts)
     * @PARAM const QString& pathToPythonFile - The path to the directory containing .py files
     */
    PythonInterpreter(const QString& pathToPythonFile);

    /*
     * This will take the file path to a .py file in the ./scripts folder and load it into the interpreter.
     * This one is better for using the same module over a number of calls (i.e. creating a listener to the web socket).
     * @PARAM const QString& pythonModuleFileName - The name of the file (i.e. "queryClient.py")
     */
    PyObject* createReusablePythonModule(const QString& pythonModuleFileName);

    /*
     * This will take a pythonModule that was previously imported and it'll call the function in it give the types of the
     * parameters and their values to they're translated to Python properly. The output is populated by reference so that
     * we can use a boolean for whether the call was successful. An unsuccessful call may be due to the Python module having
     * a syntax error, or there may be a typo or disparity between the paramTypes and values if a change is made on the Python-side.
     * It's up to the user to determine how they want to interpret the output, but this will return everything as a std::string for now.
     * @PARAM PyObject*      pythonModule - Python module that should've been instantiated from createReusablePythonModule(...)
     * @PARAM const QString& function     - The name of the function in the Python module you want to call
     * @PARAM const QString& paramTypes   - The types of the parameters of the python functions. Format details can be found here:
     *                                      https://docs.python.org/3/extending/extending.html ("Ctrl + f" for "Examples (to the left the call, to the right the resulting Python value):")
     *                                      More function details and documentation can be found here
     *                                      https://docs.python.org/3/c-api/object.html#c.PyObject_CallObject
     * @PARAM const QString& paramValues  - The values for the function that will be interpreted according to the paramTypes
     * @PARAM const QString& output       - The output, if any, for a call to the function
     */
    bool callPythonModuleFunction(PyObject* pythonModule, const QString& function, const QString& paramTypes, const QString& paramValues, std::string& output);


    bool callPythonModuleFunction(PyObject* pythonModule, const QString& function, PyObject* args, std::string& output);

    /*
     * This will be a helper function for calling something one time and not needing to keep the module open after the call is made.
     * This is good for one-time calls, such as seeding a lot of data, but only doing so once.
     * @PARAM const QString& pythonModuleFileName - The name of the file (i.e. "queryClient.py")
     * @PARAM PyObject*      pythonModule         - Python module that should've been instantiated from createReusablePythonModule(...)
     * @PARAM const QString& function             - The name of the function in the Python module you want to call
     * @PARAM const QString& paramTypes           - The types of the parameters of the python functions. Format details can be found here:
     *                                              https://docs.python.org/3/extending/extending.html ("Ctrl + f" for "Examples (to the left the call, to the right the resulting Python value):")
     *                                              More function details and documentation can be found here
     *                                              https://docs.python.org/3/c-api/object.html#c.PyObject_CallObject
     * @PARAM const QString& paramValues          - The values for the function that will be interpreted according to the paramTypes
     * @PARAM const QString& output               - The output, if any, for a call to the function
     */
    bool callStandAloneFunction(const QString& pythonModuleFileName, const QString& function, const QString& paramTypes, const QString& paramValues, std::string& output);

};

#endif // PYTHONINTERPRETER_H
