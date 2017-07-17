<?php

namespace setting;

$PROJECT_DIR = realpath(dirname(dirname(__FILE__)));
$GEN_PHP_DIR = $PROJECT_DIR."/idls/gen-php";
$THRIFT_LIB_DIR = $PROJECT_DIR.'/vendor/apache/thrift/lib/php/lib';
$THRIFT_CLASSLOADER = $THRIFT_LIB_DIR.'/Thrift/ClassLoader/ThriftClassLoader.php';

// get socket info
$config = file_get_contents($PROJECT_DIR.'/socket.json');
$data = json_decode($config, true);
$SERVER_IP = $data['server_ip'];
$SERVER_PORT = (int)$data['server_port'];
$LOCAL_IP = $data['local_server_ip'];
$LISTEN_IP = $data['listen_ip'];
