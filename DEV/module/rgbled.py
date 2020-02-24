from migen import *
from migen.genlib.cdc import MultiReg
from litex.soc.interconnect.csr import *
from litex.soc.cores import pwm

# RGB LED ---------------------------------------------------------------------------
class RGBLed(Module, AutoCSR):
    def __init__(self, pads):
        self.submodules.r = pwm.PWM(pads.r)
        self.submodules.g = pwm.PWM(pads.g)
        self.submodules.b = pwm.PWM(pads.b)
