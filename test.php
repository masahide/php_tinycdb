<?php

const CDBFILE1 = "sample.cdb";
const CDBFILE2 = "sample2.cdb";

if ( cdb_name() !== CDBFILE1){
   	if(cdb_load_dbfile(CDBFILE1)){
		echo "load db file:".cdb_name()."\n";
	}else{
		echo "Not load db file\n";
		exit(1);
	}
}

$str = cdb_get("one");
echo "one = $str\n";
$str = cdb_get("two");
echo "two = $str\n";

if ( cdb_name() !== CDBFILE2){
   	if(cdb_load_dbfile(CDBFILE2)){
		echo "load db file:".cdb_name()."\n";
	}else{
		echo "Not load db file\n";
		exit(1);
	}
}

$str = cdb_get("090-0927-7689");
echo "090-0927-7689 = $str\n";
$str = cdb_get("080-4760-4466");
echo "080-4760-4466 = $str\n";

cdb_close_dbfile();
echo "load db file:'".cdb_name()."'\n";
