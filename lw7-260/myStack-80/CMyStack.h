#pragma once

template <typename T>
class CMyStack
{
	struct Item
	{
		Item(T data, Item* next)
			: data(std::move(data))
			, next(next)
		{
		}

		T data;
		Item* next;
	};

public:
	CMyStack() = default;

	CMyStack(CMyStack const& stack)
		: CMyStack()
	{
		try
		{
			Item* stackPtr = stack.m_top;

			while (stackPtr)
			{
				Item* newItem = new Item(stackPtr->data, nullptr);
				Item* cutItem = m_top;

				if (!m_top)
				{
					m_top = newItem;
				}
				else
				{
					cutItem->next = newItem;
				}

				cutItem = newItem;
				stackPtr = stackPtr->next;
			}
		}
		catch (...)
		{
			Clear();
			throw;
		}
	}

	CMyStack<T>& operator=(CMyStack const& stack)
	{
		if (this != &stack)
		{
			CMyStack tmp = CMyStack(stack);
			std::swap(tmp.m_top, m_top);
		}
		return *this;
	}

	CMyStack(CMyStack&& stack)
		: CMyStack()
	{
		std::swap(m_top, stack.m_top);
	}

	CMyStack<T>& operator=(CMyStack&& stack)
	{
		if (this != &stack)
		{
			Clear();
			m_top = stack.m_top;
			stack = nullptr;
		}
		return *this;
	}

	bool IsEmpty() const
	{
		return !m_top;
	}

	void Push(const T& data)
	{
		Item* newItem = new Item(data, m_top);
		m_top = newItem;
	}

	void Pop()
	{
		if (IsEmpty())
		{
			throw std::logic_error("ERROR: Stack is empty\n");
		}

		Item* itemPtr = m_top;
		m_top = m_top->next;
		delete itemPtr;
	}

	T& GetTop() const
	{
		if (IsEmpty())
		{
			throw std::logic_error("ERROR: Stack is empty\n");
		}

		return m_top->data;
	}

	void Clear()
	{
		while (m_top)
		{
			Item* itemPtr = m_top;
			m_top = m_top->next;
			delete itemPtr;
		}
	}

	~CMyStack()
	{
		Clear();
	}

private:
	Item* m_top = nullptr;
};
