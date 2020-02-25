from migen import *
from migen.genlib.cdc import MultiReg

from litex.soc.interconnect.csr import *

# VGA Controller ---------------------------------------------------------------------------

class VGAcontroller(Module, AutoCSR):
    """VGA display controller
    
    Provides a video controller circuit to drive the sync and color signals with the correct timing
    in order to produce a working display system.
    """
    def __init__(self, hs, vs, r_out, g_out, b_out):
        h_rez = 640
        h_startsync = 640 + 16
        h_endsync = h_startsync + 96
        h_max = 800
        h_count = Signal(max = h_max)
        
        v_rez = 480
        v_startsync = 480 + 10
        v_endsync = v_startsync + 2
        v_max = 525
        v_count = Signal(max = v_max)
    
        pxl_freq = 25e6 # pixel counter frequency 25MHz
        pxl_tick_count = Signal(max = int(100e6/pxl_freq))
        pxl_tick = Signal()
        
        active = Signal()
        
        memory_width = len(r_out)+len(g_out)+len(b_out)
        mem = Memory(memory_width, h_rez*v_rez)
        self.specials += mem
        
        p_r = mem.get_port()
        p_w = mem.get_port(write_capable=True)
        self.specials += p_r, p_w
    
        # CSR -----------------------------------------------------------------------------
        self._mem_adr = CSRStorage(len(p_w.adr))
        self._mem_we = CSRStorage(len(p_w.we))
        self._mem_data_w = CSRStorage(memory_width)
        self._mem_data_r = CSRStatus(memory_width)
        
        self.comb += [
            p_w.adr.eq(self._mem_adr.storage),
            p_w.we.eq(self._mem_we.storage),
            self._mem_data_r.status.eq(p_w.dat_r),
            p_w.dat_w.eq(self._mem_data_w.storage)
        ]
    
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
        
        # Horiontal and vertical counters
        If(pxl_tick,
            If(h_count >= h_max -1,
            h_count.eq(0),
            If(v_count >= v_max -1,
                v_count.eq(0)
            ).Else(
            v_count.eq(v_count+1)
            )
        ).Else(
            h_count.eq(h_count+1)
        )
        ),
        
        # Adress read sync
        p_r.adr.eq(v_count*h_rez+h_count)
        ]

        self.comb += [
            # h sync
        hs.eq((h_count >= h_startsync) & (h_count < h_endsync)),
        # v sync
        vs.eq((v_count >= v_startsync) & (v_count < v_endsync)),
        # display sync
        active.eq((h_count < h_rez) & (v_count < v_rez)),
        # red out
        r_out.eq(active * p_r.dat_r[8:12]),
        # green out
        g_out.eq(active * p_r.dat_r[4:8]),
        # blue out
        b_out.eq(active * p_r.dat_r[0:4])
        ]
