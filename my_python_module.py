# my_python_module.py

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

def add_two_integers(a,b):
    return a + b

class MyClass:
    def __init__(self):
        self.result = 0
    
    def add(self, a, b):
        self.result = a + b
    
    def get_result(self):
        return self.result

if __name__ == "__main__":
    print("This is the main module.")
