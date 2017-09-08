#pragma once

template<typename T>
class CMyStack
{
	struct Node
	{
		Node(const T &value, const std::shared_ptr<Node> &next = nullptr)
			: value(value)
			, next(next)
		{
		};
		T value;
		std::shared_ptr<Node> next;
	};

public:
	CMyStack()
		: m_top(nullptr)
	{
	};
	CMyStack(const CMyStack &other)
	{
		if (std::addressof(other) != this)
		{
			std::shared_ptr<Node> tmp = other.m_top;
			std::shared_ptr<Node> currentElement = std::make_shared<Node>(tmp->value);
			m_top = currentElement;

			tmp = tmp->next;
			while (tmp != nullptr)
			{
				currentElement->next = std::make_shared<Node>(tmp->value);
				currentElement = currentElement->next;

				tmp = tmp->next;
			}
		}
	};
	CMyStack(CMyStack &&other)
	{
		if (std::addressof(other) != this)
		{
			m_top = other.m_top;
			other.m_top = nullptr;
		}
	};

	void Push(const T &element)
	{
		m_top = std::make_shared<Node>(element, m_top);
	};
	void Pop()
	{
		if (IsEmpty())
		{
			throw std::logic_error("Stack is empty");
		}
		m_top = m_top->next;
	};
	T GetElement() const
	{
		if (IsEmpty())
		{
			throw std::logic_error("Stack is empty");
		}
		return m_top->value;
	};
	bool IsEmpty() const
	{
		return !m_top;
	};
	void Clear()
	{
		while (m_top != nullptr)
		{
			m_top = m_top->next;
		}
	};

	CMyStack& operator=(const CMyStack &right)
	{
		if (std::addressof(right) != this)
		{
			std::shared_ptr<Node> tmp = right.m_top;
			std::shared_ptr<Node> currentElement = std::make_shared<Node>(tmp->value);
			m_top = currentElement;

			tmp = tmp->next;
			while (tmp != nullptr)
			{
				currentElement->next = std::make_shared<Node>(tmp->value);
				currentElement = currentElement->next;

				tmp = tmp->next;
			}
		}
		return *this;
	};
	CMyStack& operator=(CMyStack &&right)
	{
		if (std::addressof(right) != this)
		{
			m_top = right.m_top;
			right.m_top = nullptr;
		}
		return *this;
	};

	~CMyStack()
	{
		Clear();
	};

private:
	std::shared_ptr<Node> m_top;
};



