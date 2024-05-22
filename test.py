import subprocess

def run_c_program_with_parameters(executable_path, parameters):
    # Run the executable file with parameters using subprocess
    process = subprocess.Popen([executable_path] + parameters, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    stdout, stderr = process.communicate()

    # Retrieve the value returned by the C program
    return_code = process.returncode

    return return_code, stdout.decode(), stderr.decode()

def get_New_Value(hex):
    # Display the input values
    # Path to the executable file
    executable_path = "./keymath.exe"

    # Parameters to pass to the executable
    parameters = [hex, "/", 2]

    # Run the C program with parameters
    res1, stdout, stderr = run_c_program_with_parameters(executable_path, parameters)

    # Parameters to pass to the executable
    parameters = [hex, "+", 1]

    # Run the C program with parameters
    res2, stdout, stderr = run_c_program_with_parameters(executable_path, parameters)

    int_res1 = int(res1, 16)
    int_res2 = int(res2, 16)

    # Add the integers
    res = int_num1 + int_num2

    # Convert the result back to a hexadecimal string
    hex_res = hex(res)

    parameters = [hex_res, "/", 2]

    # Run the C program with parameters
    res, stdout, stderr = run_c_program_with_parameters(executable_path, parameters)

    return res

value = input("Enter 32 byte hexadecimal value: ")
n = int(input("Enter times: ")) 

while count < n:
    # Your code here
    value = get_New_Value(value)
    print(value)