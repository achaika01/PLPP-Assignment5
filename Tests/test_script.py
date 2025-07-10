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
            "input": "test\n5 + 4",
            "expected_output": "Enter expression: Result: 9"
        },
        {
            "input": "test\n2+(3*4)",
            "expected_output": "Enter expression: Result: 14"
        },
        {
            "input": "test\n(1 + 2) * (3 + 4)",
            "expected_output": "Enter expression: Result: 21"
        },
        {
            "input": "test\n100 - 25 * (2 + 1)",
            "expected_output": "Enter expression: Result: 25"
        },
        {
            "input": "test\n  42/  2 +6",
            "expected_output": "Enter expression: Result: 27"
        },
        {
            "input": "test\n-5 + 3",
            "expected_output": "Enter expression: Result: -2"
        },
        {
            "input": "test\n-(2 + 3)",
            "expected_output": "Enter expression: Result: -5"
        },
        {
            "input": "test\n4 * -2",
            "expected_output": "Enter expression: Result: -8"
        },
        {
            "input": "test\n-(1 + 2) * (3 - 4)",
            "expected_output": "Enter expression: Result: 3"
        },
        {
            "input": "test\n-4 + -(-3)",
            "expected_output": "Enter expression: Result: -1"
        },
        {
            "input": "test\npow(2, 3)",
            "expected_output": "Enter expression: Result: 8"
        },
        {
            "input": "test\npow(5, 0)",
            "expected_output": "Enter expression: Result: 1"
        },
        {
            "input": "test\nabs(-10)",
            "expected_output": "Enter expression: Result: 10"
        },
        {
            "input": "test\nabs(7)",
            "expected_output": "Enter expression: Result: 7"
        },
        {
            "input": "test\nmax(3, 4)",
            "expected_output": "Enter expression: Result: 4"
        },
        {
            "input": "test\nmax(-5, -2)",
            "expected_output": "Enter expression: Result: -2"
        },
        {
            "input": "test\nmin(3, 4)",
            "expected_output": "Enter expression: Result: 3"
        },
        {
            "input": "test\nmin(-5, -2)",
            "expected_output": "Enter expression: Result: -5"
        },
        {
            "input": "test\npow(2, 3) + abs(-4)",
            "expected_output": "Enter expression: Result: 12"
        },
        {
            "input": "test\nmax(5, min(3, 2))",
            "expected_output": "Enter expression: Result: 5"
        },
        {
            "input": "test\npow(2, 2) + pow(3, 2)",
            "expected_output": "Enter expression: Result: 13"
        },
        {
            "input": "test\nabs(-pow(2, 3))",
            "expected_output": "Enter expression: Result: 8"
        },
        {
            "input": "test\nmax(pow(2, 3), pow(3, 2))",
            "expected_output": "Enter expression: Result: 9"
        },
        {
            "input": "test\nmin(abs(-10), abs(5 - 15))",
            "expected_output": "Enter expression: Result: 10"
        },
        {
            "input": "test\nmax(2, min(3, 1)) + abs(-5)",
            "expected_output": "Enter expression: Result: 7"
        },
        {
            "input": "test\npow(2, 3) * min(4, 2)",
            "expected_output": "Enter expression: Result: 16"
        },
        {
            "input": "test\n-pow(2, 2) + abs(-3 * 2)",
            "expected_output": "Enter expression: Result: 2"
        },
        {
            "input": "test\nmin(max(1, 2), max(3, 4))",
            "expected_output": "Enter expression: Result: 2"
        },
        {
            "input": "test\npow(2, 2 + 1)",
            "expected_output": "Enter expression: Result: 8"
        },
        {
            "input": "test\npow(2, pow(1+1, 2))",
            "expected_output": "Enter expression: Result: 16"
        },
        {
            "input": "test\nmax(abs(-3), min(10, pow(2, 3)))",
            "expected_output": "Enter expression: Result: 8"
        },
        {
            "input": "test\nabs(-pow(2, 2) + min(5, 10))",
            "expected_output": "Enter expression: Result: 1"
        },
        {
            "input": "test\ndef sum(a,b) { a + b }\nsum(3,4)",
            "expected_output": "Enter expression: Result: 7"
        },
        {
            "input": "test\ndef square(x) { x * x }\nsquare(5)",
            "expected_output": "Enter expression: Result: 25"
        },
        {
            "input": "test\ndef complex(a,b) { min(a,b) + max(a,b) * 2 }\ncomplex(3,4)",
            "expected_output": "Enter expression: Result: 11"
        }
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
