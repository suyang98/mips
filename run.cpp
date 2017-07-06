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
		switch (a.sy) {
		case 0: {
			t = new Add(mem, is, os, reg);
			t->IF(a);
			break;
		}
		case 1: {
			t = new Addu(mem, is, os, reg);
			t->IF(a);
			break;
		}
		case 2: {
			t = new Addiu(mem, is, os, reg);
			t->IF(a);
			break;
		}
		case 3: {
			t = new Sub(mem, is, os, reg);
			t->IF(a);
			break;
		}
		case 4: {
			t = new Subu(mem, is, os, reg);
			t->IF(a);
			break;
		}
		case 5: {
			t = new Mul(mem, is, os, reg);
			t->IF(a);
			break;
		}
		case 6: {
			t = new Mulu(mem, is, os, reg);
			t->IF(a);
			break;
		}
		case 7: {
			t = new Mul2(mem, is, os, reg);
			t->IF(a);
			break;
		}
		case 8: {
			t = new Mulu2(mem, is, os, reg);
			t->IF(a);
			break;
		}
		case 9: {
			t = new Div(mem, is, os, reg);
			t->IF(a);
			break;
		}
		case 10: {
			t = new Divu(mem, is, os, reg);
			t->IF(a);
			break;
		}
		case 11: {
			t = new Div2(mem, is, os, reg);
			t->IF(a);
			break;
		}
		case 12: {
			t = new Divu2(mem, is, os, reg);
			t->IF(a);
			break;
		}
		case 13: {
			t = new Xor(mem, is, os, reg);
			t->IF(a);
			break;
		}
		case 14: {
			t = new Xoru(mem, is, os, reg);
			t->IF(a);
			break;
		}
		case 15: {
			t = new Neg(mem, is, os, reg);
			t->IF(a);
			break;
		}
		case 16: {
			t = new Negu(mem, is, os, reg);
			t->IF(a);
			break;
		}
		case 17: {
			t = new Rem(mem, is, os, reg);
			t->IF(a);
			break;
		}
		case 18: {
			t = new Remu(mem, is, os, reg);
			t->IF(a);
			break;
		}
		case 19: {
			t = new li(mem, is, os, reg);
			t->IF(a);
			break;
		}
		case 20: {
			t = new Seq(mem, is, os, reg);
			t->IF(a);
			break;
		}
		case 21: {
			t = new Sge(mem, is, os, reg);
			t->IF(a);
			break;
		}
		case 22: {
			t = new Sgt(mem, is, os, reg);
			t->IF(a);
			break;
		}
		case 23: {
			t = new Sle(mem, is, os, reg);
			t->IF(a);
			break;
		}
		case 24: {
			t = new Slt(mem, is, os, reg);
			t->IF(a);
			break;
		}
		case 25: {
			t = new Sne(mem, is, os, reg);
			t->IF(a);
			break;
		}
		case 26: {
			t = new J(mem, is, os, reg, *this, i);
			t->IF(a);
			break;
		}
		case 27: {
			t = new Beq(mem, is, os, reg, *this, i);
			t->IF(a);
			break;
		}
		case 28: {
			t = new Bne(mem, is, os, reg, *this, i);
			t->IF(a);
			break;
		}
		case 29: {
			t = new Bge(mem, is, os, reg, *this, i);
			t->IF(a);
			break;
		}
		case 30: {
			t = new Ble(mem, is, os, reg, *this, i);
			t->IF(a);
			break;
		}
		case 31: {
			t = new Bgt(mem, is, os, reg, *this, i);
			t->IF(a);
			break;
		}
		case 32: {
			t = new Blt(mem, is, os, reg, *this, i);
			t->IF(a);
			break;
		}
		case 33: {
			t = new Beqz(mem, is, os, reg, *this, i);
			t->IF(a);
			break;
		}
		case 34: {
			t = new Bnez(mem, is, os, reg, *this, i);
			t->IF(a);
			break;
		}
		case 35: {
			t = new Blez(mem, is, os, reg, *this, i);
			t->IF(a);
			break;
		}
		case 36: {
			t = new Bgez(mem, is, os, reg, *this, i);
			t->IF(a);
			break;
		}
		case 37: {
			t = new Bgtz(mem, is, os, reg, *this, i);
			t->IF(a);
			break;
		}
		case 38: {
			t = new Bltz(mem, is, os, reg, *this, i);
			t->IF(a);
			break;
		}
		case 39: {
			t = new Jr(mem, is, os, reg, *this, i);
			t->IF(a);
			break;
		}
		case 40: {
			t = new Jal(mem, is, os, reg, *this, i);
			t->IF(a);
			break;
		}
		case 41: {
			t = new Jalr(mem, is, os, reg, *this, i);
			t->IF(a);
			break;
		}
		case 42: {
			t = new La(mem, is, os, reg);
			t->IF(a);
			break;
		}
		case 43: {
			t = new Lb(mem, is, os, reg);
			t->IF(a);
			break;
		}
		case 44: {
			t = new Lh(mem, is, os, reg);
			t->IF(a);
			break;
		}
		case 45: {
			t = new Lw(mem, is, os, reg);
			t->IF(a);
			break;
		}
		case 46: {
			t = new Sb(mem, is, os, reg);
			t->IF(a);
			break;
		}
		case 47: {
			t = new Sh(mem, is, os, reg);
			t->IF(a);
			break;
		}
		case 48: {
			t = new Sw(mem, is, os, reg);
			t->IF(a);
			break;
		}
		case 49: {
			t = new Move(mem, is, os, reg);
			t->IF(a);
			break;
		}
		case 50: {
			t = new Move(mem, is, os, reg);
			a.two = 33; a._two = address;
			t->IF(a);
			break;
		}
		case 51: {
			t = new Move(mem, is, os, reg);
			a.two = 32; a._two = address;
			t->IF(a);
			break;
		}
		case 52: {
			t = new syscall(mem, is, os, reg, *this);
			t->IF(a);
			break;
		}
		}

		v1.push(t);
	}
}