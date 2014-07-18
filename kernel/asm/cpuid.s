
[GLOBAL cpuid_get]

; ---------------------------------------
; cpuid_get
;
; Fetches all registers after a cpuid call
;
cpuid_get:
	push	rax								; save registers known to be modifie
	push	rbx
	push	rcx
	push	rdx

	mov		rax, rdi						; code is passed in rdi
	cpuid

	mov		[rsi], eax						; rsi holds a pointer to the 16 byte string
	mov		[rsi + 4], ebx					; to store the post-cpuid register states in
	mov		[rsi + 8], ecx
	mov		[rsi + 12], edx

	pop		rdx								; restore registers after use
	pop		rcx
	pop		rbx
	pop		rax

	ret 									; get out - nothing on the stack
