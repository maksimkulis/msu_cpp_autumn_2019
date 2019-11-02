#include <cstring>
#include <algorithm>

#include "BigInt.h"

BigInt::BigInt(int value)
        : _size(0)
        , _sign((value >= 0) - (value < 0))
{
    long long int tmp = value;
    tmp = tmp * _sign;
    do {
        ++_size;
        value /= 10;
    } while (value != 0);
    _data = new char[_size];
    for (int i = 0; i < _size; ++i, tmp /= 10) {
        _data[i] = tmp % 10;
    }
}

BigInt::BigInt(const BigInt& value)
        : _size(value._size)
        , _sign(value._sign)
{
    _data = new char[_size];
    std::memcpy(_data, value._data, _size);
}

BigInt::BigInt(BigInt&& value)
        : _size(value._size)
        , _sign(value._sign)
{
    _data = value._data;
    value._data = nullptr;
}

BigInt::BigInt(char _sign, size_t _size, char* _data)
        : _sign(_sign)
        , _size(_size)
        , _data(_data)
{
}

BigInt::~BigInt()
{
    delete[] _data;
}

BigInt& BigInt::operator=(const BigInt& value)
{
    if (this == &value) {
        return *this;
    }
    if (_size < value._size) {
        char* tmp = new char[value._size];
        delete[] _data;
        _data = tmp;
        _size = value._size;
    }
    std::memcpy(_data, value._data, value._size);
    std::memset(_data + value._size, 0, value._size - _size);
    _sign = value._sign;
    return *this;
}

BigInt& BigInt::operator=(BigInt&& value)
{
    if (this == &value) {
        return *this;
    }
    _data = value._data;
    value._data = nullptr;
    _size = value._size;
    _sign = value._sign;
    return *this;
}

bool BigInt::operator==(const BigInt& other) const
{
    if (_sign != other._sign) {
        return false;
    }
    if (memcmp(_data, other._data, std::min(_size, other._size)) != 0) {
        return false;
    }
    for (size_t i = std::min(_size, other._size); i < _size; ++i) {
        if (_data[i] != 0) {
            return false;
        }
    }
    for (size_t i = std::min(_size, other._size); i < other._size; ++i) {
        if (other._data[i] != 0) {
            return false;
        }
    }
    return true;
}

bool BigInt::operator!=(const BigInt& other) const
{
    return !(*this == other);
}

int BigInt::_cmp(const char* other, size_t other_size) const
{
    for (size_t i = _size - 1; i >= other_size; --i) {
        if (_data[i] != 0) {
            return 1;
        }
    }
    for (size_t i = other_size - 1; i >= _size; --i) {
        if (other[i] != 0) {
            return -1;
        }
    }
    for (size_t i = std::min(_size, other_size) - 1; i > 0; --i) {
        if (_data[i] != other[i]) {
            return _data[i] - other[i];
        }
    }
    return _data[0] - other[0];
}

bool BigInt::operator<=(const BigInt& other) const
{
    if (_sign != other._sign) {
        return _sign < other._sign;
    }
    return _sign * _cmp(other._data, other._size) <= 0;
}

bool BigInt::operator<(const BigInt& other) const
{
    if (_sign != other._sign) {
        return _sign < other._sign;
    }
    return _sign * _cmp(other._data, other._size) < 0;
}

bool BigInt::operator>=(const BigInt& other) const
{
    if (_sign != other._sign) {
        return _sign > other._sign;
    }
    return _sign * _cmp(other._data, other._size) >= 0;
}

bool BigInt::operator>(const BigInt& other) const
{
    if (_sign != other._sign) {
        return _sign > other._sign;
    }
    return _sign * _cmp(other._data, other._size) > 0;
}

char* BigInt::_abs_sum(const char* other, size_t other_size, size_t& new_size) const
{
    int sum = 0;
    int extra_byte = 0;
    size_t i;
    for (i = std::max(_size, other_size) - 1; i > 0; --i) {
        sum = (i < _size) * _data[(i < _size) * i] +
        (i < other_size) * other[(i < other_size) * i];
        if (sum > 9) {
            extra_byte = 1;
            break;
        } else if (sum < 9) {
            break;
        }
    }
    if (i == 0) {
        extra_byte = (_data[0] + other[0]) / 10;
    }

    new_size = std::max(_size, other_size) + extra_byte;
    char* res = new char[new_size];
    int extra_value = 0;
    for (size_t i = 0; i < std::min(_size, other_size); ++i) {
        res[i] = (_data[i] + other[i] + extra_value) % 10;
        extra_value = (_data[i] + other[i] + extra_value) / 10;
    }

    for (size_t i = std::min(_size, other_size); i < _size; ++i) {
        res[i] = (_data[i] + extra_value) % 10;
        extra_value = (_data[i] + extra_value) / 10;
    }
    for (size_t i = std::min(_size, other_size); i < other_size; ++i) {
        res[i] = (other[i] + extra_value) % 10;
        extra_value = (other[i] + extra_value) / 10;
    }
    if (extra_value == 1) {
        res[std::max(_size, other_size)] = 1;
    }
    return res;
}

char* BigInt::_abs_sub(const char* other, size_t other_size, char& sign, size_t& new_size) const
{
    int cmp = _cmp(other, other_size);
    const char* left = cmp >= 0 ? _data : other;
    const char* right = cmp < 0 ? _data : other;
    size_t lsize = cmp >= 0 ? _size : other_size;
    size_t rsize = cmp < 0 ? _size : other_size;
    if (cmp < 0) {
        sign *= -1;
    }
    new_size = std::max(rsize, lsize);
    char* res = new char[new_size];
    int extra_value = 0;

    for (size_t i = 0; i < std::min(rsize, lsize); ++i) {
        res[i] = (left[i] - right[i] - extra_value + 10) % 10;
        extra_value = (left[i] - right[i] - extra_value) < 0;
    }
    for (size_t i = std::min(rsize, lsize); i < lsize; ++i) {
        res[i] = (left[i] - extra_value + 10) % 10;
        extra_value = (left[i] - extra_value) < 0;
    }
    return res;
}

BigInt BigInt::operator+(const BigInt& other) const
{
    char* new_data;
    char new_sign = _sign;
    size_t new_size;
    if (_sign == other._sign) {
        new_data = _abs_sum(other._data, other._size, new_size);
        return BigInt(new_sign, new_size, new_data);
    }
    new_data = _abs_sub(other._data, other._size, new_sign, new_size);
    return BigInt(new_sign, new_size, new_data);
}

BigInt BigInt::operator-(const BigInt& other) const
{
    char* new_data;
    char new_sign = _sign;
    size_t new_size;
    if (_sign != other._sign) {
        new_data = _abs_sum(other._data, other._size, new_size);
        return BigInt(new_sign, new_size, new_data);
    }
    new_data = _abs_sub(other._data, other._size, new_sign, new_size);
    return BigInt(new_sign, new_size, new_data);
}

BigInt BigInt::operator-() const
{
    BigInt res = *this;
    res._sign *= -1;
    return res;
}

std::ostream& operator<<(std::ostream& out, const BigInt& bint)
{
    if (bint._sign < 0) {
        out << '-';
    }
    size_t i = bint._size - 1;
    while (i > 0 && bint._data[i] == 0) {
        --i;
    }
    while (i > 0) {
        out << char(bint._data[i] + '0');
        --i;
    }
    out << char(bint._data[0] + '0');
    return out;
}
