#!/bin/bash

MUSICROOT=~/Music

if [ $1 = '-v' ]; then

shift 1

find -LE $MUSICROOT -type f -iname "*$**" -iregex '.*\.(3g[2|p]|a(ac|c3|dts|if[c|f]?|mr|nd|u)|caf|m4[a|r]|mp([1-4|a]|eg[0,9]?)|sd2|wav)' -print -exec afplay "{}" \; &

elif [ $1 = '-g' ]; then

shift 1

find -E $MUSICROOT -type f -iname "*$**" -iregex '.*\.(3g[2|p]|a(ac|c3|dts|if[c|f]?|mr|nd|u)|caf|m4[a|r]|mp([1-4|a]|eg[0,9]?)|sd2|wav)' -exec open -a QuickTime\ Player "{}" \; -exec osascript -e 'tell application "QuickTime Player" to play document 1' \; &
else

find -E $MUSICROOT -type f -iname "*$**" -iregex '.*\.(3g[2|p]|a(ac|c3|dts|if[c|f]?|mr|nd|u)|caf|m4[a|r]|mp([1-4|a]|eg[0,9]?)|sd2|wav)' -exec afplay "{}" \; &

fi

