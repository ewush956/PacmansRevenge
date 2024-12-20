
            xdef _trap28_isr
            xdef _trap70_isr
            xdef _set_ipl
            xref _do_vbl
            xref _do_IKBD_isr

_trap28_isr:  
            movem.l d0-2/a0-2,-(sp)
            jsr _do_vbl
            movem.l (sp)+,d0-2/a0-2
            rte
            
_trap70_isr:    
            movem.l d0-2/a0-2,-(sp)
            jsr _do_IKBD_isr
            movem.l (sp)+,d0-2/a0-2
            rte


;-----------
; Credit to Marc for this sub routine below--got this from the course material
;------------
_set_ipl:   
            move.w sr,d0
            move.w d0,-(sp)         ;place orig. sr on stack
            lsr.w #8,d0             ;will return orig. ipl
            and.w #$0007,d0         ; ... in d0.w
            andi.w #$F8FF,(sp)
            move.w d1,-(sp)
            move.w 8(sp),d1         ; place new ipl in d1.w
            lsl.w #8,d1
            and.w #$0700,d1
            or.w d1,2(sp)           ; insert it into sr on stack
            Page 21 of 28
            move.w (sp)+,d1
            rte                    