#include <iostream>
#include <cmath>

using namespace std;

string base64_chars = 
    "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/" ;

string convert_to_binary(char input) {
    // Convert character to its 8-bit binary representation
    string result = "";
    int temp = input;
    
    while(temp != 0) {
        result = to_string(temp % 2) + result;
        temp /= 2;
    }
    
    // Ensure 8-bit representation (pad with leading zeros)
    while(result.size() < 8) {
        result = "0" + result;
    }

    return result;
}

int binary_to_int(string input) {
    int data = 0;
    int power = 0;
    for(int i = input.size() - 1; i >= 0; i--) {
        data += (input[i] - '0') * (int)pow(2, power);
        power += 1;
    }
    return data;
}

string base64_encode(const string& input) {
    string binary_string = "";
    for(char c : input) {
        binary_string += convert_to_binary(c);
    }

    int rem_bits = binary_string.size() % 6;
    // Add padding zeros to make the total number of bits a multiple of 6
    while (binary_string.size() % 6 != 0) {
        binary_string += "0";
    }

    string base64_string = "";
    // Process each 6-bit chunk and convert to base64
    for (int i = 0; i < binary_string.size(); i += 6) {
        string chunk = binary_string.substr(i, 6);
        int index = binary_to_int(chunk);
        base64_string += base64_chars[index];
    }

    // Handle padding
    int padding = (3 - input.size() % 3) % 3;
    for (int i = 0; i < padding; i++) {
        base64_string += "=";
    }

    return base64_string;
}

int main(int argc , char ** argv) {

    if (argc < 2){
        cout << "Please provide target string to be encoded"<<endl;
        cout << "Format should be ./base64_convert <input-string>"<<endl;
        exit(1);

    }
    string input(argv[1]);
  // Test string
    cout << "Input string: " << input << endl;
    
    string encoded = base64_encode(input);
    cout << "Base64 encoded string: " << encoded << endl;
    
    return 0;
}
