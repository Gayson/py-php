<?php
//$br = (php_sapi_name() == "cli")? "":"<br>";

//if (!extension_loaded('vehicle')) {
//dl('vehicle.' . PHP_SHLIB_SUFFIX);
//}
//$module = 'vehicle';
//$functions = get_extension_funcs($module);
//echo "Functions available in the test extension:$br\n";
//foreach ($functions as $func) {
//echo $func."$br\n";
//}
//echo "$br\n";
//$function = 'confirm_' . $module . '_compiled';
//if (extension_loaded($module)) {
//$str = $function($module, "2");
//} else {
//$str = "Module $module is not compiled into PHP";
//}

//$arr1 = array("k1", "k2" => "v1", "k3" => "val2");
//$arr2 = array("k4", "k4" => "v3", "k3" => "val3");

//var_dump(other_array_concat($arr1, $arr2));

$c = new \Vehicle\Foo();
$val = null;
$dVal = 1;
$val1 = &$val;
$dVal1 = &$dVal;
$c->getVal($val, $dVal);
echo "$val, $dVal\n";

gc_collect_cycles();

echo "$val\n";


$cc = new \Vehicle\FooChild();
$cc->long_child_val = 20;
echo $cc->long_child_val."\n";
echo $cc->child()."\n";
