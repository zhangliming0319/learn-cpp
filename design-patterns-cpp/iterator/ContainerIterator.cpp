#include <iostream>
#include <vector>

// 前置声明 IntContainer
class IntContainer;

// 迭代器类：IntIterator
class IntIterator {
public:
    IntIterator(IntContainer& container, int index = 0) : container(container), index(index) {}

    int& operator*();
    IntIterator& operator++();
    bool operator!=(IntIterator& other) const;

private:
    IntContainer& container;
    int index;
};

// 容器类：IntContainer
class IntContainer {
public:
    void add(int value) {
        values.push_back(value);
    }

    int& operator[](int index) {
        return values[index];
    }

    int size() const {
        return static_cast<int>(values.size());
    }

    IntIterator begin() {
        return IntIterator(*this);
    }

    IntIterator end()  {
        return IntIterator(*this, size());
    }

private:
    std::vector<int> values;

    friend class IntIterator;
};

// 迭代器实现
int& IntIterator::operator*() {
    return container[index];
}

IntIterator& IntIterator::operator++() {
    ++index;
    return *this;
}

bool IntIterator::operator!=(IntIterator& other) const {
    return index != other.index;
}

// 主函数
int main() {
    IntContainer container;
    for (int i = 0; i < 5; ++i) {
        container.add(i);
    }

    // 使用迭代器遍历集合元素
    for (const auto& it : container) {
        std::cout << it << ' ';
    }
    std::cout << std::endl;

    return 0;
}