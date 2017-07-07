#pragma once
#ifndef _text_h
#endif _text_h
#include<fstream>
#include<iostream>
#include<string>
#include"memory.h"
#include"registers.h"
#include"run.h"
using std::string;
using std::istream;

class text {
private:
	memory &mem;
	istream &is;
	registers &reg;
	run &r;
	char get_char();
	void read_data();
	void read_text();
	void instr(int &i, string s, int &a, type &_a, int &b, type &_b, string &d);
public:
	text(memory &_mem, istream &_is, registers &_reg, run &_r) :mem(_mem), is(_is), reg(_reg), r(_r) {}
	void read_all();
	void tran();
	int bianhao(string s, type ty, int i);
};
