# Convert dbc-file to C-structs, enums and functions

This explains how to convert dbc-file to C-files using python script. Python needs to be installed first, then run: pip install cantools

## Convert dbc-file to C-structs, enums and functions
Right click on the file: **cmc_can.dbc** in VS Code and select: "Open with integratied terminal".

The filename must not be changed, as the generated .h and .c file and structs will have the same name or name prefix as the dbc-file.

Type the following command in the terminal: 

### Copy to terminal
cantools generate_c_source cmc_can_message.dbc
Copy-Item cmc_can_message.c ..\Core\Src\can\
Copy-Item cmc_can_message.h ..\Core\Inc\can\
echo "done"

This will generate the files: **cmc_can_message.h** and **cmc_can_message.c** and
copy and replace the files into the folder **Core\Inc\can\** and **Core\Src\can\** of the project by runnin this in the termial:

### Important notes
Remember to edit the generated file: **cmc_can_message.c** and change the include statement from:

```c
#include "cmc_can_message.h"
```

to 

```c
#include "can/cmc_can_message.h"
```

