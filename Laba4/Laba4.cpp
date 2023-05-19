#include <iostream>
#include <vector>
#include <random>
using namespace std;

vector<int> scramble(const vector<int>& binary_signal);
vector<int> descramble(const vector<int>& binary_signal);
void print_signal(const vector<int>& binary_signal);
void scrambling(const vector<int>& binary_to_scramble);
vector<int> generate_signal(int n);


int main()
{
    vector<int> signal = generate_signal(50);
    scrambling(signal);
    signal = generate_signal(50);
    scrambling(signal);
    signal = generate_signal(50);
    scrambling(signal);
}

vector<int> scramble(const vector<int>& binary_signal)
{
    vector<int> scrambled_signal;
    vector<int> shift_register = { 1,0,0,0,1,0,1,0,1 };
    for (int i = 0; i < binary_signal.size(); i++) {
        int feedback = shift_register[0] ^ shift_register[8];
        int scrambled_bit = binary_signal[i] ^ feedback;
        scrambled_signal.push_back(scrambled_bit);
        shift_register.pop_back();
        shift_register.insert(shift_register.begin(), scrambled_bit);
    }
    return scrambled_signal;
}

vector<int> descramble(const vector<int>& binary_signal)
{
    vector<int> descrambled_signal;
    vector<int> shift_register = { 1,0,0,0,1,0,1,0,1 };
    for (int i = 0; i < binary_signal.size(); i++) {
        int feedback = shift_register[0] ^ shift_register[8];
        int descrambled_bit = binary_signal[i] ^ feedback;
        descrambled_signal.push_back(descrambled_bit);
        shift_register.pop_back();
        shift_register.insert(shift_register.begin(), binary_signal[i]);
    }
    return descrambled_signal;
}

void print_signal(const vector<int>& binary_signal)
{
    for (int i : binary_signal) {
        cout << i;
    }
    cout << endl;
}

void scrambling(const vector<int>& binary_to_scramble)
{
    cout << "Original signal:    ";
    print_signal(binary_to_scramble);
    cout << "Scrambled signal: ";
    vector<int> scrambled_signal = scramble(binary_to_scramble);
    print_signal(scrambled_signal);
    cout << "Descrambled signal: ";
    vector<int> descrambled_signal = descramble(scrambled_signal);
    print_signal(descrambled_signal);
    cout << "-------------------------------------------" << endl;
}

vector<int> generate_signal(int n)
{
    random_device generator;
    mt19937 engine(generator());
    uniform_int_distribution<> distributor(0, 1);
    vector<int> signal;
    for (int i = 0; i < n; i++) {
        signal.push_back(distributor(engine));
    }
    return signal;
}
