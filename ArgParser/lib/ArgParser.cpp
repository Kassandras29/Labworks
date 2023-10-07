#include "ArgParser.h"
#include "Arguments.h"
#include <string>
#include <vector>
#include <cmath>

ArgumentParser::ArgParser::ArgParser() {}

ArgumentParser::ArgParser::ArgParser(const std::string name) {

    parser_name_ = name;

}

ArgumentParser::ArgParser::~ArgParser() {}

bool ArgumentParser::ArgParser::Parse(std::vector<std::string> args) {

    if (all_arguments_.empty() && args.size() == 1) {
        return true;
    }

    int count_of_args = 0;

    if (!all_arguments_.empty() && args.size() >= 1) {
        for (int j = 0; j < args.size(); j++) {
            for (int i = 0; i < all_arguments_.size(); i++) {

                if (args.size() == 1 && !all_arguments_[i]->GetDefault().empty()) {
                    all_arguments_[i]->Value(all_arguments_[i]->GetDefault());
                    ++count_of_args;
                }
                else if (args[j].substr(0, all_arguments_[i]->GetPrName().length()) == all_arguments_[i]->GetPrName() && args.size() != 1 && args[j][0] == '-' && !all_arguments_[i]->FlagMultiValue() && !all_arguments_[i]->GetName().empty()) {
                    all_arguments_[i]->Value(args[j].substr(all_arguments_[i]->GetPrName().length(), args[j].size()));

                    if (all_arguments_[i]->FlagStoreStrValue()) {
                        all_arguments_[i]->AddStoreValue(all_arguments_[i]->GetValue());
                    }
                    ++count_of_args;
                }
                else if (args[j].substr(0, all_arguments_[i]->GetPrShortname().length()) == all_arguments_[i]->GetPrShortname() && args.size() != 1 && args[j][0] == '-' && all_arguments_[i]->FlagShortname() && !all_arguments_[i]->FlagMultiValue()) {
                    all_arguments_[i]->Value(args[j].substr(all_arguments_[i]->GetPrShortname().length(), args[j].size()));

                    if (all_arguments_[i]->FlagStoreStrValue()) {
                        all_arguments_[i]->AddStoreValue(all_arguments_[i]->GetValue());
                    }
                    ++count_of_args;
                }

                else if (all_arguments_[i]->FlagMultiValue()) {
                    if (args[j].substr(0, all_arguments_[i]->GetPrName().length()) == all_arguments_[i]->GetPrName() && args.size() != 1 && args[j][0] == '-') {
                        all_arguments_[i]->Value(args[j].substr(all_arguments_[i]->GetPrName().length(), args[j].size()));

                        all_arguments_[i]->MultiCount();
                    }
                    else if (args[j].substr(0, all_arguments_[i]->GetPrShortname().length()) == all_arguments_[i]->GetPrShortname() && args.size() != 1 && args[j][0] == '-' && all_arguments_[i]->FlagShortname()) {
                        all_arguments_[i]->Value(args[j].substr(all_arguments_[i]->GetPrShortname().length(), args[j].size()));

                        all_arguments_[i]->MultiCount();
                    }

                    if (all_arguments_[i]->FlagStoreIntValues() && args[j][0] == '-') {
                        all_arguments_[i]->AddStoreValues(all_arguments_[i]->GetValue());
                        all_arguments_[i]->AddValueVector(all_arguments_[i]->GetValue());
                    }
                }

                if (all_arguments_[i]->Flag()) {
                    if (args[j].substr(0, all_arguments_[i]->GetPrNameFlag().length()) == all_arguments_[i]->GetPrNameFlag()) {
                        if (all_arguments_[i]->FlagStoreFlag()) {
                            all_arguments_[i]->AddStoreFlag(all_arguments_[i]->FullFlag());
                        }
                        ++count_of_args;
                    }

                    else if (args[j].length() > 2 && args[j][0] == '-' && args[j][1] != '-') {
                        for (int k = 1; k < args[j].size(); k++) {
                            if (args[j][k] == all_arguments_[i]->GetShortnameFlag()) {
                                if (all_arguments_[i]->FlagStoreFlag()) {
                                    all_arguments_[i]->AddStoreFlag(all_arguments_[i]->FullFlag());
                                }
                                ++count_of_args;
                            }
                        }
                    }
                }

                else if (all_arguments_[i]->FlagPositional()) {
                    if (args[j] == "1" || args[j] == "2" || args[j] == "3" || args[j] == "4" || args[j] == "5") {
                        all_arguments_[i]->Value(args[j]);
                        all_arguments_[i]->MultiCount();

                        if (all_arguments_[i]->FlagStoreIntValues()) {
                            all_arguments_[i]->AddStoreValues(all_arguments_[i]->GetValue());
                            all_arguments_[i]->AddValueVector(all_arguments_[i]->GetValue());
                        }
                    }
                }

                else if (args[j].substr(0, all_arguments_[i]->GetPrNameHelp().length()) == all_arguments_[i]->GetPrNameHelp() && all_arguments_[i]->GetPrNameHelp().length() != 2 && args[j] != "app") {
                    all_arguments_[i]->GetHelp();
                    ++count_of_args;
                }
            }
        }

        for (int i = 0; i < all_arguments_.size(); i++) {
            if (all_arguments_[i]->GetMultiCount() > 0) {
                ++count_of_args;
            }
            if (all_arguments_[i]->FlagDefaultFlag()) {
                ++count_of_args;
            }
            if (all_arguments_[i]->GetMultiCount() > 0 && all_arguments_[i]->GetMinArgsCount() > all_arguments_[i]->GetMultiCount()) {
                return false;
            }
        }

        if (count_of_args == all_arguments_.size()) {
            return true;
        } else {
            for (int i = 0; i < all_arguments_.size(); i++) {
                if (all_arguments_[i]->FlagHelp()) {
                    return true;
                }
            }

            return false;
        }
    }

}

ArgumentParser::Arguments& ArgumentParser::ArgParser::AddStringArgument(const std::string arg_string) {

    Arguments* new_str = new Arguments(arg_string);
    all_arguments_.push_back(new_str);
    return *new_str;

}

ArgumentParser::Arguments& ArgumentParser::ArgParser::AddStringArgument(const char arg_char, const std::string arg_string) {

    Arguments* new_str = new Arguments(arg_char, arg_string);
    all_arguments_.push_back(new_str);
    return *new_str;

}

ArgumentParser::Arguments& ArgumentParser::ArgParser::AddStringArgument(const char arg_char, const std::string arg_string, const std::string info) {

    Arguments* new_str = new Arguments(arg_char, arg_string);
    all_arguments_.push_back(new_str);
    new_str->Info(info);
    return *new_str;

}

std::string ArgumentParser::ArgParser::GetStringValue(const std::string arg_name) {

    for (int i = 0; i < all_arguments_.size(); i++) {
        if (all_arguments_[i]->GetName() == arg_name) {
            return all_arguments_[i]->GetValue();
        }
    }

}

ArgumentParser::Arguments& ArgumentParser::ArgParser::AddIntArgument(const std::string arg_int) {

    Arguments* new_int = new Arguments(arg_int);
    all_arguments_.push_back(new_int);
    return *new_int;

}

ArgumentParser::Arguments& ArgumentParser::ArgParser::AddIntArgument(const char arg_char_int, const std::string arg_int) {

    Arguments* new_int = new Arguments(arg_char_int, arg_int);
    all_arguments_.push_back(new_int);
    return *new_int;

}

ArgumentParser::Arguments& ArgumentParser::ArgParser::AddIntArgument(const std::string arg_int, const std::string info) {

    Arguments* new_int = new Arguments(arg_int);
    all_arguments_.push_back(new_int);
    new_int->Info(info);
    return *new_int;

}

int ArgumentParser::ArgParser::GetIntValue(const std::string arg_name) {

    for (int i = 0; i < all_arguments_.size(); i++) {
        if (all_arguments_[i]->GetName() == arg_name) {

            int arg_value = 0;
            int p = 0;

            for (int j = all_arguments_[i]->GetValue().size() -1 ; j >= 0; j--) {
                int temp = int(all_arguments_[i]->GetValue()[j]) - 48;
                arg_value = arg_value + (temp * pow(10, p));
                p++;
            }

            return arg_value;
        }
    }

}

int ArgumentParser::ArgParser::GetIntValue(const std::string arg_name, const int index) {

    if (all_arguments_[index]->GetName() == arg_name) {
        return all_arguments_[index]->GetVectorValue(index);
    }

}

ArgumentParser::Arguments& ArgumentParser::ArgParser::AddFlag(const char arg_char, const std::string arg_flag) {

    Arguments* new_flag = new Arguments();
    new_flag->NameAndShortNameFlag(arg_char, arg_flag);
    all_arguments_.push_back(new_flag);
    return *new_flag;

}

ArgumentParser::Arguments& ArgumentParser::ArgParser::AddFlag(const char arg_char, const std::string arg_flag, const std::string info) {

    Arguments* new_flag = new Arguments();
    new_flag->NameAndShortNameFlag(arg_char, arg_flag);
    all_arguments_.push_back(new_flag);
    new_flag->Info(info);
    return *new_flag;

}

ArgumentParser::Arguments& ArgumentParser::ArgParser::AddFlag(const std::string arg_flag, const std::string info) {

    Arguments* new_flag = new Arguments();
    new_flag->NameFlag(arg_flag);
    all_arguments_.push_back(new_flag);
    new_flag->Info(info);
    return *new_flag;

}

bool ArgumentParser::ArgParser::GetFlag(const std::string name_flag) {

    for (int i = 0; i < all_arguments_.size(); i++) {
        if (all_arguments_[i]->GetNameFlag() == name_flag) {
            return true;
        }
    }

    return false;
}

ArgumentParser::Arguments& ArgumentParser::ArgParser::AddHelp(const char arg_char, const std::string arg_help, const std::string info) {

    Arguments* new_help = new Arguments();
    new_help->NameHelp(arg_char, arg_help);
    new_help->Info(info);
    all_arguments_.push_back(new_help);
    return *new_help;

}

bool ArgumentParser::ArgParser::Help() {

    return true;
}

std::string ArgumentParser::ArgParser::HelpDescription() {

    for (int i = 0; i < all_arguments_.size(); ++i) {
        if (all_arguments_[i]->FlagHelp()) {
            return " ";
        }
    }

}
