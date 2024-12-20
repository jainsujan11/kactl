"""
 * Author: AlooParatha
 * Description: stress testing script for competitive programming
 """

import random
import os
from tqdm import tqdm
def generate():
    with open("input.txt", "w") as f:
        test_cases = 1
        f.write(str(test_cases) + "\n")
        n = 100
        f.write(str(n) + "\n")
        a = [i for i in range(1, n + 1)] * 2
        # shuffle the list
        random.shuffle(a)
        # write the shuffled list to the file
        f.write(" ".join(map(str, a)) + "\n")
        # now tree has 2n nodes so print 2n-1 lines
        for i in range(2 * n - 1):
            f.write(str(i+2) + " " + str(random.randint(1, i+1)) + "\n")
def main():
    # Compile before program starts
    # Write input and execute the compiled program
    for i in tqdm(range(1000)):
        generate()
        run_command = "\"d:\\C++_Program\\help\""
        return_code = os.system(run_command)
        if return_code != 0:
            print("Runtime Error")
            break
        run_brute = "\"d:\\C++_Program\\help_brute\""
        return_code = os.system(run_brute)
        if return_code != 0:
            print("Runtime Error")
            break
        # Compare the output of the two programs
        with open("output.txt") as f1, open("output_brute.txt") as f2:
            if f1.read() != f2.read():
                print("Wrong Answer")
                break
if __name__ == "__main__":
    main()