#!/bin/sh
#+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#+ copy.sh
#+   copy libs to arduino
#+ author
#+   meegoo.tsui@gmail.com, 2013-01-29
#+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
LOCAL_LIB_PATH=SSD1351OLED
ARDUINO_LIB_PATH=$HOME/Documents/Arduino/libraries/$LOCAL_LIB_PATH
LIB_H=$LOCAL_LIB_PATH/$LOCAL_LIB_PATH.h
LIB_CC=$LOCAL_LIB_PATH/$LOCAL_LIB_PATH.cpp
LIB_KEYWORDS=$LOCAL_LIB_PATH/keywords.txt

#+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
if [ ! -d "$ARDUINO_LIB_PATH" ]; then
	mkdir "$ARDUINO_LIB_PATH"
fi

set -v on
cp -f $LIB_H        "$ARDUINO_LIB_PATH"
cp -f $LIB_CC       "$ARDUINO_LIB_PATH"
cp -f $LIB_KEYWORDS "$ARDUINO_LIB_PATH"
