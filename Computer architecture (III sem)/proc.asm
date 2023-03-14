.686
.model flat

public _szukaj_max
public _szukaj4_max
.code

_szuKAj4_max PROC

	; ebp+8, ebp+12, ebp+16, ebp+20
	push ebp ; zapisanie zawartoœci EBP na stosie
	mov ebp, esp ; kopiowanie zawartoœci ESP do EBP

	mov eax, [ebp+8] ; liczba x
	cmp eax, [ebp+12] ; porownanie liczb x i y
	jge x_wieksza ; skok, gdy x >= y
	; przypadek x < y
	mov eax, [ebp+12] ; liczba y
	cmp eax, [ebp+16] ; porownanie liczb y i z
	jge y_wieksza ; skok, gdy y >= z
	; przypadek y < z
	; zatem z jest liczb¹ najwieksz¹
	wpisz_z: mov eax, [ebp+16] ; liczba z
	zakoncz:
	cmp eax, [ebp+20]
	jg eax_wieksza
	mov eax, [ebp+20]
	eax_wieksza:
	pop ebp
	ret
	x_wieksza:
	cmp eax, [ebp+16] ; porownanie x i z
	jge zakoncz ; skok, gdy x >= z
	jmp wpisz_z
	y_wieksza:
	mov eax, [ebp+12] ; liczba y
	jmp zakoncz

_szukaj4_max ENDP


_szukaj_max PROC
	push ebp ; zapisanie zawartoœci EBP na stosie
	mov ebp, esp ; kopiowanie zawartoœci ESP do EBP
	mov eax, [ebp+8] ; liczba x
	cmp eax, [ebp+12] ; porownanie liczb x i y
	jge x_wieksza ; skok, gdy x >= y
	; przypadek x < y
	mov eax, [ebp+12] ; liczba y
	cmp eax, [ebp+16] ; porownanie liczb y i z
	jge y_wieksza ; skok, gdy y >= z
	; przypadek y < z
	; zatem z jest liczb¹ najwieksz¹
	wpisz_z: mov eax, [ebp+16] ; liczba z
	zakoncz:
	pop ebp
	ret
	x_wieksza:
	cmp eax, [ebp+16] ; porownanie x i z
	jge zakoncz ; skok, gdy x >= z
	jmp wpisz_z
	y_wieksza:
	mov eax, [ebp+12] ; liczba y
	jmp zakoncz
_szukaj_max ENDP

END