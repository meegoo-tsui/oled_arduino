#!/bin/sh
#+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#+ copy.sh
#+   copy libs to arduino
#+ author
#+   meegoo.tsui@gmail.com, 2013-01-29
#+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
LOCAL_LIB_PATH=SSD1351OLED
ARDUINO_LIB_PATH=$HOME/Documents/Arduino/libraries

#+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
if [ ! -d "$ARDUINO_LIB_PATH" ]; then
	mkdir -p "$ARDUINO_LIB_PATH"
fi

set -v on
cp -rf $LOCAL_LIB_PATH "$ARDUINO_LIB_PATH"
