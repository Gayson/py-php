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

use Thrift\Factory\TBinaryProtocolFactory;
use Thrift\Factory\TTransportFactory;

use Thrift\Exception\TException;
use Thrift\Server\TServerSocket;
use Thrift\Server\TSimpleServer;

class CalculatorHandler implements \DataService\CalculatorIf{
	protected $logs= array();

	public function ping() {
		print 'ping request'; return 'pong';
	}

	public function add($num1, $num2) {
		return $num1 + $num2;
	}

	public function calculate($logid, \DataService\Work $w) {
		switch ($w->op) {
		case \DataService\Operation::ADD:
			$val = $w->num1 + $w->num2;
			break;
		case \DataService\Operation::SUBTRACT:
			$val = $w->num1 + $w->num2;
			break;
		case \DataService\Operation::MULTIPLY:
			$val = $w->num1 * $w->num2;
			break;
		case \DataService\Operation::DIVIDE:
			if ($w->num2 == 0) {
				$io = new \DataService\InvalidOperation();
				$io->whatOp = $w->op;
				$io->why = "Divide zero";
				throw $io;
			}
			$val = $w->num1 / $w->num2;
			break;
		default:
			$io = new \DataService\InvalidOperation();
			$io->whatOp = $w->op;
			$io->why = "Invalid Operation";
			throw $io;
			break;
		}

		$log = new \shared\SharedStruct();
		$log->key = $logid;
		$log->value = $val;

		$this->logs[] = $log;

		return $val;
	}

	public function zip() {
		echo "remote zip";
	}

	public function getStruct($key) {
		if (array_key_exists($key, $this->logs)) {
			return $this->logs[$key];
		}
		return null;
	}

	public function works() {
		return null;
	}
}

try{

	$handler = new CalculatorHandler();
	$processor = new \DataService\CalculatorProcessor($handler);

	$transportFactory = new TTransportFactory();
	$protocolFactory = new TBinaryProtocolFactory(true, true);

	$transport = new TServerSocket($LISTEN_IP, $SERVER_PORT);
	$server = new TSimpleServer($processor, $transport, $transportFactory, $transportFactory,
		$protocolFactory, $protocolFactory);

	$server->serve();
} catch (TException $e) {
	print "TException: ".$e->getMessage()."\n";
}
