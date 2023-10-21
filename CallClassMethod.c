#include <Python.h>

int main() {
    // Initialize the Python interpreter
    Py_Initialize();

    // Import the Python module
    PyObject *pModule = PyImport_ImportModule("my_python_module");
    if (pModule == NULL) {
        PyErr_Print();
        Py_Finalize();
        return 1; // Exit with an error code
    }

    // Get a reference to the Python class (MyClass)
    PyObject *pClass = PyObject_GetAttrString(pModule, "MyClass");
    if (!PyCallable_Check(pClass)) {
        PyErr_Print();
        Py_Finalize();
        return 1; // Exit with an error code
    }

    // Create an instance of the Python class
    PyObject *pInstance = PyObject_CallObject(pClass, NULL);
    if (pInstance == NULL) {
        PyErr_Print();
        Py_Finalize();
        return 1; // Exit with an error code
    }

    // Call the "add" method of the class
    // "ii" -> fisrt i: integer, second i: integer
    PyObject_CallMethod(pInstance, "add", "ii", 25, -50);

    // Call the "get_result" method to retrieve the result
    PyObject *pResult = PyObject_CallMethod(pInstance, "get_result", NULL);
    if (pResult != NULL) {
        int result = PyLong_AsLong(pResult);
        printf("Result from Python: %d\n", result);
        Py_DECREF(pResult);
    } else {
        PyErr_Print();
    }

    // Finalize the Python interpreter
    Py_Finalize();

    return 0; // Exit successfully
}
