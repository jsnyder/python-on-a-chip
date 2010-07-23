#parse dev id


$fname = "PK2DeviceFile.dat";

open(INPUT,"$fname") || die "Cannot open $fname for reading\n";
binmode INPUT;
$i=0;
while (read(INPUT,$c,1)) {
$buf[$i]= unpack 'C', $c;
$i++;
}
$bufsize = $i;

print("Read $bufsize characters.\n");

$offset = 0x0520;  #starting offset
# now parse it.
while ($offset < $bufsize) {
#look for "PIC"
#printf("%x\n",$buf[$offset]);
 
 if ( (($buf[$offset] == 0x50) &&($buf[$offset+1] == 0x49) && ($buf[$offset+2] == 0x43)) ||
      (($buf[$offset] == 0x64) &&($buf[$offset+1] == 0x73))
      ) {
	 $len = $buf[$offset-1];
	 $devname = "";
	 for ($k=0;$k<$len;$k++){	   
	  $devname = $devname . chr($buf[$offset+$k]);
	 }
	 $devid = $buf[$offset+$len+2] + $buf[$offset+$len+3]*256;
	 
	 printf("$devname  %04x\n",$devid);
	 $offset = $offset + $len + 4;	 
  } else {
   $offset = $offset + 1;
  } 
  if ( ($buf[$offset] == 0x48) &&($buf[$offset+1] == 0x56) && ($buf[$offset+2] == 0x50)
        && ($buf[$offset+3] == 0x72) && ($buf[$offset+4] == 0x6f)) {
		last;
		}



}

close(INPUT);



