<?php
if (substr($_SERVER['HTTP_HOST'], 0, 6) == 'thrift') {
 \ErrorHandler::setType(\ErrorHandler::TYPE_THRIFT);

 // get service.
 $path = parse_url($_SERVER['REQUEST_URI'], PHP_URL_PATH);
 $name = substr($path, 1);
 $serviceCls = "\\$name\\Service";
 if (!class_exists($serviceCls)) {
  throw new \Exception("service $name not exist.");
 }
 $service = $serviceCls::instance();

 // init processor.
 $trans = new TMemoryBuffer(file_get_contents("php://input"));
 $proto = new TBinaryProtocol($trans, true, true);
 $tracker = new Tracker;
 $processor = new TTrackedProcessor(
  $service->getThriftServiceClassLoader(),
  $service->getHandler(),
  $tracker
 );

 \Mta::Thrift()->poke('before-process');

 // process.
 ob_start();
 $processor->process($proto, $proto);
 ob_end_clean();

 \Mta::Thrift()->poke('process');

 // send response.
 header("HTTP/1.1 200");
 header("Content-Type: application/x-thrift");

 echo $trans->getValue();

 Mta::Thrift()->send();
 exit;
}
