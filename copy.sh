#!/bin/sh
#+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#+ copy.sh
#+   copy libs to arduino
#+ author
#+   meegoo.tsui@gmail.com, 2013-01-29
#+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
LOCAL_LIB_PATH=SSD1351OLED
if [ "$OS" == "Windows_NT" ]; then
	ARDUINO_LIB_PATH=$HOME/Documents/Arduino/libraries
else
	OS=$(awk '/DISTRIB_ID=/' /etc/*-release | sed 's/DISTRIB_ID=//' | tr '[:upper:]' '[:lower:]')
	ARCH=$(uname -m | sed 's/x86_//;s/i[3-6]86/32/')
	VERSION=$(awk '/DISTRIB_RELEASE=/' /etc/*-release | sed 's/DISTRIB_RELEASE=//' | sed 's/[.]0/./')
	echo "Copy for $OS-$ARCH-$VERSION"
	ARDUINO_LIB_PATH=$HOME/sketchbook/libraries
fi

#+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
if [ ! -d "$ARDUINO_LIB_PATH" ]; then
	mkdir -p "$ARDUINO_LIB_PATH"
fi

set -v on
cp -rf $LOCAL_LIB_PATH "$ARDUINO_LIB_PATH"
