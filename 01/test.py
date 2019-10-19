import subprocess

def Test(expression, expected_result='0', return_code=0):
    output = subprocess.run(['./program', expression], stdout=subprocess.PIPE)
    result = output.stdout.decode('utf-8').strip()
    if output.returncode != return_code:
        print(f"У вас бага с выражением '{expression}', сэр!",
              f"Expected return code: {expected_result}, ",
              f"given return code: {output.returncode}")
    elif return_code == 0 and result != expected_result:
        print(f"У вас бага с выражением '{expression}', сэр!",
              f"Expected stdout: {expected_result}, "
              f"given stdout: {result}")

Test("10", "10")
Test("10 * 12", "120")
Test("2 +   2 *2", "6")
Test("1 + 1 +1+ 1  +- 1      -     1", "2")
Test("0 + 0", "0")
Test("2 * 2 * 2 * 2 * 2 * 2 + 1", "65")
Test("10000 / 0", return_code=255)
Test("", return_code=255)
Test("kek", return_code=255)
