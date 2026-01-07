import sys
import re


def __main__():
    fin = "blocks.txt"
    fout = "blocks.json"

    if len(sys.argv) > 2:
        fout = sys.argv[2]
    if len(sys.argv) > 1:
        fin = sys.argv[1]

    with open(fout, "w") as out:
        out.write("{\n")
        with open(fin, "r") as file:
            counter = 0
            line = file.readline().rstrip()
            while line:
                char = line
                if len(char) != 1:
                    print("Invalid character line size for: " + str(counter))
                    exit(-1)

                arr = [line]
                for _ in range(5):
                    counter += 1
                    line = file.readline().replace("\n", "")
                    if not line:  # End of file check
                        break
                    if len(line) != 5:
                        print("Wrong line size at: " + str(counter))
                        exit(-1)
                    arr.append(line)

                if len(arr) != 6:
                    print("Incomplete character block for: " + str(counter))
                    exit(-1)

                out.write(f'\t"{char}": "')

                binary_str = ""
                for i in range(1, 6):
                    binary_str += arr[i].replace(" ", "0")
                    binary_str = re.sub(r"[^0]", "1", binary_str)

                out.write(binary_str + '",\n')

                counter += 1
                line = file.readline().rstrip()

            out.write("}\n")


if __name__ == "__main__":
    __main__()
