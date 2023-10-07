#include "number.h"
#include <cmath>

uint2022_t from_uint(uint32_t i) {

    uint2022_t value;
    uint32_t temp = i;
    for (int j = 0; j < ARR_SIZE; j++) {
        value.arr[j] = temp % DIVIDER;
        temp = temp / DIVIDER;
    }

    return value;
}

uint2022_t from_string(const char* buff) {

    uint2022_t value;
    int key = 0;
    std::string temp_buff = buff;
    std::string arr_str = "";

    for (int i = temp_buff.size() - 1; i >= 0; i--) {
        if (arr_str.size() < 9) {
            arr_str = temp_buff[i] + arr_str;
        }
        if (arr_str.size() == 9) {
            uint32_t temp_arg = 0;
            int p = 0;
            for(int j = arr_str.size() - 1; j >= 0; j--) {
                int temp = int(arr_str[j]) - 48;
                temp_arg = temp_arg + (temp * pow(10, p));
                p++;
            }
            value.arr[key] = temp_arg;
            arr_str = "";
            key++;
        }
    }

    uint32_t temp_arg = 0;
    int p = 0;
    for (int j = arr_str.size() - 1; j >= 0; j--) {
        int temp = int(arr_str[j]) - 48;
        temp_arg = temp_arg + (temp * pow(10, p));
        p++;
    }
    value.arr[key] = temp_arg;
    arr_str = "";
    key++;

    return value;
}

uint2022_t operator+(const uint2022_t& lhs, const uint2022_t& rhs) {

    uint2022_t value;
    uint2022_t temp;
    for (int i = 0; i < ARR_SIZE; i++) {
        temp.arr[i] = lhs.arr[i] + rhs.arr[i];
    }

    uint32_t billions = 0;
    for (int i = 0; i < ARR_SIZE; i++) {
        if (temp.arr[i] < DIVIDER) {
            if ((temp.arr[i] == DIVIDER - 1) && (billions == 1)) {
                value.arr[i] = 0;
                billions = 1;
            } else {
                value.arr[i] = temp.arr[i] + billions;
                billions = 0;
            }
        }
        if (temp.arr[i] >= DIVIDER) {
            value.arr[i] = (temp.arr[i] % DIVIDER) + billions;
            billions = 1;
        }
    }

    return value;
}

uint2022_t operator-(const uint2022_t& lhs, const uint2022_t& rhs) {

    uint2022_t value;
    uint32_t billions = 0;
    for (int i = 0; i < ARR_SIZE; i++) {
        if(lhs.arr[i] > rhs.arr[i]) {
            value.arr[i] = (lhs.arr[i] - rhs.arr[i]) - billions;
            billions = 0;
        }
        if (lhs.arr[i] == rhs.arr[i]) {
            value.arr[i] = 0;
            billions = 0;
        }
        if (lhs.arr[i] < rhs.arr[i]) {
            value.arr[i] = ((lhs.arr[i] + DIVIDER) - rhs.arr[i]) - billions;
            billions = 1;
        }
    }

    return value;
}

uint2022_t operator*(const uint2022_t& lhs, const uint2022_t& rhs) {

    uint2022_t value;
    uint64_t billions = 0;
    int shift = 0;
    for (int i = 0; i < ARR_SIZE; i++) {
        uint2022_t temp;
        for (int j = 0; j + shift < ARR_SIZE; j++) {
            temp.arr[j + shift] = ((uint64_t)lhs.arr[j] * (uint64_t)rhs.arr[i] + billions) % DIVIDER;
            billions = ((uint64_t)lhs.arr[j] * (uint64_t)rhs.arr[i] + billions) / DIVIDER;
        }
        value = value + temp;
        shift++;
    }

    return value;
}

uint2022_t operator/(const uint2022_t& lhs, const uint2022_t& rhs) {
    return uint2022_t();
}

bool operator==(const uint2022_t& lhs, const uint2022_t& rhs) {

    for (int i = 0; i < ARR_SIZE; i++) {
        if (lhs.arr[i] != rhs.arr[i]) {
            return false;
        }
    }

    return true;
}

bool operator!=(const uint2022_t& lhs, const uint2022_t& rhs) {

    return !(lhs == rhs);
}

std::ostream& operator<<(std::ostream& stream, const uint2022_t& value) {

    int flag = 0;
    for (int i = ARR_SIZE -1; i >= 0; i--) {
        if (value.arr[i] != 0) {
            flag = i;
            break;
        }
    }

    for (int i = flag; i >= 0; i--) {
        if (i == flag) {
            stream << value.arr[i];
        } else {
            stream.width(9);
            stream.fill('0');
            stream << value.arr[i];
        }
    }

    return stream;
}
