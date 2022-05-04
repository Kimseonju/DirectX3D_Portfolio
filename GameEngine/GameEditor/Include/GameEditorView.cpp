
// GameEditorView.cpp: CGameEditorView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "GameEditor.h"
#endif

#include "GameEditorDoc.h"
#include "GameEditorView.h"
#include "Engine.h"
#include "IMGUIManager.h"
#include "EditorWindow/LogWindow.h"
#include "EditorWindow/ObjectWindow.h"
#include "EditorWindow/DetailWindow.h"
#include "EditorWindow/InspectorWindow.h"
#include "EditorWindow/PrefabWindow.h"
#include "EditorWindow/ComponentWindow.h"
#include "EditorWindow/ToolWindow.h"

//테스트용도윈도우
#include "EditorWindow/SaveLoadWindow.h"


#include "Scene/SceneManager.h"
#include "Scene/Scene.h"
#include "Scene/EditorScene.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CGameEditorView

IMPLEMENT_DYNCREATE(CGameEditorView, CView)

BEGIN_MESSAGE_MAP(CGameEditorView, CView)
	ON_COMMAND(ID_ObjectWindow, &CGameEditorView::OnObjectwindow)
	ON_COMMAND(ID_LogWindow, &CGameEditorView::OnLogwindow)
END_MESSAGE_MAP()

// CGameEditorView 생성/소멸

CGameEditorView::CGameEditorView() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.

	//_CrtSetBreakAlloc(3339075);
}

CGameEditorView::~CGameEditorView()
{
}

BOOL CGameEditorView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CGameEditorView 그리기

void CGameEditorView::OnDraw(CDC* /*pDC*/)
{
	CGameEditorDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
}


// CGameEditorView 진단

#ifdef _DEBUG
void CGameEditorView::AssertValid() const
{
	CView::AssertValid();
}

void CGameEditorView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CGameEditorDoc* CGameEditorView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGameEditorDoc)));
	return (CGameEditorDoc*)m_pDocument;
}
#endif //_DEBUG


// CGameEditorView 메시지 처리기


void CGameEditorView::OnInitialUpdate()
{
	CView::OnInitialUpdate();
	CEngine::GetInst()->SetEditor(true);
	// AfxGetInstanceHandle : HINSTANCE를 얻어온다.
	// 사이즈가 일치하지않으면 렌더타겟 묶어줄때에러뜸
	
	CEngine::GetInst()->Init(AfxGetInstanceHandle(), m_hWnd, 1280, 720);
	//우선순위별
	CIMGUIManager::GetInst()->AddWindow<CToolWindow>("ToolWindow");


	CIMGUIManager::GetInst()->AddWindow<CObjectWindow>("ObjectWindow");
	CIMGUIManager::GetInst()->AddWindow<CInspectorWindow>("InspectorWindow");
	CIMGUIManager::GetInst()->AddWindow<CPrefabWindow>("PrefabWindow");
	CIMGUIManager::GetInst()->AddWindow<CComponentWindow>("ComponentWindow");

	CIMGUIManager::GetInst()->AddWindow<CSaveLoadWindow>("SaveLoadWindow");
	

	CSceneManager::GetInst()->SetSceneMode<CEditorScene>();
	CObjectWindow* objWindow = (CObjectWindow*)CIMGUIManager::GetInst()->FindIMGUIWindow("ObjectWindow");
	objWindow->SetScene(CSceneManager::GetInst()->GetScene());
	objWindow->SetComponentWindow((CComponentWindow*)CIMGUIManager::GetInst()->FindIMGUIWindow("ComponentWindow"));
	
}


extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

LRESULT CGameEditorView::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	if (ImGui_ImplWin32_WndProcHandler(m_hWnd, message, wParam, lParam))
		return true;

	return CView::WindowProc(message, wParam, lParam);
}


void CGameEditorView::OnObjectwindow()
{
	CIMGUIWindow* Window = CIMGUIManager::GetInst()->FindIMGUIWindow("ObjectWindow");

	Window->Open();
}


void CGameEditorView::OnLogwindow()
{
	CIMGUIWindow* Window = CIMGUIManager::GetInst()->FindIMGUIWindow("LogWindow");

	Window->Open();
}
