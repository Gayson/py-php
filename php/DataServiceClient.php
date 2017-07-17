<?php

namespace DataService\php;

require_once 'setting.php';
require_once $THRIFT_CLASSLOADER;

use Thrift\ClassLoader\ThriftClassLoader;

$loader = new ThriftClassLoader();
$loader->registerNamespace('Thrift', $THRIFT_LIB_DIR);
$loader->registerDefinition('shared', $GEN_PHP_DIR);
$loader->registerDefinition('DataService', $GEN_PHP_DIR);

$loader->register();

use Thrift\Protocol\TBinaryProtocol;
use Thrift\Transport\TSocket;
use Thrift\Transport\THttpClient;
use Thrift\Transport\TBufferedTransport;
use Thrift\Exception\TException;

try{
	if (array_search('--http', $argv)) {
		$socket = new THttpClient($LOCAL_IP, $SERVER_PORT, './DataServiceServer.php');
	} else {
		$socket = new TSocket($LOCAL_IP, $SERVER_PORT);
	}

	$transport = new TBufferedTransport($socket, 1024, 1024);
	$protocol = new TBinaryProtocol($transport);
	$client = new \DataService\CalculatorClient($protocol);

	$transport->open();

	print $client->ping()."\n";

	$work = new \DataService\Work();
	$arrNum1 = array(6, 6, 6);
	$arrNum2 = array(3, 0, 2);
	$ops = array(\DataService\Operation::DIVIDE, \DataService\Operation::DIVIDE, 6);
	$keys = array(1, 2, 3);

	for ($x = 0; $x < 3; $x++) {
		$work->num1 = $arrNum1[$x];
		$work->num2 = $arrNum2[$x];
		$work->op = $ops[$x];

		try {
			print $client->calculate($keys[$x], $work)."\n";
		} catch (\DataService\InvalidOperation $io) {
			print "Invalidation: $io->why\n";
		}
	}

	$log = $client->getStruct(1);
	print "Log: $log->value\n";

	$transport->close();
} catch (TException $tx) {
	print 'TException: '.$tx->getMessage()."\n";
}
