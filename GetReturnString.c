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
    PyObject *pValue = PyObject_CallObject(pFunc, NULL);

    // Check if the function call was successful
    if (pValue != NULL) {
        // Convert the Python return value to a C string
        const char *result = PyUnicode_AsUTF8(pValue);
        printf("Python function returned: %s\n", result);

        // Release the Python object reference
        Py_DECREF(pValue);
    } else {
        PyErr_Print();
    }

    // Finalize the Python interpreter
    Py_Finalize();

    return 0; // Exit successfully
}
