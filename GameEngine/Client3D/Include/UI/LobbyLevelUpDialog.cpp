
#include "LobbyLevelUpDialog.h"
#include "Device.h"
#include "../PublicData.h"
#include "../DataTable/ItemDataTable.h"
#include "../PublicData.h"
#include "../DataTable/PlayerDataTable.h"
#include "Scene/Scene.h"
#include "Scene/SceneResource.h"
CLobbyLevelUpDialog::CLobbyLevelUpDialog():
	m_Count(0),
	m_SelectItem(0),
	m_NowLevel(1),
	m_NextLevel(1),
	m_InputExp(0),
	m_MaxCount(0),
	m_MaxExp(0),
	m_Status(nullptr)
{
}

CLobbyLevelUpDialog::CLobbyLevelUpDialog(const CLobbyLevelUpDialog& widget):
	CWidgetWindow(widget)
{
	m_Count = widget.m_Count;
	m_SelectItem = widget.m_SelectItem;
	m_NowLevel = widget.m_NowLevel;
	m_NextLevel = widget.m_NextLevel;
	m_InputExp = widget.m_InputExp;
	m_MaxCount = widget.m_MaxCount;
	m_MaxExp = widget.m_MaxExp;
	m_Status = widget.m_Status;
}

CLobbyLevelUpDialog::~CLobbyLevelUpDialog()
{
}

void CLobbyLevelUpDialog::Enable(bool bEnable)
{
	CWidgetWindow::Enable(bEnable);
	if (bEnable)
	{
		CSound* Sound = m_Scene->GetResource()->FindSound2D("PopUpIn");
		Sound->Play();
	}
}

void CLobbyLevelUpDialog::Start()
{
	CWidgetWindow::Start(); 
	if (m_MaxCount <= m_Count)
		return;

	if (m_MaxExp < m_InputExp + m_Status->Exp)
		return;
	m_Count++;


	ItemData* Data = m_vecPlayerUpgradeItemInfo[m_SelectItem].Data;
	m_InputExp = Data->Exp * m_Count;
	m_ExpText->SetText(std::to_wstring(m_InputExp).c_str());
	m_NowLevelText->SetText(std::to_wstring(m_NowLevel).c_str());
	m_CountText->SetText(std::to_wstring(m_Count).c_str());

	int Exp = Data->Exp * m_Count + m_Status->Exp;
	m_NextLevel = LevelUp(Exp);
	m_NextLevelText->SetText(std::to_wstring(m_NextLevel).c_str());
	m_ProgressBarCount->SetPercent(float(m_Count) / float(m_MaxCount));
}

bool CLobbyLevelUpDialog::Init()
{
	CWidgetWindow::Init();
	Resolution RS = CDevice::GetInst()->GetResolution();
	SetZOrder(Widget_ZOrder_Dialog);

	CImage* Image = CreateWidget<CImage>("BG_");
	Image->SetPos(0.f, 0.f);
	Image->SetSize(RS.Width, RS.Height);
	Image->SetCollision(false);
	Image->SetZOrder(0);
	Image->SetColorTint(0.f, 0.f, 0.f, 0.2f);

	Image = CreateWidget<CImage>("BG_2");
	Image->SetPos(205.f, 85.f);
	Image->SetSize(860.f, 560.f);
	Image->SetCollision(false);
	Image->SetZOrder(1);
	Image->SetTexture("UI_Btn_Blue", TEXT("UI/Share/UI_Btn_Blue.png"));
	Image->SetColorTint(1.f, 1.f, 1.f, 1.f);

	m_BtnBack = CreateWidget<CButton>("BtnBack");
	m_BtnBack->SetPos(980.f, 590.f);
	m_BtnBack->SetSize(80.f, 50.f);
	m_BtnBack->SetCollision(true);
	m_BtnBack->SetZOrder(2);
	m_BtnBack->SetColorTint(0.f, 0.f, 0.f, 0.f);
	m_BtnBack->SetStateTexture(Button_State::Normal, "UI_Opacity0", TEXT("UI/Share/UI_Opacity0.png"));
	m_BtnBack->SetStateTexture(Button_State::MouseOn, "UI_Opacity0", TEXT("UI/Share/UI_Opacity0.png"));
	m_BtnBack->SetStateTexture(Button_State::Disabled, "UI_Opacity0", TEXT("UI/Share/UI_Opacity0.png"));
	m_BtnBack->SetStateTexture(Button_State::Click, "UI_Opacity0", TEXT("UI/Share/UI_Opacity0.png"));
	m_BtnBack->SetClickCallback<CLobbyLevelUpDialog>(this, &CLobbyLevelUpDialog::BtnCannelCallback);

	CText* Text = CreateWidget<CText>("XX");
	Text->SetPos(980.f, 590.f);
	Text->SetSize(80.f, 50.f);
	Text->SetFontSize(30.f);
	Text->SetCollision(false);
	Text->SetAlignH(TEXT_ALIGN_H::Center);
	Text->SetAlignV(TEXT_ALIGN_V::Middle);
	Text->SetZOrder(3);
	Text->SetText(TEXT("X"));

	Text = CreateWidget<CText>("ItemSelectText");
	Text->SetPos(205.f, 570.f);
	Text->SetSize(860.f, 50.f);
	Text->SetFontSize(30.f);
	Text->SetCollision(false);
	Text->SetAlignH(TEXT_ALIGN_H::Center);
	Text->SetAlignV(TEXT_ALIGN_V::Bottom);
	Text->SetZOrder(3);
	Text->SetText(TEXT("아이템 선택"));

	Text = CreateWidget<CText>("Text");
	Text->SetPos(250.f, 520.f);
	Text->SetSize(180.f, 50.f);
	Text->SetFontSize(30.f);
	Text->SetCollision(false);
	Text->SetAlignH(TEXT_ALIGN_H::Left);
	Text->SetAlignV(TEXT_ALIGN_V::Bottom);
	Text->SetZOrder(3);
	Text->SetText(TEXT("경험치 획득"));

	m_ExpText = CreateWidget<CText>("ExpText");
	m_ExpText->SetPos(500.f, 520.f);
	m_ExpText->SetSize(180.f, 50.f);
	m_ExpText->SetFontSize(30.f);
	m_ExpText->SetCollision(false);
	m_ExpText->SetAlignH(TEXT_ALIGN_H::Left);
	m_ExpText->SetAlignV(TEXT_ALIGN_V::Bottom);
	m_ExpText->SetZOrder(3);
	m_ExpText->SetText(TEXT("1234"));

	Text = CreateWidget<CText>("Level");
	Text->SetPos(650.f, 520.f);
	Text->SetSize(130.f, 50.f);
	Text->SetFontSize(30.f);
	Text->SetCollision(false);
	Text->SetAlignH(TEXT_ALIGN_H::Left);
	Text->SetAlignV(TEXT_ALIGN_V::Bottom);
	Text->SetZOrder(3);
	Text->SetText(TEXT("Level Up"));

	m_NowLevelText = CreateWidget<CText>("NowLevel");
	m_NowLevelText->SetPos(790.f, 520.f);
	m_NowLevelText->SetSize(30.f, 50.f);
	m_NowLevelText->SetFontSize(30.f);
	m_NowLevelText->SetCollision(false);
	m_NowLevelText->SetAlignH(TEXT_ALIGN_H::Left);
	m_NowLevelText->SetAlignV(TEXT_ALIGN_V::Bottom);
	m_NowLevelText->SetZOrder(3);
	m_NowLevelText->SetText(TEXT("1"));

	Text = CreateWidget<CText>("Level1");
	Text->SetPos(820.f, 520.f);
	Text->SetSize(30.f, 50.f);
	Text->SetFontSize(30.f);
	Text->SetCollision(false);
	Text->SetAlignH(TEXT_ALIGN_H::Left);
	Text->SetAlignV(TEXT_ALIGN_V::Bottom);
	Text->SetZOrder(3);
	Text->SetColor(1.f, 1.f, 0.f);
	Text->SetColorTint(1.f, 1.f, 0.f, 0.5f);
	Text->SetText(TEXT(">"));

	Text = CreateWidget<CText>("Level2");
	Text->SetPos(840.f, 520.f);
	Text->SetSize(30.f, 50.f);
	Text->SetFontSize(30.f);
	Text->SetCollision(false);
	Text->SetAlignH(TEXT_ALIGN_H::Left);
	Text->SetAlignV(TEXT_ALIGN_V::Bottom);
	Text->SetZOrder(3);
	Text->SetColor(1.f, 1.f, 0.f);
	Text->SetText(TEXT(">"));

	m_NextLevelText = CreateWidget<CText>("NextLevel");
	m_NextLevelText->SetPos(880.f, 520.f);
	m_NextLevelText->SetSize(30.f, 50.f);
	m_NextLevelText->SetFontSize(30.f);
	m_NextLevelText->SetCollision(false);
	m_NextLevelText->SetAlignH(TEXT_ALIGN_H::Left);
	m_NextLevelText->SetAlignV(TEXT_ALIGN_V::Bottom);
	m_NextLevelText->SetZOrder(3);
	m_NextLevelText->SetText(TEXT("2"));

	//인벤토리제작
	//사용수량
	Text = CreateWidget<CText>("Level2");
	Text->SetPos(260.f, 240.f);
	Text->SetSize(150.f, 50.f);
	Text->SetFontSize(30.f);
	Text->SetCollision(false);
	Text->SetAlignH(TEXT_ALIGN_H::Left);
	Text->SetAlignV(TEXT_ALIGN_V::Bottom);
	Text->SetZOrder(3);
	Text->SetText(TEXT("사용 수량"));

	m_CountText = CreateWidget<CText>("CountText");
	m_CountText->SetPos(405.f, 240.f);
	m_CountText->SetSize(40.f, 50.f);
	m_CountText->SetFontSize(30.f);
	m_CountText->SetCollision(false);
	m_CountText->SetAlignH(TEXT_ALIGN_H::Left);
	m_CountText->SetAlignV(TEXT_ALIGN_V::Bottom);
	m_CountText->SetZOrder(3);
	m_CountText->SetText(TEXT("1"));


	m_BtnCountSub = CreateWidget<CButton>("BtnCountSub");
	m_BtnCountSub->SetPos(550.f, 240.f);
	m_BtnCountSub->SetSize(65.f, 60.f);
	m_BtnCountSub->SetCollision(true);
	m_BtnCountSub->SetZOrder(2);
	m_BtnCountSub->SetColorTint(0.f, 0.f, 0.f, 0.f);
	m_BtnCountSub->SetStateTexture(Button_State::Normal, "-", TEXT("UI/Icon/-.png"));
	m_BtnCountSub->SetStateTexture(Button_State::MouseOn, "-", TEXT("UI/Icon/-.png"));
	m_BtnCountSub->SetStateTexture(Button_State::Disabled, "-", TEXT("UI/Icon/-.png"));
	m_BtnCountSub->SetStateTexture(Button_State::Click, "-", TEXT("UI/Icon/-.png"));
	m_BtnCountSub->SetClickCallback<CLobbyLevelUpDialog>(this, &CLobbyLevelUpDialog::BtnCountSubCallback);

	m_BtnCountAdd = CreateWidget<CButton>("BtnCountAdd");
	m_BtnCountAdd->SetPos(970.f, 240.f);
	m_BtnCountAdd->SetSize(65.f, 60.f);
	m_BtnCountAdd->SetCollision(true);
	m_BtnCountAdd->SetZOrder(2);
	m_BtnCountAdd->SetColorTint(0.f, 0.f, 0.f, 0.f);
	m_BtnCountAdd->SetStateTexture(Button_State::Normal, "+", TEXT("UI/Icon/+.png"));
	m_BtnCountAdd->SetStateTexture(Button_State::MouseOn, "+", TEXT("UI/Icon/+.png"));
	m_BtnCountAdd->SetStateTexture(Button_State::Disabled, "+", TEXT("UI/Icon/+.png"));
	m_BtnCountAdd->SetStateTexture(Button_State::Click, "+", TEXT("UI/Icon/+.png"));
	m_BtnCountAdd->SetClickCallback<CLobbyLevelUpDialog>(this, &CLobbyLevelUpDialog::BtnCountAddCallback);

	m_ProgressBarCount = CreateWidget<CProgressBar>("ProgressBarCount");
	m_ProgressBarCount->SetPos(630.f, 255.f);
	m_ProgressBarCount->SetSize(320.f, 30.f);
	m_ProgressBarCount->SetCollision(false);
	m_ProgressBarCount->SetZOrder(2);

	std::vector<ItemData*>* Data = CPublicData::GetInst()->GetItemDataTable()->FindvecData(ItemType::PlayerUpgradeItem);

	auto iter = Data->begin();
	auto iterEnd = Data->end();
	int i = 0;
	for (; iter != iterEnd; ++iter)
	{
		std::string str;
		str = std::to_string(i);
		i++;

		CButton* ItemButton = CreateWidget<CButton>("ItemButton" + str);
		CImage* ItemImage = CreateWidget<CImage>("ItemImage" + str);
		Text = CreateWidget<CText>("ItemText" + str);

		ItemInfo Info;
		Info.Button = ItemButton;
		Info.ItemImage = ItemImage;
		Info.Text = Text;
		Info.Data = (*iter);
		ItemButton->SetClickCallback(this, &CLobbyLevelUpDialog::BtnSelectUpgradeItemCallback);
		m_vecPlayerUpgradeItemInfo.push_back(Info);
		
		ItemButton->SetSize(144.f, 160.f);
		ItemButton->SetPos(200.f + 170.f * i, 320.f);
		ItemButton->SetStateTexture(Button_State::Normal, "UI_4", TEXT("UI/Share/UI_4.png"));
		ItemButton->SetStateTexture(Button_State::MouseOn, "UI_4", TEXT("UI/Share/UI_4.png"));
		ItemButton->SetStateTexture(Button_State::Disabled, "UI_4", TEXT("UI/Share/UI_4.png"));
		ItemButton->SetStateTexture(Button_State::Click, "UI_4", TEXT("UI/Share/UI_4.png"));
		ItemButton->SetZOrder(2);

		ItemImage->SetSize(140.f, 130.f);
		ItemImage->SetPos(202.f + 170.f * i, 350.f);
		ItemImage->SetCollision(false);
		ItemImage->SetZOrder(3);
		ItemImage->SetTexture(Info.Data->FileName, Info.Data->FilePath.c_str());

		Text->SetSize(100.f, 25.f);
		Text->SetPos(225.f + 170.f * i, 320.f);
		Text->SetFontSize(30.f);
		Text->SetCollision(false);
		Text->SetAlignH(TEXT_ALIGN_H::Center);
		Text->SetAlignV(TEXT_ALIGN_V::Bottom);
		Text->SetZOrder(3);
		Text->SetText(TEXT("Lv.3"));
		Text->SetColor(0.f, 0.f, 0.f);
	}


	//취소, 확인
	m_BtnCannel = CreateWidget<CButton>("BtnCannel");
	m_BtnCannel->SetPos(240.f, 130.f);
	m_BtnCannel->SetSize(390.f, 70.f);
	m_BtnCannel->SetCollision(true);
	m_BtnCannel->SetZOrder(3);
	m_BtnCannel->SetStateTexture(Button_State::Normal, "UI_Btn_BlueAlpha", TEXT("UI/Share/UI_Btn_BlueAlpha.png"));
	m_BtnCannel->SetStateTexture(Button_State::MouseOn, "UI_Btn_BlueAlpha", TEXT("UI/Share/UI_Btn_BlueAlpha.png"));
	m_BtnCannel->SetStateTexture(Button_State::Disabled, "UI_Btn_BlueAlpha", TEXT("UI/Share/UI_Btn_BlueAlpha.png"));
	m_BtnCannel->SetStateTexture(Button_State::Click, "UI_Btn_Blue", TEXT("UI/Share/UI_Btn_Blue.png"));
	m_BtnCannel->SetClickCallback<CLobbyLevelUpDialog>(this, &CLobbyLevelUpDialog::BtnCannelCallback);
	Text = CreateWidget<CText>("Level2");
	Text->SetPos(240.f, 130.f);
	Text->SetSize(390.f, 70.f);
	Text->SetFontSize(30.f);
	Text->SetCollision(false);
	Text->SetAlignH(TEXT_ALIGN_H::Center);
	Text->SetAlignV(TEXT_ALIGN_V::Middle);
	Text->SetZOrder(3);
	Text->SetText(TEXT("취소"));


	m_BtnEnter = CreateWidget<CButton>("BtnCannel");
	m_BtnEnter->SetPos(650.f, 130.f);
	m_BtnEnter->SetSize(390.f, 70.f);
	m_BtnEnter->SetCollision(true);
	m_BtnEnter->SetZOrder(3);
	m_BtnEnter->SetStateTexture(Button_State::Normal, "UI_Btn_BlueAlpha", TEXT("UI/Share/UI_Btn_BlueAlpha.png"));
	m_BtnEnter->SetStateTexture(Button_State::MouseOn, "UI_Btn_BlueAlpha", TEXT("UI/Share/UI_Btn_BlueAlpha.png"));
	m_BtnEnter->SetStateTexture(Button_State::Disabled, "UI_Btn_BlueAlpha", TEXT("UI/Share/UI_Btn_BlueAlpha.png"));
	m_BtnEnter->SetStateTexture(Button_State::Click, "UI_Btn_Blue", TEXT("UI/Share/UI_Btn_Yellow.png"));
	m_BtnEnter->SetClickCallback<CLobbyLevelUpDialog>(this, &CLobbyLevelUpDialog::BtnEnterCallback);
	Text = CreateWidget<CText>("Level2");
	Text->SetPos(650.f, 130.f);
	Text->SetSize(390.f, 70.f);
	Text->SetFontSize(30.f);
	Text->SetCollision(false);
	Text->SetAlignH(TEXT_ALIGN_H::Center);
	Text->SetAlignV(TEXT_ALIGN_V::Middle);
	Text->SetZOrder(3);
	Text->SetText(TEXT("확인"));

	return true;
}

void CLobbyLevelUpDialog::Update(float DeltaTime)
{
	CWidgetWindow::Update(DeltaTime);
	if (m_Status)
	{
		m_NowLevelText->SetText(std::to_wstring(m_Status->Level).c_str());
		m_NextLevelText->SetText(std::to_wstring(m_NextLevel).c_str());
		m_ExpText->SetText(std::to_wstring(m_InputExp).c_str());
	}
	size_t Size = m_vecPlayerUpgradeItemInfo.size();
	for (size_t i = 0; i < Size; ++i)
	{
		int Count = m_vecPlayerUpgradeItemInfo[i].Data->Count;
		m_vecPlayerUpgradeItemInfo[i].Text->SetText(std::to_wstring(Count).c_str());
	}
}

void CLobbyLevelUpDialog::PostUpdate(float DeltaTime)
{
	CWidgetWindow::PostUpdate(DeltaTime);
}

void CLobbyLevelUpDialog::Render()
{
	CWidgetWindow::Render();
}

CLobbyLevelUpDialog* CLobbyLevelUpDialog::Clone()
{
	return new CLobbyLevelUpDialog(*this);
}

void CLobbyLevelUpDialog::SetLevelUpDialog()
{
	m_Count = 1;
	m_SelectItem = 0;
	ItemData* Data = m_vecPlayerUpgradeItemInfo[m_SelectItem].Data;

	m_InputExp = Data->Exp * m_Count;
	int MaxExp1 = Data->Exp * Data->Count;
	int MaxExp2 = (m_Status->LevelMax -m_Status->Level) * m_Status->ExpMax- m_Status->Exp;
	m_MaxExp = MaxExp1 > MaxExp2 ? MaxExp2 : MaxExp1;
	m_MaxCount = m_MaxExp / Data->Exp;
	m_NowLevel = m_Status->Level;

	m_ExpText->SetText(std::to_wstring(m_InputExp).c_str());
	m_NowLevelText->SetText(std::to_wstring(m_NowLevel).c_str());
	m_CountText->SetText(std::to_wstring(m_Count).c_str());
	int Exp = Data->Exp * m_Count + m_Status->Exp;
	int m_NextLevel = LevelUp(Exp);
	m_NextLevelText->SetText(std::to_wstring(m_NextLevel).c_str());
	m_ProgressBarCount->SetPercent(float(m_Count) / float(m_MaxCount));

}

int CLobbyLevelUpDialog::LevelUp(int Exp)
{
	int Level=m_Status->Level;
	while (true)
	{
		if (Exp >= m_Status->ExpMax)
		{
			Level++;
			Exp -= m_Status->ExpMax;
		}
		else
		{
			break;
		}
	}

	return Level;
}

void CLobbyLevelUpDialog::BtnEnterCallback()
{
	CPublicData::GetInst()->GetPlayerDataTable()->AddExp(m_Status->Name, m_InputExp);
	m_vecPlayerUpgradeItemInfo[m_SelectItem].Data->Count -= m_Count;


	CSound* Sound = m_Scene->GetResource()->FindSound2D("Upgrade");
	Sound->Play();
	Enable(false);
}

void CLobbyLevelUpDialog::BtnCannelCallback()
{
	CSound* Sound = m_Scene->GetResource()->FindSound2D("PopUpOut");
	Sound->Play();
	Enable(false);
}

void CLobbyLevelUpDialog::BtnSelectUpgradeItemCallback()
{
	CSound* Sound = m_Scene->GetResource()->FindSound2D("ButtonClick");
	Sound->Play();
}

void CLobbyLevelUpDialog::BtnCountAddCallback()
{
	CSound* Sound = m_Scene->GetResource()->FindSound2D("ButtonClick");
	Sound->Play();
	//아이템 카운트
	if (m_MaxCount <= m_Count)
		return;
	
	if (m_MaxExp < m_InputExp+m_Status->Exp)
		return;
	m_Count++;


	ItemData* Data = m_vecPlayerUpgradeItemInfo[m_SelectItem].Data;
	m_InputExp = Data->Exp * m_Count;
	m_ExpText->SetText(std::to_wstring(m_InputExp).c_str());
	m_NowLevelText->SetText(std::to_wstring(m_NowLevel).c_str());
	m_CountText->SetText(std::to_wstring(m_Count).c_str());

	int Exp = Data->Exp * m_Count + m_Status->Exp;
	m_NextLevel = LevelUp(Exp);
	m_NextLevelText->SetText(std::to_wstring(m_NextLevel).c_str());
	m_ProgressBarCount->SetPercent(float(m_Count) / float(m_MaxCount));
}

void CLobbyLevelUpDialog::BtnCountSubCallback()
{
	CSound* Sound = m_Scene->GetResource()->FindSound2D("ButtonClick");
	Sound->Play();
	//아이템 카운트
	if (m_Count == 1)
		return;

	m_Count--;


	ItemData* Data = m_vecPlayerUpgradeItemInfo[m_SelectItem].Data;
	m_InputExp = Data->Exp * m_Count;
	m_ExpText->SetText(std::to_wstring(m_InputExp).c_str());
	m_NowLevelText->SetText(std::to_wstring(m_NowLevel).c_str());
	m_CountText->SetText(std::to_wstring(m_Count).c_str());

	int Exp = Data->Exp * m_Count + m_Status->Exp;
	m_NextLevel = LevelUp(Exp);
	m_NextLevelText->SetText(std::to_wstring(m_NextLevel).c_str());
	m_ProgressBarCount->SetPercent(float(m_Count) / float(m_MaxCount));
}
