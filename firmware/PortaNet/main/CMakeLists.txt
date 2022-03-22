idf_component_register(SRCS
"main.c"
"interfaces/ApInterface.c"
"controllers/ApController.c"
"interfaces/DisplayInterface.c"
"controllers/DisplayController.c"
"interfaces/TerminalInterface.c"
"controllers/TerminalController.c"
"drivers/flags.c"
"drivers/flash.c"
"drivers/i2c.c"
"drivers/uart.c"
INCLUDE_DIRS ".")
