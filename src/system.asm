
global stacktop

section .bootstrap
global set_pd_bootstrap
set_pd_bootstrap:
	push ebp
	mov ebp, esp
	mov ecx, [ebp+8]
	mov cr3, ecx
	pop ebp
	ret

global enable_mmu
enable_mmu:
	; enable 4mb pages
	mov ecx, cr4
	or ecx, 0x00000010
	mov cr4, ecx

	; enable mmu
	mov ecx, cr0
	or ecx, 0x80000000
	mov cr0, ecx
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

