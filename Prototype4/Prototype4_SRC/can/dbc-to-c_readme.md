# Convert dbc-file to C-structs, enums and functions

This explains how to convert dbc-file to C-files using python script. Python needs to be installed first, then run: pip install cantools

## Convert dbc-file to C-structs, enums and functions
Right click on the file: **cmc_can.dbc** in VS Code and select: "Open with integratied terminal".

The filename must not be changed, as the generated .h and .c file and structs will have the same name or name prefix as the dbc-file.

Type the following command in the terminal: 

* cantools generate_c_source cmc_can_message.dbc

This will generate the files: **cmc_can_message.h** and **cmc_can_message.c**. 

## Include the generated files in your project
Copy / replace the files into the folder **Core\Inc** and **Core\Src** of the project.

