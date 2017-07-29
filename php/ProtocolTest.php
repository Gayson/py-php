<?php

require_once 'setting.php';
require_once $THRIFT_CLASSLOADER;

use Thrift\ClassLoader\ThriftClassLoader;

$loader = new ThriftClassLoader();

$loader->registerNamespace('Thrift', $THRIFT_LIB_DIR);

$loader->register();

use Thrift\Protocol\TBinaryProtocol;

class TestTransport extends \Thrift\Transport\TTransport
{
    private $buf;
    private $len;
    private $bufSize;
    private $readLen;
    private $time;

    public function __construct($bufSize)
    {
        $this->bufSize = 0;
        $this->buf = "";
        $this->len = 0;
        $this->readLen = 0;
        $this->time = 0;
    }

    public function isOpen()
    {
        return true;
    }

    public function open()
    {
    }

    public function close()
    {
    }

    public function peek()
    {
        return $this->isOpen();
    }

    public function read($len)
    {
    }

    public function readAll($len)
    {
    }

    public function write($buf)
    {
        $this->buf .= $buf;
        if (strlen($this->buf) > $this->bufSize) {
            $this->buf = "";
            $this->len = 0;
        }
    }

    public function flush()
    {
    }
};


$transport = new TestTransport(1024);
$protocol = new \Thrift\Protocol\TBinaryProtocol($transport, true, true);

// 
$LOOP = 10000000;

echo "--------------------------------------------\n";
echo "start test\n";
echo "--------------------------------------------\n";

$ss = microtime(true);
for ($i = 0; $i < $LOOP; $i++) {
    $protocol->writeBool(false);
}
$se = microtime(true);
echo "time: ".($se-$ss)."\n";
$ss = $se;

for ($i = 0; $i < $LOOP; $i++) {
    // ascii 'a'
    $protocol->writeByte(97);
}
$se = microtime(true);
echo "time: ".($se-$ss)."\n";
$ss = $se;

for ($i = 0; $i < $LOOP; $i++) {
    $protocol->writeI16(12);
}
$se = microtime(true);
echo "time: ".($se-$ss)."\n";
$ss = $se;

for ($i = 0; $i < $LOOP; $i++) {
    $protocol->writeI32(12);
}
$se = microtime(true);
echo "time: ".($se-$ss)."\n";
$ss = $se;

for ($i = 0; $i < $LOOP; $i++) {
    $protocol->writeI64(23154812394);
}
$se = microtime(true);
echo "time: ".($se-$ss)."\n";
$ss = $se;

for ($i = 0; $i < $LOOP; $i++) {
    $protocol->writeDouble(312341.2334);
}
$se = microtime(true);
echo "time: ".($se-$ss)."\n";
$ss = $se;

for ($i = 0; $i < $LOOP; $i++) {
    $protocol->writeString("transport input input");
}
$se = microtime(true);
echo "time: ".($se-$ss)."\n";
$ss = $se;
