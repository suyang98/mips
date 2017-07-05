#include"run.h"

class run;

	std::ofstream out2("textre.txt");
void run::runn() {
	base *t;
	reg.storage[29] = 4 * 1024 * 1024;
	std::ofstream out("result.txt");
	int i = mem.find_label("main");
	//int k = mem.get_line_num();
	//for (int j = 0; j < k; ++j) {
	//	symbol a= mem.get_line(j);
	//	out2<<j<<' '<<a.sy<<' '<<a.one<<' '<< a._one<<' '<<a.two
	//		<<' '<<a._two<<' '<<a.thr<<' '<<a._thr<<endl;
	//}
	while (f) {
		if (!v4.empty()) {
			t = v4.front();
			t->WB();
			v4.pop();
			delete t;
		}
		if (!v3.empty()) {
			t = v3.front();
			t->MA();
			v3.pop();
			v4.push(t);
		}
		if (!v2.empty()) {
			t = v2.front();
			t->EX();
			v2.pop();
			v3.push(t);
		}
		if (!v1.empty()) {
			t = v1.front();
			if (t->ID()) {
				v1.pop();
				v2.push(t);
			}
		}
		/*for (int j = 0; j < 34; j++) out << reg.storage[j] << " ";
		out << i<<' '<<endl;*/
		if (i >= mem.get_line_num() || !fl) continue;
		a = mem.get_line(i);
		++i;
		if (a.sy == "syscall") {
			t = new syscall(mem, is, os, reg, *this);
			t->IF(a);
		}
		if (a.sy == "li") {
			t = new li(mem, is, os, reg);
			t->IF(a);
		}
		if (a.sy == "add") {
			t = new Add(mem, is, os, reg);
			t->IF(a);
		}
		if (a.sy == "addu") {
			t = new Addu(mem, is, os, reg);
			t->IF(a);
		}
		if (a.sy == "addiu") {
			t = new Addiu(mem, is, os, reg);
			t->IF(a);
		}
		if (a.sy == "sub") {
			t = new Sub(mem, is, os, reg);
			t->IF(a);
		}
		if (a.sy == "subu") {
			t = new Subu(mem, is, os, reg);
			t->IF(a);
		}
		if (a.sy == "mul" && a._thr != empty) {
			t = new Mul(mem, is, os, reg);
			t->IF(a);
		}
		if (a.sy == "mulu" && a._thr != empty) {
			t = new Mulu(mem, is, os, reg);
			t->IF(a);
		}
		if (a.sy == "mul" && a._thr == empty) {
			t = new Mul2(mem, is, os, reg);
			t->IF(a);
		}
		if (a.sy == "mulu" && a._thr == empty) {
			t = new Mulu2(mem, is, os, reg);
			t->IF(a);
		}
		if (a.sy == "div" && a._thr != empty) {
			t = new Div(mem, is, os, reg);
			t->IF(a);
		}
		if (a.sy == "divu" && a._thr != empty) {
			t = new Divu(mem, is, os, reg);
			t->IF(a);
		}
		if (a.sy == "div" && a._thr == empty) {
			t = new Div2(mem, is, os, reg);
			t->IF(a);
		}
		if (a.sy == "divu" && a._thr == empty) {
			t = new Divu2(mem, is, os, reg);
			t->IF(a);
		}
		if (a.sy == "xor") {
			t = new Xor(mem, is, os, reg);
			t->IF(a);
		}
		if (a.sy == "xoru") {
			t = new Xoru(mem, is, os, reg);
			t->IF(a);
		}
		if (a.sy == "neg") {
			t = new Neg(mem, is, os, reg);
			t->IF(a);
		}
		if (a.sy == "negu") {
			t = new Negu(mem, is, os, reg);
			t->IF(a);
		}
		if (a.sy == "rem") {
			t = new Rem(mem, is, os, reg);
			t->IF(a);
		}
		if (a.sy == "remu") {
			t = new Remu(mem, is, os, reg);
			t->IF(a);
		}
		if (a.sy == "seq") {
			t = new Seq(mem, is, os, reg);
			t->IF(a);
		}
		if (a.sy == "sge") {
			t = new Sge(mem, is, os, reg);
			t->IF(a);
		}
		if (a.sy == "sgt") {
			t = new Sgt(mem, is, os, reg);
			t->IF(a);
		}
		if (a.sy == "sle") {
			t = new Sle(mem, is, os, reg);
			t->IF(a);
		}
		if (a.sy == "slt") {
			t = new Slt(mem, is, os, reg);
			t->IF(a);
		}
		if (a.sy == "sne") {
			t = new Sne(mem, is, os, reg);
			t->IF(a);
		}
		if (a.sy == "b" || a.sy == "j") {
			t = new J(mem, is, os, reg, *this, i);
			t->IF(a);
		}
		if (a.sy == "beq") {
			t = new Beq(mem, is, os, reg, *this, i);
			t->IF(a);
		}
		if (a.sy == "bne") {
			t = new Bne(mem, is, os, reg, *this, i);
			t->IF(a);
		}
		if (a.sy == "bge") {
			t = new Bge(mem, is, os, reg, *this, i);
			t->IF(a);
		}
		if (a.sy == "ble") {
			t = new Ble(mem, is, os, reg, *this, i);
			t->IF(a);
		}
		if (a.sy == "bgt") {
			t = new Bgt(mem, is, os, reg, *this, i);
			t->IF(a);
		}
		if (a.sy == "blt") {
			t = new Blt(mem, is, os, reg, *this, i);
			t->IF(a);
		}
		if (a.sy == "beqz") {
			t = new Beqz(mem, is, os, reg, *this, i);
			t->IF(a);
		}
		if (a.sy == "bnez") {
			t = new Bnez(mem, is, os, reg, *this, i);
			t->IF(a);
		}
		if (a.sy == "blez") {
			t = new Blez(mem, is, os, reg, *this, i);
			t->IF(a);
		}
		if (a.sy == "bgez") {
			t = new Bgez(mem, is, os, reg, *this, i);
			t->IF(a);
		}
		if (a.sy == "bgtz") {
			t = new Bgtz(mem, is, os, reg, *this, i);
			t->IF(a);
		}
		if (a.sy == "bltz") {
			t = new Bltz(mem, is, os, reg, *this, i);
			t->IF(a);
		}
		if (a.sy == "jr") {
			t = new Jr(mem, is, os, reg, *this, i);
			t->IF(a);
		}
		if (a.sy == "jal") {
			t = new Jal(mem, is, os, reg, *this, i);
			t->IF(a);
		}
		if (a.sy == "jalr") {
			t = new Jalr(mem, is, os, reg, *this, i);
			t->IF(a);
		}
		if (a.sy == "la") {
			t = new La(mem, is, os, reg);
			t->IF(a);
		}
		if (a.sy == "lb") {
			t = new Lb(mem, is, os, reg);
			t->IF(a);
		}
		if (a.sy == "lh") {
			t = new Lh(mem, is, os, reg);
			t->IF(a);
		}
		if (a.sy == "lw") {
			t = new Lw(mem, is, os, reg);
			t->IF(a);
		}
		if (a.sy == "sb") {
			t = new Sb(mem, is, os, reg);
			t->IF(a);
		}
		if (a.sy == "sh") {
			t = new Sh(mem, is, os, reg);
			t->IF(a);
		}
		if (a.sy == "sw") {
			t = new Sw(mem, is, os, reg);
			t->IF(a);
		}
		if (a.sy == "move") {
			t = new Move(mem, is, os, reg);
			t->IF(a);
		}
		if (a.sy == "mfhi") {
			t = new Move(mem, is, os, reg);
			a.two = 33; a._two = address;
			t->IF(a);
		}
		if (a.sy == "mflo") {
			t = new Move(mem, is, os, reg);
			a.two = 32; a._two = address;
			t->IF(a);
		}
		v1.push(t);
	}
}