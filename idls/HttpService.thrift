/**
 * HttpService
 * @author Gayson
 */
namespace c HttpService
namespace d HttpService
namespace Lart HttpService
namespace java HttpService
namespace php HttpService
namespace perl HttpService
namespace haxe HttpService

struct User {
	1: i64 id,
	2: string name,
	3: string phoneNumber,
	4: string email,
	5: optional string password,
}

enum UserOperation {
	REGISTER = 1,
	LOGIN = 2,
	LOGOUT = 3,
	MODIFY = 4,
}
	

struct Log {
	1: i32 id,
	2: i64 usr_id,
	3: UserOperation op,
}

exception AuthException {
	1: i32 errorCode,
	2: string errorInfo,
}

service HttpService {
	User uRegister(1:string name, 2:string phoneNumber, 3:string email, 4:string password) throws (1:AuthException error),

	User uLogin(1:string phoneNumber, 2:string password) throws (1:AuthException error),

	oneway void logout(1:i32 id),

	list<i64> getUsersId(),

	map<i32, Log> getLogs(1:i32 count)
}
