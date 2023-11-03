# my_python_module.py

import numpy as np

def my_python_function():
    print("this is in python")
    print("this is the second message")
    return "Hello from Python!"

def return_integer_and_double():
    # Integer value
    integer_value = 42
    # Double value
    double_value = 3.14159

    return integer_value, double_value

#def add_two_integers(a,b):
#	a = np.array(a)
#	b = np.array(b)
#	res = a+b
#	print('this is python interface')
#	print(res,type(res))
#	print('end python interface')
#	return res

class MyClass:
    def __init__(self):
        self.result = 0
    
    def add(self, a, b):
        self.result = a + b
    
    def get_result(self):
        return self.result


def add_two_integers(a,b):

	calc = MyClass()
	calc.add(a,b)

	with open('file_name.txt','w') as f:

		f.write(f'{calc.get_result()}\n')
		f.write('end of python interface\n')
	
	with open('file_name.txt','r') as f:

		print(' ------ readline')
		for line in f:
			print(line,end='')

	return calc.get_result()

if __name__ == "__main__":
    print("This is the main module.")
