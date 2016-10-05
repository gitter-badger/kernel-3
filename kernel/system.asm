
global stacktop

section .bootstrap
global set_pd_bootstrap
set_pd_bootstrap:
	push ebp
	mov ebp, esp
	mov eax, [ebp+8]
	mov cr3, eax
	pop ebp
	ret

global enable_mmu
enable_mmu:
	; enable 4mb pages
	mov eax, cr4
	or eax, 0x00000010
	mov cr4, eax

	; enable mmu
	mov eax, cr0
	or eax, 0x80000000
	mov cr0, eax
	ret

section .text
global set_pd
set_pd:
	push ebp
	mov ebp, esp
	mov eax, [ebp+8]
	mov cr3, eax
	pop ebp
	ret

section .bss
align 4
stack:
	resb 16384
stacktop:

