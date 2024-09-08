#include <string>
#include <cctype>
#include <unordered_map>
#include <algorithm>

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

bool shouldSkipAppending(char code, char prevCode, char prevChar, const std::string& soundex) {
    return code == '0' || code == prevCode || toupper(prevChar) == toupper(soundex.back());
}

void appendSoundex(std::string& soundex, char code, char& prevCode, char prevChar) {
    if (shouldSkipAppending(code, prevCode, prevChar, soundex)) {
        return;
    }
    soundex += code;
    prevCode = code;
}

std::string paddingSoundex(const std::string& soundex) {
    std::string paddedSoundex = soundex;
    if (paddedSoundex.size() < 4) {
        paddedSoundex.append(4 - paddedSoundex.size(), '0');
    } else {
        paddedSoundex.resize(4);
    }
    return paddedSoundex;
}

void processCharacter(char c, char& prevCode, std::string& soundex, char prevChar) {
    if (isalpha(c)) {
        char code = mapToSoundexCode(c);
        appendSoundex(soundex, code, prevCode, prevChar);
    }
}

std::string buildSoundexLoop(const std::string& name, std::string soundex, char& prevCode, size_t index) {
    while (index < name.length() && soundex.length() < 4) {
        char prevChar = index > 0 ? name[index - 1] : '\0';
        processCharacter(name[index], prevCode, soundex, prevChar);
    }
    return soundex;
}

std::string buildSoundex(const std::string& name, std::string soundex, char prevCode, size_t index) {
    soundex = buildSoundexLoop(name, soundex, prevCode, index);
    return paddingSoundex(soundex);
}

std::string generateSoundex(const std::string& name) {
    if (name.empty()) return ""; 

    std::string soundex(1, toupper(name[0]));
    char prevCode = mapToSoundexCode(name[0]);

    return buildSoundex(name, soundex, prevCode, 1);
}
