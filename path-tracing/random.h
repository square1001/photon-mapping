class random {
private:
	unsigned seed_[4];
public:
	random(unsigned s) {
		for (int i = 0; i < 4; i++) {
			s = 1812433253U * (s ^ (s >> 30)) + i + 1;
			seed_[i] = s;
		}
	}
	double next() {
		unsigned t = seed_[0] ^ (seed_[0] << 11);
		seed_[0] = seed_[1];
		seed_[1] = seed_[2];
		seed_[2] = seed_[3];
		seed_[3] = (seed_[3] ^ (seed_[3] >> 19)) ^ (t ^ (t >> 8));
		return (seed_[3] + 0.5) / 4294967296.0;
	}
};