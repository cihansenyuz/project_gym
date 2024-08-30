To compile the project in developer mode,

in CMakeLists.txt,
	provided DEV_MODE flag, the app will skip log in screen
	provided HOST="http://localhost:3000/", the app will send http requests to provided host
	provided TOKEN="blablabla", the app will use provided token for http request. Update it with a valid one.
	
target_compile_definitions(desktop_application PRIVATE DEV_MODE HOST="http://localhost:3000/" TOKEN="eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJlbWFpbCI6ImFkbWluIiwiaWQiOiIwIiwiaWF0IjoxNzI0NjQ3OTY2LCJleHAiOjE3MjQ2OTExNjZ9.Ew4Wxb3aJ2THurSLOKaq_eH6FjqFto0E6fA6rNQ8pPk")


HTTP status codes returned by API
for API_LOGIN_ADDRESS // login
	POST request
		200 OK, email password match, returns token with code: UserFound
		400 Bad Request, no email or password, returns with code: BadRequest
		404 Not Found, email doesnot match, returns with code: NoUserFound
		404 Not Found, password doesnot match, returns with code: IncorrectPassword
 for API_REGISTER_ADDRESS // register
 	POST request
		201 Created
		400 Bad Request, returns with code: BadRequest
for API_FETCH_ADDRESS && API_PUSH_ADDRESS // users
	GET request
		200 OK, token verified
		204 No Content, first time login
		401 Unauthorized, token verify failed
		403 Forbidden, no token given
	PUT request
		200 OK, token verified
		401 Unauthorized, token verify failed
		403 Forbidden, no token given

