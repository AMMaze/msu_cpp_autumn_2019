#include <string>
#include <type_traits>
#include <iostream>


template<class T, class... TArgs>
std::string _format(std::string str, int idx, T&& arg, TArgs&&... args) {
    std::string param = '{' + std::to_string(idx) + '}';
    size_t pos = str.find(param, 0);
    if (pos == std::string::npos)
        throw std::runtime_error("Incorrect number of arguments");
    while (pos != std::string::npos) {
        if constexpr (std::is_same_v<std::decay_t<T>, const char*> || 
                std::is_same_v<std::decay_t<T>, char*> || 
                std::is_same_v<std::decay_t<T>, std::string>)
            str.replace(pos, param.size(), arg);
        else
            str.replace(pos, param.size(), std::to_string(arg));
        pos = str.find(param, pos);
    }
    if constexpr (sizeof...(args) == 0) {
        if (str.find('{', 0) != std::string::npos || 
                str.find('}', 0) != std::string::npos)
            throw std::runtime_error("Incorrect number of arguments");
        return str;
    }
    else 
        return _format(str, idx + 1,  args...);
}

template<class... TArgs>
std::string format(std::string str, TArgs&&... args) {
    return _format(str, 0, args...);
}
