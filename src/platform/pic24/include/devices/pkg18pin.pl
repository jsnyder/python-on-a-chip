###package data

## 18 pin package data, variant 1
## PIC24HJ12GP201
## dsPIC33FJ32GP201

@digio_18pin_1 = (
"RA0", 
"RA1", 
"RA2",
"RA3", 
"RA4",
"RB0", 
"RB1", 
"RB4", 
"RB7", 
"RB8", 
"RB9", 
"RB14", 
"RB15");



%pullups_18pin_1 = (
   "RA0" => "_CN2",
   "RA1" => "_CN3",
   "RA2" => "_CN30",
   "RA3" => "_CN29",
   "RA4" => "_CN0",
   "RB0" => "_CN4",
   "RB1" => "_CN5",
   "RB4" => "_CN1",
   "RB7" => "_CN23",
   "RB8" => "_CN22",
   "RB9" => "_CN21",
   "RB14" => "_CN12",
   "RB15" => "_CN11",   
   );
 
 
 %opendrain_18pin_24H_1 = (
   "RA0" => "_ODCA0",
   "RA1" => "_ODCA1",
   "RA2" => "_ODCA2",
   "RA3" => "_ODCA3",
   "RA4" => "_ODCA4",
   "RB0" => "_ODCB0",
   "RB1" => "_ODCB1",
   "RB4" => "_ODCB4",
   "RB7" => "_ODCB7",
   "RB8" => "_ODCB8",
   "RB9" => "_ODCB9",
   "RB14" => "_ODCB14",
   "RB15" => "_ODCB15",   
   );

   
  %analog_18pin_1 = (
   "RA0" => "_PCFG0",
   "RA1" => "_PCFG1",
   "RB0" => "_PCFG2",
   "RB1" => "_PCFG3",
   "RB14" => "_PCFG7",
   "RB15" => "_PCFG6",   
   );
   
  %RPanalog_18pin_1 = (
   0 => "_PCFG2",
   1 => "_PCFG3",
   14 => "_PCFG7",
   15 => "_PCFG6",   
   );
   
