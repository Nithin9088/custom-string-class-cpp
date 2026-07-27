/*
    ============================================================
    MINI PROJECT: Implement Own String Class
    ============================================================
    NOTE: The class has ONLY ONE data member -> char* str
    There is no separate 'int len' member. Wherever the length
    is needed, it is computed on the fly by scanning for '\0'.

    MEMBER FUNCTIONS (use predefined C-string library functions
    like strcpy, strcmp, strcat from <cstring>):
        1) Constructor
        2) Parametrized constructor      -> String s("vector");
        3) Copy constructor              -> String s(s1);
        4) Assignment (=) operator overload
        5) + operator (concatenation)
        6) [] operator
        7) << , >> operators (friend functions)
        8) >, <, >=, <=, !=, == (relational operators)

    FRIEND FUNCTIONS (user-defined from scratch, NOT using
    <cstring>, to show how the library functions actually work
    internally):
        1)  strcpy(s1, s2)
        2)  strncpy(s1, s2, n)
        3)  strcmp(s1, s2)
        4)  strncmp(s1, s2, n)
        5)  strcat(s1, s2)
        6)  strncat(s1, s2, n)
        7)  strrev(s1)
        8)  strupper(s1)
        9)  strlower(s1)
        10) strchr(s1, ch)
        11) strrchr(s1, ch)
        12) strstr(s1, s2)
        13) strlen(s1)
    ============================================================
*/

#include <iostream>
#include <cstring>   // used ONLY inside member functions, as required
using namespace std;

class String {
private:
    char* str;   
    int length() const {
        int count = 0;
        while (str[count] != '\0')
            count++;
        return count;
    }

public:
    
    // 1) Default constructor
    String() {
        str = new char[1];
        str[0] = '\0';
    }

  
    // 2) Parametrized constructor  
   
    String(const char* s) {
        str = new char[strlen(s) + 1];
        strcpy(str, s);
    }

    
    // 3) Copy constructor  ->  String s(s1);
    
    String(const String& other) {
        str = new char[strlen(other.str) + 1];
        strcpy(str, other.str);
    }

    // Destructor
    ~String() {
        delete[] str;
    }

    
    // 4) Assignment operator overloaed
    String& operator=(const String& p) {
        if (this == &p) return *this;   
        delete[] str;
        str = new char[strlen(p.str) + 1];
        strcpy(str, p.str);
        return *this;
    }

    
    // 5) + operator 
   
    String operator+(const String& p) const {
        char* q = new char[strlen(str) + strlen(p.str) + 1];
        strcpy(q, str);
        strcat(q, p.str);
        String result(q);
        delete[] q;
        return result;
    }

    
    // 6) [] operator 
   
    char& operator[](int i) {
        if (i < 0 || i >= length()) {
            cout << "Index out of range!" << endl;
            static char d = '\0';
            return d;
        }
        return str[i];
    }

    // ---------------------------------------------------------
    // 8) Relational operators: >, <, >=, <=, !=, ==
    // ---------------------------------------------------------
    bool operator==(const String& p) const
    { 
	    return strcmp(str, p.str) == 0;
    }
    bool operator!=(const String& p) const
    {
	    return strcmp(str, p.str) != 0;
    }
    bool operator<(const String& p)  const
    {
	    return strcmp(str, p.str) < 0;
    }
    bool operator>(const String& p)  const
    {
	    return strcmp(str, p.str) > 0;
    }
    bool operator<=(const String& p) const
    {
	    return strcmp(str, p.str) <= 0; 
    }
    bool operator>=(const String& p) const
    {
	    return strcmp(str, p.str) >= 0;
    }

    friend ostream& operator<<(ostream& out, const String& s);
    friend istream& operator>>(istream& in, String& s);

    friend void myStrcpy(String& dest, const String& src);
    friend void myStrncpy(String& dest, const String& src, int n);
    friend int  myStrcmp(const String& s1, const String& s2);
    friend int  myStrncmp(const String& s1, const String& s2, int n);
    friend void myStrcat(String& s1, const String& s2);
    friend void myStrncat(String& s1, const String& s2, int n);
    friend void myStrrev(String& s);
    friend void myStrupper(String& s);
    friend void myStrlower(String& s);
    friend int  myStrchr(const String& s, char ch);
    friend int  myStrrchr(const String& s, char ch);
    friend int  myStrstr(const String& s1, const String& s2);
    friend int  myStrlen(const String& s);
};

ostream& operator<<(ostream& out, const String& s) {
    out << s.str;
    return out;
}

istream& operator>>(istream& in, String& s) {
    char b[1000];
    in >> b;
    delete[] s.str;
    s.str = new char[strlen(b) + 1];
    strcpy(s.str, b);
    return in;
}


// 1) strcpy(s1, s2) : copy src into dest
void myStrcpy(String& dest, const String& src) {
    int Len = 0;
    while (src.str[Len] != '\0') Len++;

    delete[] dest.str;
    dest.str = new char[Len + 1];
    int i = 0;
    for (; i < Len; i++)
        dest.str[i] = src.str[i];
    dest.str[i] = '\0';
}

// 2) strncpy(s1, s2, n) : copy first n chars of src into dest
void myStrncpy(String& dest, const String& src, int n) {
    int srcLen = 0;
    while (src.str[srcLen] != '\0') srcLen++;

    int copyLen = (n < srcLen) ? n : srcLen;
    delete[] dest.str;
    dest.str = new char[copyLen + 1];
    int i = 0;
    for (; i < copyLen; i++)
        dest.str[i] = src.str[i];
    dest.str[i] = '\0';
}

// 3) strcmp(s1, s2) : lexicographic comparison
int myStrcmp(const String& s1, const String& s2) {
    int i = 0;
    while (s1.str[i] != '\0' && s2.str[i] != '\0') {
        if (s1.str[i] != s2.str[i])
            return s1.str[i] - s2.str[i];
        i++;
    }
    return s1.str[i] - s2.str[i];
}

// 4) strncmp(s1, s2, n) : compare first n characters
int myStrncmp(const String& s1, const String& s2, int n) {
    int i = 0;
    while (i < n && s1.str[i] != '\0' && s2.str[i] != '\0') {
        if (s1.str[i] != s2.str[i])
            return s1.str[i] - s2.str[i];
        i++;
    }
    if (i == n) return 0;
    return s1.str[i] - s2.str[i];
}

// 5) strcat(s1, s2) : append s2 onto s1
void myStrcat(String& s1, const String& s2) {
    int len1 = 0; while (s1.str[len1] != '\0') len1++;
    int len2 = 0; while (s2.str[len2] != '\0') len2++;

    char* buffer = new char[len1 + len2 + 1];
    int i = 0;
    for (; i < len1; i++)
        buffer[i] = s1.str[i];
    for (int j = 0; j < len2; j++, i++)
        buffer[i] = s2.str[j];
    buffer[i] = '\0';

    delete[] s1.str;
    s1.str = buffer;
}

// 6) strncat(s1, s2, n) : append first n chars of s2 onto s1
void myStrncat(String& s1, const String& s2, int n) {
    int len1 = 0; while (s1.str[len1] != '\0') len1++;
    int len2 = 0; while (s2.str[len2] != '\0') len2++;

    int appendLen = (n < len2) ? n : len2;
    char* buffer = new char[len1 + appendLen + 1];
    int i = 0;
    for (; i < len1; i++)
        buffer[i] = s1.str[i];
    for (int j = 0; j < appendLen; j++, i++)
        buffer[i] = s2.str[j];
    buffer[i] = '\0';

    delete[] s1.str;
    s1.str = buffer;
}

// 7) strrev(s) : reverse the string in place
void myStrrev(String& s) {
    int len = 0; while (s.str[len] != '\0') len++;
    int i = 0, j = len - 1;
    while (i < j) {
        char temp = s.str[i];
        s.str[i] = s.str[j];
        s.str[j] = temp;
        i++;
        j--;
    }
}

// 8) strupper(s) : convert to uppercase in place
void myStrupper(String& s) {
    for (int i = 0; s.str[i] != '\0'; i++) {
        if (s.str[i] >= 'a' && s.str[i] <= 'z')
            s.str[i] = s.str[i] - 'a' + 'A';
    }
}

// 9) strlower(s) : convert to lowercase in place
void myStrlower(String& s) {
    for (int i = 0; s.str[i] != '\0'; i++) {
        if (s.str[i] >= 'A' && s.str[i] <= 'Z')
            s.str[i] = s.str[i] - 'A' + 'a';
    }
}

// 10) strchr(s, ch) : index of first occurrence of ch, else -1
int myStrchr(const String& s, char ch) {
    for (int i = 0; s.str[i] != '\0'; i++) {
        if (s.str[i] == ch)
            return i;
    }
    return -1;
}

// 11) strrchr(s, ch) : index of last occurrence of ch, else -1
int myStrrchr(const String& s, char ch) {
    int len = 0; while (s.str[len] != '\0') len++;
    for (int i = len - 1; i >= 0; i--) {
        if (s.str[i] == ch)
            return i;
    }
    return -1;
}

// 12) strstr(s1, s2) : index of first occurrence of s2 in s1, else -1
int myStrstr(const String& s1, const String& s2) {
    int len1 = 0; while (s1.str[len1] != '\0') len1++;
    int len2 = 0; while (s2.str[len2] != '\0') len2++;

    if (len2 == 0) return 0;
    for (int i = 0; i <= len1 - len2; i++) {
        int j = 0;
        for (; j < len2; j++) {
            if (s1.str[i + j] != s2.str[j])
                break;
        }
        if (j == len2)
            return i;
    }
    return -1;
}

// 13) strlen(s) : length of the string
int myStrlen(const String& s) {
    int count = 0;
    while (s.str[count] != '\0')
        count++;
    return count;
}

int main() {

   /* String s1;                 // 1) default constructor
    String s2("vector");       // 2) parametrized constructor
    String s3(s2);             // 3) copy constructor

    cout << "s2 = " << s2 << endl;
    cout << "s3 (copy of s2) = " << s3 << endl;

   s1 = s2;                   // 4) assignment operator
    cout << "s1 (assigned from s2) = " << s1 << endl;

    String s4("Hello ");
    String s5("World");
    String s6 = s4 + s5;       // 5) + operator
    cout << "s4 + s5 = " << s6 << endl;

    cout << "s6[0] = " << s6[0] << endl;   // 6) [] operator
    s6[0] = 'h';
    cout << "after s6[0]='h' -> " << s6 << endl;

    cout << "Enter a string: ";
    String s7;
    cin >> s7;                 // 7) >> operator
    cout << "You entered: " << s7 << endl;   // << operator

    // 8) relational operators
    String a("vector"), b("vector");
    cout << "a == b : " << (a == b) << endl;
    cout << "a != b : " << (a != b) << endl;
    cout << "a < b  : " << (a < b)  << endl;
    cout << "a > b  : " << (a > b)  << endl;
    cout << "a <= b : " << (a <= b) << endl;
    cout << "a >= b : " << (a >= b) << endl;

    cout << "\n===== FRIEND FUNCTION  =====" << endl;
*/
    String x("hello"), y("world"), dest;

    myStrcpy(dest, x);
    cout << "myStrcpy(dest, x) -> dest = " << dest << endl;

    myStrncpy(dest, y, 3);
    cout << "myStrncpy(dest, y, 3) -> dest = " << dest << endl;

  /*  cout << "myStrcmp(x, y) = " << myStrcmp(x, y) << endl;
    cout << "myStrncmp(x, y, 2) = " << myStrncmp(x, y, 2) << endl;

    String s8("Hello ");
    myStrcat(s8, y);
    cout << "myStrcat(s8, y) -> s8 = " << s8 << endl;

    String s9("Hello ");
    myStrncat(s9, y, 3);
    cout << "myStrncat(s9, y, 3) -> s9 = " << s9 << endl;

    String s10("Programming");
    myStrrev(s10);
    cout << "myStrrev(Programming) = " << s10 << endl;

    String s11("Programming");
    myStrupper(s11);
    cout << "myStrupper(Programming) = " << s11 << endl;

    String s12("Programming");
    myStrlower(s12);
    cout << "myStrlower(Programming) = " << s12 << endl;

    String s13("Programming");
    cout << "myStrchr(s13, 'g') = " << myStrchr(s13, 'g') << endl;
    cout << "myStrrchr(s13, 'g') = " << myStrrchr(s13, 'g') << endl;

    String s14("Hello World"), s15("World");
    cout << "myStrstr(s14, s15) = " << myStrstr(s14, s15) << endl;

    String s16("Programming");
    cout << "myStrlen(s16) = " << myStrlen(s16) << endl;
*/
    return 0;
}
