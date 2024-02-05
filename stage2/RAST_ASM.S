;			xdef		_plot_something_2

; [TO DO] delete this example function

;y			equ		14
;x			equ		12
;base			equ		8

;_plot_something_2:	link		a6,#0
;			movea.l		base(a6),a0
;			move.w		x(a6),d0
;			move.w		y(a6),d1
		;	...		...
;			unlk		a6
;			rts

; recall: cc68x assumes d0-2/a0-2 are *not* preserved across subroutine calls!

; ------------ QUICK CLEAR FROM LAB -------------

; quick clear (uses movem to reduce fetch-execute cycle overhead)
;
; takes about half the number of clock cycles as the code in clear.s, and
; so runs in about 1/100th of a second (at 8MHz) instead of 1/50th

		xdef		_clear_screen_q

base		equ		64		; offset from SP, not A6

_clear_screen_q:	movem.l		d0-7/a0-6,-(sp)
		lea		zeros,a0
		movem.l		(a0)+,d1-7/a1-6
		movea.l		base(sp),a0
		adda.l		#32000,a0
		move.w		#614,d0
fill_loop:	movem.l		d1-7/a1-6,-(a0)
		dbra		d0,fill_loop
		movem.l		d1-5,-(a0)
		movem.l		(sp)+,d0-7/a0-6
		rts

zeros:		ds.l		13
; -----------------------
		xdef		_clear_screen

base		equ		8

_clear_screen:	link		a6,#0
		movem.l		d0-1/a0,-(sp)
		movea.l		base(a6),a0
		move.w		#7999,d0
		clr.l		d1
fill_loop:	move.l		d1,(a0)+        ; strangely, faster than clr
		dbra		d0,fill_loop
		movem.l		(sp)+,d0-1/a0
		unlk		a6
		rts
; ----------- from 2655

	xdef	_read_char

_read_char:	movem.l	d1-d2/a0-a2,-(sp)
		move.w	#1,-(sp)
		trap	#1
		addq.l	#2,sp
		movem.l	(sp)+,d1-d2/a0-a2
		rts
