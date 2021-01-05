using namespace std;

class Keystroke {
    public:
		Keystroke (int *keys_array, int num_keys);
		int *keys_array, num_keys;
};

Keystroke::Keystroke (int *keys_array, int num_keys) {
	this->keys_array = keys_array;
	this->num_keys = num_keys;
}
