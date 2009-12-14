#!/usr/bin/env python

import urllib, zipfile, StringIO
from os import path, mkdir

extra_headers = ['stm32f10x.h','core_cm3.h','cortexm3_macro.h','system_stm32f10x.h']
extra_sources = ['core_cm3.c','cortexm3_macro.s','system_stm32f10x.c']
startup_files = ['startup_stm32f10x_hd.s']

stm32liburl = 'http://www.st.com/stonline/products/support/micro/files/stm32f10x_stdperiph_lib.zip'

webFile = urllib.urlopen(stm32liburl)
print 'Downloading Peripheral Library...'
stm32lib = zipfile.ZipFile(StringIO.StringIO(webFile.read()))

if not path.exists('FWlib'):
  mkdir('FWlib')

print 'Extracting...'
for file in stm32lib.filelist:
  if path.split(path.dirname(file.filename))[0][-26:] == 'STM32F10x_StdPeriph_Driver':
     if file.filename[-1] == 'c' or file.filename[-1] == 'h':
       file.filename = path.join('FWlib',path.split(path.dirname(file.filename))[1], path.basename(file.filename))
       print file.filename
       stm32lib.extract(file)
  if path.basename(file.filename) in extra_headers:
    file.filename = path.join('FWlib','inc',path.basename(file.filename))
    print file.filename
    stm32lib.extract(file)
  if path.basename(file.filename) in extra_sources:
    file.filename = path.join('FWlib','src',path.basename(file.filename))
    print file.filename
    stm32lib.extract(file)
  if path.basename(file.filename) in startup_files:
    if path.split(path.dirname(file.filename))[1] == 'gcc':
      file.filename = path.join('FWlib','src',path.basename(file.filename))
      print file.filename
      stm32lib.extract(file)
