        ; Local inclusions.
        .nolist
        .list

        .section .libdsp, code

        .global _FASTSUM                    ; provide global scope to routine
_FASTSUM:
    	disi  #0x100  ;fix to disable interrupts when running pid loop
        push.s
	push w2
	push w1
	push w0

	clr w2;
	repeat   #8-1
	add    w2,[w0++],w2
	mov w2, [w1]

	pop w0
	pop w1
	pop w2
        pop.s
	disi #0
        return

