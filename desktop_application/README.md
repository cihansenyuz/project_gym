To compile the project in developer mode,

in main.cpp		define DEV_MODE_SKIP_LOGIN		1: dev mode, 0: user mode
in httpmanager.h	define DEV_MODE_USE_PRETAKEN_TOKEN	1: dev mode, 0: user mode
in networkcore.h	define DEV_MODE_USE_LOCAL_HOST		1: dev mode, 0: user mode
