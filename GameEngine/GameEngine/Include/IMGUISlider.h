#pragma once
#include "IMGUIWidget.h"

//입력텍스트
class CIMGUISlider :
	public CIMGUIWidget
{
	friend class CIMGUIWindow;

protected:
	CIMGUISlider();
	virtual ~CIMGUISlider();

protected:
	bool	m_Align;

	bool	m_NumberInt;
	bool	m_NumberFloat;

	int		m_ValueInt;
	int		m_ValueIntMin;
	int		m_ValueIntMax;
	float	m_ValueFloat;
	float	m_ValueFloatMin;
	float	m_ValueFloatMax;

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

	void SetIntMinMax(int min, int max)
	{
		m_ValueIntMin = min;
		m_ValueIntMax = max;
	}

	void SetFloatMinMax(float min, float max)
	{
		m_ValueFloatMin = min;
		m_ValueFloatMax = max;
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
