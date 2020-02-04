
from migen import *
from migen.genlib.cdc import MultiReg

from litex.soc.interconnect.csr import *

# VGA Controller ---------------------------------------------------------------------------

class VGAcontroller(Module, AutoCSR):
    """VGA display controller
    
    Provides a video controller circuit to drive the sync and color signals with the correct timing
    in order to produce a working display system.
    """
    def __init__(self, hs, vs, r_out, g_out, b_out, sram):
        h_rez = 640
        h_startsync = 640 + 16
        h_endsync = 640 + 16 + 96
        h_max = 800
        
        v_rez = 480
        v_startsync = 480 + 10
        v_endsync = 480 + 10 + 2
        v_max = 525
        
        pxl_tick_count = Signal(2)
        pxl_tick = Signal()
        
        self.active = Signal()
        
        self.h_count = Signal(10)
        self.v_count = Signal(10)
        
        
        
        """
        vram_data_width = 4 # color bits per pixel 2^6 > 3*12bits
        vram_depth = h_rez * v_rez
        
        mem = Memory(vram_data_width, vram_depth)
        port = mem.get_port(write_capable = True, has_re=True)
        """
        # # #
        self._writeenable = CSRStorage()
        self._adr = CSRStorage(19)
        self._data_write = CSRStorage(32)
        self._sel = CSRStorage(4)
        
        self.comb += [
        	If(self._writeenable.storage,
        		sram.bus.write(self._adr.storage, self._data_write.storage, self._sel.storage)
        	)
        ]
        
        
        """
        self._red = CSRStorage(4)
        self._green = CSRStorage(4)
        self._blue = CSRStorage(4)
        self._hpos = CSRStatus(len(self.h_count))
        self._vpos = CSRStatus(len(self.v_count))
        self.specials += MultiReg(self.h_count, self._hpos.status)
        self.specials += MultiReg(self.v_count, self._vpos.status)
        
        self._memadr = CSRStorage(len(port.adr))
        self._memwe = CSRStorage()
        self._memdatw = CSRStorage(vram_data_width)
        self._memdatr = CSRStatus(vram_data_width)
        
        self.comb += [
            If(port.we,
                port.adr.eq(self._memadr.storage)
            ).Else(
                port.adr.eq(self.v_count*h_rez+self.h_count)
            ),
            port.we.eq(self._memwe.storage),
            port.dat_w.eq(self._memdatw.storage),
            port.re.eq(1),
            
            self._memdatr.status.eq(port.dat_r)
            ]
        
        """
        # # #
        
        self.sync += [
        	# Pxl clock generation
	        If(pxl_tick_count >= (3),
	            pxl_tick_count.eq(0),
	            pxl_tick.eq(1)
	        ).Else(
	            pxl_tick_count.eq(pxl_tick_count + 1),
	            pxl_tick.eq(0)
            ),
	        If(pxl_tick,
	            # counters
			    If(self.h_count >= h_max -1,
			        self.h_count.eq(0),
			        If(self.v_count >= v_max -1,
			            self.v_count.eq(0)
			        ).Else(
			            self.v_count.eq(self.v_count+1)
			        )
			    ).Else(
			        self.h_count.eq(self.h_count+1)
			    ),
			    
			    # h sync
			    If(self.h_count > h_startsync,
			        If(self.h_count <= h_endsync,
			            hs.eq(0)
			        ).Else(
			            hs.eq(1)
			        )
			    ).Else(
			        hs.eq(1)
			    ),
			    
			    # v sync
			    If(self.v_count > v_startsync,
			        If(self.v_count <= v_endsync,
			            vs.eq(0)
			        ).Else(
			            vs.eq(1)
			        )
			    ).Else(
			        vs.eq(1)
			    ),
			    
			    #display sync
			    If(self.v_count >= v_rez/2,
			        self.active.eq(0)
			    ).Else(
			        If(self.h_count >= h_rez/2,
			            self.active.eq(0)
			        ).Else(
			            self.active.eq(1)
			        )
			    ),
			    
			    If(self.active,
			    	r_out.eq(sram.bus.read(self.v_count*h_rez/2+self.h_count)),#self._red.storage),
		        	g_out.eq(sram.bus.read(self.v_count*h_rez/2+self.h_count)),#self._green.storage),
		        	b_out.eq(sram.bus.read(self.v_count*h_rez/2+self.h_count))#self._blue.storage)
			    ).Else(
			        r_out.eq(0),
			        g_out.eq(0),
			        b_out.eq(0)
			    )
	        )
        ]

