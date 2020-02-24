
from migen import *
from migen.genlib.cdc import MultiReg

from litex.soc.interconnect.csr import *

# Seven Segment ---------------------------------------------------------------------------

class SevenSegment(Module, AutoCSR):
    def __init__(self, segment_out, digit_out):
        
        nb_dig = len(digit_out)
        dgt_count = Signal(max = nb_dig)
    
        refresh_period = 16*10**(-3)  # refresh of 16ms (from datasheet)
        digit_period = refresh_period/nb_dig # period for 1 digit
        
        dgt_tick = Signal()
        dgt_tick_count = Signal(max = int(digit_period*100e6))
        
        self.displays = Array(Signal(len(segment_out)) for i in range(nb_dig))
        
    # CSR -----------------------------------------------------------------------------
    
        self._dig_0 = CSRStorage(8)
        self._dig_1 = CSRStorage(8)
        self._dig_2 = CSRStorage(8)
        self._dig_3 = CSRStorage(8)
        self._dig_4 = CSRStorage(8)
        self._dig_5 = CSRStorage(8)
        self._dig_6 = CSRStorage(8)
        self._dig_7 = CSRStorage(8)
        
        self.comb += [
            self.displays[0].eq(self._dig_0.storage),
            self.displays[1].eq(self._dig_1.storage),
            self.displays[2].eq(self._dig_2.storage),
            self.displays[3].eq(self._dig_3.storage),
            self.displays[4].eq(self._dig_4.storage),
            self.displays[5].eq(self._dig_5.storage),
            self.displays[6].eq(self._dig_6.storage),
            self.displays[7].eq(self._dig_7.storage)
        ]
    
        # # #
        
        self.sync += [
            # Digit tick counter
            If(dgt_tick_count >= int(digit_period*100e6-1),
                dgt_tick_count.eq(0),
                dgt_tick.eq(1)
            ).Else(
                dgt_tick_count.eq(dgt_tick_count + 1),
                dgt_tick.eq(0)
            ),
            # Digit counter
        If(dgt_tick,
            If(dgt_count >= nb_dig-1,
            dgt_count.eq(0)
        ).Else(
            dgt_count.eq(dgt_count + 1)
        )
        )
        ]
        
        self.comb += [
        # digit_out
            digit_out.eq(~(1<<dgt_count)),
            # segment_out
        segment_out.eq(~self.displays[dgt_count])
        ]
