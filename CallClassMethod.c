#include <Python.h>

int main() {
    // Initialize the Python interpreter
    Py_Initialize();

	// Setting Python Module Path
	PyObject* sysPath = PySys_GetObject("path"); // get python module serach path list; Borrowed reference; Return <pythonList>
	//PyList_Insert(sysPath,0,"/work/e05/e05/wkjee/Software/gulpklmc/CPython"); // char* "..." is not PyObject* need to be converted > at least warning invoked
	PyList_Insert(sysPath,0,PyUnicode_DecodeFSDefault("/work/e05/e05/wkjee/Software/gulpklmc/CPython"));

    // Import the Python module
    PyObject *pModule = PyImport_ImportModule("my_python_module"); // import python module 'my_python_module.py'; New reference
    if (pModule == NULL) {
        PyErr_Print();
        Py_Finalize();
        return 1; // Exit with an error code
    }

    // Get a reference to the Python class (MyClass)
    PyObject *pClass = PyObject_GetAttrString(pModule, "MyClass"); // get class from module 'my_python_module.py'; New reference
    if (!PyCallable_Check(pClass)) {
        PyErr_Print();
        Py_Finalize();
        return 1; // Exit with an error code
    }

    // Create an instance of the Python class; class is a callable
    PyObject *pInstance = PyObject_CallObject(pClass, NULL); // New reference
    if (pInstance == NULL) {
        PyErr_Print();
        Py_Finalize();
        return 1; // Exit with an error code
    }

    // Call the "add" method of the class
    // "ii" -> fisrt i: integer, second i: integer
    PyObject_CallMethod(pInstance, "add", "ii", 25, -50);

    // Call the "get_result" method to retrieve the result
    PyObject *pResult = PyObject_CallMethod(pInstance, "get_result", NULL); // New reference
    if (pResult != NULL) {
        int result = PyLong_AsLong(pResult);
        printf("Result from Python: %d\n", result);
        Py_DECREF(pResult);
    } else {
        PyErr_Print();
    }

	// DECREF All
	Py_XDECREF(pModule);
	Py_XDECREF(pClass);
	Py_XDECREF(pInstance);
	Py_XDECREF(pResult);


    // Finalize the Python interpreter
    Py_Finalize();

    return 0; // Exit successfully
}
