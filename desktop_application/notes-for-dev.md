To compile the project in developer mode,

in main.cpp		define DEV_MODE_SKIP_LOGIN		1: dev mode, 0: user mode
in httpmanager.h	define DEV_MODE_USE_PRETAKEN_TOKEN	1: dev mode, 0: user mode
in networkcore.h	define DEV_MODE_USE_LOCAL_HOST		1: dev mode, 0: user mode


HTTP status codes returned by API
for API_LOGIN_ADDRESS
	POST request
		200 OK, email password match, returns token with code: UserFound
		400 Bad Request, no email or password, returns with code: BadRequest
		404 Not Found, email doesnot match, returns with code: NoUserFound
		404 Not Found, password doesnot match, returns with code: IncorrectPassword
 for API_REGISTER_ADDRESS
 	POST request
		201 Created
		400 Bad Request, returns with code: BadRequest
for API_FETCH_ADDRESS && API_PUSH_ADDRESS
	GET request
		200 OK, token verified
		204 No Content, first time login
		401 Unauthorized, token verify failed
		403 Forbidden, no token given
	PUT request
		200 OK, token verified
		401 Unauthorized, token verify failed
		403 Forbidden, no token given

