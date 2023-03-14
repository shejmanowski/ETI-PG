.686
.model flat
extern _ExitProcess@4 : PROC
extern __write : PROC
extern __read : PROC
public _main

.data
znaki db 12 dup (?)
obszar db 12 dup (?)
dziesiec dd 10 ; mnożnik
dekoder db '0123456789ABCDEF'
liczba dd 43626h

.code

wyswietl_EAX PROC
	pusha
	push ebp
	mov ebp, esp


	cmp edi, 0		; if edi = 0, then just skip whole procedure
	je endf

	mov eax, [edi]

	mov esi, 10		; indeks w tablicy 'znaki'
	mov ebx, 10		; dzielnik równy 10
	sub esp, 12
	konwersja:
	mov edx, 0		; zerowanie starszej części dzielnej
	div ebx			; dzielenie przez 10, reszta w EDX,
					; iloraz w EAX
	add dl, 30H		; zamiana reszty z dzielenia na kod
					; ASCII

	mov [esp + esi], dl	; mov znaki [esi], dl		; zapisanie cyfry w kodzie ASCII
	dec esi					; zmniejszenie indeksu
	cmp eax, 0				; sprawdzenie czy iloraz = 0
	jne konwersja			; skok, gdy iloraz niezerowy
			
	; wypełnienie pozostałych bajtów spacjami i wpisanie
	; znaków nowego wiersza
	wypeln:
	or esi, esi
	jz wyswietl						; skok, gdy ESI = 0S
	; mov byte PTR znaki [esi], 20H	; kod spacji
	mov byte ptr [esp + esi], 20h
	dec esi							; zmniejszenie indeksu
	jmp wypeln
	wyswietl:
	; mov byte PTR znaki [0], 0AH			; kod nowego wiersza
	; mov byte PTR znaki [11], 0AH		; kod nowego wiersza
	mov byte ptr [esp], 0Ah
	mov byte ptr [esp + 11], 0Ah
	mov ebx, esp
	; wyświetlenie cyfr na ekranie
	push dword PTR 12				; liczba wyświetlanych znaków
	; push dword PTR OFFSET znaki		; adres wyśw. obszaru
	push dword ptr ebx
	push dword PTR 1				; numer urządzenia (ekran ma numer 1)
	call __write					; wyświetlenie liczby na ekranie
	add esp, 12						; usunięcie parametrów ze stosu

	endf:

	mov esp, ebp
	pop ebp
	popa
	ret
wyswietl_EAX ENDP

wczytaj_do_EAX PROC
	push ebx
	push ecx

	push dword PTR 12
	push dword PTR OFFSET obszar ; adres obszaru pamięci
	push dword PTR 0; numer urządzenia (0 dla klawiatury)
	call __read ; odczytywanie znaków z klawiatury
	; (dwa znaki podkreślenia przed read)
	add esp, 12 ; usunięcie parametrów ze stosu
	; bieżąca wartość przekształcanej liczby przechowywana jest
	; w rejestrze EAX; przyjmujemy 0 jako wartość początkową
	mov eax, 0
	mov ebx, OFFSET obszar ; adres obszaru ze znakami
	pobieraj_znaki:
	mov cl, [ebx] ; pobranie kolejnej cyfry w kodzie
	; ASCII
	inc ebx ; zwiększenie indeksu
	cmp cl,10 ; sprawdzenie czy naciśnięto Enter
	je byl_enter ; skok, gdy naciśnięto Enter
	sub cl, 30H ; zamiana kodu ASCII na wartość cyfry
	movzx ecx, cl ; przechowanie wartości cyfry w
	; rejestrze ECX
	; mnożenie wcześniej obliczonej wartości razy 10
	mul dword PTR dziesiec
	add eax, ecx ; dodanie ostatnio odczytanej cyfry
	jmp pobieraj_znaki ; skok na początek pętli
	byl_enter:
	; wartość binarna wprowadzonej liczby znajduje się teraz w rejestrze EAX

	pop ecx
	pop ebx
	ret
wczytaj_do_EAX ENDP

kwadrat_z_EAX PROC
	
	mul eax

	ret
kwadrat_z_EAX ENDP

wyswietl_EAX_hex PROC
; wyświetlanie zawartości rejestru EAX
; w postaci liczby szesnastkowej
pusha ; przechowanie rejestrów

; rezerwacja 12 bajtów na stosie (poprzez zmniejszenie
; rejestru ESP) przeznaczonych na tymczasowe przechowanie
; cyfr szesnastkowych wyświetlanej liczby
sub esp, 12
mov edi, esp ; adres zarezerwowanego obszaru
; pamięci
; przygotowanie konwersji
mov ecx, 8 ; liczba obiegów pętli konwersji
mov esi, 1 ; indeks początkowy używany przy
; zapisie cyfr
; pętla konwersji
ptl3hex:
; przesunięcie cykliczne (obrót) rejestru EAX o 4 bity w lewo
; w szczególności, w pierwszym obiegu pętli bity nr 31 - 28
; rejestru EAX zostaną przesunięte na pozycje 3 - 0
rol eax, 4
; wyodrębnienie 4 najmłodszych bitów i odczytanie z tablicy
; 'dekoder' odpowiadającej im cyfry w zapisie szesnastkowym
mov ebx, eax ; kopiowanie EAX do EBX
and ebx, 0000000FH ; zerowanie bitów 31 - 4 rej.EBX
mov dl, dekoder[ebx] ; pobranie cyfry z tablicy
; przesłanie cyfry do obszaru roboczego
mov [edi][esi], dl
inc esi ;inkrementacja modyfikatora
loop ptl3hex ; sterowanie pętlą

; wpisanie znaku nowego wiersza przed i po cyfrach
mov byte PTR [edi][0], 10
mov byte PTR [edi][9], 10

mov esi, 1
zero_to_space:
	mov bl, [edi][esi]
	cmp bl, 30h
	jne done
	mov byte PTR[edi][esi], ' '
	inc esi

loop zero_to_space

done:
; wyświetlenie przygotowanych cyfr
push 10 ; 8 cyfr + 2 znaki nowego wiersza
push edi ; adres obszaru roboczego
push 1 ; nr urządzenia (tu: ekran)
call __write ; wyświetlenie
; usunięcie ze stosu 24 bajtów, w tym 12 bajtów zapisanych
; przez 3 rozkazy push przed rozkazem call
; i 12 bajtów zarezerwowanych na początku podprogramu
add esp, 24

popa ; odtworzenie rejestrów
ret ; powrót z podprogramu
wyswietl_EAX_hex ENDP

wczytaj_do_EAX_hex PROC
; wczytywanie liczby szesnastkowej z klawiatury – liczba po
; konwersji na postać binarną zostaje wpisana do rejestru EAX
; po wprowadzeniu ostatniej cyfry należy nacisnąć klawisz
; Enter
push ebx
push ecx
push edx
push esi
push edi
push ebp
; rezerwacja 12 bajtów na stosie przeznaczonych na tymczasowe
; przechowanie cyfr szesnastkowych wyświetlanej liczby
sub esp, 12 ; rezerwacja poprzez zmniejszenie ESP
mov esi, esp ; adres zarezerwowanego obszaru pamięci
push dword PTR 10 ; max ilość znaków wczytyw. liczby
push esi ; adres obszaru pamięci
push dword PTR 0; numer urządzenia (0 dla klawiatury)
call __read ; odczytywanie znaków z klawiatury
; (dwa znaki podkreślenia przed read)
add esp, 12 ; usunięcie parametrów ze stosu
mov eax, 0 ; dotychczas uzyskany wynik
pocz_konw:
mov dl, [esi] ; pobranie kolejnego bajtu
inc esi ; inkrementacja indeksu
cmp dl, 10 ; sprawdzenie czy naciśnięto Enter
je gotowe ; skok do końca podprogramu
; sprawdzenie czy wprowadzony znak jest cyfrą 0, 1, 2 , ..., 9
cmp dl, '0'
jb pocz_konw ; inny znak jest ignorowany
cmp dl, '9'
ja sprawdzaj_dalej
sub dl, '0' ; zamiana kodu ASCII na wartość cyfry
dopisz:
shl eax, 4 ; przesunięcie logiczne w lewo o 4 bity
or al, dl ; dopisanie utworzonego kodu 4-bitowego
; na 4 ostatnie bity rejestru EAX
jmp pocz_konw ; skok na początek pętli konwersji
; sprawdzenie czy wprowadzony znak jest cyfrą A, B, ..., F
sprawdzaj_dalej:
cmp dl, 'A'
jb pocz_konw ; inny znak jest ignorowany
cmp dl, 'F'
ja sprawdzaj_dalej2
sub dl, 'A' - 10 ; wyznaczenie kodu binarnego
jmp dopisz
; sprawdzenie czy wprowadzony znak jest cyfrą a, b, ..., f
sprawdzaj_dalej2:
cmp dl, 'a'
jb pocz_konw ; inny znak jest ignorowany
cmp dl, 'f'
ja pocz_konw ; inny znak jest ignorowany
sub dl, 'a' - 10
jmp dopisz
gotowe:
; zwolnienie zarezerwowanego obszaru pamięci
add esp, 12
pop ebp
pop edi
pop esi
pop edx
pop ecx
pop ebx
ret
wczytaj_do_EAX_hex ENDP


_main PROC
	
	mov edi, offset liczba
	call wyswietl_EAX
	
	call _ExitProcess@4

_main ENDP

END