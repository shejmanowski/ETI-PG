.686
.model flat
public _tablica_nieparzystych
extern _malloc : PROC
.code

_tablica_nieparzystych PROC

	push ebp		; PRO
	mov ebp, esp	;    LOG
	push ebx
	push esi
	push edi
	push edx

	mov edi, [ebp+12] ; zapis liczby elementow tablicy do ecx
	mov ecx, [edi]
	mov ebx, 0
	mov esi, [ebp+8]  ; zapis adresu talibcy do esi
	;add esi, 8


	check_odd_n:
		mov dx, [esi]	; wpisz wartosc elementu tablicy
		bt dx, 0		; sprwadz czy parzysta
		jnc evenn			; jesli parzysta skacz dalej
		inc ebx			; jesli nieparzysta zwieksz licznik
		evenn:
		add esi, 2
	loop check_odd_n

	mov eax, ebx	; ebx - 
	mov ecx, 4
	mul ecx
	push eax
	call _malloc
	add esp, 4

	mov esi, [ebp+12]
	mov ecx, [esi]
	mov [edi], ebx
	mov esi, [ebp+8]
	mov edi, eax


	uzupelnij_tablice:
		mov dx, [esi]	; wpisz wartosc elementu tablicy
		bt dx, 0		; sprwadz czy parzysta
		jnc evennn			; jesli parzysta skacz dalej
		mov [edi], dx
		mov word ptr [edi+2], 0
		mov dword ptr [edi+4], 0
		add edi, 8
		evennn:
		add esi, 2
	loop uzupelnij_tablice

	pop edx
	pop edi
	pop esi
	pop ebx
	pop ebp
	ret
_tablica_nieparzystych ENDP

END