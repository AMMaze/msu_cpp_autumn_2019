#pragma once
#include <iostream>
#include <string>
#include <exception>

#ifndef __ERROR__
#define __ERROR__
enum class Error
{
    NoError,
    CorruptedArchive
};
#endif

class Deserializer
{
    static constexpr char Separator = ' ';
public:
    explicit Deserializer(std::istream& in)
        : in_(in)
    {
    }

    template <class T>
    Error load(T& object)
    {
        return object.deserialize(*this);
    }

    template <class... ArgsT>
    Error operator()(ArgsT&... args)
    {
        return process(args...);
    }
    
private:
    std::istream& in_;

    template <class T, class... TArgs>
    Error process(T& arg, TArgs&... args) {
        std::string str;
        in_ >> str;
        if constexpr (std::is_same<std::decay_t<T>, uint64_t>::value) {
            try { 
                arg = std::stoul(str);
            } catch (std::exception& e) {
                return Error::CorruptedArchive;
            }
        }
        else if constexpr (std::is_same<std::decay_t<T>, bool>::value) { 
            if(!str.compare("true"))
                arg = true;
            else if (!str.compare("false"))
                arg = false;
            else
                return Error::CorruptedArchive;
        }
        else 
            return Error::CorruptedArchive;
        if constexpr (sizeof...(args) == 0) 
            return Error::NoError;
        else
            return process(args...);
    }
};
