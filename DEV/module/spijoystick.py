from migen import *
from migen.genlib.cdc import MultiReg
from litex.soc.interconnect.csr import *

#  SpiJoystick ---------------------------------------------------------------------------
""" SpiJoystick est interfacé sur un port Pmod
"""

class SpiJoystick(Module,AutoCSR):
	def __init__(self, pads):
	# Clock generation -------------------------------------------------------------------------
		self._clk = CSRStorage()
		self.comb += pads.clk.eq(self._clk.storage)
	# Chip Select generation -------------------------------------------------------------------
		self._cs = CSRStorage(reset=1)
		self.comb += pads.cs_n.eq(self._cs.storage)
	# Master Out Slave In (MOSI) generation ----------------------------------------------------
		self._mosi = CSRStorage()
		self.comb += pads.mosi.eq(self._mosi.storage)
	# Master In Slave Out (MISO) capture -------------------------------------------------------
		self._miso = CSRStatus()
		self.comb += self._miso.status.eq(pads.miso)
