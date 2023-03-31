// TODO: replace with #include "stack_pimpl/stack_pimpl.hpp" after finishing CMake
#include "../include/stack_pimpl/stack_pimpl.hpp"

#include <utility>

namespace stack_pimpl
{
    template <class T, size_t Size, size_t Alignment>
    template <class... Args>
    stack_pimpl<T, Size, Alignment>::stack_pimpl(Args&&... args) noexcept(std::is_nothrow_constructible<T, Args...>::value) {
        new (ptr()) T(std::forward<Args>(args)...);
    }

    template <class T, size_t Size, size_t Alignment>
    stack_pimpl<T, Size, Alignment>::stack_pimpl(stack_pimpl&& other) noexcept(std::is_nothrow_move_assignable<T>::value) {
        *ptr() = std::move(*other);
    }

    template <class T, size_t Size, size_t Alignment>
    stack_pimpl<T, Size, Alignment>& stack_pimpl<T, Size, Alignment>::operator=(stack_pimpl&& other) noexcept(std::is_nothrow_move_assignable<T>::value) {
        *ptr() = std::move(*other);
        return *this;
    }

    template <class T, size_t Size, size_t Alignment>
    stack_pimpl<T, Size, Alignment>::~stack_pimpl() noexcept(noexcept(std::declval<T>().~T())) {
        ensure<Size, Alignment>();
        ptr()->~T();
    }

    template <class T, size_t Size, size_t Alignment>
    T* stack_pimpl<T, Size, Alignment>::operator->() noexcept {
        return ptr();
    }

    template <class T, size_t Size, size_t Alignment>
    const T* stack_pimpl<T, Size, Alignment>::operator->() const noexcept {
        return ptr();
    }

    template <class T, size_t Size, size_t Alignment>
    T& stack_pimpl<T, Size, Alignment>::operator*() noexcept {
        return *ptr();
    }

    template <class T, size_t Size, size_t Alignment>
    const T& stack_pimpl<T, Size, Alignment>::operator*() const noexcept {
        return *ptr();
    }

    template <class T, size_t Size, size_t Alignment>
    template <size_t ActualSize, size_t ActualAlignment>
    void stack_pimpl<T, Size, Alignment>::ensure() noexcept {
        static_assert(Size == ActualSize, "Provided Size doesn't equal to sizeof(T)");
        static_assert(Alignment == ActualAlignment, "Provided alignment doesn't equal to alignof(T)");
    }

    // TODO: maybe const here
    template <class T, size_t Size, size_t Alignment>
    T* stack_pimpl<T, Size, Alignment>::ptr() noexcept {
        return reinterpret_cast<T*>(&data_);
    }
}
