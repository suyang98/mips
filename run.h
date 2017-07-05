#pragma once
#ifndef _run_h
#endif _run_h
#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include "memory.h"
#include "registers.h"
using std::istream;
using std::ostream;
using std::string;
using std::queue;

class base;
class run {
private:
	symbol a;
	memory &mem;
	istream &is;
	ostream &os;
	registers &reg;
	queue<base*> v1, v2, v3, v4;
public:
	bool f, fl;
	int ret;
	run(memory &_mem, istream &_is, ostream &_os, registers &_reg) :
		mem(_mem), is(_is), os(_os), reg(_reg), f(true), fl(true), ret(0) {}
	void runn();
};

class base {
protected:
	symbol a;
	memory &mem;
	istream &is;
	ostream &os;
	registers &reg;
public:
	base(memory &_mem, istream &_is, ostream &_os, registers &_reg) :
		mem(_mem), is(_is), os(_os), reg(_reg) {}
	virtual void IF(symbol b) { 
		a = b;
		//cout << a.sy << ' ' << a.one << ' ' << a._one << ' ' << a.two << ' ' << a._two << ' ' << a.thr << ' ' << a._thr << endl; 
	}
	virtual bool ID() = 0;
	virtual void EX() = 0;
	virtual void MA() = 0;
	virtual void WB() = 0;
};

class li :public base {
private:
	int r, i;
public:
	li(memory &_mem, istream &_is, ostream &_os, registers &_reg) :
		base(_mem, _is, _os, _reg) {}
	bool ID() { r = a.one;i = a.two;reg.used[r] = true;return true; }
	void EX() {}
	void MA() {}
	void WB() { reg.storage[r] = i; reg.used[r] = false; }
};

class base_sign :public base {
protected:
	int tmp, num1, num2;
public:
	base_sign(memory &_mem, istream &_is, ostream &_os, registers &_reg)
		:base(_mem, _is, _os, _reg) {}
	bool ID() {
		if (reg.used[a.two] || (a._thr == 0 && reg.used[a.thr])) return false;
		num1 = reg.storage[a.two];
		if (a._thr == 0) num2 = reg.storage[a.thr]; else num2 = a.thr;
		reg.used[a.one] = true;return true;
	}
	virtual void EX() = 0;
	void MA() {}
	void WB() { 
		reg.storage[a.one] = tmp; 
		reg.used[a.one] = false; 
	}
};
class Add :public base_sign {
public:
	Add(memory &_mem, istream &_is, ostream &_os, registers &_reg) :base_sign(_mem, _is, _os, _reg) {}
	void EX() { tmp = num1 + num2; }
};
class Sub :public base_sign {
public:
	Sub(memory &_mem, istream &_is, ostream &_os, registers &_reg) : base_sign(_mem, _is, _os, _reg) {}
	void EX() {
		tmp = num1 - num2; 
	}
};
class Mul :public base_sign {
public:
	Mul(memory &_mem, istream &_is, ostream &_os, registers &_reg) : base_sign(_mem, _is, _os, _reg) {}
	void EX() { tmp = num1 * num2; }
};
class Div :public base_sign {
public:
	Div(memory &_mem, istream &_is, ostream &_os, registers &_reg) : base_sign(_mem, _is, _os, _reg) {}
	void EX() { tmp = num1 / num2; }
};
class Xor :public base_sign {
public:
	Xor(memory &_mem, istream &_is, ostream &_os, registers &_reg) : base_sign(_mem, _is, _os, _reg) {}
	void EX() { tmp = num1 ^ num2; }
};
class Rem :public base_sign {
public:
	Rem(memory &_mem, istream &_is, ostream &_os, registers &_reg) : base_sign(_mem, _is, _os, _reg) {}
	void EX() { tmp = num1 % num2; }
};

class base_unsign :public base {
protected:
	unsigned int num1, num2, tmp;
public:
	base_unsign(memory &_mem, istream &_is, ostream &_os, registers &_reg) :base(_mem, _is, _os, _reg) {}
	bool ID() {
		if (reg.used[a.two] || (a._thr == 0 && reg.used[a.thr])) return false;
		num1 = reg.storage[a.two];
		if (a._thr == 0) num2 = reg.storage[a.thr]; else num2 = a.thr;
		reg.used[a.one] = true;return true;
	}
	virtual void EX() = 0;
	void MA() {}
	void WB() { reg.storage[a.one] = tmp; reg.used[a.one] = false; }
};
class Addu : public base_unsign {
public:
	Addu(memory &_mem, istream &_is, ostream &_os, registers &_reg) : base_unsign(_mem, _is, _os, _reg) {}
	void EX() { tmp = num1 + num2; }
};
class Addiu : public base_unsign {
public:
	Addiu(memory &_mem, istream &_is, ostream &_os, registers &_reg) : base_unsign(_mem, _is, _os, _reg) {}
	void EX() { tmp = num1 + num2; }
};
class Subu :public base_unsign {
public:
	Subu(memory &_mem, istream &_is, ostream &_os, registers &_reg) : base_unsign(_mem, _is, _os, _reg) {}
	void EX() { tmp = num1 - num2; }
};
class Mulu :public base_unsign {
public:
	Mulu(memory &_mem, istream &_is, ostream &_os, registers &_reg) : base_unsign(_mem, _is, _os, _reg) {}
	void EX() { tmp = num1 * num2; }
};
class Divu :public base_unsign {
public:
	Divu(memory &_mem, istream &_is, ostream &_os, registers &_reg) : base_unsign(_mem, _is, _os, _reg) {}
	void EX() { tmp = num1 / num2; }
};
class Xoru :public base_unsign {
public:
	Xoru(memory &_mem, istream &_is, ostream &_os, registers &_reg) : base_unsign(_mem, _is, _os, _reg) {}
	void EX() { tmp = num1 ^ num2; }
};
class Remu : public base_unsign {
public:
	Remu(memory &_mem, istream &_is, ostream &_os, registers &_reg) : base_unsign(_mem, _is, _os, _reg) {}
	void EX() { tmp = num1 % num2; }
};

class base_2 :public base {
protected:
	int num1, num2;
	long long tmp, tmp1, tmp2;
public:
	base_2(memory &_mem, istream &_is, ostream &_os, registers &_reg) :base(_mem, _is, _os, _reg) {}
	bool ID() {
		if (reg.used[a.one] || (a._two == 0 && reg.used[a.two])) return false;
		num1 = reg.storage[a.one];
		if (a._two == 0) num2 = reg.storage[a.two]; 
		else num2 = a.two;
		reg.used[32] = true; reg.used[33] = true;return true;
	}
	virtual void EX() = 0;
	void MA() {}
	void WB() { reg.storage[32] = tmp1; reg.storage[33] = tmp2;reg.used[32] = false; reg.used[33] = false; }
};
class Mul2 :public base_2 {
public:
	Mul2(memory &_mem, istream &_is, ostream &_os, registers &_reg) :base_2(_mem, _is, _os, _reg) {}
	void EX() {
		tmp = (long long)num1 * num2;
		tmp1 = tmp & 0xffffffff;
		tmp2 = (tmp >> 32) & 0xffffffff;
	}
};
class Div2 :public base_2 {
public:
	Div2(memory &_mem, istream &_is, ostream &_os, registers &_reg) :base_2(_mem, _is, _os, _reg) {}
	void EX() {
		tmp1 = num1 / num2;
		tmp2 = num1 % num2;
	}
};

class baseu_2 :public base {
protected:
	unsigned int num1, num2;
	unsigned long long tmp, tmp1, tmp2;
public:
	baseu_2(memory &_mem, istream &_is, ostream &_os, registers &_reg) :base(_mem, _is, _os, _reg) {}
	bool ID() {
		if (reg.used[a.one] || (a._two == 0 && reg.used[a.two])) return false;
		num1 = reg.storage[a.one];if (a._two == 0) num2 = reg.storage[a.two]; else num2 = a.two;
		reg.used[32] = true; reg.used[33] = true;return true;
	}
	virtual void EX() = 0;
	void MA() {}
	void WB() { reg.storage[32] = tmp1; reg.storage[33] = tmp2;reg.used[32] = false; reg.used[33] = false; }
};
class Mulu2 :public baseu_2 {
public:
	Mulu2(memory &_mem, istream &_is, ostream &_os, registers &_reg) :baseu_2(_mem, _is, _os, _reg) {}
	void EX() {
		tmp = (unsigned long long)num1 * num2;
		tmp1 = tmp & 0xffffffff;
		tmp2 = (tmp >> 32) & 0xffffffff;
	}
};
class Divu2 :public baseu_2 {
public:
	Divu2(memory &_mem, istream &_is, ostream &_os, registers &_reg) :baseu_2(_mem, _is, _os, _reg) {}
	void EX() {
		tmp1 = num1 / num2;
		tmp2 = num1 % num2;
	}
};

class Neg :public base {
protected:
	int tmp;
public:
	Neg(memory &_mem, istream &_is, ostream &_os, registers &_reg) :base(_mem, _is, _os, _reg) {}
	bool ID() {
		if (a._two == 0 && reg.used[a.two]) return false;
		if (a._two == 0) tmp = reg.storage[a.two];else tmp = a.two;
		reg.used[a.one] = true;
		return true;
	}
	void EX() { 
		tmp = -tmp; 
	}
	void MA() {}
	void WB() { 
		reg.storage[a.one] = tmp; 
		reg.used[a.one] = false; 
	}
};
class Negu :public base {
protected:
	unsigned int tmp;
public:
	Negu(memory &_mem, istream &_is, ostream &_os, registers &_reg) :base(_mem, _is, _os, _reg) {}
	bool ID() {
		if (a._two == 0 && reg.used[a.two]) return false;
		if (a._two == 0) tmp = reg.storage[a.two];else tmp = a.two;
		reg.used[a.one] = true;
		return true;
	}
	void EX() { tmp = -tmp; }
	void MA() {}
	void WB() { reg.storage[a.one] = tmp; reg.used[a.one] = true; }
};

class com :public base {
protected:
	int num1, num2, tmp;
public:
	com(memory &_mem, istream &_is, ostream &_os, registers &_reg) :
		base(_mem, _is, _os, _reg) {}
	bool ID() {
		if (reg.used[a.two] || (a._thr == 0 && reg.used[a.thr])) return false;
		num1 = reg.storage[a.two];if (a._thr == 0) num2 = reg.storage[a.thr]; else num2 = a.thr;
		reg.used[a.one] = true; return true;
	}
	virtual void EX() = 0;
	void MA() {}
	void WB() { reg.storage[a.one] = tmp; reg.used[a.one] = false; }
};
class Seq :public com {
public:
	Seq(memory &_mem, istream &_is, ostream &_os, registers &_reg) : com(_mem, _is, _os, _reg) {}
	void EX() { if (num1 == num2) tmp = 1;else tmp = 0; }
};
class Sge :public com {
public:
	Sge(memory &_mem, istream &_is, ostream &_os, registers &_reg) : com(_mem, _is, _os, _reg) {}
	void EX() { if (num1 >= num2) tmp = 1;else tmp = 0; }
};
class Sgt :public com {
public:
	Sgt(memory &_mem, istream &_is, ostream &_os, registers &_reg) : com(_mem, _is, _os, _reg) {}
	void EX() { if (num1 > num2) tmp = 1;else tmp = 0; }
};
class Sle :public com {
public:
	Sle(memory &_mem, istream &_is, ostream &_os, registers &_reg) : com(_mem, _is, _os, _reg) {}
	void EX() { if (num1 <= num2) tmp = 1;else tmp = 0; }
};
class Slt :public com {
public:
	Slt(memory &_mem, istream &_is, ostream &_os, registers &_reg) : com(_mem, _is, _os, _reg) {}
	void EX() { 
		if (num1 < num2) tmp = 1;
		else tmp = 0; 
	}
};
class Sne :public com {
public:
	Sne(memory &_mem, istream &_is, ostream &_os, registers &_reg) : com(_mem, _is, _os, _reg) {}
	void EX() { if (num1 != num2) tmp = 1;else tmp = 0; }
};

class J :public base {
protected:
	int &i, t;
	run &r;
	string s;
public:
	J(memory &_mem, istream &_is, ostream &_os, registers &_reg, run &_r, int &_i) :
		base(_mem, _is, _os, _reg), r(_r), i(_i) {}
	void IF(symbol b) {
		a = b; r.fl = false;
		//cout << a.sy << ' ' << a.one << ' ' << a._one << ' ' << a.two << ' ' << a._two << ' ' << a.thr << ' ' << a._thr << endl;
	}
	virtual bool ID() {
		t = a.one;
		return true;
	}
	virtual void EX() {}
	void MA() {}
	virtual void WB() { i = t; r.fl = true; }
};
class Beq :public J {
public:
	int num1, num2;
	bool tmp;
	Beq(memory &_mem, istream &_is, ostream &_os, registers &_reg, run &_r, int &_i) :
		J(_mem, _is, _os, _reg, _r, _i), tmp(false) {}
	bool ID() {
		if (reg.used[a.one] || (a._two == 0 && reg.used[a.two])) return false;
		num1 = reg.storage[a.one];
		if (a._two == 0) num2 = reg.storage[a.two];
		else num2 = a.two;
		t = a.thr;
		return true;
	}
	virtual void EX() { if (num1 == num2) tmp = true;else tmp = false; }
	void WB() 
	{
		if (tmp) i = t; r.fl = true; 
	}
};
class Bne :public Beq {
public:
	Bne(memory &_mem, istream &_is, ostream &_os, registers &_reg, run &_r, int &_i) :
		Beq(_mem, _is, _os, _reg, _r, _i) {}
	void EX() { if (num1 != num2)tmp = true;else tmp = false; }
};
class Bge :public Beq {
public:
	Bge(memory &_mem, istream &_is, ostream &_os, registers &_reg, run &_r, int &_i) :
		Beq(_mem, _is, _os, _reg, _r, _i) {}
	void EX() { 
		if (num1 >= num2)tmp = true;
		else tmp = false; 
	}
};
class Ble :public Beq {
public:
	Ble(memory &_mem, istream &_is, ostream &_os, registers &_reg, run &_r, int &_i) :
		Beq(_mem, _is, _os, _reg, _r, _i) {}
	void EX() { if (num1 <= num2)tmp = true;else tmp = false; }
};
class Bgt :public Beq {
public:
	Bgt(memory &_mem, istream &_is, ostream &_os, registers &_reg, run &_r, int &_i) :
		Beq(_mem, _is, _os, _reg, _r, _i) {}
	void EX() { 
		if (num1 > num2)tmp = true;else tmp = false;
	}
};
class Blt :public Beq {
public:
	Blt(memory &_mem, istream &_is, ostream &_os, registers &_reg, run &_r, int &_i) :
		Beq(_mem, _is, _os, _reg, _r, _i) {}
	void EX() { if (num1 < num2)tmp = true;else tmp = false; }
};
class Beqz :public base {
protected:
	int num, &i; bool tmp;
	run &r; string s;
public:
	Beqz(memory &_mem, istream &_is, ostream &_os, registers &_reg, run &_r, int &_i) :
		base(_mem, _is, _os, _reg), r(_r), i(_i) {}
	void IF(symbol b) {
		a = b;r.fl = false;
		//cout << a.sy << ' ' << a.one << ' ' << a._one << ' ' << a.two << ' ' << a._two << ' ' << a.thr << ' ' << a._thr << endl;
	}
	bool ID() {
		if (reg.used[a.one]) return false;
		num = reg.storage[a.one];return true;
	}
	virtual void EX() { if (num == 0)tmp = true; else tmp = false; }
	void MA() {}
	void WB() { 
		if (tmp) i = a.two;
		r.fl = true; 
	}
};
class Bnez :public Beqz {
public:
	Bnez(memory &_mem, istream &_is, ostream &_os, registers &_reg, run &_r, int &_i) :
		Beqz(_mem, _is, _os, _reg, _r, _i) {}
	void EX() { if (num != 0)tmp = true; else tmp = false; }
};
class Blez :public Beqz {
public:
	Blez(memory &_mem, istream &_is, ostream &_os, registers &_reg, run &_r, int &_i) :
		Beqz(_mem, _is, _os, _reg, _r, _i) {}
	void EX() { if (num <= 0)tmp = true; else tmp = false; }
};
class Bgez :public Beqz {
public:
	Bgez(memory &_mem, istream &_is, ostream &_os, registers &_reg, run &_r, int &_i) :
		Beqz(_mem, _is, _os, _reg, _r, _i) {}
	void EX() { 
		if (num >= 0)tmp = true; 
		else tmp = false; 
	}
};
class Bgtz :public Beqz {
public:
	Bgtz(memory &_mem, istream &_is, ostream &_os, registers &_reg, run &_r, int &_i) :
		Beqz(_mem, _is, _os, _reg, _r, _i) {}
	void EX() { if (num > 0)tmp = true; else tmp = false; }
};
class Bltz :public Beqz {
public:
	Bltz(memory &_mem, istream &_is, ostream &_os, registers &_reg, run &_r, int &_i) :
		Beqz(_mem, _is, _os, _reg, _r, _i) {}
	void EX() { if (num < 0)tmp = true; else tmp = false; }
};
class Jal :public J {
public:
	Jal(memory &_mem, istream &_is, ostream &_os, registers &_reg, run &_r, int &_i) :
		J(_mem, _is, _os, _reg, _r, _i) {}
	bool ID() { reg.used[31] = true; t = a.one; return true; }
	void WB() { reg.storage[31] = a.i + 1;i = t; r.fl = true;reg.used[31] = false; }
};
class Jr :public base {
protected:
	int &i, t;
	run &r;
public:
	Jr(memory &_mem, istream &_is, ostream &_os, registers &_reg, run &_r, int &_i) :
		base(_mem, _is, _os, _reg), r(_r), i(_i) {}
	void IF(symbol b) {
		a = b;r.fl = false;
		//cout << a.sy << ' ' << a.one << ' ' << a._one << ' ' << a.two << ' ' << a._two << ' ' << a.thr << ' ' << a._thr << endl;
	}
	virtual bool ID() {
		if (reg.used[a.one]) return false;
		t = reg.storage[a.one];return true;
	}
	void EX() {}
	void MA() {}
	virtual void WB() { i = t;r.fl = true; }
};
class Jalr :public Jr {
public:
	Jalr(memory &_mem, istream &_is, ostream &_os, registers &_reg, run &_r, int &_i) :
		Jr(_mem, _is, _os, _reg, _r, _i) {}
	bool ID() {
		if (reg.used[a.one]) return false;
		t = reg.storage[a.one];reg.used[31] = true;return true;
	}
	void WB() { i = reg.storage[31] = t; r.fl = true; reg.used[31] = false; }
};

class La :public base {
protected:
	int tmp;
public:
	La(memory &_mem, istream &_is, ostream &_os, registers &_reg) :
		base(_mem, _is, _os, _reg) {}
	bool ID() { reg.used[a.one] = true;return true; }
	void EX() { tmp = a.two; if (a._thr == add) tmp = tmp + a.thr; }
	void MA() {}
	void WB() { reg.storage[a.one] = tmp; reg.used[a.one] = false; }
};
class L :public base {
protected:
	int tmp, num;//num要存的数tmp为data中的位置
	char t1, t2, t3, t4;
public:
	L(memory &_mem, istream &_is, ostream &_os, registers &_reg) :
		base(_mem, _is, _os, _reg), num(0) {}
	bool ID() { 
		if (a._thr == 2) tmp = a.two;
		else {
			if(reg.used[a.two]) return false;
			tmp = reg.storage[a.two] + a.thr;
		}
		reg.used[a.one] = true;return true; 
	}
	void EX() {}
	void MA() {
		t4 = mem.get_data(tmp++); t3 = mem.get_data(tmp++);
		t2 = mem.get_data(tmp++); t1 = mem.get_data(tmp);
	}
	virtual void WB() = 0;
};
class Lb :public L {
public:
	Lb(memory &_mem, istream &_is, ostream &_os, registers &_reg) :
		L(_mem, _is, _os, _reg) {}
	void WB() { reg.storage[a.one] = t4 & 0xff; reg.used[a.one] = false; }
};
class Lh :public L {
public:
	Lh(memory &_mem, istream &_is, ostream &_os, registers &_reg) :
		L(_mem, _is, _os, _reg) {}
	void WB() { 
		num = (t3 << 8 & 0xff00) | t4 & 0xff;
		reg.storage[a.one] = num; reg.used[a.one] = false; 
	}
};
class Lw :public L {
public:
	Lw(memory &_mem, istream &_is, ostream &_os, registers &_reg) :
		L(_mem, _is, _os, _reg) {}
	void WB() {
		num = ((t1 << 24) & 0xffffffff) | ((t2 << 16) & 0xffffff) | ((t3 << 8) & 0xffff) | (t4 & 0xff);
		reg.storage[a.one] = num; reg.used[a.one] = false;
	}
};

class S :public base {
protected:
	int num, tmp; //num要存的数tmp为data中的位置
	char t1, t2, t3, t4;
public:
	S(memory &_mem, istream &_is, ostream &_os, registers &_reg) :
		base(_mem, _is, _os, _reg) {}
	bool ID() {
		if (reg.used[a.one]) return false;
		num = reg.storage[a.one];
		if (a._thr == 2) tmp = a.two;
		else {
			if (reg.used[a.two]) return false;
			tmp = reg.storage[a.two] + a.thr;
		}
		return true;
	}
	void EX() {
		t4 = char(num >> 24) & 255;
		t3 = char((num >> 16) & 255);
		t2 = char((num >> 8) & 255);
		t1 = char(num & 255);
	}
	virtual void MA() = 0;
	void WB() {}
};
class Sb :public S {
public:
	Sb(memory &_mem, istream &_is, ostream &_os, registers &_reg) :
		S(_mem, _is, _os, _reg) {}
	void MA() { 
		mem.change_data(tmp, t1); 
	}
};
class Sh :public S {
public:
	Sh(memory &_mem, istream &_is, ostream &_os, registers &_reg) :
		S(_mem, _is, _os, _reg) {}
	void MA() { 
		mem.change_data(tmp++, t1);mem.change_data(tmp, t2); 
	}
};
class Sw :public S {
public:
	Sw(memory &_mem, istream &_is, ostream &_os, registers &_reg) :
		S(_mem, _is, _os, _reg) {}
	void MA() {
		mem.change_data(tmp++, t1);mem.change_data(tmp++, t2);
		mem.change_data(tmp++, t3);mem.change_data(tmp, t4);
	}
};

class Move :public base {
protected:
	int tmp, t;
public:
	Move(memory &_mem, istream &_is, ostream &_os, registers &_reg) :
		base(_mem, _is, _os, _reg) {}
	bool ID() {
		if (reg.used[a.two]) return false;
		tmp = reg.storage[a.two];reg.used[a.one] = true;return true;
	}
	void EX() {}
	void MA() {}
	void WB() { reg.storage[a.one] = tmp; reg.used[a.one] = false; }
};

class syscall :public base {
private:
	int num, tmp, len, beg, ret;
	run &r;
	string s = "";
public:
	syscall(memory &_mem, istream &_is, ostream &_os, registers &_reg, run &_r) :
		base(_mem, _is, _os, _reg), r(_r) {}
	bool ID() {
		if (reg.used[2]) return false;
		num = reg.storage[2];
		if (num == 1) { 
			if (reg.used[4]) return false; 
			else tmp = reg.storage[4]; 
		}
		if (num == 4) {
			if (reg.used[4]) return false;
			else {
				int i = reg.storage[4];
				while (mem.get_data(i) != '\0') { s = s + mem.get_data(i);++i; }
			}
		}
		if (num == 5) reg.used[2] = true;
		if (num == 8) { 
			if (reg.used[4] || reg.used[5]) return false;
			beg = reg.storage[4]; len = reg.storage[5];
		}
		if (num == 9) { if (reg.used[4]) return false; else { tmp = reg.storage[4]; reg.used[2] = true; } }
		return true;
	}
	void EX() {
		if (num == 1)
			os << tmp;
		if (num == 4) 
			os << s;
		if (num == 5) { is >> tmp; }
		if (num == 8) { is >> s; }
		if (num == 9) { beg = mem.get_data_num(); }
	}
	void MA() {
		if (num == 8) {
			for (int i = beg;s[i-beg]!='\0' && (i-beg+1)<len; ++i)
			 mem.change_data(i,s[i-beg]); 
		}
		if (num == 9) { mem.sp(tmp); }
	}
	void WB() {
		if (num == 5) { reg.storage[2] = tmp; reg.used[2] = false; }
		//if (num == 8) { reg.storage[4] = beg; reg.storage[5] = len;reg.used[4] = false;reg.used[5] = false; }
		if (num == 9) { reg.storage[2] = beg; reg.used[2] = false; }
		if (num == 10) r.f = false;
		if (num == 17) { r.f = false; r.ret = reg.storage[4]; }
	}
};




