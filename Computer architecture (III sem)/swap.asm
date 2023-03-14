.686					; Szymon Hejmanowski
.model flat				; Grupa: 2
public _przestaw_abs	; Data: 01.12.2022
public _to_abs			; Termin: 01.12.2022
.code					; Lab4

_to_abs PROC

	push ebp
	mov ebp, esp
	push ebx
	mov ebx, [ebp+8]
	mov ecx, [ebp+12]
	
	ptl: mov eax, [ebx]

	cmp eax, 0
	jnl dont_change
	neg eax
	mov [ebx], eax
	dont_change:

	add ebx, 4
	loop ptl

	pop ebx
	pop ebp
	ret

_to_abs ENDP

_przestaw_abs PROC
push ebp ; zapisanie zawartoœci EBP na stosie
mov ebp,esp ; kopiowanie zawartoœci ESP do EBP
push ebx ; przechowanie zawartoœci rejestru EBX

push [ebp+12]
push [ebp+8]
call _to_abs
add esp, 8

mov ebx, [ebp+8] ; adres tablicy tabl
mov ecx, [ebp+12] ; liczba elementów tablicy

dec ecx
; wpisanie kolejnego elementu tablicy do rejestru EAX
ptl: mov eax, [ebx]
; porównanie elementu tablicy wpisanego do EAX z nastêpnym

cmp eax, [ebx+4]
jle gotowe ; skok, gdy nie ma przestawiania
; zamiana s¹siednich elementów tablicy
mov edx, [ebx+4]
mov [ebx], edx
mov [ebx+4], eax
gotowe:
add ebx, 4 ; wyznaczenie adresu kolejnego elementu
loop ptl ; organizacja pêtli
pop ebx ; odtworzenie zawartoœci rejestrów
pop ebp
ret ; powrót do programu g³ównego
_przestaw_abs ENDP
 END
