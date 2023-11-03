#include <Python.h>

int main() {
    // Initialize the Python interpreter
    Py_Initialize();


    // Import the Python module
	// PySys_SetPath("/work/e05/e05/wkjee/Software/gulpklmc/CPython");
    // PyObject *pModule = PyImport_ImportModule("my_python_module");
    // PyObject *pModule = PyImport_ImportModule("/work/e05/e05/wkjee/Software/gulpklmc/CPython/my_python_module");

	// const char *modulePath = "/work/e05/e05/wkjee/Software/gulpklmc/CPython/my_python_module.py";
	PyObject *sysPath = PySys_GetObject("path");
	PyList_Insert(sysPath, 0, PyUnicode_DecodeFSDefault("/work/e05/e05/wkjee/Software/gulpklmc/CPython"));
    PyObject *pModule = PyImport_ImportModule("my_python_module");
    if (pModule == NULL) {
        printf("Module Found Err\n");
        PyErr_Print();
        Py_Finalize();
        return 1; // Exit with an error code
    }
	printf(" ------ module loaded\n");

    // Get a reference to the Python function
    PyObject *pFunc = PyObject_GetAttrString(pModule, "return_integer_and_double");
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

	if( PyTuple_Check(pValue) && PyTuple_Size(pValue) == 2 ){

		PyObject* pInteger = PyTuple_GetItem(pValue,0);
		PyObject* pDouble = PyTuple_GetItem(pValue,1);

		const long integer_result = PyLong_AsLong(pInteger);
		const double double_result = PyFloat_AsDouble(pDouble);

		printf("Python Integer result : %ld\n",integer_result);
		printf("Python Double  result : %lf\n",double_result);
	}
        //const char *result = PyUnicode_AsUTF8(pValue);
        //printf("Python function returned: %s\n", result);

        // Release the Python object reference
        Py_DECREF(pValue);
    } else {
        PyErr_Print();
    }

    // Finalize the Python interpreter
    Py_Finalize();

    return 0; // Exit successfully
}
