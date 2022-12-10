#pragma once
#include<iostream>
#include<string>
#include<algorithm>
#include<vector>
#include<math.h>

#define HEX "0123456789abcdef"
#define H_INICIAL { 0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a, 0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19 }

namespace func {
	uint32_t SR(int n, int d) {
		return ((n >> d) | (n << (32 - d)));
	}
	uint32_t Ch(uint32_t x, uint32_t y, uint32_t z) {
		return ((x & y) ^ (~x & z));
	}
	uint32_t Maj(uint32_t a, uint32_t b, uint32_t c) {
		return ((a & b) ^ (a & c) ^ (b & c));
	}
	uint32_t s0(uint32_t x) {
		return (func::SR(x, 2) ^ func::SR(x, 13) ^ func::SR(x, 22));
	}
	uint32_t s1(uint32_t x) {
		return (func::SR(x, 6) ^ func::SR(x, 11) ^ func::SR(x, 25));
	}
	uint32_t o0(uint32_t x) {
		return (func::SR(x, 7) ^ func::SR(x, 18) ^ (x >> 3));
	}
	uint32_t o1(uint32_t x) {
		return (func::SR(x, 17) ^ func::SR(x, 19) ^ (x >> 10));
	}
}

uint32_t K[64] = {
	0x428a2f98,0x71374491,0xb5c0fbcf,0xe9b5dba5,0x3956c25b,0x59f111f1,
	0x923f82a4,0xab1c5ed5,0xd807aa98,0x12835b01,0x243185be,0x550c7dc3,
	0x72be5d74,0x80deb1fe,0x9bdc06a7,0xc19bf174,0xe49b69c1,0xefbe4786,
	0x0fc19dc6,0x240ca1cc,0x2de92c6f,0x4a7484aa,0x5cb0a9dc,0x76f988da,
	0x983e5152,0xa831c66d,0xb00327c8,0xbf597fc7,0xc6e00bf3,0xd5a79147,
	0x06ca6351,0x14292967,0x27b70a85,0x2e1b2138,0x4d2c6dfc,0x53380d13,
	0x650a7354,0x766a0abb,0x81c2c92e,0x92722c85,0xa2bfe8a1,0xa81a664b,
	0xc24b8b70,0xc76c51a3,0xd192e819,0xd6990624,0xf40e3585,0x106aa070,
	0x19a4c116,0x1e376c08,0x2748774c,0x34b0bcb5,0x391c0cb3,0x4ed8aa4a,
	0x5b9cca4f,0x682e6ff3,0x748f82ee,0x78a5636f,0x84c87814,0x8cc70208,
	0x90befffa,0xa4506ceb,0xbef9a3f7,0xc67178f2
};

uint32_t H[8] = H_INICIAL;


std::string int2bin(int n, int bits = 8) {
	std::string r = std::string(bits, '0');
	while (n) {
		r.at(--bits) = ((n & 1) + 48);
		n >>= 1;
	}
	return r;
}
std::string msg2bin(std::string t) {
	std::string r = "";
	for (auto c : t) r += int2bin(c);
	return r;
}
int bin2int(std::string b) {
	int r = 0;
	for (int i = 0; i < b.length(); i++) r += b.at(b.length() - 1 - i) == '1' ? pow(2, i) : 0;
	return r;
}
std::string toHEX(uint32_t n, int digits) {
	std::string res = std::string(digits, '0');
	int ind = -1, mod = 0;
	while (n > 15) {
		mod = n % 16;
		res.at(++ind) = HEX[mod];
		n = (n - mod) / 16;
	}
	res.at(++ind) = HEX[n];
	reverse(res.begin(), res.end());
	return res;
}


class sha
{
public:
	static std::string cifrar(std::string t);
};

