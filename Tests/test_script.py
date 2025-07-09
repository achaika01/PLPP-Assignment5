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
        {
            "input": "pow(2, 3)",
            "expected_output": "Enter expression: Result: 8"
        },
        {
            "input": "pow(5, 0)",
            "expected_output": "Enter expression: Result: 1"
        },
        {
            "input": "abs(-10)",
            "expected_output": "Enter expression: Result: 10"
        },
        {
            "input": "abs(7)",
            "expected_output": "Enter expression: Result: 7"
        },
        {
            "input": "max(3, 4)",
            "expected_output": "Enter expression: Result: 4"
        },
        {
            "input": "max(-5, -2)",
            "expected_output": "Enter expression: Result: -2"
        },
        {
            "input": "min(3, 4)",
            "expected_output": "Enter expression: Result: 3"
        },
        {
            "input": "min(-5, -2)",
            "expected_output": "Enter expression: Result: -5"
        },
        {
            "input": "pow(2, 3) + abs(-4)",
            "expected_output": "Enter expression: Result: 12"
        },
        {
            "input": "max(5, min(3, 2))",
            "expected_output": "Enter expression: Result: 5"
        },
        {
            "input": "pow(2, 2) + pow(3, 2)",
            "expected_output": "Enter expression: Result: 13"
        },
        {
            "input": "abs(-pow(2, 3))",
            "expected_output": "Enter expression: Result: 8"
        },
        {
            "input": "max(pow(2, 3), pow(3, 2))",
            "expected_output": "Enter expression: Result: 9"
        },
        {
            "input": "min(abs(-10), abs(5 - 15))",
            "expected_output": "Enter expression: Result: 10"
        },
        {
            "input": "max(2, min(3, 1)) + abs(-5)",
            "expected_output": "Enter expression: Result: 7"
        },
        {
            "input": "pow(2, 3) * min(4, 2)",
            "expected_output": "Enter expression: Result: 16"
        },
        {
            "input": "-pow(2, 2) + abs(-3 * 2)",
            "expected_output": "Enter expression: Result: 2"
        },
        {
            "input": "min(max(1, 2), max(3, 4))",
            "expected_output": "Enter expression: Result: 2"
        },
        {
            "input": "pow(2, 2 + 1)",
            "expected_output": "Enter expression: Result: 8"
        },
        {
            "input": "pow(2, pow(1+1, 2))",
            "expected_output": "Enter expression: Result: 16"
        },
        {
            "input": "max(abs(-3), min(10, pow(2, 3)))",
            "expected_output": "Enter expression: Result: 8"
        },
        {
            "input": "abs(-pow(2, 2) + min(5, 10))",
            "expected_output": "Enter expression: Result: 1"
        },
    ]
    for test in tests:
        input_data = test["input"]
        expected_output = test["expected_output"]

        output, error = run_inter(input_data)

        if error:
            print(f"\n!!!ERROR!!!!\nTest failed for input:\n{input_data}")
            print(f"\nError:\n{error}")
        elif output.strip() != expected_output:
            print(f"\n!!!ERROR!!!!\nTest failed for input:\n{input_data}")
            print(f"Expected:\n{expected_output}")
            print(f"Got:\n{output}")
        else:
            print(f"Test passed for input:\n{input_data}")



if __name__ == "__main__":
    test_inter()
