<?php

namespace ppthrift\php;

error_reporting(E_ALL);

require_once "./vendor/apache/thrift/lib/php/lib/Thrift/ClassLoader/ThriftClassLoader.php";
require_once "./gen-php/PingPong.php";
use Thrift\ClassLoader\ThriftClassLoader;

$GEN_DIR = realpath(dirname(__FILE__))."/gen-php";
print "$GEN_DIR\n";

$loader = new ThriftClassLoader();
$loader->registerNamespace("Thrift", "./vendor/apache/thrift/lib/php/lib");
$loader->registerDefinition("PingPong", $GEN_DIR);

$loader->register();

use Thrift\Protocol\TBinaryProtocol;
use Thrift\Transport\TSocket;
use Thrift\Transport\THttpClient;
use Thrift\Transport\TBufferedTransport;
use Thrift\Exception\TException;

try{
	if (array_search("--http", $argv)) {
		print "start htep client\n";
		$socket = new THttpClient("tc64", 6000, "/php/PhpServer.php");
	} else {
		print "start socket\n";
		$socket = new TSocket("115.159.222.144", 6000);
	}

	$transport = new TBufferedTransport($socket, 1024, 1024);
	$protocol = new TBinaryProtocol($transport);
	$client = new \PingPongClient($protocol);

	$transport->open();

	print "start ping\n";
	print $client->ping();
}
catch (TException $tx){
	print "TException: ".$tx->getMessage()."\n";

}
