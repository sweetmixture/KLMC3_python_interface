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
    PyObject *pFunc = PyObject_GetAttrString(pModule, "add_two_integers");
    if (!PyCallable_Check(pFunc)) {
        printf("Function Found Err\n");
        PyErr_Print();
        Py_Finalize();
        return 1; // Exit with an error code
    }

    // Prepare the arguments as Python objects
    PyObject *pArgs = PyTuple_Pack(2, PyLong_FromLong(10), PyLong_FromLong(20));

    // Call the Python function with the arguments
    PyObject *pResult = PyObject_CallObject(pFunc, pArgs);

    // Check if the function call was successful
    if (pResult != NULL) {
        // Convert the Python result to a C long
        long sum_result = PyLong_AsLong(pResult);
        printf("Sum of two integers: %ld\n", sum_result);

        // Release the Python object references
        Py_DECREF(pArgs);
        Py_DECREF(pResult);
    } else {
        PyErr_Print();
    }

    // Finalize the Python interpreter
    Py_Finalize();

    return 0; // Exit successfully
}
