#pragma once

#include <type_traits>

#if __cplusplus > 201703L
#include <cstddef>
#endif

namespace stack_pimpl
{
    // TODO: maybe change name to stack_pimpl
    template <class T, size_t Size, size_t Alignment>
    class stack_pimpl final {
    public:
        // TODO: maybe remove noexcept condition here
        template <class... Args>
        explicit stack_pimpl(Args&&... args) noexcept(std::is_nothrow_constructible<T, Args...>::value);

        stack_pimpl(const stack_pimpl&) = delete;
        stack_pimpl& operator=(const stack_pimpl&) = delete;

        // TODO: maybe remove noexcept conditions here
        stack_pimpl(stack_pimpl&& other) noexcept(std::is_nothrow_move_assignable<T>::value);
        stack_pimpl& operator=(stack_pimpl&& other) noexcept(std::is_nothrow_move_assignable<T>::value);

        ~stack_pimpl() noexcept(noexcept(std::declval<T>().~T()));

        T* operator->() noexcept;
        const T* operator->() const noexcept;

        T& operator*() noexcept;
        const T& operator*() const noexcept;
    private:
        template <size_t ActualSize, size_t ActualAlignment>
        static void ensure() noexcept;

        T* ptr() noexcept;

    #if __cplusplus > 201703L
        alignas(Alignment) std::byte data_[Size];
    #elif __cplusplus > 201103L
        alignas(Alignment) unsigned char data_[Size];
    #else
        static_assert(false, "Using stack_pimpl is only available for C++ standards greater or equal to 11th");
    #endif
    };
}
