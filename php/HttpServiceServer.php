<?php

namespace HttpService\php;

require_once 'setting.php';
require_once $THRIFT_CLASSLOADER;

use Thrift\ClassLoader\ThriftClassLoader;

$loader = new ThriftClassLoader();

$loader->registerNamespace('Thrift', $THRIFT_LIB_DIR);
$loader->registerDefinition('HttpService', $GEN_PHP_DIR);

$loader->register();

use Thrift\Protocol\TBinaryProtocol;
use Thrift\Transport\TMemoryBuffer;
use Thrift\Transport\TPhpStream;

use Thrift\Transport\TBufferedTransport;
use Thrift\Exception\TException;


class HttpServiceHandler implements \HttpService\HttpServiceIf {
	protected $logs = array();
	protected $users = array();

	public function uRegister($name, $phoneNumber, $email, $password) {
		echo "register";
		if (array_key_exists($phoneNumber, $this->users)) {
			$ae = new \HttpService\AuthException();
			$ae->errorCode = 500;
			$ae->errorInfo = "user exists";
			throw $ae;
		}
		$newUser = new \HttpService\User();
		$newUser->id = count($this->users);
		$newUser->name = $name;
		$newUser->phoneNumber = $phoneNumber;
		$newUser->email = $email;
		$newUser->password = $password;
		$this->users[$phoneNumber] = $newUser;

		$this->writeLog($newUser->id, \HttpService\UserOperation::REGISTER);

		return $newUser;
	}


	public function uLogin($phoneNumber, $password) {
		if (array_key_exists($phoneNumber, $this->users)) {
			return $this->users[phoneNumber];
		}

		$ae = new \HttpService\AuthException();
		$ae->errorCode = 501;
		$ae->errorInfo = "user non-exists";

		$this->writeLog($this->users[$phoneNumber]->id, \HttpService\UserOperation::LOGIN);

		throw $ae;
	}

	public function logout($id) {
		$this->writeLog($id, \HttpService\UserOperation::LOGOUT);
		echo "id: $id logout";
	}

	public function getUsersId() {
		$res = array();
		foreach ($this->users as $key => $user) {
			$res[] = $user->id;
		}
		return $res;
	}

	public function writeLog($usr_id, $op) {
		$log = new \HttpService\Log();
		$log->id = count($this->logs);
		$log->usr_id = $usr_id;
		$log->op = $op;
		$this->logs[$log->id] = $log;

		echo "operation: $log->op, user: $log->usr_id";

	}


	public function getLogs($count) {
		$res = array_reverse($this->logs);
		$res = array_slice($res, 0, $count);

	}
}

// start server
//

header('Content-Type', 'application/x-thrift');
if (php_sapi_name() == 'cli') {
	echo "\r\n";
}


$handler = new HttpServiceHandler();
$processor = new \HttpService\HttpServiceProcessor($handler);

$transport = new TBufferedTransport(new TPhpStream(TPhpStream::MODE_R | TPhpStream::MODE_W));
$protocol = new TBinaryProtocol($transport, true, true);

$transport->open();
$processor->process($protocol, $protocol);
$transport->close();

