# print_lists.py

def print_lists(string_list, double_2d_list):

	print(' * * * In Python Interface * * *')

	# Print the string list
	print("String List:")
	print(string_list)

	# Print the 2D double list
	print("2D Double Array:")
	for row in double_2d_list:
		print(row)


# modify_and_return.py
def modify_and_return_2d_array(double_2d_list):
	# Add +5 to each element in the 2D double list
	modified_list = [[element + 5 for element in row] for row in double_2d_list]
	
	# Return the modified 2D array
	return modified_list
