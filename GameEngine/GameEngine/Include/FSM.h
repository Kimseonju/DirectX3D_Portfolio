#pragma once
#include "GameEngine.h"
#include <map>
// #include "DebugMessageBox.h"

template<typename T>
class FSM
{
public:
	// ���� ���� Ŭ����
	class FSM_State
	{
	public:
		T* m_Obj;
		void(T::* m_StartFunc)();
		void(T::* m_StayFunc)();
		void(T::* m_EndFunc)();

	public:

		// ��ŸƮ �����Լ�
		void FSMStart()
		{
			if (nullptr == m_StartFunc)
			{
				return;
			}
			(m_Obj->*m_StartFunc)();
		}

		void FSMEnd()
		{
			if (nullptr == m_EndFunc)
			{
				return;
			}
			(m_Obj->*m_EndFunc)();
		}

		void Update()
		{
			if (m_StayFunc)
			{
				(m_Obj->*m_StayFunc)();
			}
		}
	public:
		FSM_State() :m_Obj(nullptr), m_StartFunc(nullptr), m_EndFunc(nullptr), m_StayFunc(nullptr)
		{

		}
		~FSM_State()
		{

		}
	};

	// ��ü�� ���µ��� �̸��� �Բ� �����Ѵ�.
	std::unordered_map<std::string, FSM_State> m_States;
	// ���� ���ư��� ����
	FSM_State* m_CurState;
	bool m_Play;

public: // FSM ����
	void CreateState(const std::string& _StateName, T* _Obj, void(T::* _StayFunc)(), void(T::* _StartFunc)() = nullptr, void(T::* _EndFunc)() = nullptr)
	{
		if (m_States.end() != m_States.find(_StateName))
		{
			//CDebugMessageBox::GetInst()->OutMessageBox(L"FSM", L"�������� �̹� ������ FSM");
			return;
		}

		m_States[_StateName].m_Obj = _Obj;
		m_States[_StateName].m_StartFunc = _StartFunc;
		m_States[_StateName].m_StayFunc = _StayFunc;
		m_States[_StateName].m_EndFunc = _EndFunc;
	}

	// ���¸� �������ִ� �Լ�
	void ChangeState(const std::string& _StateName)
	{
		if (m_States.end() == m_States.find(_StateName))
		{
			//CDebugMessageBox::GetInst()->OutMessageBox(L"FSM", L"FSM Change ����");
			return;
		}

		// ���� �������� ���°� �ִٸ� �ش� ������ end �Լ��� ��������ش�.
		if (nullptr != m_CurState)
		{
			m_CurState->FSMEnd();
		}
		// ���� �������� ���°� ������ ����Ǹ�

		// m_CurState�� �޾ƿ� ���¸� ã�� ����Ű�ԵǸ�
		m_CurState = &m_States[_StateName];
		// �ش� ������ Start�Լ��� ��������ش�.
		m_CurState->FSMStart();
	}

	void Update()
	{
		// ���´� �׻� �����ؾ��ϴ� ���ٸ� ��Ʈ����.
		if (m_Play)
		{
			if (m_CurState)
			{
				m_CurState->Update();
			}
		}
	}

	void IsPlay(bool Play)
	{
		m_Play = Play;
	}
	FSM() : m_CurState(nullptr), m_Play(true)
	{}
	~FSM()
	{}
};