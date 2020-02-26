# Migen

![migen](./Images/migen.png)

Migen est une bibliothèque Python permettant de manipuler et générer plus facilement des circuits logiques complexes. voici deux lien vers les sites du développeur (S Bourdeauducq):

https://m-labs.hk/migen/manual/introduction.html

https://github.com/m-labs/migen

Actuellement lorsque vous souhaitez décrire une architecture FPGA, vous utilisez généralement deux langages: le VHDL ou le Verilog. Migen apporte une nouvelle façon de décrire vos architectures en utilisant le langage Python et de le convertir directement par une simple fonction print en VHDL ou en Vérilog.

Nous n'allons pas reprendre ici l'ensemble de la syntaxe Migen, car elle est bien documentée sur le site du développeur, ainsi que sur d'autres sites dont voici les liens:

- Article en français:

  https://connect.ed-diamond.com/GNU-Linux-Magazine/GLMF-149/Migen-une-boite-a-outils-en-Python-pour-concevoir-des-circuits-logiques-complexes

- Voici un exemple extrait du site:

   http://blog.lambdaconcept.com/doku.php?id=migen:tutorial

Il s'agit de la description d'un afficheur 7 segments réaliser en python utilisant la bibliothèque Migen:

```python
from migen import *
from migen.fhdl import verilog
 
class sevenseg_ctrl(Module):
    def __init__(self):
        self.abcdefg = abcdefg = Signal(7)
        self.hexa = hexa = Signal(4)
        table = [
            0x3f, 0x06, 0x5b, 0x4f, 
            0x66, 0x6d, 0x7d, 0x07, 
            0x7f, 0x6f, 0x77, 0x7c, 
            0x39, 0x5e, 0x79, 0x71
            ]
 
        cases = {}
        for i in range(16):
            cases[i] = abcdefg.eq(table[i])
 
        self.comb += Case(hexa, cases)
 
example = sevenseg_ctrl()
print(verilog.convert(example, {example.hexa, example.abcdefg}))
```

La fonction print à la fin vous retourne le code Verilog suivant:

```python
/* Machine-generated using Migen */
module top(
	output reg [6:0] abcdefg,
	input [3:0] hexa
);
 
 
 
// Adding a dummy event (using a dummy signal 'dummy_s') to get the simulator
// to run the combinatorial process once at the beginning.
// synthesis translate_off
reg dummy_s;
initial dummy_s <= 1'd0;
// synthesis translate_on
 
 
// synthesis translate_off
reg dummy_d;
// synthesis translate_on
always @(*) begin
	abcdefg <= 7'd0;
	case (hexa)
		1'd0: begin
			abcdefg <= 6'd63;
		end
		1'd1: begin
			abcdefg <= 3'd6;
		end
		2'd2: begin
			abcdefg <= 7'd91;
		end
		2'd3: begin
			abcdefg <= 7'd79;
		end
		3'd4: begin
			abcdefg <= 7'd102;
		end
		3'd5: begin
			abcdefg <= 7'd109;
		end
		3'd6: begin
			abcdefg <= 7'd125;
		end
		3'd7: begin
			abcdefg <= 3'd7;
		end
		4'd8: begin
			abcdefg <= 7'd127;
		end
		4'd9: begin
			abcdefg <= 7'd111;
		end
		4'd10: begin
			abcdefg <= 7'd119;
		end
		4'd11: begin
			abcdefg <= 7'd124;
		end
		4'd12: begin
			abcdefg <= 6'd57;
		end
		4'd13: begin
			abcdefg <= 7'd94;
		end
		4'd14: begin
			abcdefg <= 7'd121;
		end
		4'd15: begin
			abcdefg <= 7'd113;
		end
	endcase
// synthesis translate_off
	dummy_d <= dummy_s;
// synthesis translate_on
end
 
endmodule
```





