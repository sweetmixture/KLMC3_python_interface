#include <Python.h>

void pass_data_to_python() {
	// Example string array in C
	const char* str_array[] = {"string1", "string2", "string3"};

	// Example 10x3 double array in C
	double double_2d_array[10][3] = {
		{1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}, {7.0, 8.0, 9.0},
		{10.0, 11.0, 12.0}, {13.0, 14.0, 15.0}, {16.0, 17.0, 18.0},
		{19.0, 20.0, 21.0}, {22.0, 23.0, 24.0}, {25.0, 26.0, 27.0},
		{28.0, 29.0, 30.0}
	};

	// ---- Create Python List for String Array ----
	PyObject* py_str_list = PyList_New(3);	// Create a new Python list with 3 elements

	for (int i = 0; i < 3; i++) {

		// Create a Python string object from each C string
		PyObject* py_str = PyUnicode_FromString(str_array[i]);
		if (py_str == NULL) {
			PyErr_Print();
			return;  // Handle error if PyUnicode_FromString fails
		}
		// Set the Python string object in the list
		PyList_SetItem(py_str_list, i, py_str);  // This transfers ownership, no need to Py_DECREF py_str // 'py_str' reference expire here
	}

	// ---- Create Python List for 2D Double Array (10x3) ----
	PyObject* py_2d_list = PyList_New(10);	// Create a list with 10 elements (each will be a sublist)
	for (int i = 0; i < 10; i++) {
		// Create a sublist for each row
		PyObject* py_row_list = PyList_New(3);	// Each row has 3 elements
		for (int j = 0; j < 3; j++) {
			// Create a Python float object for each double in the row
			PyObject* py_double = PyFloat_FromDouble(double_2d_array[i][j]);
			if (py_double == NULL) {
				PyErr_Print();
				return;  // Handle error if PyFloat_FromDouble fails
			}
			// Set the Python float object in the row list
			PyList_SetItem(py_row_list, j, py_double);	// Transfers ownership, no need to Py_DECREF
		}
		// Set the row list in the 2D list
		PyList_SetItem(py_2d_list, i, py_row_list);  // Transfers ownership, no need to Py_DECREF
	}

	// At this point, both py_str_list and py_2d_list are strong references to Python objects
	// You can now pass these to a Python function or module

	// Example: Printing them in Python
	//PyObject* sys = PyImport_ImportModule("sys");
	//if (sys != NULL) {
	//	  PyObject* py_stdout = PyObject_GetAttrString(sys, "stdout");
	//	  if (py_stdout != NULL) {
	//		  PyObject* print_function = PyObject_GetAttrString(PyImport_ImportModule("builtins"), "print");

	//		  if (print_function && PyCallable_Check(print_function)) {
	//			  // Print the string list
	//			  PyObject_CallFunctionObjArgs(print_function, py_str_list, NULL);
	//			  // Print the 2D double list
	//			  PyObject_CallFunctionObjArgs(print_function, py_2d_list, NULL);
	//		  }
	//		  Py_XDECREF(print_function);
	//		  Py_XDECREF(py_stdout);
	//	  }
	//	  Py_XDECREF(sys);
	//}


	PyObject *sysPath = PySys_GetObject("path"); // get python module search path list // Borrowed reference
	PyList_Insert(sysPath, 0, PyUnicode_DecodeFSDefault("/work/e05/e05/wkjee/Software/gulpklmc/CPython/Application1_data_handling"));

	// ---- Import Python Module and Call Python Function ----
	PyObject* pModule = PyImport_ImportModule("print_lists"); // New reference

	if (pModule != NULL) {
		PyObject* pFunc = PyObject_GetAttrString(pModule, "print_lists");
		if (pFunc && PyCallable_Check(pFunc)) {
			// Call the Python function and pass the lists as arguments
			PyObject* pArgs = PyTuple_Pack(2, py_str_list, py_2d_list);
			PyObject* pValue = PyObject_CallObject(pFunc, pArgs);
			if (pValue == NULL) {
				PyErr_Print();
			}
			Py_XDECREF(pValue);
			Py_DECREF(pArgs);
		}
		Py_XDECREF(pFunc);
		Py_DECREF(pModule);
	} else {
		PyErr_Print();
	}


	// ---- Clean up strong references (Py_DECREF when done with them) ----
	Py_DECREF(py_str_list);
	Py_DECREF(py_2d_list);
}

int main(int argc, char *argv[]) {
	// Initialize the Python interpreter
	Py_Initialize();

	// Pass the data to Python
	pass_data_to_python();

	// Finalize the Python interpreter
	Py_Finalize();
	return 0;
}

