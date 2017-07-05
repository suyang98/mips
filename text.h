#pragma once
#ifndef _text_h
#endif _text_h
#include<fstream>
#include<iostream>
#include<string>
#include"memory.h"
#include"registers.h"
using std::string;
using std::istream;

class text {
private:
	memory &mem;
	istream &is;
	registers &reg;
	char get_char();
	void read_data();
	void read_text();
	void instr(int &i, string s, int &a, type &_a, int &b, type &_b, string &d);
public:
	text(memory &_mem, istream &_is, registers &_reg) :mem(_mem), is(_is), reg(_reg) {}
	void read_all();
	void tran();
};
