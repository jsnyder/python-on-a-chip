###package data

## 64 pin package data, variant 1
## PIC24HJ64GP206
## PIC24HJ128GP206
## PIC24HJ256GP206
## PIC24HJ128GP306
## PIC24HJ64GP506
## PIC24HJ128GP506


@digio_64pin_1 = (
"RB0",
"RB1",
"RB2",
"RB3",
"RB4",
"RB5",
"RB6",
"RB7",
"RB8",
"RB9",
"RB10",
"RB11",
"RB12",
"RB13",
"RB14",
"RB15",
"RC1",
"RC2",
"RC12",
"RC13",
"RC14",
"RC15",
"RD0",
"RD1",
"RD2",
"RD3",
"RD4",
"RD5",
"RD6",
"RD7",
"RD8",
"RD9",
"RD10",
"RD11",
"RF0",
"RF1",
"RF2",
"RF3",
"RF4",
"RF5",
"RF6",
"RG0",
"RG1",
"RG2",
"RG3",
"RG6",
"RG7",
"RG8",
"RG9",
"RG12",
"RG13",
"RG14",
"RG15"
);




%pullups_64pin_1 = (
"RB0"=> "_CN2",
"RB1"=> "_CN3",
"RB2"=> "_CN4",
"RB3"=> "_CN5",
"RB4"=> "_CN6",
"RB5"=> "_CN7",
"RB15"=> "_CN12",
"RC13"=> "_CN1",
"RC14"=> "_CN0",
"RD4"=> "_CN13",
"RD5"=> "_CN14",
"RD6"=> "_CN15",
"RD7"=> "_CN16",
"RF4"=> "_CN17",
"RF5"=> "_CN18",
"RG6"=> "_CN8",
"RG7"=> "_CN9",
"RG8"=> "_CN10",
"RG9"=> "_CN11",
   );
 
 ##these parts are strange, open drain no avaialable
 ## on RB or RC
 
 %opendrain_64pin_24H_1 = (
 "RD0"=> "_ODCD0",
"RD1"=> "_ODCD1",
"RD2"=> "_ODCD2",
"RD3"=> "_ODCD3",
"RD4"=> "_ODCD4",
"RD5"=> "_ODCD5",
"RD6"=> "_ODCD6",
"RD7"=> "_ODCD7",
"RD8"=> "_ODCD8",
"RD9"=> "_ODCD9",
"RD10"=> "_ODCD10",
"RD11"=> "_ODCD11",
"RF0"=> "_ODCF0",
"RF1"=> "_ODCF1",
"RF2"=> "_ODCF2",
"RF3"=> "_ODCF3",
"RF4"=> "_ODCF4",
"RF5"=> "_ODCF5",
"RF6"=> "_ODCF6",
"RG0"=> "_ODCG0",
"RG1"=> "_ODCG1",
"RG2"=> "_ODCG2",
"RG3"=> "_ODCG3",
"RG6"=> "_ODCG6",
"RG7"=> "_ODCG7",
"RG8"=> "_ODCG8",
"RG9"=> "_ODCG9",
"RG12"=> "_ODCG12",
"RG13"=> "_ODCG13",
"RG14"=> "_ODCG14",
"RG15" => "_ODCG15",
   );

   
  %analog_64pin_1 = (  
 "RB0"=> "_PCFG0",
"RB1"=> "_PCFG1",
"RB2"=> "_PCFG2",
"RB3"=> "_PCFG3",
"RB4"=> "_PCFG4",
"RB5"=> "_PCFG5",
"RB6"=> "_PCFG6",
"RB7"=> "_PCFG7",
"RB8"=> "_PCFG8",
"RB9"=> "_PCFG9",
"RB10"=> "_PCFG10",
"RB11"=> "_PCFG11",
"RB12"=> "_PCFG12",
"RB13"=> "_PCFG13",
"RB14"=> "_PCFG14",
"RB15"=> "_PCFG15",
"RC1"=> "_PCFG16",
"RC2"=> "_PCFG17",
   );
   
   
  %RPanalog_64pin_1 = (  );
  
  1;
  
  
   
