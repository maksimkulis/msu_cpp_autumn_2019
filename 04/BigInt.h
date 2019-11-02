#pragma once
#include <string>
#include <iostream>

class BigInt
{
public:
    friend std::ostream& operator<<(std::ostream& out, const BigInt& value);
    BigInt(int value=0);
    BigInt(const BigInt& value);
    BigInt(BigInt&& value);
    ~BigInt();
    BigInt& operator=(const BigInt& value);
    BigInt& operator=(BigInt&& value);
    bool operator==(const BigInt& other) const;
    bool operator!=(const BigInt& other) const;
    bool operator<=(const BigInt& other) const;
    bool operator>=(const BigInt& other) const;
    bool operator<(const BigInt& other) const;
    bool operator>(const BigInt& other) const;
    BigInt operator+(const BigInt& other) const;
    BigInt operator-(const BigInt& other) const;
    BigInt operator-() const;
private:
    BigInt(char _sign, size_t _size, char* _data);
    char* _abs_sum(const char* other, size_t other_size, size_t& new_size) const;
    char* _abs_sub(const char* other, size_t other_size, char& sign, size_t& new_size) const;
    int _cmp(const char* other, size_t other_size) const;
    char _sign;
    char* _data;
    size_t _size;
};

std::ostream& operator<<(std::ostream& out, const BigInt& value);
