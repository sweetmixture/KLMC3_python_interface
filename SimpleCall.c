#include <Python.h>

int main() {
    // Initialize the Python interpreter
    Py_Initialize();

    // Import the Python module
    PyObject *pModule = PyImport_ImportModule("my_python_module");
    if (pModule == NULL) {
	printf("Module Found Err\n");
        PyErr_Print();
        Py_Finalize();
        return 1; // Exit with an error code
    }

    // Get a reference to the Python function
    PyObject *pFunc = PyObject_GetAttrString(pModule, "my_python_function");
    if (!PyCallable_Check(pFunc)) {
	printf("Function Found Err\n");
        PyErr_Print();
        Py_Finalize();
        return 1; // Exit with an error code
    }

    // Call the Python function
    PyObject_CallObject(pFunc, NULL);

    // Finalize the Python interpreter
    Py_Finalize();

    return 0; // Exit successfully
}
