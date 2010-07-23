require "pic24dev_data.pl";

$rp_max = 46;    #max value for higher end devices

%ports = ("Name" => ());
%pullups = ("Name" => ());
%ods = ("Name" => ());
%analogs = ("Name" => ());

$i = 0;
foreach $devref (@pic24_devices) {
  # Name each field nicely
  $devname = $$devref[0];  
  $ioref =$$devref[1];
  $pullref=$$devref[2];
  $odref=$$devref[3];
  $anaref=$$devref[4];
  $rpanaref=$$devref[5];
  $disanaref = $$devref[6];
  $reverse_anaref = &get_reverse_hash($anaref);
  
  $ports{"Name"}->[$i] = $devname;
  $pullups{"Name"}->[$i] = $devname;
  $ods{"Name"}->[$i] = $devname;
  $analogs{"Name"}->[$i] = $devname;
  
  
  # Dump out which ports are defined
  foreach $j (@$ioref) {
    $ports{$j}->[$i] = "X";
  }
  
  # Dump out which pullups map to ports
  foreach $j (keys(%$pullref)) {
    # Return just the numeric portion using substr.
    $pullups{$j}->[$i] = int(substr($pullref->{$j}, 3));
  }
  
  # Demp out which open-drains map to ports
  foreach $j (keys(%$odref)) {
    # Return just the numeric portion using substr.
    # PIC24F uses _ODxy, but PIC24H uses _ODCxy.
    # Look for this case
    $pin = substr($odref->{$j}, 3);
    $secondChar = substr($pin, 1, 1);
    if ( (ord($secondChar) >= ord('A')) && (ord($secondChar) <= ord('Z')) ) {
#      print "$secondChar - $pin => ";
      $pin = substr($pin, 1); 
#      print "$pin\n";
    }
    $ods{$j}->[$i] = $pin;
  }
  
  # Determine which analog inputs map to ports
  foreach $j (keys(%$anaref)) {
    # Return just the numeric portion using substr
    $analogs{$j}->[$i] = int(substr($anaref->{$j}, 5));
  }

  # Write each device's info out to a header file
  $fname = $devname . "_pyports.h";  
  unlink($fname) if (-e $fname);
  open(OUTPUT, ">$fname") || die "Cannot create file $fname";
  
  # Generate a table which matches digital port/pin to analog and pullups
  print "$devname:\n";
  print OUTPUT
        "#define AN_CN_MAP \\\n" .
        "  /*   AN pin   ,    CN pin    */ \\\n" .
        "  /* -----------, ------------ */";
  foreach $port ("A" .. "G") {
    # Scan to see if this port has any defined pins
    $hasPins = 0;
    foreach $pin (0 .. 15) {
      $key = "R$port$pin";
      
      $an = $analogs{$key}->[$i];
      $hasPins = 1 unless (length($an) == 0);
      
      $cn = $pullups{$key}->[$i];
      $hasPins = 1 unless (length($cn) == 0);
    }
    last if ($hasPins == 0);
	  
    foreach $pin (0 .. 15) {
	  # Print each port/pin's string.
      $key = "R$port$pin";
      
      # Replace empty AN pins with a message
      $an = $analogs{$key}->[$i];
      if (length($an) == 0) {
        $an = "UNDEF_AN_PIN";
        $anStr = "xx";
      } else {
        $anStr = $an;
      }
      
      # Replace empty CN pins with a message
      $cn = $pullups{$key}->[$i];
      if (length($cn) == 0) {
        $cn = "UNDEF_CN_PIN";
        $cnStr = "xx";
      } else {
        $cnStr = $cn;
      }
      
      # Format and print
      printf(OUTPUT " \\\n  { %12s, %12s },  /* %4s => %4s, %4s */", 
        $an, $cn, $key, "AN$anStr", "CN$cnStr");
    }
  }
  print OUTPUT "\n\n";
  
  # Close the file
  print OUTPUT "#define _PIC24_PYDIGIO_DEFINED\n";
  close(OUTPUT);

  # Update the count
  $i = $i + 1;
#  exit;
}

#printList(\%ports);
#printList(\%pullups);
#printList(\%ods);
#printList(\%analogs);

## This function prints out a list sorted by port/pin.
#  It expects a reference to a dict.
sub printList {
  %list = %{$_[0]};
  # Print out a list in order
  $value = $list{"Name"};
  print "\n\nName," . join(',', @$value) . "\n";
  foreach $port ("A" .. "G") {
    foreach $pin (0 .. 15) {
	  # Print each port/pin's string.
      $key = "R$port$pin";
      print "$key," . join(',', @{$list{$key}}) . "\n" if exists $list{$key};
      
      # See if OD and ports line up. The conclusion: nope.
#      for ($k = 0; $k < $#{$list{$key}}; $k++) {
#       if (($ports{$key}->[$k] ne "") && ($list{$key}->[$k] eq "")) {
#          print "$k " . $ports{$key}->[$k] . " " . $list{$key}->[$k] . "\n";
#          print "$key has no pullup.\n" unless ();
#       }
#      }
      
      next;
      # Compare all the strings in this port/pin to see if they're the same.
      $val = "";
      foreach $k (@{$list{$key}}) {
		# Skip empty entries
		next if (length($k) == 0);
		if (length($val) == 0) {
		  $val = $k;
		} else {
		  print "Mismatch in $key; expected $val.\n" unless ($val eq $k);
		}
      }
    }
  }
}

# Done!
exit;
 
  
  # creating mapping of analog ports to 
 sub get_reverse_hash {
 my ($fwdhashref) = @_;
 my $revhashref;
 my $fwdkey, $fwdval;
  
 #init hash
 
 $revhashref = { };
 foreach $fwdkey (keys(%$fwdhashref)) {
  $fwdval = $$fwdhashref{$fwdkey};
  $$revhashref{$fwdval} = $fwdkey;
 }
 return $revhashref;  
 }
 
 
 &printanalog_disable($disanaref);
 
 sub printanalog_disable{
 my($hashref) = @_;
 my $fwdkey, $fwdval;
 my $newkey;
 
 foreach $fwdkey (keys(%disable_analog_master_list)) {
  $fwdval = $disable_analog_master_list{$fwdkey};
  if (exists($$hashref{$fwdkey})) {
   $newkey = $$hashref{$fwdkey};
   if ($newkey ne "") {
     printf (OUTPUT "#define DISABLE_%s_ANALOG()   CONFIG_%s_AS_DIGITAL() \n",$fwdkey, $newkey);
	 } 
   else {
	 printf (OUTPUT "#define DISABLE_%s_ANALOG()   \n",$fwdkey);
	 }	 
  } 
  else {
   printf (OUTPUT "#define DISABLE_%s_ANALOG()   \n",$fwdkey);
  }
  }
 
 }
 
 sub printanaout {
  my($revhashref) = @_;
  my($i);
  my($pcfg);
  my($digport);
  
  for ($i=0;$i<= 31;$i++) {
    $pcfg = "_PCFG" . $i;
    print OUTPUT "#ifdef $pcfg\n";
    printf (OUTPUT "static inline void CONFIG_AN%d_AS_ANALOG(){\n",$i);
	
	if (exists($$revhashref{$pcfg})) {
	  $digport = $$revhashref{$pcfg};
	  printf (OUTPUT "  CONFIG_%s_AS_DIG_INPUT();\n",$digport);
	}
	printf (OUTPUT "  %s = 0;\n",$pcfg);
	print OUTPUT "}\n"; 
	printf (OUTPUT "static inline void CONFIG_AN%d_AS_DIGITAL(){\n",$i);
	printf (OUTPUT "  %s = 1;\n",$pcfg);
	print OUTPUT "}\n"; 	
    print OUTPUT "#endif\n";  
  }
 }
 
 sub printrpdigin {
 my ($href) = @_;
 my ($i);
 
  for($i=0;$i<$rp_max;$i++){
  
   if (exists($$href{$i})){
     printf(OUTPUT "#define CONFIG_RP%d_AS_DIG_PIN()  %s = 1\n",$i,$$href{$i});
   } else {
      printf(OUTPUT "#define CONFIG_RP%d_AS_DIG_PIN() \n", $i);
     }
  
   }  
 
 }
 
sub printdevice {
  my ($lref, $ioref, $pullref, $odref, $anaref, $rpanaref) = @_;
  my ($device);
  
  print(OUTPUT "#if ");   
 foreach $device (@$lref){
 
 printf(OUTPUT " defined(%s) || ",$device);  
  
  }
 print(OUTPUT " 0 \n");
  
 &printpullups($ioref, $pullref);
 &printcninterrupts($ioref, $pullref);
 &printopendrain($ioref, $odref);
 &printdigout($ioref, $anaref);
 &printdigin($ioref, $anaref);
 &printrpdigin($rpanaref);
  
 print(OUTPUT "#define _PIC24_DIGIO_DEFINED\n");
 print(OUTPUT "#endif\n");
 
 

}


sub printdigout {

 my ($lref, $href, $pullref,$odref) = @_;
 my ($v);
 
  #do output macros   
 foreach $port (@$lref) {  
    $v = substr $port,1;
	$v = "_TRIS" ."$v";
	printf (OUTPUT "static inline void CONFIG_%s_AS_DIG_OUTPUT(){\n",$port);
	if (exists($$pullref{$port})) {
	printf (OUTPUT " DISABLE_%s_PULLUP();\n", $port);
	}
	if (exists($$odref{$port})) {
	printf (OUTPUT " DISABLE_%s_OPENDRAIN();\n", $port);
	}
	printf (OUTPUT " %s = 0;\n",$v);
        if (exists($$href{$port})) {
	 $v = $$href{$port};
	 printf (OUTPUT " %s = 1;\n",$v);
	}	
	printf (OUTPUT "}\n");   
 } 
 }
 
 sub printdigoutod {

 my ($lref, $href, $pullref,$odref) = @_;
 my ($v);
 
  #do output macros   
 foreach $port (@$lref) {  
    $v = substr $port,1;
	$v = "_TRIS" ."$v";
	printf (OUTPUT "static inline void CONFIG_%s_AS_DIG_OD_OUTPUT(){\n",$port);
	if (exists($$pullref{$port})) {
	printf (OUTPUT " DISABLE_%s_PULLUP();\n", $port);
	}
	if (exists($$odref{$port})) {
	printf (OUTPUT " ENABLE_%s_OPENDRAIN();\n", $port);
	}
	printf (OUTPUT " %s = 0;\n",$v);
        if (exists($$href{$port})) {
	 $v = $$href{$port};
	 printf (OUTPUT " %s = 1;\n",$v);
	}	
	printf (OUTPUT "}\n");   
 } 
 }
 
 sub printdigin {

 my ($lref, $href,$pullref) = @_;
 my ($v);
 foreach $port (@$lref) {
    $v = substr $port,1;
	$v = "_TRIS" ."$v";
    printf (OUTPUT "static inline void CONFIG_%s_AS_DIG_INPUT(){\n",$port);
	if (exists($$pullref{$port})) {
	printf (OUTPUT " DISABLE_%s_PULLUP();\n", $port);
	}
	printf (OUTPUT " %s = 1;\n",$v);
	if (exists($$href{$port})) {
	 $v = $$href{$port};
	 printf (OUTPUT " %s = 1;\n",$v);
	}
	printf (OUTPUT "}\n");
 
 } 
 
 }

 

sub printpullups {

 my ($lref, $href) = @_;
 my ($v);
 
 foreach $port (@$lref) {
  if (exists($$href{$port})) {
    $v = $$href{$port};
	printf (OUTPUT "#define ENABLE_%s_PULLUP() %sPUE = 1\n",$port,$v);
   printf (OUTPUT "#define DISABLE_%s_PULLUP() %sPUE = 0\n",$port,$v);  
   } 
 }
 }
 
 sub printcninterrupts {

 my ($lref, $href) = @_;
 my ($v);
 
 foreach $port (@$lref) {
  if (exists($$href{$port})) {
    $v = $$href{$port};
	printf (OUTPUT "#define ENABLE_%s_CN_INTERRUPT() %sIE = 1\n",$port,$v);
    printf (OUTPUT "#define DISABLE_%s_CN_INTERRUPT() %sIE = 0\n",$port,$v);  
   } 
 }
 }
 
 sub printanalog {

 my ($lref, $href) = @_;
 my ($v);
 
 foreach $port (@$lref) {
  if (exists($$href{$port})) {
    $v = $$href{$port};
	printf (OUTPUT "#define DISABLE_%s_ANALOG() %s = 1\n",$port,$v);
    printf (OUTPUT "#define ENABLE_%s_ANALOG() %s = 0\n",$port,$v);  
   } 
 }
 }
 
 sub printopendrain {

 my ($lref, $href) = @_;
 my ($v);
 
 foreach $port (@$lref) {
  if (exists($$href{$port})) {
    $v = $$href{$port};
	printf (OUTPUT "#define ENABLE_%s_OPENDRAIN() %s = 1\n",$port,$v);
   printf (OUTPUT "#define DISABLE_%s_OPENDRAIN() %s = 0\n",$port,$v);  
   } 
 }
 }
 
 
 



