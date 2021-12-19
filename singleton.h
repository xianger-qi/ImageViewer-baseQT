#ifndef SINGLETON_H
#define SINGLETON_H

#include <cstdlib>
#include <new>
#include <atomic>

class spin_lock
{
private:
    std::atomic_flag flag_ = ATOMIC_FLAG_INIT;
public:
    void lock() { while(flag_.test_and_set(std::memory_order_acquire)); }

    void unlock() { flag_.clear(std::memory_order_release); }
};

template<typename T, bool LongLifeTime = false> class singleton;

template<typename T>
class singleton<T, false>
{
public:

    template<typename... Args>
    static T& instance(Args&&... args) {
        static T obj(std::forward<Args>(args)...);
        return obj;
    }

protected:
    singleton() = default;
    virtual ~singleton() {}

private:
    singleton(const singleton&) = delete;
    singleton& operator=(const singleton&) = delete;
    singleton(singleton&&) = delete;
    singleton& operator=(singleton&&) = delete;
};



template<typename T>
class singleton<T, true>
{
public:

    template<typename... Args>
    static T& instance(Args&&... args)
    {
        if(!pInstance_)
        {
            // DCL
            lock_.lock();

            if(!pInstance_)
            {
                destroyed_ ? on_dead_reference(std::forward<Args>(args)...)
                        : create(std::forward<Args>(args)...);
            }

            lock_.unlock();
        }

        return *pInstance_;
    }

private:

    template<typename... Args>
    static void create(Args&&... args)
    {
        static T obj(std::forward<Args>(args)...);
        pInstance_ = &obj;
    }

    template<typename... Args>
    static void on_dead_reference(Args&&... args)
    {
        create(std::forward<Args>(args)...);
        new(pInstance_) T(std::forward<Args>(args)...);
        std::atexit(kill_singleton);
        destroyed_ = false;

    }

    static void kill_singleton()
    {
        pInstance_->~singleton();
    }


    singleton(const singleton&);
    singleton& operator=(const singleton&);
    singleton(singleton&&);
    singleton& operator=(singleton&&);

    static spin_lock lock_;

protected:
    singleton() = default;
    virtual ~singleton()
    {
        pInstance_ = nullptr;
        destroyed_ = true;
    }


    static T* pInstance_;
    static bool destroyed_;
};

template<typename T> T* singleton<T, true>::pInstance_ = nullptr;
template<typename T> bool singleton<T, true>::destroyed_ = false;
template<typename T> spin_lock singleton<T, true>::lock_;

#endif // SINGLETON_H
