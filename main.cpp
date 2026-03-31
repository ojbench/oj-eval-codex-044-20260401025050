#include <bits/stdc++.h>
using namespace std;

class mystring {
private:
    char* ch = nullptr;
    int len = 0;

public:
    mystring() : ch(nullptr), len(0) {}

    mystring(int _len, int c) : ch(nullptr), len(0) {
        if (_len > 0) {
            len = _len;
            ch = new char[len];
            memset(ch, c, static_cast<size_t>(len));
        }
    }

    mystring(string& s) : ch(nullptr), len(0) {
        if (!s.empty()) {
            len = static_cast<int>(s.length());
            ch = new char[len];
            memcpy(ch, s.data(), static_cast<size_t>(len));
        }
    }

    // Copy constructor
    mystring(const mystring& other) : ch(nullptr), len(0) {
        if (other.len > 0) {
            len = other.len;
            ch = new char[len];
            memcpy(ch, other.ch, static_cast<size_t>(len));
        }
    }

    // Move constructor
    mystring(mystring&& other) noexcept : ch(other.ch), len(other.len) {
        other.ch = nullptr;
        other.len = 0;
    }

    ~mystring() {
        delete[] ch;
        ch = nullptr;
        len = 0;
    }

    // Copy assignment
    mystring& operator=(const mystring& other) {
        if (this == &other) return *this;
        if (other.len == 0) {
            delete[] ch;
            ch = nullptr;
            len = 0;
            return *this;
        }
        char* n = new char[other.len];
        memcpy(n, other.ch, static_cast<size_t>(other.len));
        delete[] ch;
        ch = n;
        len = other.len;
        return *this;
    }

    // Move assignment
    mystring& operator=(mystring&& other) noexcept {
        if (this == &other) return *this;
        delete[] ch;
        ch = other.ch;
        len = other.len;
        other.ch = nullptr;
        other.len = 0;
        return *this;
    }

    // Indexing (0-based). Out-of-range returns '\0'.
    char operator[](int x) const {
        if (x < 0 || x >= len) return '\0';
        return ch[x];
    }

    // Lexicographical compare by characters, then by length
    bool operator<(const mystring& rhs) const {
        int n = min(len, rhs.len);
        for (int i = 0; i < n; ++i) {
            if (ch[i] != rhs.ch[i]) return ch[i] < rhs.ch[i];
        }
        return len < rhs.len;
    }

    // Optional equality operator (mentioned in background)
    bool operator==(const mystring& rhs) const {
        if (len != rhs.len) return false;
        if (len == 0) return true;
        return memcmp(ch, rhs.ch, static_cast<size_t>(len)) == 0;
    }

    // Concatenate rhs to this (ADD)
    void ADD(const mystring& rhs) {
        if (rhs.len == 0) return;
        if (len == 0) {
            // adopt copy of rhs
            char* n = new char[rhs.len];
            memcpy(n, rhs.ch, static_cast<size_t>(rhs.len));
            delete[] ch;
            ch = n;
            len = rhs.len;
            return;
        }
        char* n = new char[static_cast<size_t>(len) + rhs.len];
        memcpy(n, ch, static_cast<size_t>(len));
        memcpy(n + len, rhs.ch, static_cast<size_t>(rhs.len));
        delete[] ch;
        ch = n;
        len += rhs.len;
    }

    // Output the stored string as-is (no newline)
    void out() const {
        if (len > 0) cout.write(ch, len);
    }

    int get_len() const { return len; }

    // Allow streaming via operator<< (not required by judge, but convenient)
    friend ostream& operator<<(ostream& os, const mystring& s) {
        if (s.len > 0) os.write(s.ch, s.len);
        return os;
    }
};

string str_in1, str_in2;
int n, id;

int main() {
    // Keep default iostream sync to avoid mixing issues with C stdio
    // and preserve expected output ordering.

    if (!(cin >> id)) return 0;
    if (id == 1) {
        mystring str1(100, 'a');
        str1.out();
        cout << '\n';
        // cout << str1 << endl;
    } else if (id == 2) {
        cin >> str_in1;
        mystring str2 = str_in1;
        cin >> n;
        for (int i = 0, x; i < n; ++i) {
            cin >> x;
            cout << str2[x] << '\n';
        }
    } else if (id == 3) {
        cin >> str_in1 >> str_in2;
        mystring str2 = str_in1;
        mystring str3 = str_in2;
        cout << (int)(str2 < str3) << '\n';
    } else if (id == 4) {
        cin >> str_in1 >> str_in2;
        mystring str2 = str_in1;
        mystring str3 = str_in2;
        str2.ADD(str3);
        str2.out();
        cout << '\n';
        // cout << str2 << endl;
    } else {
        cin >> str_in1 >> str_in2;
        mystring str2 = str_in1;
        mystring str3 = str_in2;
        cin >> n;
        for (int i = 0, x; i < n; ++i) {
            cin >> x;
            cout << str3[x] << '\n';
        }
        cout << str2.get_len() << " " << str3.get_len() << '\n';
        cout << (int)(str2 < str3) << '\n';
        str2.ADD(str3);
        str2.out();
        cout << '\n';
        // cout << str2 << endl;
        cout << str2.get_len() << '\n';
    }
    return 0;
}
