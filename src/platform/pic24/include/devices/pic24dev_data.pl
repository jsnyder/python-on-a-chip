

require "pkg18pin.pl";
require "pkg28pin.pl";
require "pkg44pin.pl";
require "pkg64pin.pl";
require "pkg64pinF_GA.pl";
require "pkg64pinF_GB.pl";
require "pkg100pin.pl";
require "pkg100pinF_GA.pl";
require "pkg100pinF_GB.pl";
require "pkg80pinF_GA.pl";
require "pkg80pinF_GB.pl";

%disable_analog_default = ();

#used for when a hardcoded pin function is mapped to an analog pin, and the analog pin has to be disabled before the function is used.
%disable_analog_master_list = (  
 "INT0" => "", 
 "INT1" => "",  
 "INT2" => "",
 "T1CK" => "",
 "T2CK" => "",
 "T3CK" => "",
 "T4CK" => "",
 "T5CK" => "",
 "IC1" => "",
 "IC2" => "",
 "IC3" => "",
 "IC4" => "",
 "IC5" => "",
 "IC6" => "",
 "IC7" => "",
 "IC8" => "",
 "OCFA" => "",
 "OCFB" => "",
 "U1RX" => "",
 "U2RX" => "",
 "U2CTS" => "",
 "SDI1" => "",
 "SCK1" => "",
 "SS1" => "",
 "SDI2" => "",
 "SCK2" => "",
 "SS2" => "",
 "C1RX" => "",
 "C2RX" => "",
 "C1OUT" => "",
 "C2OUT" => "",
 "U1TX" => "",
 "U1RTS" => "",
 "U1CTS" => "",
 "U2TX" => "",
 "U2RTS" => "",
 "U2CTS" => "",
 "SDO1" => "",
 "SDO2" => "",
 "C1TX" => "",
 "OC1" => "",
 "OC2" => "",
 "OC3" => "",
 "OC4" => "",
 "OC5" => "",
 "RTCC" => "",
 "U1BCLK" => "",
 "U2BCLK" => "",
 "C1INA" => "",
 "C1INB" => "",
 "C1INC" => "",
 "C1IND" => "",
 "C1OUT" => "",
 "C2INA" => "",
 "C21INB" => "",
 "C2INC" => "",
 "C2IND" => "",
 "C2OUT" => "",
 "CTED1" => "",
 "CTED2" => "",
 "CTPLS" => "", 
 "U3TX" => "",
 "U3RX" => "",
 "U3RTS" => "",
 "U3CTS" => "",
 "U4TX" => "",
 "U4RX" => "",
 "U4RTS" => "",
 "U4CTS" => "",
);



@pic24_devices = (
 ##PIC24FK devices
 ##28-pin devices, variant 1
 ["pic24f16ka102",\@digio_28pin_K, \%pullups_28pin_K, \%opendrain_28pin_24K_1,\%analog_28pin_K,\%RPanalog_28pin_K,\%disable_analog_28pin_K],
 ##dsPIC33 devices
 ## 18-pin devices, variant 1
 ["dspic33fj12gp201",\@digio_18pin_1, \%pullups_18pin_1, \%opendrain_18pin_24H_1,\%analog_18pin_1,\%RPanalog_18pin_1,\%disable_analog_default],
 ##28-pin devices, variant 1
 ["dspic33fj32gp202",\@digio_28pin_1, \%pullups_28pin_1, \%opendrain_28pin_24H_1,\%analog_28pin_1,\%RPanalog_28pin_1,\%disable_analog_default],
 
 ["dspic33fj32gp302",\@digio_28pin_1, \%pullups_28pin_1, \%opendrain_28pin_24H_1,\%analog_28pin_1,\%RPanalog_28pin_1,\%disable_analog_default],
 ["dspic33fj64gp202",\@digio_28pin_1, \%pullups_28pin_1, \%opendrain_28pin_24H_1,\%analog_28pin_1,\%RPanalog_28pin_1,\%disable_analog_default],
 ["dspic33fj64gp802",\@digio_28pin_1, \%pullups_28pin_1, \%opendrain_28pin_24H_1,\%analog_28pin_1,\%RPanalog_28pin_1,\%disable_analog_default],
 ["dspic33fj128gp202",\@digio_28pin_1, \%pullups_28pin_1, \%opendrain_28pin_24H_1,\%analog_28pin_1,\%RPanalog_28pin_1,\%disable_analog_default],
 ["dspic33fj128gp802",\@digio_28pin_1, \%pullups_28pin_1, \%opendrain_28pin_24H_1,\%analog_28pin_1,\%RPanalog_28pin_1,\%disable_analog_default],
 
 ## 28-pin devices, variant 2
["dspic33fj12gp202",\@digio_28pin_1, \%pullups_28pin_1, \%opendrain_28pin_24H_1,\%analog_28pin_2,\%RPanalog_28pin_2,\%disable_analog_default],
 ##44-pin devices, variant 1
["dspic33fj16gp304",\@digio_44pin_1, \%pullups_44pin_1, \%opendrain_44pin_24H_1,\%analog_44pin_1,\%RPanalog_44pin_1,\%disable_analog_default],
["dspic33fj32gp204",\@digio_44pin_1, \%pullups_44pin_1, \%opendrain_44pin_24H_1,\%analog_44pin_1,\%RPanalog_44pin_1,\%disable_analog_default],
["dspic33fj32gp304",\@digio_44pin_1, \%pullups_44pin_1, \%opendrain_44pin_24H_1,\%analog_44pin_1,\%RPanalog_44pin_1,\%disable_analog_default],
["dspic33fj64gp204",\@digio_44pin_1, \%pullups_44pin_1, \%opendrain_44pin_24H_1,\%analog_44pin_1,\%RPanalog_44pin_1,\%disable_analog_default],
["dspic33fj64gp804",\@digio_44pin_1, \%pullups_44pin_1, \%opendrain_44pin_24H_1,\%analog_44pin_1,\%RPanalog_44pin_1,\%disable_analog_default],
["dspic33fj128gp204",\@digio_44pin_1, \%pullups_44pin_1, \%opendrain_44pin_24H_1,\%analog_44pin_1,\%RPanalog_44pin_1,\%disable_analog_default],
["dspic33fj128gp804",\@digio_44pin_1, \%pullups_44pin_1, \%opendrain_44pin_24H_1,\%analog_44pin_1,\%RPanalog_44pin_1,\%disable_analog_default],

 ##PIC24 Devices
 ## 18-pin devices, variant 1
 ["pic24hj12gp201",\@digio_18pin_1, \%pullups_18pin_1, \%opendrain_18pin_24H_1,\%analog_18pin_1,\%RPanalog_18pin_1,\%disable_analog_default],
 ##28-pin devices, variant 1
["pic24hj32gp202",\@digio_28pin_1, \%pullups_28pin_1, \%opendrain_28pin_24H_1,\%analog_28pin_1,\%RPanalog_28pin_1,\%disable_analog_default],
["pic24hj32gp302",\@digio_28pin_1, \%pullups_28pin_1, \%opendrain_28pin_24H_1,\%analog_28pin_1,\%RPanalog_28pin_1,\%disable_analog_default],
["pic24hj64gp202",\@digio_28pin_1, \%pullups_28pin_1, \%opendrain_28pin_24H_1,\%analog_28pin_1,\%RPanalog_28pin_1,\%disable_analog_default],
["pic24hj64gp502",\@digio_28pin_1, \%pullups_28pin_1, \%opendrain_28pin_24H_1,\%analog_28pin_1,\%RPanalog_28pin_1,\%disable_analog_default],
["pic24hj128gp202",\@digio_28pin_1, \%pullups_28pin_1, \%opendrain_28pin_24H_1,\%analog_28pin_1,\%RPanalog_28pin_1,\%disable_analog_default],
["pic24hj128gp502",\@digio_28pin_1, \%pullups_28pin_1, \%opendrain_28pin_24H_1,\%analog_28pin_1,\%RPanalog_28pin_1,\%disable_analog_default],

## 28-pin devices, variant 2
["pic24hj12gp202",\@digio_28pin_1, \%pullups_28pin_1, \%opendrain_28pin_24H_1,\%analog_28pin_2,\%RPanalog_28pin_2,\%disable_analog_default],
##44-pin devices, variant 1
["pic24hj16gp304",\@digio_44pin_1, \%pullups_44pin_1, \%opendrain_44pin_24H_1,\%analog_44pin_1,\%RPanalog_44pin_1,\%disable_analog_default],
["pic24hj32gp204",\@digio_44pin_1, \%pullups_44pin_1, \%opendrain_44pin_24H_1,\%analog_44pin_1,\%RPanalog_44pin_1,\%disable_analog_default],
["pic24hj32gp304",\@digio_44pin_1, \%pullups_44pin_1, \%opendrain_44pin_24H_1,\%analog_44pin_1,\%RPanalog_44pin_1,\%disable_analog_default],
["pic24hj64gp204",\@digio_44pin_1, \%pullups_44pin_1, \%opendrain_44pin_24H_1,\%analog_44pin_1,\%RPanalog_44pin_1,\%disable_analog_default],
["pic24hj64gp504",\@digio_44pin_1, \%pullups_44pin_1, \%opendrain_44pin_24H_1,\%analog_44pin_1,\%RPanalog_44pin_1,\%disable_analog_default],
["pic24hj128gp204",\@digio_44pin_1, \%pullups_44pin_1, \%opendrain_44pin_24H_1,\%analog_44pin_1,\%RPanalog_44pin_1,\%disable_analog_default],
["pic24hj128gp504",\@digio_44pin_1, \%pullups_44pin_1, \%opendrain_44pin_24H_1,\%analog_44pin_1,\%RPanalog_44pin_1,\%disable_analog_default],
##64-pin devices, variant 1
["pic24hj64gp206",\@digio_64pin_1, \%pullups_64pin_1, \%opendrain_64pin_24H_1,\%analog_64pin_1,\%RPanalog_64pin_1,\%disable_analog_default],
["pic24hj128gp206",\@digio_64pin_1, \%pullups_64pin_1, \%opendrain_64pin_24H_1,\%analog_64pin_1,\%RPanalog_64pin_1,\%disable_analog_default],
["pic24hj256gp206",\@digio_64pin_1, \%pullups_64pin_1, \%opendrain_64pin_24H_1,\%analog_64pin_1,\%RPanalog_64pin_1,\%disable_analog_default],
["pic24hj128gp306",\@digio_64pin_1, \%pullups_64pin_1, \%opendrain_64pin_24H_1,\%analog_64pin_1,\%RPanalog_64pin_1,\%disable_analog_default],
["pic24hj64gp506",\@digio_64pin_1, \%pullups_64pin_1, \%opendrain_64pin_24H_1,\%analog_64pin_1,\%RPanalog_64pin_1,\%disable_analog_default],
["pic24hj128gp506",\@digio_64pin_1, \%pullups_64pin_1, \%opendrain_64pin_24H_1,\%analog_64pin_1,\%RPanalog_64pin_1,\%disable_analog_default],
##100-pin devices, variant 1
["pic24hj64gp210",\@digio_100pin_1, \%pullups_100pin_1, \%opendrain_100pin_24H_1,\%analog_100pin_1,\%RPanalog_100pin_1,\%disable_analog_default],
["pic24hj128gp210",\@digio_100pin_1, \%pullups_100pin_1, \%opendrain_100pin_24H_1,\%analog_100pin_1,\%RPanalog_100pin_1,\%disable_analog_default],
["pic24hj128gp310",\@digio_100pin_1, \%pullups_100pin_1, \%opendrain_100pin_24H_1,\%analog_100pin_1,\%RPanalog_100pin_1,\%disable_analog_default],
["pic24hj256gp210",\@digio_100pin_1, \%pullups_100pin_1, \%opendrain_100pin_24H_1,\%analog_100pin_1,\%RPanalog_100pin_1,\%disable_analog_default],
["pic24hj64gp510",\@digio_100pin_1, \%pullups_100pin_1, \%opendrain_100pin_24H_1,\%analog_100pin_1,\%RPanalog_100pin_1,\%disable_analog_default],
["pic24hj128gp510",\@digio_100pin_1, \%pullups_100pin_1, \%opendrain_100pin_24H_1,\%analog_100pin_1,\%RPanalog_100pin_1,\%disable_analog_default],
["pic24hj256gp610",\@digio_100pin_1, \%pullups_100pin_1, \%opendrain_100pin_24H_1,\%analog_100pin_1,\%RPanalog_100pin_1,\%disable_analog_default],
##PIC24F Devices
##28-pin devices, variant 1
["pic24fj16ga002",\@digio_28pin_1, \%pullups_28pin_1, \%opendrain_28pin_24F_1,\%analog_28pin_1,\%RPanalog_28pin_1,\%disable_analog_default],
["pic24fj32ga002",\@digio_28pin_1, \%pullups_28pin_1, \%opendrain_28pin_24F_1,\%analog_28pin_1,\%RPanalog_28pin_1,\%disable_analog_default],
["pic24fj48ga002",\@digio_28pin_1, \%pullups_28pin_1, \%opendrain_28pin_24F_1,\%analog_28pin_1,\%RPanalog_28pin_1,\%disable_analog_default],
["pic24fj64ga002",\@digio_28pin_1, \%pullups_28pin_1, \%opendrain_28pin_24F_1,\%analog_28pin_1,\%RPanalog_28pin_1,\%disable_analog_default],
##PIC24FJXXGA102
["pic24fj32ga102",\@digio_28pin_1, \%pullups_28pin_1, \%opendrain_28pin_24F_1,\%analog_28pin_1,\%RPanalog_28pin_1,\%disable_analog_default],
["pic24fj64ga102",\@digio_28pin_1, \%pullups_28pin_1, \%opendrain_28pin_24F_1,\%analog_28pin_1,\%RPanalog_28pin_1,\%disable_analog_default],
##28-pin devices, FB
["pic24fj32gb002",\@digio_28pin_FB, \%pullups_28pin_FB, \%opendrain_28pin_FB,\%analog_28pin_FB,\%RPanalog_28pin_FB,\%disable_analog_default],
["pic24fj64gb002",\@digio_28pin_FB, \%pullups_28pin_FB, \%opendrain_28pin_FB,\%analog_28pin_FB,\%RPanalog_28pin_FB,\%disable_analog_default],
##44-pin devices, variant 1
["pic24fj16ga004",\@digio_44pin_1, \%pullups_44pin_1, \%opendrain_44pin_24F_1,\%analog_44pin_1,\%RPanalog_44pin_1,\%disable_analog_default],
["pic24fj32ga004",\@digio_44pin_1, \%pullups_44pin_1, \%opendrain_44pin_24F_1,\%analog_44pin_1,\%RPanalog_44pin_1,\%disable_analog_default],
["pic24fj48ga004",\@digio_44pin_1, \%pullups_44pin_1, \%opendrain_44pin_24F_1,\%analog_44pin_1,\%RPanalog_44pin_1,\%disable_analog_default],
["pic24fj64ga004",\@digio_44pin_1, \%pullups_44pin_1, \%opendrain_44pin_24F_1,\%analog_44pin_1,\%RPanalog_44pin_1,\%disable_analog_default],
##PIC24FJXXGA104
["pic24fj32ga104",\@digio_44pin_1, \%pullups_44pin_1, \%opendrain_44pin_24F_1,\%analog_44pin_1,\%RPanalog_44pin_1,\%disable_analog_default],
["pic24fj64ga104",\@digio_44pin_1, \%pullups_44pin_1, \%opendrain_44pin_24F_1,\%analog_44pin_1,\%RPanalog_44pin_1,\%disable_analog_default],
##44-pin devices, FB
["pic24fj32gb004",\@digio_44pin_FB, \%pullups_44pin_FB, \%opendrain_44pin_FB,\%analog_44pin_FB,\%RPanalog_44pin_FB,\%disable_analog_default],
["pic24fj64gb004",\@digio_44pin_FB, \%pullups_44pin_FB, \%opendrain_44pin_FB,\%analog_44pin_FB,\%RPanalog_44pin_FB,\%disable_analog_default],
#64-pin devices, F_GA
["pic24fj128ga106",\@digio_64pin_F_GA, \%pullups_64pin_F_GA, \%opendrain_64pin_F_GA,\%analog_64pin_F_GA,\%RPanalog_64pin_F_GA,\%disable_analog_default],
["pic24fj192ga106",\@digio_64pin_F_GA, \%pullups_64pin_F_GA, \%opendrain_64pin_F_GA,\%analog_64pin_F_GA,\%RPanalog_64pin_F_GA,\%disable_analog_default],
["pic24fj256ga106",\@digio_64pin_F_GA, \%pullups_64pin_F_GA, \%opendrain_64pin_F_GA,\%analog_64pin_F_GA,\%RPanalog_64pin_F_GA,\%disable_analog_default],
#64-pin devices, F_GA0
["pic24fj64ga006",\@digio_64pin_F_GA, \%pullups_64pin_F_GA0, \%opendrain_64pin_F_GA,\%analog_64pin_F_GA,\%RPanalog_64pin_F_GA0,\%disable_analog_default],
["pic24fj96ga006",\@digio_64pin_F_GA, \%pullups_64pin_F_GA0, \%opendrain_64pin_F_GA,\%analog_64pin_F_GA,\%RPanalog_64pin_F_GA0,\%disable_analog_default],
["pic24fj128ga006",\@digio_64pin_F_GA, \%pullups_64pin_F_GA0, \%opendrain_64pin_F_GA,\%analog_64pin_F_GA,\%RPanalog_64pin_F_GA0,\%disable_analog_default],
#64-pin devices, F_GB
["pic24fj64gb106",\@digio_64pin_F_GB, \%pullups_64pin_F_GB, \%opendrain_64pin_F_GB,\%analog_64pin_F_GB,\%RPanalog_64pin_F_GB,\%disable_analog_default],
["pic24fj128gb106",\@digio_64pin_F_GB, \%pullups_64pin_F_GB, \%opendrain_64pin_F_GB,\%analog_64pin_F_GB,\%RPanalog_64pin_F_GB,\%disable_analog_default],
["pic24fj192gb106",\@digio_64pin_F_GB, \%pullups_64pin_F_GB, \%opendrain_64pin_F_GB,\%analog_64pin_F_GB,\%RPanalog_64pin_F_GB,\%disable_analog_default],
["pic24fj256gb106",\@digio_64pin_F_GB, \%pullups_64pin_F_GB, \%opendrain_64pin_F_GB,\%analog_64pin_F_GB,\%RPanalog_64pin_F_GB,\%disable_analog_default],
#100-pin devices, F_GA1
["pic24fj128ga110",\@digio_100pin_F_GA, \%pullups_100pin_F_GA, \%opendrain_100pin_F_GA,\%analog_100pin_F_GA,\%RPanalog_100pin_F_GA,\%disable_analog_default],
["pic24fj192ga110",\@digio_100pin_F_GA, \%pullups_100pin_F_GA, \%opendrain_100pin_F_GA,\%analog_100pin_F_GA,\%RPanalog_100pin_F_GA,\%disable_analog_default],
["pic24fj256ga110",\@digio_100pin_F_GA, \%pullups_100pin_F_GA, \%opendrain_100pin_F_GA,\%analog_100pin_F_GA,\%RPanalog_100pin_F_GA,\%disable_analog_default],
#100-pin devices, F_GA0
["pic24fj64ga010",\@digio_100pin_F_GA, \%pullups_100pin_F_GA0, \%opendrain_100pin_F_GA,\%analog_100pin_F_GA,\%RPanalog_100pin_F_GA0,\%disable_analog_default],
["pic24fj96ga010",\@digio_100pin_F_GA, \%pullups_100pin_F_GA0, \%opendrain_100pin_F_GA,\%analog_100pin_F_GA,\%RPanalog_100pin_F_GA0,\%disable_analog_default],
["pic24fj128ga010",\@digio_100pin_F_GA, \%pullups_100pin_F_GA0, \%opendrain_100pin_F_GA,\%analog_100pin_F_GA,\%RPanalog_100pin_F_GA0,\%disable_analog_default],
#100-pin devices, F_GB
["pic24fj64gb110",\@digio_100pin_F_GB, \%pullups_100pin_F_GB, \%opendrain_100pin_F_GB,\%analog_100pin_F_GB,\%RPanalog_100pin_F_GB,\%disable_analog_default],
["pic24fj128gb110",\@digio_100pin_F_GB, \%pullups_100pin_F_GB, \%opendrain_100pin_F_GB,\%analog_100pin_F_GB,\%RPanalog_100pin_F_GB,\%disable_analog_default],
["pic24fj192gb110",\@digio_100pin_F_GB, \%pullups_100pin_F_GB, \%opendrain_100pin_F_GB,\%analog_100pin_F_GB,\%RPanalog_100pin_F_GB,\%disable_analog_default],
["pic24fj256gb110",\@digio_100pin_F_GB, \%pullups_100pin_F_GB, \%opendrain_100pin_F_GB,\%analog_100pin_F_GB,\%RPanalog_100pin_F_GB,\%disable_analog_default],
#80-pin devices, F_GA
["pic24fj128ga108",\@digio_80pin_F_GA, \%pullups_80pin_F_GA, \%opendrain_80pin_F_GA,\%analog_80pin_F_GA,\%RPanalog_80pin_F_GA,\%disable_analog_default],
["pic24fj192ga108",\@digio_80pin_F_GA, \%pullups_80pin_F_GA, \%opendrain_80pin_F_GA,\%analog_80pin_F_GA,\%RPanalog_80pin_F_GA,\%disable_analog_default],
["pic24fj256ga108",\@digio_80pin_F_GA, \%pullups_80pin_F_GA, \%opendrain_80pin_F_GA,\%analog_80pin_F_GA,\%RPanalog_80pin_F_GA,\%disable_analog_default],
#80-pin devices, F_GA0
["pic24fj64ga008",\@digio_80pin_F_GA, \%pullups_80pin_F_GA0, \%opendrain_80pin_F_GA,\%analog_80pin_F_GA,\%RPanalog_80pin_F_GA0,\%disable_analog_default],
["pic24fj96ga008",\@digio_80pin_F_GA, \%pullups_80pin_F_GA0, \%opendrain_80pin_F_GA,\%analog_80pin_F_GA,\%RPanalog_80pin_F_GA0,\%disable_analog_default],
["pic24fj128ga008",\@digio_80pin_F_GA, \%pullups_80pin_F_GA0, \%opendrain_80pin_F_GA,\%analog_80pin_F_GA,\%RPanalog_80pin_F_GA0,\%disable_analog_default],
#80-pin devices, F_GB
["pic24fj64gb108",\@digio_80pin_F_GB, \%pullups_80pin_F_GB, \%opendrain_80pin_F_GB,\%analog_80pin_F_GB,\%RPanalog_80pin_F_GB,\%disable_analog_default],
["pic24fj128gb108",\@digio_80pin_F_GB, \%pullups_80pin_F_GB, \%opendrain_80pin_F_GB,\%analog_80pin_F_GB,\%RPanalog_80pin_F_GB,\%disable_analog_default],
["pic24fj192gb108",\@digio_80pin_F_GB, \%pullups_80pin_F_GB, \%opendrain_80pin_F_GB,\%analog_80pin_F_GB,\%RPanalog_80pin_F_GB,\%disable_analog_default],
["pic24fj256gb108",\@digio_80pin_F_GB, \%pullups_80pin_F_GB, \%opendrain_80pin_F_GB,\%analog_80pin_F_GB,\%RPanalog_80pin_F_GB,\%disable_analog_default],
);





