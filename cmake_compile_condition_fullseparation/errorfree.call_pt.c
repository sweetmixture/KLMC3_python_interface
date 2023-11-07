#include <stdio.h>

#ifdef __PYTHON
#include "python_interface.h"
#include <Python.h>

void PyInit(PyObject** sysPath, PyObject** pModule) {
    Py_Initialize();

    *sysPath = PySys_GetObject("path");
    PyList_Insert(*sysPath, 0, PyUnicode_DecodeFSDefault("/work/e05/e05/wkjee/Software/gulpklmc/CPython"));

    *pModule = PyImport_ImportModule("test_module");

    if (*pModule == NULL) {
        PyErr_Print();
        Py_Finalize();
        return;
    }

    return;
}

void PyFinal(PyObject* sysPath, PyObject* pModule) {
    Py_XDECREF(sysPath);
    Py_XDECREF(pModule);
    Py_Finalize();
}
#endif

int main() {

#ifdef __PYTHON
    PyObject* sysPath;
    PyObject* pModule;
    PyInit(&sysPath, &pModule);

    char* method = "random_gen";
    // bool call_python_serial(PyObject* pModule, const char* method_name);
    call_python_serial(pModule, method);

    printf("flagZero\n");
    PyFinal(sysPath, pModule);
    printf("flagZero\n");
#else
    printf("Python module is not loaded\n");
#endif
    return 0;
}

