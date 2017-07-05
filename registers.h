#pragma once
#ifndef _registers_h
#endif _registers_h
#include<fstream>
#include<iostream>
#include<string>
#include<map>
#include"registers.h"
using std::map;
using std::string;

class registers{
public:
	int storage[40];
	bool used[40];
	map<string, int> m;
	registers(){
		m["zero"] = m["0"] = 0;
		m["at"] = m["1"] = 1;
		m["v0"] = m["2"] = 2;
		m["v1"] = m["3"] = 3;
		m["a0"] = m["4"] = 4;
		m["a1"] = m["5"] = 5;
		m["a2"] = m["6"] = 6;
		m["a3"] = m["7"] = 7;
		m["t0"] = m["8"] = 8;
		m["t1"] = m["9"] = 9;
		m["t2"] = m["10"] = 10;
		m["t3"] = m["11"] = 11;
		m["t4"] = m["12"] = 12;
		m["t5"] = m["13"] = 13;
		m["t6"] = m["14"] = 14;
		m["t7"] = m["15"] = 15;
		m["s0"] = m["16"] = 16;
		m["s1"] = m["17"] = 17;
		m["s2"] = m["18"] = 18;
		m["s3"] = m["19"] = 19;
		m["s4"] = m["20"] = 20;
		m["s5"] = m["21"] = 21;
		m["s6"] = m["22"] = 22;
		m["s7"] = m["23"] = 23;
		m["t8"] = m["24"] = 24;
		m["t9"] = m["25"] = 25;
		m["k0"] = m["26"] = 26;
		m["k1"] = m["27"] = 27;
		m["gp"] = m["28"] = 28;
		m["sp"] = m["29"] = 29;
		m["fp"] = m["30"] = 30;
		m["ra"] = m["31"] = 31;
		m["lo"] = m["32"] = 32;
		m["hi"] = m["33"] = 33;
		for (int i = 0; i < 40; ++i) { used[i] = false; storage[i] = 0; }
	}


};
