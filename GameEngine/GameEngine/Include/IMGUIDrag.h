#pragma once
#include "IMGUIWidget.h"

//입력텍스트
class CIMGUIDrag :
	public CIMGUIWidget
{
	friend class CIMGUIWindow;

protected:
	CIMGUIDrag();
	virtual ~CIMGUIDrag();

protected:
	bool	m_Align;

	bool	m_NumberInt;
	bool	m_NumberFloat;

	int		m_ValueInt;
	float	m_ValueFloat;
	float	m_Speed;

	std::function<void()>	m_InputCallback;
public:
	int GetValueInt()	const
	{
		return m_ValueInt;
	}

	float GetValueFloat()	const
	{
		return m_ValueFloat;
	}

public:

	void SetInt(int Value)
	{
		m_ValueInt = Value;
	}

	void SetFloat(float Value)
	{
		m_ValueFloat = Value;
	}

	void SetSpeed(float Speed)
	{
		m_Speed = Speed;
	}


	void SetNumberInt(bool NumberInt)
	{
		m_NumberInt = NumberInt;
	}

	void SetNumberFloat(bool NumberFloat)
	{
		m_NumberFloat = NumberFloat;
	}

public:
	virtual bool Init();
	virtual void Render();

public:
	template <typename T>
	void SetInputCallback(T* Obj, void(T::* Func)())
	{
		m_InputCallback = std::bind(Func, Obj);
	}
};
