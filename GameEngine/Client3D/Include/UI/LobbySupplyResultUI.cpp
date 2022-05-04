
#include "LobbySupplyResultUI.h"
#include <Device.h>
#include "../PublicData.h"
#include "UIManager.h"
#include "Scene/Scene.h"
#include "Scene/SceneResource.h"
#include "../StageManager.h"
CLobbySupplyResultUI::CLobbySupplyResultUI():
	m_SupplyShowCount(0),
	m_Timer(0.4f)
{
}

CLobbySupplyResultUI::CLobbySupplyResultUI(const CLobbySupplyResultUI& widget) :
	CWidgetWindow(widget)
{
	m_SupplyShowCount = widget.m_SupplyShowCount;
	m_Timer = widget.m_Timer;
}

CLobbySupplyResultUI::~CLobbySupplyResultUI()
{
}


void CLobbySupplyResultUI::Start()
{
	CWidgetWindow::Start();
}

bool CLobbySupplyResultUI::Init()
{
	CWidgetWindow::Init();
	Resolution RS = CDevice::GetInst()->GetResolution();

	CImage* Image;
	Image = CreateWidget<CImage>("BG_2");
	Image->SetSize((float)RS.Width, (float)RS.Height);
	Image->SetPos(0.f, 0.f);
	Image->SetCollision(false);
	Image->SetZOrder(1);
	Image->SetTexture("UI_BG", TEXT("UI/Share/UI_BG.png"));
	Image->SetColorTint(1.f, 1.f, 1.f, 1.f);



	//금화
	Image = CreateWidget<CImage>("GoldBG");
	Image->SetPos(835.f, 670.f);
	Image->SetSize(160.f, 30.f);
	Image->SetCollision(false);
	Image->SetTexture("UI_Btn_Gray", TEXT("UI/Share/UI_Btn_Gray.png"));
	Image->SetZOrder(4);

	Image = CreateWidget<CImage>("Gold");
	Image->SetPos(835.f, 670.f);
	Image->SetSize(36.f, 36.f);
	Image->SetCollision(false);
	Image->SetTexture("Gold", TEXT("UI/MainPage/Gold.png"));
	Image->SetZOrder(5);

	m_GoldText = CreateWidget<CText>("GoldText");
	m_GoldText->SetPos(870.f, 670.f);
	m_GoldText->SetSize(100.f, 30);
	m_GoldText->SetFontSize(20.f);
	m_GoldText->SetCollision(false);
	m_GoldText->SetText(std::to_wstring(CPublicData::GetInst()->GetGold()).c_str());
	m_GoldText->SetZOrder(6);
	m_GoldText->SetAlignH(TEXT_ALIGN_H::Right);
	m_GoldText->SetAlignV(TEXT_ALIGN_V::Bottom);

	//크리스탈
	Image = CreateWidget<CImage>("CrystalBG");
	Image->SetPos(1050.f, 670.f);
	Image->SetSize(150.f, 30.f);
	Image->SetCollision(false);
	Image->SetTexture("UI_Btn_Gray", TEXT("UI/Share/UI_Btn_Gray.png"));
	Image->SetZOrder(4);

	Image = CreateWidget<CImage>("Crystal");
	Image->SetPos(1050.f, 670.f);
	Image->SetSize(36.f, 36.f);
	Image->SetCollision(false);
	Image->SetTexture("Crystal", TEXT("UI/MainPage/Crystal.png"));
	Image->SetZOrder(5);

	m_CrystalText = CreateWidget<CText>("CrystalText");
	m_CrystalText->SetPos(1095, 670.f);
	m_CrystalText->SetSize(80.f, 30.f);
	m_CrystalText->SetFontSize(20.f);
	m_CrystalText->SetCollision(false);
	m_CrystalText->SetText(std::to_wstring(CPublicData::GetInst()->GetCrystal()).c_str());
	m_CrystalText->SetZOrder(6);
	m_CrystalText->SetAlignH(TEXT_ALIGN_H::Right);
	m_CrystalText->SetAlignV(TEXT_ALIGN_V::Bottom);

#pragma region BtnBack
	m_BtnBack = CreateWidget<CButton>("BackButton");
	m_BtnBack->SetPos(0.f, 650.f);
	m_BtnBack->SetSize(130.f, 50.f);
	m_BtnBack->SetCollision(true);
	m_BtnBack->SetZOrder(4);
	m_BtnBack->SetStateTexture(Button_State::Normal, "UI_Btn_Yellow", TEXT("UI/Share/UI_Btn_Yellow.png"));
	m_BtnBack->SetStateTexture(Button_State::MouseOn, "UI_Btn_Yellow", TEXT("UI/Share/UI_Btn_Yellow.png"));
	m_BtnBack->SetStateTexture(Button_State::Disabled, "UI_Btn_Yellow", TEXT("UI/Share/UI_Btn_Yellow.png"));
	m_BtnBack->SetStateTexture(Button_State::Click, "UI_Btn_Yellow", TEXT("UI/Share/UI_Btn_Yellow.png"));
	m_BtnBack->SetClickCallback<CLobbySupplyResultUI>(this, &CLobbySupplyResultUI::BtnBackCallback);

	CText* Text = CreateWidget<CText>("BackText");
	Text->SetPos(10.f, 660.f);
	Text->SetSize(100.f, 50.f);
	Text->SetFontSize(30.f);
	Text->SetCollision(false);
	Text->SetAlignH(TEXT_ALIGN_H::Left);
	Text->SetAlignV(TEXT_ALIGN_V::Bottom);
	Text->SetZOrder(5);
	Text->SetColor(0.f, 0.f, 0.f);
	Text->SetText(TEXT("< 뒤로"));
#pragma endregion



	return true;
}

void CLobbySupplyResultUI::Update(float DeltaTime)
{
	CWidgetWindow::Update(DeltaTime);
	LobbySupplyResultUpdate(DeltaTime);
	m_CrystalText->SetText(std::to_wstring(CPublicData::GetInst()->GetCrystal()).c_str());

}

void CLobbySupplyResultUI::PostUpdate(float DeltaTime)
{
	CWidgetWindow::PostUpdate(DeltaTime);
}

void CLobbySupplyResultUI::Render()
{
	CWidgetWindow::Render();
}

CLobbySupplyResultUI* CLobbySupplyResultUI::Clone()
{
	return new CLobbySupplyResultUI(*this);
}


void CLobbySupplyResultUI::SetSupply(int SupplyCount)
{
	m_SupplyShowCount = -1;
	size_t Size = m_SupplyResult.size();

	for (size_t i = 0; i < Size; ++i)
	{
		m_SupplyResult[i].Active(false);
	}
	m_SupplyResult.clear();
	for (int i = 0; i < SupplyCount; ++i)
	{
		//10개뿐이니까..
		int x = i;
		int y = 0;
		if (x >= 5)
		{
			y++;
			x -= 5;
		}
		std::vector<ItemData*>* PlayerUpgradeItem = CPublicData::GetInst()->GetItemDataTable()->FindvecData(ItemType::PlayerUpgradeItem);
		std::vector<ItemData*>* WeaponUpgradeItem = CPublicData::GetInst()->GetItemDataTable()->FindvecData(ItemType::WeaponUpgradeItem);

		size_t PlayerUpgradeSize = PlayerUpgradeItem->size();
		size_t WeaponUpgradeSize = WeaponUpgradeItem->size();

		int SelectNum=GetRandom(0, (int)(PlayerUpgradeSize + WeaponUpgradeSize-1));
		ItemData* Data = nullptr;
		if (PlayerUpgradeSize <= SelectNum)
		{
			SelectNum -= PlayerUpgradeSize;
			Data = (*WeaponUpgradeItem)[SelectNum];
		}
		else
		{
			Data = (*PlayerUpgradeItem)[SelectNum];
		}
		Data->Count++;


		std::string str;
		str = std::to_string(i);
		CImage* BG = CreateWidget<CImage>("ItemButton" + str);
		CImage* ItemImage = CreateWidget<CImage>("ItemImage" + str);
		CText* Text = CreateWidget<CText>("ItemText" + str);


		SupplyResultUI Info;
		Info.BG = BG;
		Info.ItemImage = ItemImage;
		Info.Data = Data;
		Info.Enable(false);
		m_SupplyResult.push_back(Info);

		BG->SetSize(144.f*2.f, 160.f * 2.f);
		BG->SetPos(200.f + 190.f * x, 420.f - 200.f * y);
		BG->SetCenter();
		BG->SetTexture("UI_4", TEXT("UI/Share/UI_4.png"));
		BG->SetZOrder(6);

		ItemImage->SetSize(140.f * 2.f, 130.f * 2.f);
		ItemImage->SetPos(202.f + 190.f * x, 440.f- 200.f * y);
		ItemImage->SetCollision(false);
		ItemImage->SetCenter();
		ItemImage->SetZOrder(7);
		ItemImage->SetTexture(Info.Data->FileName, Info.Data->FilePath.c_str());
	}

}
void CLobbySupplyResultUI::BtnBackCallback()
{
	CStageManager::GetInst()->BGMPlay("ShopBG");
	CSound* Sound = m_Scene->GetResource()->FindSound2D("ButtonClick");
	Sound->Play();
	CUIManager::GetInst()->FindWidgetWindow("LobbySupplyUI")->Enable(true);
	Enable(false);
}

void CLobbySupplyResultUI::LobbySupplyResultUpdate(float DeltaTime)
{
	if (m_SupplyShowCount >= (int)m_SupplyResult.size())
		return;
	m_Timer += DeltaTime;
	if (m_Timer > 0.4f)
	{
		if (m_SupplyShowCount >= 0)
		{
			CImage* BG = m_SupplyResult[m_SupplyShowCount].BG;
			CImage* ItemImage = m_SupplyResult[m_SupplyShowCount].ItemImage;
			BG->SetSize(144.f, 160.f);
			ItemImage->SetSize(140.f, 130.f);
		}

		m_SupplyShowCount++;
		if (m_SupplyShowCount >= (int)m_SupplyResult.size())
			return;
		m_Timer -= 0.4f;
		m_SupplyResult[m_SupplyShowCount].Enable(true);
		CSound* Sound = m_Scene->GetResource()->FindSound2D("ShopResult");
		Sound->Play();
	}
	else
	{
		CImage* BG = m_SupplyResult[m_SupplyShowCount].BG;
		CImage* ItemImage = m_SupplyResult[m_SupplyShowCount].ItemImage;
		BG->SetSize(BG->GetSize() - BG->GetSize()*DeltaTime*2.f);
		ItemImage->SetSize(ItemImage->GetSize() - ItemImage->GetSize() * DeltaTime * 2.f);
		if (BG->GetSize().x < 144.f)
		{
			BG->SetSize(144.f, 160.f);
		}
		if (ItemImage->GetSize().x < 140.f)
		{
			ItemImage->SetSize(140.f, 130.f);
		}
	}
}
