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

use Thrift\Transport\THttpClient;
use Thrift\Transport\TBufferedTransport;
use Thrift\Transport\TPhpStream;
use Thrift\Exception\TException;

try{
	//$socket = new THttpClient($LOCAL_IP, $SERVER_PORT, '/php/HttpServiceServer.php');
	$transport = new TBufferedTransport(new TPhpStream(TPhpStream::MODE_R | TPhpStream::MODE_W));
	$protocol = new TBinaryProtocol($transport);
	$client = new \HttpService\HttpServiceClient($protocol);

	$transport->open();

	$userName = 'foo';
	$userTel = 'ph';
	$email = 'e';
	$password = 'p';

	for ($i = 0; $i < 10; $i++) {
		$tempName = $userName + (string)$i;
		$tempTel = $userTel + (string)$i;
		$tempEmail = $email + (string)$i;
		$tempPassword = $password + (string)$i;

		$user = $client->uRegister($tempName, $tempTel, $tempEmail, $tempPassword);
		echo "$user->id, $user->name, $user->phoneNumber, $user->email\n";
	}

	//$client->uRegister('foo0', 'ph0', 'e0', 'p0');
	//$client->uLogin('ph0', 'p0');

	//foreach ($client->getUsersId() as $val) {
	//print "id: $val\n";
	//}

	//foreach ($client->getLogs(5) as $key => $log) {
	//print "id: $key, op: ".$log->op.", user_id: ".$log->usr_id."\n";
	//}

	$transport->close();
} catch (TException $tx) {
	print 'TException: '.$tx->getMessage()."\n";
}

