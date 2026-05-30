#pragma once
#include <concepts>
#include <functional>
#include <memory>
#include <vector>

template <typename T>
concept Cloneable = std::has_virtual_destructor_v<T> && requires(const T& obj)
{
    { obj.clone() } -> std::same_as<std::unique_ptr<T>>;
};

template <Cloneable T>
class PolymorphicContainer {
public:
    PolymorphicContainer() = default;

    PolymorphicContainer(const PolymorphicContainer& other);
    PolymorphicContainer& operator=(const PolymorphicContainer& other);

    PolymorphicContainer(PolymorphicContainer&& other) noexcept = default;
    PolymorphicContainer& operator=(PolymorphicContainer&& other) = default;

    void pushBack(const T& obj);
    void pushBack(const std::unique_ptr<T>& ptr);
    void pushBack(std::unique_ptr<T>&& ptr);

    template <typename U> requires std::is_base_of_v<T, U>
    void pushBack(const std::unique_ptr<U>& ptr);

    void erase(size_t index);

    T& operator[](size_t index);
    const T& operator[](size_t index) const;

    // these delegate to the vector's iterator, so the iteration will be over unique_ptr<T>
    // if we want to iterate over T& we should implement a custom iterator
    auto begin() noexcept;
    auto end() noexcept;
    auto cbegin() const noexcept;
    auto cend() const noexcept;
    auto rbegin() noexcept;
    auto rend() noexcept;

protected:
    std::vector<std::unique_ptr<T>> items;
private:
    void copyFrom(const PolymorphicContainer& other);
};

template <Cloneable T>
void PolymorphicContainer<T>::copyFrom(const PolymorphicContainer& other) {
    std::vector<std::unique_ptr<T>> copiedItems(other.items.size());
    for (const auto& ptr : other.items) {
        if (ptr) {
            copiedItems.push_back(ptr->clone());
        }
    }
    items = std::move(copiedItems);
}

template <Cloneable T>
PolymorphicContainer<T>::PolymorphicContainer(const PolymorphicContainer& other) {
    copyFrom(other);
}

template <Cloneable T>
PolymorphicContainer<T>& PolymorphicContainer<T>::operator=(const PolymorphicContainer& other) {
    if (this != &other) {
        copyFrom(other);
    }
    return *this;
}

template <Cloneable T>
void PolymorphicContainer<T>::erase(size_t index) {
    items.erase(items.begin() + index);
}

template <Cloneable T>
T& PolymorphicContainer<T>::operator[](size_t index) {
    return *items[index];
}

template <Cloneable T>
const T& PolymorphicContainer<T>::operator[](size_t index) const {
    return *items[index];
}

template <Cloneable T>
void PolymorphicContainer<T>::pushBack(const T& obj) {
    items.push_back(obj.clone());
}

template <Cloneable T>
void PolymorphicContainer<T>::pushBack(const std::unique_ptr<T>& ptr) {
    items.push_back(ptr->clone());
}

template <Cloneable T>
void PolymorphicContainer<T>::pushBack(std::unique_ptr<T>&& ptr) {
    items.push_back(std::move(ptr));
}

template <Cloneable T>
template <typename U> requires std::is_base_of_v<T, U>
void PolymorphicContainer<T>::pushBack(const std::unique_ptr<U>& ptr) {
    items.push_back(ptr->clone());
}

template <Cloneable T>
auto PolymorphicContainer<T>::begin() noexcept {
    return items.begin();
}

template <Cloneable T>
auto PolymorphicContainer<T>::end() noexcept {
    return items.end();
}

template <Cloneable T>
auto PolymorphicContainer<T>::cbegin() const noexcept {
    return items.cbegin();
}

template <Cloneable T>
auto PolymorphicContainer<T>::cend() const noexcept {
    return items.cend();
}

template <Cloneable T>
auto PolymorphicContainer<T>::rbegin() noexcept {
    return items.rbegin();
}

template <Cloneable T>
auto PolymorphicContainer<T>::rend() noexcept {
    return items.rend();
}
