
            xdef _trap28_isr
            xdef _trap70_isr
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
            