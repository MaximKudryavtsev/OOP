#pragma once

class CStringStack
{
    struct Node
    {
        std::string str;
        Node *next;
    };
public:
    CStringStack();
    ~CStringStack() noexcept;

    void Push(const std::string &str);
    void Pop();

    std::string GetLastElement() const;

    bool IsEmpty() const;

    size_t GetSize() const;

private:
    Node *m_top = nullptr;
    int m_size = 0;
};
