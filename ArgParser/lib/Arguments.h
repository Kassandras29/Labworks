#pragma once

#include <string>
#include <vector>

namespace ArgumentParser {

    class Arguments {
    private:

        std::string arg_name_;
        std::string pr_arg_name_;
        char arg_shortname_;
        std::string pr_arg_shortname_;
        bool flag_shortname_ = false;

        std::string value_;
        std::string info_;

        std::string def_value_;
        std::string* store_value_;
        bool* store_flag_;
        std::vector<int>* store_values_;
        std::vector<int> vector_values_;
        bool flag_store_str_value_ = false;
        bool flag_store_flag_ = false;
        bool flag_store_int_values_ = false;
        bool flag_multi_value_ = false;
        int multi_count_ = 0;
        int min_args_count_;
        bool flag_positional_ = false;

        std::string name_flag_;
        std::string pr_name_flag_;
        char shortname_flag_;
        std::string pr_shortname_flag_;
        bool flag_shortname_flag_ = false;
        bool flag_ = false;
        bool def_flag_;
        bool flag_def_flag_ = false;
        bool full_flag_ = false;
        bool short_flag_ = false;

        std::string name_help_;
        std::string pr_name_help_;
        char shortname_help_;
        std::string pr_shortname_help_;
        bool flag_help_ = false;

    public:

        Arguments();
        Arguments(std::string arg_name);
        Arguments(char arg_shortname, std::string arg_name);
        ~Arguments();

        std::string GetName();
        std::string GetPrName();
        std::string GetPrShortname();
        bool FlagShortname();
        void Value(std::string arg_value);
        std::string GetValue();
        void Default(const char* def_value);
        void Default(bool def_flag);
        std::string GetDefault();
        bool FlagDefaultFlag();
        void StoreValue(std::string& store_value);
        void StoreValue(bool& store_flag);
        void StoreValues(std::vector<int>& store_int_values);
        void AddStoreValue(std::string arg_value);
        void AddStoreFlag(bool arg_flag);
        void AddStoreValues(std::string arg_value);
        bool FlagStoreStrValue();
        bool FlagStoreFlag();
        bool FlagStoreIntValues();
        Arguments& MultiValue();
        Arguments& MultiValue(int min_args_count);
        int GetMinArgsCount();
        bool FlagMultiValue();
        bool MultiCount();
        int GetMultiCount();
        void AddValueVector(std::string value);
        int GetVectorValue(int index);
        void Info(std::string info);
        Arguments& Positional();
        bool FlagPositional();

        void NameFlag(std::string name_flag);
        void NameAndShortNameFlag(char shortname_flag, std::string name_flag);
        bool Flag();
        std::string GetNameFlag();
        char GetShortnameFlag();
        std::string GetPrNameFlag();
        bool FullFlag();
        void NameHelp(char shortname_help, std::string name_help);
        std::string GetPrNameHelp();
        void GetHelp();
        bool FlagHelp();

    };

}
