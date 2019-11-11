#pragma once
#include <iostream>
#include <type_traits>
#include <string>

#ifndef __ERROR__
#define __ERROR__
enum class Error
{
    NoError,
    CorruptedArchive
};
#endif

class Serializer
{
    static constexpr char Separator = ' ';
public:
    explicit Serializer(std::ostream& out)
        : out_(out)
    {
    }

    template <class T>
    Error save(T& object)
    {
        return object.serialize(*this);
    }

    template <class... ArgsT>
    Error operator()(ArgsT... args)
    {
        return process(args...);
    }
    
private:
    std::ostream& out_;

    template <class T, class... TArgs>
    Error process(T&& arg, TArgs&&... args) {
        if constexpr (std::is_same<std::decay_t<T>, uint64_t>::value) 
            out_ << arg;
        else if constexpr (std::is_same<std::decay_t<T>, bool>::value) 
            out_ << (arg ? std::string("true") : std::string("false"));
        else 
            return Error::CorruptedArchive;
        if constexpr (sizeof...(args) == 0)
            return Error::NoError;
        else {
            out_ << Separator;
            return process(std::forward<TArgs>(args)...);
        }
    }
};
