#!/bin/bash

w=0
while [ "$w" != 7 ]
do
m1="1. Nazwa pliku: $NAZWA"
m2="2. Katalog: $KATALOG"
m3="3. Większe niż: $WIEKSZE"
m4="4. Właściciel: $WLASCICIEL"
m5="5. Zawartość: $ZAWARTOSC"
m6="6. Szukaj: " 
m7="7. Koniec: " 

MENU=("$m1" "$m2" "$m3" "$m4" "$m5" "$m6" "$m7")
	w=$(zenity --list --column=MENU "${MENU[@]}" --height 350 --width 350)

case "$w" in

        $m1)NAZWA=$(zenity --entry --title "Szukaj" --text "Podaj nazwe pliku: ")
            SZUK_NAZWA="-name $NAZWA"
			if [ -z $NAZWA ]
			then
			SZUK_NAZWA=""
			fi
			;;

        $m2)KATALOG=$(zenity --entry --title "Szukaj" --text "Podaj katalog: ")
			SZUK_KATALOG="/home/${KATALOG}"
			if [ -z $KATALOG ]
            then
            SZUK_KATALOG=""
            fi
			;;

       $m3)WIEKSZE=$(zenity --entry --title "Szukaj" --text "Podaj MIN rozmiar pliku: ")
			SZUK_WIEKSZE="-size +${WIEKSZE}c"
			if [ -z $WIEKSZE ]
            then
            SZUK_WIEKSZE=""
            fi
			;;

        $m4)WLASCICIEL=$(zenity --entry --title "Szukaj" --text "Podaj właściciela: ")
			SZUK_WLASCICIEL="-user ${WLASCICIEL}"
			if [ -z $WLASCICIEL ]
            then
            SZUK_WLASCICIEL=""
            fi
			;;

        $m5)ZAWARTOSC=$(zenity --entry --title "Szukaj" --text "Podaj zawartość: ")
			SZUK_ZAWARTOSC="-exec grep -l "$ZAWARTOSC" {} +"
			if [ -z "$ZAWARTOSC" ]
            then
            SZUK_ZAWARTOSC=""
            fi
			;;
		$m6)znaleziono="find $SZUK_KATALOG -type f $SZUK_NAZWA $SZUK_WIEKSZE $SZUK_WLASCICIEL $SZUK_ZAWARTOSC | \zenity --text-info --title \"Znaleziono\" --width 320 --height 400"
eval $znaleziono
			;;
		$m7) w=7
			;;
	esac

done


