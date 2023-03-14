#!/bin/bash
w=0
while [ $w != 7 ]
do
echo "1. File name: $NAZWA"
echo "2. Directory: $KATALOG"
echo "3. Size greater then: $WIEKSZE"
echo "4. User: $WLASCICIEL"
echo "5. Content: $ZAWARTOSC"
echo "6. Find " 
echo "7. Exit: " 

read w
clear
case "$w" in

		1)read NAZWA
            SZUK_NAZWA="-name $NAZWA"
			if [ -z $NAZWA ]
			then
			SZUK_NAZWA=""
			fi
			;;
		2)read KATALOG
			SZUK_KATALOG="${KATALOG}"
			if [ -z $KATALOG ]
            then
            SZUK_KATALOG=""
            fi
			;;
		3)read WIEKSZE
			SZUK_WIEKSZE="-size +${WIEKSZE}c"
			if [ -z $WIEKSZE ]
            then
            SZUK_WIEKSZE=""
            fi
			;;
		4)read WLASCICIEL
			SZUK_WLASCICIEL="-user ${WLASCICIEL}"
			if [ -z $WLASCICIEL ]
            then
            SZUK_WLASCICIEL=""
            fi
			;;
		5)read ZAWARTOSC
			SZUK_ZAWARTOSC="-exec grep -l "$ZAWARTOSC" {} ;"
			if [ -z "$ZAWARTOSC" ]
            then
            SZUK_ZAWARTOSC=""
            fi
			;;
		6)szukaj=$(find $SZUK_KATALOG -type f $SZUK_NAZWA $SZUK_WIEKSZE $SZUK_WLASCICIEL $SZUK_ZAWARTOSC)
if [ -z "$szukaj" ]; then
echo "No such file"
else
echo $szukaj
fi
			;;
		7) w=7
			;;
	esac

done


