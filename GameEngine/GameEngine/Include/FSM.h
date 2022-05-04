#pragma once
#include "GameEngine.h"
#include <map>
// #include "DebugMessageBox.h"

template<typename T>
class FSM
{
public:
	// 상태 저장 클래스
	class FSM_State
	{
	public:
		T* m_Obj;
		void(T::* m_StartFunc)();
		void(T::* m_StayFunc)();
		void(T::* m_EndFunc)();

	public:

		// 스타트 진입함수
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

	// 객체의 상태들을 이름과 함께 보관한다.
	std::unordered_map<std::string, FSM_State> m_States;
	// 현재 돌아가는 상태
	FSM_State* m_CurState;
	bool m_Play;

public: // FSM 생성
	void CreateState(const std::string& _StateName, T* _Obj, void(T::* _StayFunc)(), void(T::* _StartFunc)() = nullptr, void(T::* _EndFunc)() = nullptr)
	{
		if (m_States.end() != m_States.find(_StateName))
		{
			//CDebugMessageBox::GetInst()->OutMessageBox(L"FSM", L"생성오류 이미 생성된 FSM");
			return;
		}

		m_States[_StateName].m_Obj = _Obj;
		m_States[_StateName].m_StartFunc = _StartFunc;
		m_States[_StateName].m_StayFunc = _StayFunc;
		m_States[_StateName].m_EndFunc = _EndFunc;
	}

	// 상태를 변경해주는 함수
	void ChangeState(const std::string& _StateName)
	{
		if (m_States.end() == m_States.find(_StateName))
		{
			//CDebugMessageBox::GetInst()->OutMessageBox(L"FSM", L"FSM Change 오류");
			return;
		}

		// 현재 실행중인 상태가 있다면 해당 상태의 end 함수를 실행시켜준다.
		if (nullptr != m_CurState)
		{
			m_CurState->FSMEnd();
		}
		// 현재 진행중인 상태가 완전히 종료되면

		// m_CurState는 받아온 상태를 찾고 가르키게되며
		m_CurState = &m_States[_StateName];
		// 해당 상태의 Start함수를 실행시켜준다.
		m_CurState->FSMStart();
	}

	void Update()
	{
		// 상태는 항상 존재해야하니 없다면 터트린다.
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