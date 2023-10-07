#include "Arguments.h"
#include <string>
#include <vector>
#include <cmath>

ArgumentParser::Arguments::Arguments() {}

ArgumentParser::Arguments::Arguments(const std::string arg_name) {

    arg_name_ = arg_name;
    pr_arg_name_ = "--" + arg_name + "=";

}

ArgumentParser::Arguments::Arguments(const char arg_shortname, const std::string arg_name) {

    arg_name_ = arg_name;
    pr_arg_name_ = "--" + arg_name + "=";

    arg_shortname_ = arg_shortname;
    pr_arg_shortname_ = "-";
    pr_arg_shortname_.push_back(arg_shortname_);
    pr_arg_shortname_ = pr_arg_shortname_ + "=";
    flag_shortname_ = true;

}

ArgumentParser::Arguments::~Arguments() {}

std::string ArgumentParser::Arguments::GetName() {

    return arg_name_;
}

std::string ArgumentParser::Arguments::GetPrName() {

    return pr_arg_name_;
}

std::string ArgumentParser::Arguments::GetPrShortname() {

    return pr_arg_shortname_;
}

bool ArgumentParser::Arguments::FlagShortname() {

    return flag_shortname_;
}

void ArgumentParser::Arguments::Value(const std::string arg_value) {

    value_ = arg_value;
}

std::string ArgumentParser::Arguments::GetValue() {

    return value_;
}

void ArgumentParser::Arguments::Default(const char* def_value) {

    def_value_ = def_value;
}

void ArgumentParser::Arguments::Default(const bool def_flag) {

    def_flag_ = def_flag;
    flag_def_flag_ = true;

}

std::string ArgumentParser::Arguments::GetDefault() {

    return def_value_;
}

bool ArgumentParser::Arguments::FlagDefaultFlag() {

    return flag_def_flag_;
}

void ArgumentParser::Arguments::StoreValue(std::string& store_str_value) {

    flag_store_str_value_ = true;
    store_value_ = &store_str_value;
}

void ArgumentParser::Arguments::StoreValue(bool& store_flag) {

    flag_store_flag_ = true;
    store_flag_ = &store_flag;

}

void ArgumentParser::Arguments::StoreValues(std::vector<int>& store_int_values) {

    flag_store_int_values_ = true;
    store_values_ = &store_int_values;
}

void ArgumentParser::Arguments::AddStoreValue(const std::string arg_value) {

    *store_value_ = arg_value;
}

void ArgumentParser::Arguments::AddStoreFlag(const bool arg_flag) {

    *store_flag_ = arg_flag;
}

void ArgumentParser::Arguments::AddStoreValues(const std::string arg_value) {

    int temp_arg_value = 0;
    int p = 0;

    for (int j = arg_value.size() -1 ; j >= 0; j--) {
        int temp = int(arg_value[j]) - 48;
        temp_arg_value = temp_arg_value + (temp * pow(10, p));
        p++;
    }
    (*store_values_).push_back(temp_arg_value);

}

bool ArgumentParser::Arguments::FlagStoreStrValue() {

    return flag_store_str_value_;
}

bool ArgumentParser::Arguments::FlagStoreFlag() {

    return flag_store_flag_;
}

bool ArgumentParser::Arguments::FlagStoreIntValues() {

    return flag_store_int_values_;
}

ArgumentParser::Arguments& ArgumentParser::Arguments::MultiValue() {

    flag_multi_value_ = true;
    return *this;
}

ArgumentParser::Arguments& ArgumentParser::Arguments::MultiValue(const int min_args_count) {

    flag_multi_value_ = true;
    min_args_count_ = min_args_count;
    return *this;
}

int ArgumentParser::Arguments::GetMinArgsCount() {

    return min_args_count_;
}

bool ArgumentParser::Arguments::FlagMultiValue() {

    return flag_multi_value_;
}

bool ArgumentParser::Arguments::MultiCount() {

    multi_count_++;
}

int ArgumentParser::Arguments::GetMultiCount() {

    return multi_count_;
}

void ArgumentParser::Arguments::AddValueVector(const std::string value) {

    int temp_value = 0;
    int p = 0;

    for (int j = value.size() -1 ; j >= 0; j--) {
        int temp = int(value[j]) - 48;
        temp_value = temp_value + (temp * pow(10, p));
        p++;
    }
    vector_values_.push_back(temp_value);

}

int ArgumentParser::Arguments::GetVectorValue(const int index) {

    return vector_values_[index];
}

void ArgumentParser::Arguments::Info(const std::string info) {

    info_ = info;
}

ArgumentParser::Arguments& ArgumentParser::Arguments::Positional() {

    flag_positional_ = true;
    return *this;

}

bool ArgumentParser::Arguments::FlagPositional() {

    return flag_positional_;
}

void ArgumentParser::Arguments::NameFlag(const std::string name_flag) {

    name_flag_ = name_flag;
    pr_name_flag_ = "--" + name_flag;
    flag_ = true;

}

void ArgumentParser::Arguments::NameAndShortNameFlag(const char shortname_flag, const std::string name_flag) {

    name_flag_ = name_flag;
    pr_name_flag_ = "--" + name_flag;

    shortname_flag_ = shortname_flag;
    pr_shortname_flag_ = "-";
    pr_shortname_flag_.push_back(shortname_flag);
    flag_shortname_flag_ = true;
    flag_ = true;

}

bool ArgumentParser::Arguments::Flag() {

    return flag_;
}

std::string ArgumentParser::Arguments::GetNameFlag() {

    return name_flag_;
}

char ArgumentParser::Arguments::GetShortnameFlag() {

    return shortname_flag_;
}

std::string ArgumentParser::Arguments::GetPrNameFlag() {

    return pr_name_flag_;
}

bool ArgumentParser::Arguments::FullFlag() {

    full_flag_ = true;
    return full_flag_;

}

void ArgumentParser::Arguments::NameHelp(const char shortname_help, const std::string name_help) {

    name_help_ = name_help;
    pr_name_help_ = "--" + name_help;

    shortname_help_ = shortname_help;
    pr_shortname_help_ = '-';
    pr_shortname_help_.push_back(shortname_help);

}

std::string ArgumentParser::Arguments::GetPrNameHelp() {

    return pr_name_help_;
}

void ArgumentParser::Arguments::GetHelp() {

    flag_help_ = true;
}

bool ArgumentParser::Arguments::FlagHelp() {

    return flag_help_;
}
