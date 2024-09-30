#include <Python.h>
#include <stdio.h>

void pass_data_to_python() {
	// Example 10x3 double array in C
	double double_2d_array[10][3] = {
		{1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}, {7.0, 8.0, 9.0},
		{10.0, 11.0, 12.0}, {13.0, 14.0, 15.0}, {16.0, 17.0, 18.0},
		{19.0, 20.0, 21.0}, {22.0, 23.0, 24.0}, {25.0, 26.0, 27.0},
		{28.0, 29.0, 30.0}
	};

	// ---- Create Python List for 2D Double Array (10x3) ----
	PyObject* py_2d_list = PyList_New(10);	// Create a list with 10 elements (each will be a sublist)
	for (int i = 0; i < 10; i++) {
		PyObject* py_row_list = PyList_New(3);	// Each row has 3 elements
		for (int j = 0; j < 3; j++) {
			PyObject* py_double = PyFloat_FromDouble(double_2d_array[i][j]);
			if (py_double == NULL) {
				PyErr_Print();
				return;  // Handle error if PyFloat_FromDouble fails
			}
			PyList_SetItem(py_row_list, j, py_double);
		}
		PyList_SetItem(py_2d_list, i, py_row_list);
	}

	PyObject *sysPath = PySys_GetObject("path"); // get python module search path list
	PyList_Insert(sysPath, 0, PyUnicode_DecodeFSDefault("/work/e05/e05/wkjee/Software/gulpklmc/CPython/Application1_data_handling"));

	// ---- Import Python Module and Call Python Function ----
	PyObject* pModule = PyImport_ImportModule("print_lists");  // Import modify_and_return_2d_array function
	if (pModule != NULL) {
		PyObject* pFunc = PyObject_GetAttrString(pModule, "modify_and_return_2d_array");
		if (pFunc && PyCallable_Check(pFunc)) {
			// Call the Python function and pass the 2D list
			PyObject* pArgs = PyTuple_Pack(1, py_2d_list);	// Prepare arguments
			PyObject* pValue = PyObject_CallObject(pFunc, pArgs);  // Call the Python function
			Py_DECREF(pArgs);  // Clean up pArgs reference

			if (pValue != NULL) {
				// ---- Extract the modified 2D array back in C ----
				for (int i = 0; i < 10; i++) {
					PyObject* py_row = PyList_GetItem(pValue, i);  // Get each row
					if (PyList_Check(py_row)) {
						for (int j = 0; j < 3; j++) {
							PyObject* py_double = PyList_GetItem(py_row, j);  // Get each element
							double value = PyFloat_AsDouble(py_double);  // Convert Python float to C double
							if (PyErr_Occurred()) {
								PyErr_Print();
								return;
							}
							printf("Element [%d][%d] = %f\n", i, j, value);  // Print the modified value
						}
					}
				}
				Py_DECREF(pValue);	// Clean up pValue reference
			} else {
				PyErr_Print();	// Handle error if Python function call failed
			}
		}
		Py_XDECREF(pFunc);
		Py_DECREF(pModule);
	} else {
		PyErr_Print();	// Handle error if module import failed
	}

	// ---- Clean up strong references ----
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
