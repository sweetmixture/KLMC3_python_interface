#include <Python.h>

int main() {
	// Initialize Python interpreter
	Py_Initialize();

	PyObject* sysPath = PySys_GetObject("path");
	PyList_Insert(sysPath,0,PyUnicode_DecodeFSDefault("/work/e05/e05/wkjee/Software/gulpklmc/CPython"));

	// Example of importing and creating an instance of a Python class
	PyObject *pModule = PyImport_ImportModule("my_python_module");
	if (!pModule) {
		PyErr_Print();
		Py_Finalize();
		return 1;
	}

	PyObject *pClass = PyObject_GetAttrString(pModule, "MyClass"); // Get MyClass
	if (!pClass || !PyCallable_Check(pClass)) {
		PyErr_Print();
		Py_DECREF(pModule);
		Py_Finalize();
		return 1;
	}

	// Create an instance of the Python class (equivalent to calling MyClass())
	PyObject *pInstance = PyObject_CallObject(pClass, NULL); // New reference
	if (!pInstance) {
		PyErr_Print();
		Py_DECREF(pClass);
		Py_DECREF(pModule);
		Py_Finalize();
		return 1;
	}

	// Call the "add" method using PyObject_CallMethodObjArgs
	PyObject *pMethodName = PyUnicode_FromString("add"); // Method name as Python string
	PyObject *pArg1 = PyLong_FromLong(25);	// First argument (25)
	PyObject *pArg2 = PyLong_FromLong(-50); // Second argument (-50)

	// Call the method with two arguments
	PyObject *pResult = PyObject_CallMethodObjArgs(pInstance, pMethodName, pArg1, pArg2, NULL);

	if (!pResult) {
		PyErr_Print();
		Py_DECREF(pArg1);
		Py_DECREF(pArg2);
		Py_DECREF(pMethodName);
		Py_DECREF(pInstance);
		Py_DECREF(pClass);
		Py_DECREF(pModule);
		Py_Finalize();
		return 1;
	}

	// Clean up after calling the method
	Py_DECREF(pResult);
	Py_DECREF(pArg1);
	Py_DECREF(pArg2);
	Py_DECREF(pMethodName);

	// Optionally, call the 'get_result' method to get the result
	PyObject *pGetResult = PyUnicode_FromString("get_result");

	//PyObject *pFinalResult = PyObject_CallMethodObjArgs(pInstance, pGetResult, NULL); // no argument, specified by 'NULL'

	//PyObject *pFinalResult = PyObject_CallMethodOneArg(pInstance, pGetResult, NULL); // using CallMethodeOneArg()
	/*
		Error, 'NULL' argument cannot be used for NoArg case: i.e., the actual python class must take one argument, even if it is NULL

		$PyObject_CallMethodOneArg: Assertion `arg != NULL' failed. Aborted (core dumped)
	*/

	PyObject *pFinalResult = PyObject_CallMethodNoArgs(pInstance, pGetResult); // using CallMethodNoArgs()

	if (pFinalResult) {
		long result = PyLong_AsLong(pFinalResult);
		printf("Result of add: %ld\n", result); // Output should be -25
		Py_DECREF(pFinalResult);
	} else {
		PyErr_Print();
	}

	// Clean up
	Py_DECREF(pGetResult);
	Py_DECREF(pInstance);
	Py_DECREF(pClass);
	Py_DECREF(pModule);

	// Finalize the Python interpreter
	Py_Finalize();
	return 0; // Exit successfully
}

