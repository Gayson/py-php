<?php

namespace DataServiceServer\php;

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

class CalculatorHandler implements \DataService\CalculatorIf{
	protected $logs= array();

	public function ping() {
		print 'ping request';
		return 'pong';
	}

	public function add($num1, $num2) {
		return $num1 + $num2;
	}

	public function calculate($logid, $work) {
	}
}
