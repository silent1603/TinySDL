#ifndef SINGLETON_HPP
#define SINGLETON_HPP
#include <iostream>
#include <mutex>
namespace Tetris
{
    template <class T>
    class Singleton
    {
    protected:
        static T* m_pInstance;
        static std::mutex m_mutex;
        Singleton();
        ~Singleton();

    public:
        Singleton(Singleton &signelton) = delete;
        Singleton(Singleton &&signelton) = delete;
        Singleton &operator=(Singleton &Singlenton) = delete;
        Singleton &operator=(Singleton &&Singlenton) = delete;
        static T* getInstance();
        static void destroyInstance();
    };

    template<class T>
    Singleton<T>::Singleton()
    {

    }

    template<class T>
    Singleton<T>::~Singleton()
    {

    }   

    template<class T>
    T* Singleton<T>::getInstance(){
        std::lock_guard<std::mutex> lock(m_mutex);
        if(m_pInstance == nullptr)
        {
            m_pInstance = new T();
        }
        return m_pInstance;
    } 

    template<class T>
    void Singleton<T>::destroyInstance()
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        if(m_pInstance != nullptr)
        {
            delete m_pInstance;
        }
    }

    template <class T>
    T* Singleton<T>::m_pInstance {nullptr};

    template<class T>
    std::mutex Singleton<T>::m_mutex;

}

#endif