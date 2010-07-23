


while (<STDIN>) {
 chop;
 s/\.h//g;
 s/\<//g;
 s/\>//g;
 @words = split;
 if (@words > 1) {
   if ($words[0] eq "#include") {
     print "$words[1]\n";
   
     }
 }
 
}
