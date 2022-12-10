#include "sha.h"

std::string sha::cifrar(std::string t)
{
	uint32_t ini[] = H_INICIAL;
	for (int i = 0; i < 8; i++) H[i] = ini[i];
	std::string msg = msg2bin(t) + "1";
	int longitud_original = msg.length() - 1;
	while (msg.length() % 512 != 448) msg += '0';

	std::vector<std::vector<int>> M = std::vector<std::vector<int>>();
	for (int i = 0; i < msg.length(); i += 512) {
		std::vector<int> trozo = std::vector<int>(16);
		std::string sub_msg = msg.substr(i, 512);

		for (int j = 0; j < 512; j += 32) {
			std::string n = sub_msg.substr(j, 32);
			trozo.at(j / 32) = bin2int(n);
		}
		M.push_back(trozo);
	}

	for (auto Mi : M) {
		uint32_t a = H[0], b = H[1], c = H[2], d = H[3], e = H[4], f = H[5], g = H[6], h = H[7];
		std::vector<uint32_t> W = std::vector<uint32_t>(64);
		for (int i = 0; i < 64; i++) {
			if (i < 16) W[i] = Mi[i];
			else W[i] = func::o1(W.at(i - 2)) + W.at(i - 7) + func::o0(W.at(i - 15)) + W.at(i - 16);
			uint32_t T1 = h + func::s1(e) + func::Ch(e, f, g) + K[i] + W[i];
			uint32_t T2 = func::s0(a) + func::Maj(a, b, c);
			h = g;
			g = f;
			f = e;
			e = d + T1;
			d = c;
			c = b;
			b = a;
			a = T1 + T2;
		}
		H[0] = a + H[0];
		H[1] = b + H[1];
		H[2] = c + H[2];
		H[3] = d + H[3];
		H[4] = e + H[4];
		H[5] = f + H[5];
		H[6] = g + H[6];
		H[7] = h + H[7];
	}

	std::string resultado = "";
	for (auto h : H) resultado += toHEX(h, 8);
	return resultado;
}
