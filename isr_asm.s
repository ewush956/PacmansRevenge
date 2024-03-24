
            xdef _trap28_isr
            xref _do_vbl

_trap28_isr:  
            movem.l d0-2/a0-2,-(sp)
            jsr _do_vbl
            movem.l (sp)+,d0-2/a0-2
                    ;change render requests here possibly ?
            rte
            