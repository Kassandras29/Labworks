#pragma once

#include "Arguments.h"
#include <string>
#include <vector>

namespace ArgumentParser {

    class ArgParser {
        // Your Implementation here!
    private:

        std::string parser_name_;
        std::vector<Arguments*> all_arguments_;

    public:

        ArgParser();
        ArgParser(std::string name);
        ~ArgParser();

        bool Parse(std::vector<std::string> args);
        Arguments& AddStringArgument(std::string arg_string);
        Arguments& AddStringArgument(char arg_char, std::string arg_string);
        Arguments& AddStringArgument(char arg_char, std::string arg_string, std::string info);
        std::string GetStringValue(std::string arg_name);
        Arguments& AddIntArgument(std::string arg_int);
        Arguments& AddIntArgument(char arg_char_int, std::string arg_int);
        Arguments& AddIntArgument(std::string arg_int, std::string info);
        int GetIntValue(std::string arg_name);
        int GetIntValue(std::string arg_name, int index);
        Arguments& AddFlag(char arg_char, std::string arg_flag);
        Arguments& AddFlag(char arg_char, std::string arg_flag, std::string info);
        Arguments& AddFlag(std::string arg_flag, std::string info);
        bool GetFlag(std::string name_flag);
        Arguments& AddHelp(char arg_char, std::string arg_help, std::string info);
        bool Help();
        std::string HelpDescription();

    };

} // namespace ArgumentParser
