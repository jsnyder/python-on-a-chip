###package data

## 28 pin package data, variant 1
##
## PIC24HJ32GP202
## PIC24HJ32GP302,
## PIC24HJ64GP202,
## PIC24HJ64GP502,
## PIC24HJ128GP202,
## PIC24HJ128GP502,
## PIC24FJ64GA002
## dsPIC33FJ32GP202

## Variant 2, differs by analog pin mapping
## PIC24HJ12GP202
##
   


@digio_28pin_1 = ("RA0", "RA1", "RA2", "RA3", "RA4",
"RB0", "RB1", "RB2", "RB3", "RB4", "RB5",
"RB6","RB7", "RB8", "RB9", "RB10", "RB11",
"RB12", "RB13", "RB14", "RB15");



%pullups_28pin_1 = (
   "RA0" => "_CN2",
   "RA1" => "_CN3",
   "RA2" => "_CN30",
   "RA3" => "_CN29",
   "RA4" => "_CN0",
   "RB0" => "_CN4",
   "RB1" => "_CN5",
   "RB2" => "_CN6",
   "RB3" => "_CN7",
   "RB4" => "_CN1",
   "RB5" => "_CN27",
   "RB6" => "_CN24",
   "RB7" => "_CN23",
   "RB8" => "_CN22",
   "RB9" => "_CN21",
   "RB10" => "_CN16",
   "RB11" => "_CN15",
   "RB12" => "_CN14",
   "RB13" => "_CN13",
   "RB14" => "_CN12",
   "RB15" => "_CN11",   
   );
 
 
 %opendrain_28pin_24H_1 = (
   "RA0" => "_ODCA0",
   "RA1" => "_ODCA1",
   "RA2" => "_ODCA2",
   "RA3" => "_ODCA3",
   "RA4" => "_ODCA4",
   "RB0" => "_ODCB0",
   "RB1" => "_ODCB1",
   "RB2" => "_ODCB2",
   "RB3" => "_ODCB3",
   "RB4" => "_ODCB4",
   "RB5" => "_ODCB5",
   "RB6" => "_ODCB6",
   "RB7" => "_ODCB7",
   "RB8" => "_ODCB8",
   "RB9" => "_ODCB9",
   "RB10" => "_ODCB10",
   "RB11" => "_ODCB11",
   "RB12" => "_ODCB12",
   "RB13" => "_ODCB13",
   "RB14" => "_ODCB14",
   "RB15" => "_ODCB15",   
   );

%opendrain_28pin_24F_1 = (
   "RA0" => "_ODA0",
   "RA1" => "_ODA1",
   "RA2" => "_ODA2",
   "RA3" => "_ODA3",
   "RA4" => "_ODA4",
   "RB0" => "_ODB0",
   "RB1" => "_ODB1",
   "RB2" => "_ODB2",
   "RB3" => "_ODB3",
   "RB4" => "_ODB4",
   "RB5" => "_ODB5",
   "RB6" => "_ODB6",
   "RB7" => "_ODB7",
   "RB8" => "_ODB8",
   "RB9" => "_ODB9",
   "RB10" => "_ODB10",
   "RB11" => "_ODB11",
   "RB12" => "_ODB12",
   "RB13" => "_ODB13",
   "RB14" => "_ODB14",
   "RB15" => "_ODB15",   
   );

   
  %analog_28pin_1 = (
   "RA0" => "_PCFG0",
   "RA1" => "_PCFG1",
   "RB0" => "_PCFG2",
   "RB1" => "_PCFG3",
   "RB2" => "_PCFG4",
   "RB3" => "_PCFG5",
   "RB12" => "_PCFG12",
   "RB13" => "_PCFG11",
   "RB14" => "_PCFG10",
   "RB15" => "_PCFG9",   
   );
   
  %RPanalog_28pin_1 = (
   0 => "_PCFG2",
   1 => "_PCFG3",
   2 => "_PCFG4",
   3 => "_PCFG5",
   12 => "_PCFG12",
   13 => "_PCFG11",
   14 => "_PCFG10",
   15 => "_PCFG9",   
   );
   

 %analog_28pin_2 = (
   "RA0" => "_PCFG0",
   "RA1" => "_PCFG1",
   "RB0" => "_PCFG2",
   "RB1" => "_PCFG3",
   "RB2" => "_PCFG4",
   "RB3" => "_PCFG5",
   "RB12" => "_PCFG9",
   "RB13" => "_PCFG8",
   "RB14" => "_PCFG7",
   "RB15" => "_PCFG6",   
   );

 %RPanalog_28pin_2 = (
   0 => "_PCFG2",
   1 => "_PCFG3",
   2 => "_PCFG4",
   3 => "_PCFG5",
   12 => "_PCFG9",
   13 => "_PCFG8",
   14 => "_PCFG7",
   15 => "_PCFG6",   
   );
   
   @digio_28pin_K = ("RA0", "RA1", "RA2", "RA3", "RA4", "RA5", "RA6", "RA7",
"RB0", "RB1", "RB2", "RB3", "RB4", "RB5",
"RB6","RB7", "RB8", "RB9", "RB10", "RB11",
"RB12", "RB13", "RB14", "RB15");

%pullups_28pin_K = (
   "RA0" => "_CN2",
   "RA1" => "_CN3",
   "RA2" => "_CN30",
   "RA3" => "_CN29",
   "RA4" => "_CN0",
   "RB0" => "_CN4",
   "RB1" => "_CN5",
   "RB2" => "_CN6",
   "RB3" => "_CN7",
   "RB4" => "_CN1",
   "RB5" => "_CN27",
   "RB6" => "_CN24",
   "RB7" => "_CN23",
   "RB8" => "_CN22",
   "RB9" => "_CN21",
   "RB10" => "_CN16",
   "RB11" => "_CN15",
   "RB12" => "_CN14",
   "RB13" => "_CN13",
   "RB14" => "_CN12",
   "RB15" => "_CN11",   
   );
   
   %opendrain_28pin_24K_1 = (
   "RA0" => "_ODA0",
   "RA1" => "_ODA1",
   "RA2" => "_ODA2",
   "RA3" => "_ODA3",
   "RA4" => "_ODA4",
   "RA5" => "_ODA5",
   "RA6" => "_ODA6",
   "RA7" => "_ODA7",
   "RB0" => "_ODB0",
   "RB1" => "_ODB1",
   "RB2" => "_ODB2",
   "RB3" => "_ODB3",
   "RB4" => "_ODB4",
   "RB5" => "_ODB5",
   "RB6" => "_ODB6",
   "RB7" => "_ODB7",
   "RB8" => "_ODB8",
   "RB9" => "_ODB9",
   "RB10" => "_ODB10",
   "RB11" => "_ODB11",
   "RB12" => "_ODB12",
   "RB13" => "_ODB13",
   "RB14" => "_ODB14",
   "RB15" => "_ODB15",   
   );
   
   
%analog_28pin_K = (
   "RA0" => "_PCFG0",
   "RA1" => "_PCFG1",
   "RB0" => "_PCFG2",
   "RB1" => "_PCFG3",
   "RB2" => "_PCFG4",
   "RB3" => "_PCFG5",
   "RB12" => "_PCFG12",
   "RB13" => "_PCFG11",
   "RB14" => "_PCFG10",
   );
   
%RPanalog_28pin_K = (  );



%disable_analog_28pin_K = (  
 "INT0" => "",
 "INT1" => "AN10",  
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
 "OCFA" => "AN10",
 "OCFB" => "",
 "U1RX" => "AN4",
 "U2RX" => "AN3",
 "U2CTS" => "",
 "SDI1" => "",
 "SCK1" => "",
 "SS1" => "",
 "SDI2" => "",
 "SCK2" => "",
 "SS2" => "",
 "C1RX" => "",
 "C2RX" => "",
 "C1OUT" => "AN10",
 "C2OUT" => "",
 "U1TX" => "",
 "U1RTS" => "",
 "U2TX" => "AN2",
 "U2RTS" => "",
 "SDO1" => "AN11",
 "SDO2" => "",
 "C1TX" => "",
 "OC1" => "",
 "OC2" => "",
 "OC3" => "",
 "OC4" => "",
 "OC5" => "",
 "RTCC" => "AN10",
 "U1BCLK" => "AN4",
 "U2BCLK" => "AN3",
 "C1INA" => "AN5",
 "C1INB" => "AN4",
 "C1INC" => "AN3",
 "C1IND" => "AN2",
 "C1OUT" => "",
 "C2INA" => "AN3",
 "C21INB" => "AN2",
 "C2INC" => "AN5",
 "C2IND" => "AN4",
 "C2OUT" => "",
 "CTED1" => "",
 "CTED2" => "AN12",
 "CTPLS" => "AN11", 
);

## PIC24 FB device

@digio_28pin_FB = ("RA0", "RA1", "RA2", "RA3", "RA4",
"RB0", "RB1", "RB2", "RB3", "RB4", "RB5",
"RB7", "RB8", "RB9", "RB10", "RB11",
 "RB13", "RB14", "RB15");

%pullups_28pin_FB = (
   "RA0" => "_CN2",
   "RA1" => "_CN3",
   "RA2" => "_CN30",
   "RA3" => "_CN29",
   "RA4" => "_CN0",
   "RB0" => "_CN4",
   "RB1" => "_CN5",
   "RB2" => "_CN6",
   "RB3" => "_CN7",
   "RB4" => "_CN1",
   "RB5" => "_CN27",
   "RB7" => "_CN23",
   "RB8" => "_CN22",
   "RB9" => "_CN21",
   "RB10" => "_CN16",
   "RB11" => "_CN15",
   "RB13" => "_CN13",
   "RB14" => "_CN12",
   "RB15" => "_CN11",   
   );
   
%opendrain_28pin_FB = (
   "RA0" => "_ODA0",
   "RA1" => "_ODA1",
   "RA2" => "_ODA2",
   "RA3" => "_ODA3",
   "RA4" => "_ODA4",
   "RB0" => "_ODB0",
   "RB1" => "_ODB1",
   "RB2" => "_ODB2",
   "RB3" => "_ODB3",
   "RB4" => "_ODB4",
   "RB5" => "_ODB5",
   "RB7" => "_ODB7",
   "RB8" => "_ODB8",
   "RB9" => "_ODB9",
   "RB10" => "_ODB10",
   "RB11" => "_ODB11",
   "RB13" => "_ODB13",
   "RB14" => "_ODB14",
   "RB15" => "_ODB15",   
   );
   
    %analog_28pin_FB = (
   "RA0" => "_PCFG0",
   "RA1" => "_PCFG1",
   "RB0" => "_PCFG2",
   "RB1" => "_PCFG3",
   "RB2" => "_PCFG4",
   "RB3" => "_PCFG5",
   "RB13" => "_PCFG11",
   "RB14" => "_PCFG10",
   "RB15" => "_PCFG9",   
   );
   
    %RPanalog_28pin_FB = (
   0 => "_PCFG2",
   1 => "_PCFG3",
   2 => "_PCFG4",
   3 => "_PCFG5",
   5 => "_PCFG0",
   6 => "_PCFG1",
   13 => "_PCFG11",
   14 => "_PCFG10",
   15 => "_PCFG9",   
   );

   
1;
 
   
   
   