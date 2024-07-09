; ------------ QUICK CLEAR FROM LAB -------------

; quick clear (uses movem to reduce fetch-execute cycle overhead)
;
; takes about half the number of clock cycles as the code in clear.s, and
; so runs in about 1/100th of a second (at 8MHz) instead of 1/50th

		xdef		_clear_screen_q
		xdef 		_set_video_base

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


;----------------------------------------

base_value 		equ		8
VIDEO_ADDR_HIGH equ 	$FF8201

_set_video_base:
		link	a6,#0
		movem.l	d0-7/a0-6,-(sp)
		move.l	base_value(a6),a1
		move.l	a1,d0
		lsr.l	#8,d0			
		lea VIDEO_ADDR_HIGH,a2
		movep.w d0,(a2)
		movem.l	(sp)+,d0-7/a0-6
		unlk	a6
		rts
;---------------------------------------------------			


zeros:		ds.l		13

