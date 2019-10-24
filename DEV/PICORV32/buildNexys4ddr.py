#!/usr/bin/env python3.7

from migen import *
from migen.genlib.io import CRG

from litex.boards.platforms import nexys4ddr

from litex.soc.integration.soc_core import *
from litex.soc.integration.builder import *


from litex.soc.cores import gpio

# BaseSoC ------------------------------------------------------------------------------------------

class BaseSoC(SoCCore):
	def __init__(self):
		platform = nexys4ddr.Platform()
		# SoC with CPU
		SoCCore.__init__(self, platform,
 			cpu_type="picorv32",
			clk_freq=100e6,
			integrated_rom_size=0x8000,
			integrated_main_ram_size=16*1024)

		# Clock Reset Generation
		self.submodules.crg = CRG(platform.request("clk100"), ~platform.request("cpu_reset"))

		# Leds
		SoCCore.add_csr(self,"leds")
		user_leds = Cat(*[platform.request("user_led", i) for i in range(16)])
		self.submodules.leds = gpio.GPIOOut(user_leds)
		
		# Switchs
		SoCCore.add_csr(self,"switchs")
		user_switchs = Cat(*[platform.request("user_sw", i) for i in range(16)])
		self.submodules.switchs = gpio.GPIOIn(user_switchs)
		
		# Buttons
		SoCCore.add_csr(self,"buttons")
		user_buttons = Cat(*[platform.request("user_btn", i) for i in range(5)])
		self.submodules.switchs = gpio.GPIOIn(user_buttons)

# Build --------------------------------------------------------------------------------------------

def main():
	builder = Builder(BaseSoC())
	builder.build()


if __name__ == "__main__":
	main()
