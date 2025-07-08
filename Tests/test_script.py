import subprocess

def run_inter(input_data):
    process = subprocess.Popen(
        ["C:\\Users\\q1112\\source\\repos\\PLPP-Assignment5\\Assignment5\\x64\\Debug\\Assignment5.exe"],
        stdin=subprocess.PIPE,
        stdout=subprocess.PIPE,
        stderr=subprocess.PIPE,
        text=True
    )
    stdout, stderr = process.communicate(input_data)
    return stdout.strip(), stderr.strip()

def test_inter():
    tests = [
        {
            "input": "5 + 4",
            "expected_output": "Enter expression: Result: 9"
        },
        {
            "input": "2+(3*4)",
            "expected_output": "Enter expression: Result: 14"
        },
        {
            "input": "(1 + 2) * (3 + 4)",
            "expected_output": "Enter expression: Result: 21"
        },
        {
            "input": "100 - 25 * (2 + 1)",
            "expected_output": "Enter expression: Result: 25"
        },
        {
            "input": "  42/  2 +6",
            "expected_output": "Enter expression: Result: 27"
        },
        {
            "input": "-5 + 3",
            "expected_output": "Enter expression: Result: -2"
        },
        {
            "input": "-(2 + 3)",
            "expected_output": "Enter expression: Result: -5"
        },
        {
            "input": "4 * -2",
            "expected_output": "Enter expression: Result: -8"
        },
        {
            "input": "-(1 + 2) * (3 - 4)",
            "expected_output": "Enter expression: Result: 3"
        },
        {
            "input": "-4 + -(-3)",
            "expected_output": "Enter expression: Result: -1"
        },
    ]
    for test in tests:
        input_data = test["input"]
        expected_output = test["expected_output"]

        output, error = run_inter(input_data)

        if error:
            print(f"Test failed for input:\n{input_data}")
            print(f"Error:\n{error}")
        elif output.strip() != expected_output:
            print(f"Test failed for input:\n{input_data}")
            print(f"Expected:\n{expected_output}")
            print(f"Got:\n{output}")
        else:
            print(f"Test passed for input:\n{input_data}")



if __name__ == "__main__":
    test_inter()
