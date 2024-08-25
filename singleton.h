#ifndef SINGLETON_H
#define SINGLETON_H

#include <global.h>

template <typename T>
class Singleton {
protected:
    // 保证子类能调用
    Singleton() = default;
    ~ Singleton() {
        std::cout << "Singleton desotry\n" << std::endl;
    }

    Singleton(const Singleton<T>&) = delete;
    Singleton& operator=(const Singleton<T>&) = delete;

    static std::shared_ptr<T> _instance;
public:
    static std::shared_ptr<T> GetInstance() {
        static std::once_flag s_flag;
        std::call_once(s_flag, [&]() {
            _instance = std::shared_ptr<T>(new T);
        });
        return _instance;
    }

    void printAddress() const {
        std::cout << _instance.get() << std::endl;
    }

};

template <typename T>
std::shared_ptr<T> Singleton<T>::_instance = nullptr;

#endif // SINGLETON_H
