#pragma once

#include <utility>
#include <new>

#if ((defined(_MSVC_LANG) && _MSVC_LANG >= 201703L) || __cplusplus >= 201703L)
#include <cstddef>
#endif

template <class T, std::size_t Size, std::size_t Alignment>
class simpl final {
public:
    template <class... Args>
    explicit simpl(Args&&... args);

    simpl(const simpl&) = delete;
    simpl& operator=(const simpl&) = delete;

    simpl(simpl&& other) noexcept;
    simpl& operator=(simpl&& other) noexcept;

    ~simpl() noexcept;

    T* operator->() noexcept;
    const T* operator->() const noexcept;

    T& operator*() noexcept;
    const T& operator*() const noexcept;
private:
    template <std::size_t ActualSize, std::size_t ActualAlignment>
    static void ensure() noexcept;

    T* ptr() noexcept;

#if ((defined(_MSVC_LANG) && _MSVC_LANG >= 201703L) || __cplusplus >= 201703L)
	alignas(Alignment) std::byte data_[Size];
#else
    alignas(Alignment) unsigned char data_[Size];
#endif
};

template <class T, std::size_t Size, std::size_t Alignment>
template <class... Args>
inline simpl<T, Size, Alignment>::simpl(Args&&... args) {
	new (ptr()) T(std::forward<Args>(args)...);
}

template <class T, std::size_t Size, std::size_t Alignment>
inline simpl<T, Size, Alignment>::simpl(simpl&& other) noexcept {
	*ptr() = std::move(*other);
}

template <class T, std::size_t Size, std::size_t Alignment>
inline simpl<T, Size, Alignment>& simpl<T, Size, Alignment>::operator=(simpl&& other) noexcept {
	*ptr() = std::move(*other);
	return *this;
}

template <class T, std::size_t Size, std::size_t Alignment>
inline simpl<T, Size, Alignment>::~simpl() noexcept {
	ensure<sizeof(T), alignof(T)>();
	ptr()->~T();
}

template <class T, std::size_t Size, std::size_t Alignment>
inline T* simpl<T, Size, Alignment>::operator->() noexcept {
	return ptr();
}

template <class T, std::size_t Size, std::size_t Alignment>
inline const T* simpl<T, Size, Alignment>::operator->() const noexcept {
	return ptr();
}

template <class T, std::size_t Size, std::size_t Alignment>
inline T& simpl<T, Size, Alignment>::operator*() noexcept {
	return *ptr();
}

template <class T, std::size_t Size, std::size_t Alignment>
inline const T& simpl<T, Size, Alignment>::operator*() const noexcept {
	return *ptr();
}

template <class T, std::size_t Size, std::size_t Alignment>
template <std::size_t ActualSize, std::size_t ActualAlignment>
inline void simpl<T, Size, Alignment>::ensure() noexcept {
	static_assert(Size == ActualSize, "Provided Size doesn't equal to sizeof(T)");
	static_assert(Alignment == ActualAlignment, "Provided Alignment doesn't equal to alignof(T)");
}

template <class T, std::size_t Size, std::size_t Alignment>
inline T* simpl<T, Size, Alignment>::ptr() noexcept {
#if ((defined(_MSVC_LANG) && _MSVC_LANG >= 201703L) || __cplusplus >= 201703L)
	return std::launder(reinterpret_cast<T*>(&data_));
#else
    return reinterpret_cast<T*>(&data_);
#endif
}
