#include <string>
#include <cctype>
#include <unordered_map>

// Function to map characters to their corresponding Soundex codes
char mapToSoundexCode(char c) {
    static const std::unordered_map<char, char> soundexMap = {
        {'B', '1'}, {'F', '1'}, {'P', '1'}, {'V', '1'},
        {'C', '2'}, {'G', '2'}, {'J', '2'}, {'K', '2'}, 
        {'Q', '2'}, {'S', '2'}, {'X', '2'}, {'Z', '2'},
        {'D', '3'}, {'T', '3'}, {'L', '4'}, {'M', '5'}, 
        {'N', '5'}, {'R', '6'}
    };
    
    c = toupper(c);
    auto it = soundexMap.find(c);
    return (it != soundexMap.end()) ? it->second : '0';
}

// Main function to generate the Soundex code
std::string generateSoundex(const std::string& name) {
    if (name.empty()) return "";  // Handle empty input

    std::string soundex(1, toupper(name[0]));  // Start with first letter
    char prevCode = mapToSoundexCode(name[0]);

    for (size_t i = 1; i < name.length() && soundex.length() < 4; ++i) {
        char code = mapToSoundexCode(name[i]);
        if (code != '0' && code != prevCode) {
            soundex += code;
            prevCode = code;
        }
    }

    // Pad with zeros to ensure length of 4
    soundex.append(4 - soundex.length(), '0');

    return soundex;
}
