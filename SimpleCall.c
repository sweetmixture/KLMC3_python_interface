#include <Python.h>

int main() {
    // Initialize the Python interpreter
    Py_Initialize();

	PyObject *sysPath = PySys_GetObject("path"); // get python module search path list
	/*
		return sys.path // Return value: Borrowed reference.
		A list of strings that specifies the search path for modules. Initialized from the environment variable PYTHONPATH, plus an installation-dependent default.
	*/
                 //list   index 
	PyList_Insert(sysPath, 0, PyUnicode_DecodeFSDefault("/work/e05/e05/wkjee/Software/gulpklmc/CPython"));
	/*
		add search path to the sysPath
		> this step looks very essential otherwise C side cannot find a custom module (unless default installed, e.g., using pip)
	*/

    PyObject *pModule = PyImport_ImportModule("my_python_module"); // Here, 'pModule' is a new (strong) reference
    /*
		 Import the Python module from the search path "sysPath" - now including the newly added path in line 13
	*/

    if (pModule == NULL) {
		printf("Module Found Err\n");
		Py_XDECREF(pModule); // release pModule reference
        PyErr_Print();
        Py_Finalize();
        return 1; // Exit with an error code
    }

    PyObject *pFunc = PyObject_GetAttrString(pModule, "my_python_function"); // Here, 'pFunc' is a new (strong) reference
    /*
		 Get a reference to the Python function (in the module)
	*/

    if (!PyCallable_Check(pFunc)) { // check if pFunc is a callable
		printf("Function Found Err\n");
		Py_XDECREF(pFunc);
        PyErr_Print();
        Py_Finalize();
        return 1; // Exit with an error code
    }

    // Call the Python function
    PyObject_CallObject(pFunc, NULL);


	Py_XDECREF(pModule);
	Py_XDECREF(pFunc);
    // Finalize the Python interpreter
    Py_Finalize();

    return 0; // Exit successfully
}
