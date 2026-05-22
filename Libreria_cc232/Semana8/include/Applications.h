#pragma once

#include <optional>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

#include "ChainedHashTable.h"
#include "HashtableOA.h"
#include "HashCode.h"
#include "LinearHashTable.h"

namespace ods {

inline bool hasDuplicates(const std::vector<int>& v) {
    ChainedHashTable<int> t;
    for (int x : v) if (!t.add(x)) return true;
    return false;
}

inline std::vector<int> uniquePreservingOrder(const std::vector<int>& v) {
    ChainedHashTable<int> seen;
    std::vector<int> out;
    for (int x : v) if (seen.add(x)) out.push_back(x);
    return out;
}

inline std::optional<int> firstRepeated(const std::vector<int>& v) {
    LinearHashTable<int> t;
    for (int x : v) {
        if (t.contains(x)) return x;
        t.add(x);
    }
    return std::nullopt;
}

inline HashtableOA<std::string, int> frequencyCount(const std::vector<std::string>& words) {
    HashtableOA<std::string, int> f;
    for (const auto& raw : words) {
        std::string s = normalizeToken(raw);
        if (s.empty()) continue;
        auto cur = f.get(s);
        if (cur) {
            f.remove(s);
            f.put(s, *cur + 1);
        } else {
            f.put(s, 1);
        }
    }
    return f;
}

inline HashtableOA<std::string, int> wordFrequencyFromText(const std::string& text) {
    std::istringstream in(text);
    std::vector<std::string> words;
    std::string token;
    while (in >> token) words.push_back(token);
    return frequencyCount(words);
}

// Devuelve indices i,j tales que a[i] + a[j] == target, si existen.
inline std::optional<std::pair<int, int>> twoSum(const std::vector<int>& a, int target) {
    HashtableOA<int, int> pos;
    for (int i = 0; i < static_cast<int>(a.size()); ++i) {
        int need = target - a[i];
        auto j = pos.get(need);
        if (j) return std::make_pair(*j, i);
        pos.put(a[i], i);
    }
    return std::nullopt;
}

inline std::vector<std::string> deduplicateLogs(const std::vector<std::string>& logs) {
    ChainedHashTable<std::string> seen;
    std::vector<std::string> out;
    for (const auto& line : logs) {
        if (seen.add(line)) out.push_back(line);
    }
    return out;
}

// Indice invertido simple: palabra -> ids de documentos donde aparece.
inline HashtableOA<std::string, std::vector<int>> invertedIndex(const std::vector<std::string>& documents) {
    HashtableOA<std::string, std::vector<int>> index;
    for (int doc = 0; doc < static_cast<int>(documents.size()); ++doc) {
        std::istringstream in(documents[doc]);
        ChainedHashTable<std::string> seenInDoc;
        std::string raw;
        while (in >> raw) {
            std::string word = normalizeToken(raw);
            if (word.empty() || !seenInDoc.add(word)) continue;
            auto current = index.get(word);
            if (current) {
                auto docs = *current;
                docs.push_back(doc);
                index.remove(word);
                index.put(word, docs);
            } else {
                index.put(word, std::vector<int>{doc});
            }
        }
    }
    return index;
}

}  // namespace ods
