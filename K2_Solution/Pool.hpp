#pragma once
#include <vector>
#include <functional>
#include <optional>
#include <algorithm>

template <typename T>
class Pool {
public:
    void add(const T& obj);

    // predicates can be both function pointer or std::function
    // bool remove(bool (*predicate)(const T& obj));
    bool remove(std::function<bool(const T& obj)> predicate);

    // std::vector<T> filter(bool (*predicate)(const T& obj)) const;
    std::vector<T> filter(std::function<bool(const T& obj)> predicate) const;

    // std::optional<T> findFirst(bool (*predicate)(const T& obj)) const;
    std::optional<T> findFirst(std::function<bool(const T& obj)> predicate) const;

    size_t size() const;
    bool isEmpty() const;

protected:
    std::vector<T> items;
};

template <typename T>
void Pool<T>::add(const T& obj) {
    items.push_back(obj);
}

// template <typename T>
// bool Pool<T>::remove(bool (*predicate)(const T& obj)) {
//     return std::erase_if(items, predicate);
// }

template <typename T>
bool Pool<T>::remove(std::function<bool(const T& obj)> predicate) {
    return std::erase_if(items, predicate);
}

// template <typename T>
// std::optional<T> Pool<T>::findFirst(bool (*predicate)(const T& obj)) const {
//     for (const T& obj : items) {
//         if (predicate(obj)) {
//             return obj;
//         }
//     }
//     return std::nullopt;
// }

template <typename T>
std::optional<T> Pool<T>::findFirst(std::function<bool(const T& obj)> predicate) const {
    // alternative implementation with find_if
    auto it = std::find_if(items.begin(), items.end(), predicate);
    if (it == items.end()) {
        return std::nullopt;
    }
    return *it;
}

// template <typename T>
// std::vector<T> Pool<T>::filter(bool (*predicate)(const T& obj)) const {
//     std::vector<T> result;
//     for (const T& obj : items) {
//         if (predicate(obj)) {
//             result.push_back(obj);
//         }
//     }
//     return result;
// }

template <typename T>
std::vector<T> Pool<T>::filter(std::function<bool(const T& obj)> predicate) const {
    std::vector<T> result;
    for (const T& obj : items) {
        if (predicate(obj)) {
            result.push_back(obj);
        }
    }
    return result;
}

template <typename T>
size_t Pool<T>::size() const {
    return items.size();
}

template <typename T>
bool Pool<T>::isEmpty() const {
    return items.empty();
}
