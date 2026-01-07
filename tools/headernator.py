input_file = "blocks.json"
output_file = "blocks.h"

with open(input_file, "r") as file:
    content = file.read()

with open(output_file, "w") as file:
    file.write("#ifndef BLOCKS_H\n")
    file.write("#define BLOCKS_H\n\n")
    file.write('const char* myText = R"json(' + content + ')json";\n\n')
    file.write("#endif\n")

print("NOTE escape tokens must be manually removed")
