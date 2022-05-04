
#include "LobbyEquipmemtUI.h"
#include "UI/Image.h"
#include "UI/Button.h"
#include <Device.h>
#include "../Object/Player.h"
#include "UIManager.h"
#include "Resource/Animation.h"
#include "../PublicData.h"
#include "Scene/SceneManager.h"
#include "Device.h"
#include "../LobbyManager.h"
#include "Scene/Scene.h"
#include "Scene/CameraManager.h"
#include "LobbyValkyrieInfoUI.h"
#include "LobbyItemInfoDialog.h"
#include "LobbyWeaponInfoUI.h"
CLobbyEquipmemtUI::CLobbyEquipmemtUI():
	m_UpgradeItem(false),
	m_Weapon(true)
{
}

CLobbyEquipmemtUI::CLobbyEquipmemtUI(const CLobbyEquipmemtUI& widget)
{
}

CLobbyEquipmemtUI::~CLobbyEquipmemtUI()
{
}

void CLobbyEquipmemtUI::Start()
{
	CWidgetWindow::Start();
	m_BtnWeaponInventory->SetStateTexture(Button_State::Click, "UI_Btn_Blue", TEXT("UI/Share/UI_Btn_Blue.png"));
	m_BtnWeaponInventory->SetStateTexture(Button_State::Normal, "UI_Btn_Blue", TEXT("UI/Share/UI_Btn_Blue.png"));
	m_BtnWeaponInventory->SetStateTexture(Button_State::MouseOn, "UI_Btn_Blue", TEXT("UI/Share/UI_Btn_Blue.png"));
	m_BtnWeaponInventory->SetStateTexture(Button_State::Disabled, "UI_Btn_Blue", TEXT("UI/Share/UI_Btn_Blue.png"));

	m_BtnUpgradeItemInventory->SetStateTexture(Button_State::Normal, "UI_Btn_BlueAlpha", TEXT("UI/Share/UI_Btn_BlueAlpha.png"));
	m_BtnUpgradeItemInventory->SetStateTexture(Button_State::MouseOn, "UI_Btn_BlueAlpha", TEXT("UI/Share/UI_Btn_BlueAlpha.png"));
	m_BtnUpgradeItemInventory->SetStateTexture(Button_State::Disabled, "UI_Btn_BlueAlpha", TEXT("UI/Share/UI_Btn_BlueAlpha.png"));
	m_BtnUpgradeItemInventory->SetStateTexture(Button_State::Click, "UI_Btn_Blue", TEXT("UI/Share/UI_Btn_Blue.png"));
	m_Weapon = true;
	m_UpgradeItem = false;

	size_t Size = m_vecWeaponItemInfo.size();
	for (size_t i = 0; i < Size; ++i)
	{
		m_vecWeaponItemInfo[i].Enable(true);
	}
	Size = m_vecUpgradeItemInfo.size();
	for (size_t i = 0; i < Size; ++i)
	{
		m_vecUpgradeItemInfo[i].Enable(false);
	}
}

bool CLobbyEquipmemtUI::Init()
{
	CWidgetWindow::Init();
	Resolution RS = CDevice::GetInst()->GetResolution();

	CImage* Image;
	Image = CreateWidget<CImage>("BG_2");
	Image->SetSize((float)RS.Width, (float)RS.Height);
	Image->SetPos(0.f, 0.f);
	Image->SetCollision(false);
	Image->SetZOrder(1);
	Image->SetTexture("SpaceShipBridge_City", TEXT("UI/Share/SpaceShipBridge_City_.png"));
	Image->SetColorTint(1.f, 1.f, 1.f, 1.f);

	for (int y = 0; y < 2; ++y)
	{
		for (int x = 0; x < 6; ++x)
		{
			Image = CreateWidget<CImage>("TriangleFill");
			Image->SetSize(464.f, 200.f);
			Image->SetPos(464.f * x, 300.f + 200 * y);
			Image->SetCollision(false);
			Image->SetZOrder(2);
			Image->SetTexture("TriangleFill", TEXT("UI/Stage_Select/TriangleFill.png"));
			Image->SetColorTint(1.f, 1.f, 1.f, 0.3f);
		}
	}

	for (int y = 0; y < 2; ++y)
	{
		for (int x = 0; x < 6; ++x)
		{
			Image = CreateWidget<CImage>("HexagonalTexture");
			Image->SetSize(492.f, 284.f);
			Image->SetPos(492.f * x, 284.f * y);
			Image->SetCollision(false);
			Image->SetZOrder(2);
			Image->SetTexture("HexagonalTexture", TEXT("UI/Stage_Select/HexagonalTexture.png"));
			Image->SetColorTint(1.f, 1.f, 1.f, 0.3f);
		}
	}




	//금화
	Image = CreateWidget<CImage>("GoldBG");
	Image->SetPos(835.f, 670.f);
	Image->SetSize(160.f, 30.f);
	Image->SetCollision(false);
	Image->SetTexture("UI_Btn_Gray", TEXT("UI/Share/UI_Btn_Gray.png"));
	Image->SetZOrder(2);

	Image = CreateWidget<CImage>("Gold");
	Image->SetPos(835.f, 670.f);
	Image->SetSize(36.f, 36.f);
	Image->SetCollision(false);
	Image->SetTexture("Gold", TEXT("UI/MainPage/Gold.png"));
	Image->SetZOrder(3);

	m_GoldText = CreateWidget<CText>("GoldText");
	m_GoldText->SetPos(870.f, 670.f);
	m_GoldText->SetSize(100.f, 30);
	m_GoldText->SetFontSize(20.f);
	m_GoldText->SetCollision(false);
	m_GoldText->SetText(std::to_wstring(CPublicData::GetInst()->GetGold()).c_str());
	m_GoldText->SetZOrder(4);
	m_GoldText->SetAlignH(TEXT_ALIGN_H::Right);
	m_GoldText->SetAlignV(TEXT_ALIGN_V::Bottom);

	//크리스탈
	Image = CreateWidget<CImage>("CrystalBG");
	Image->SetPos(1050.f, 670.f);
	Image->SetSize(150.f, 30.f);
	Image->SetCollision(false);
	Image->SetTexture("UI_Btn_Gray", TEXT("UI/Share/UI_Btn_Gray.png"));
	Image->SetZOrder(2);

	Image = CreateWidget<CImage>("Crystal");
	Image->SetPos(1050.f, 670.f);
	Image->SetSize(36.f, 36.f);
	Image->SetCollision(false);
	Image->SetTexture("Crystal", TEXT("UI/MainPage/Crystal.png"));
	Image->SetZOrder(3);

	m_CrystalText = CreateWidget<CText>("CrystalText");
	m_CrystalText->SetPos(1095, 670.f);
	m_CrystalText->SetSize(80.f, 30.f);
	m_CrystalText->SetFontSize(20.f);
	m_CrystalText->SetCollision(false);
	m_CrystalText->SetText(std::to_wstring(CPublicData::GetInst()->GetCrystal()).c_str());
	m_CrystalText->SetZOrder(4);
	m_CrystalText->SetAlignH(TEXT_ALIGN_H::Right);
	m_CrystalText->SetAlignV(TEXT_ALIGN_V::Bottom);

#pragma region BtnBack
	m_BtnBack = CreateWidget<CButton>("BackButton");
	m_BtnBack->SetPos(0.f, 650.f);
	m_BtnBack->SetSize(130.f, 50.f);
	m_BtnBack->SetCollision(true);
	m_BtnBack->SetZOrder(2);
	m_BtnBack->SetStateTexture(Button_State::Normal, "UI_Btn_Yellow", TEXT("UI/Share/UI_Btn_Yellow.png"));
	m_BtnBack->SetStateTexture(Button_State::MouseOn, "UI_Btn_Yellow", TEXT("UI/Share/UI_Btn_Yellow.png"));
	m_BtnBack->SetStateTexture(Button_State::Disabled, "UI_Btn_Yellow", TEXT("UI/Share/UI_Btn_Yellow.png"));
	m_BtnBack->SetStateTexture(Button_State::Click, "UI_Btn_Yellow", TEXT("UI/Share/UI_Btn_Yellow.png"));
	m_BtnBack->SetClickCallback<CLobbyEquipmemtUI>(this, &CLobbyEquipmemtUI::BtnBackCallback);

	CText* Text = CreateWidget<CText>("BackText");
	Text->SetPos(10.f, 660.f);
	Text->SetSize(100.f, 50.f);
	Text->SetFontSize(30.f);
	Text->SetCollision(false);
	Text->SetAlignH(TEXT_ALIGN_H::Left);
	Text->SetAlignV(TEXT_ALIGN_V::Bottom);
	Text->SetZOrder(3);
	Text->SetText(TEXT("< 뒤로"));
	Text->SetColor(0.f, 0.f, 0.f);
#pragma endregion

	m_BtnWeaponInventory = CreateWidget<CButton>("BtnWeaponInventory");
	m_BtnWeaponInventory->SetPos(0.f, 556.f);
	m_BtnWeaponInventory->SetSize(166.f, 76.f);
	m_BtnWeaponInventory->SetCollision(true);
	m_BtnWeaponInventory->SetZOrder(2);
	m_BtnWeaponInventory->SetStateTexture(Button_State::Normal, "UI_Btn_BlueAlpha", TEXT("UI/Share/UI_Btn_BlueAlpha.png"));
	m_BtnWeaponInventory->SetStateTexture(Button_State::MouseOn, "UI_Btn_BlueAlpha", TEXT("UI/Share/UI_Btn_BlueAlpha.png"));
	m_BtnWeaponInventory->SetStateTexture(Button_State::Disabled, "UI_Btn_BlueAlpha", TEXT("UI/Share/UI_Btn_BlueAlpha.png"));
	m_BtnWeaponInventory->SetStateTexture(Button_State::Click, "UI_Btn_Blue", TEXT("UI/Share/UI_Btn_Blue.png"));
	m_BtnWeaponInventory->SetClickCallback<CLobbyEquipmemtUI>(this, &CLobbyEquipmemtUI::BtnWeaponInventoryCallback);
	Text = CreateWidget<CText>("Text");
	Text->SetPos(0.f, 556.f);
	Text->SetSize(166.f, 76.f);
	Text->SetFontSize(30.f);
	Text->SetCollision(false);
	Text->SetAlignH(TEXT_ALIGN_H::Center);
	Text->SetAlignV(TEXT_ALIGN_V::Middle);
	Text->SetZOrder(3);
	Text->SetText(TEXT("무기"));

	m_BtnUpgradeItemInventory = CreateWidget<CButton>("BtnUpgradeItemInventory");
	m_BtnUpgradeItemInventory->SetPos(0.f, 476.f);
	m_BtnUpgradeItemInventory->SetSize(166.f, 76.f);
	m_BtnUpgradeItemInventory->SetCollision(true);
	m_BtnUpgradeItemInventory->SetZOrder(2);
	m_BtnUpgradeItemInventory->SetStateTexture(Button_State::Normal, "UI_Btn_BlueAlpha", TEXT("UI/Share/UI_Btn_BlueAlpha.png"));
	m_BtnUpgradeItemInventory->SetStateTexture(Button_State::MouseOn, "UI_Btn_BlueAlpha", TEXT("UI/Share/UI_Btn_BlueAlpha.png"));
	m_BtnUpgradeItemInventory->SetStateTexture(Button_State::Disabled, "UI_Btn_BlueAlpha", TEXT("UI/Share/UI_Btn_BlueAlpha.png"));
	m_BtnUpgradeItemInventory->SetStateTexture(Button_State::Click, "UI_Btn_Blue", TEXT("UI/Share/UI_Btn_Blue.png"));
	m_BtnUpgradeItemInventory->SetClickCallback<CLobbyEquipmemtUI>(this, &CLobbyEquipmemtUI::BtnUpgradeItemInventoryCallback);
	Text = CreateWidget<CText>("Text");
	Text->SetPos(0.f, 476.f);
	Text->SetSize(166.f, 76.f);
	Text->SetFontSize(30.f);
	Text->SetCollision(false);
	Text->SetAlignH(TEXT_ALIGN_H::Center);
	Text->SetAlignV(TEXT_ALIGN_V::Middle);
	Text->SetZOrder(3);
	Text->SetText(TEXT("재료"));


	std::vector<ItemData*>* Data = CPublicData::GetInst()->GetItemDataTable()->FindvecData(ItemType::Weapon);
	auto iter = Data->begin();
	auto iterEnd = Data->end();
	int i = 0;
	for (; iter != iterEnd; ++iter)
	{
		std::string str;
		str = std::to_string(i);
		CButton* ItemButton = CreateWidget<CButton>("ItemButton" + str);
		CImage* ItemImage = CreateWidget<CImage>("ItemImage" + str);
		CText* Text = CreateWidget<CText>("ItemText" + str);

		EquipItemInfo Info;
		Info.Button = ItemButton;
		Info.ItemImage = ItemImage;
		Info.Text = Text;
		Info.Status = (*iter);
		ItemButton->SetClickCallback(this, &CLobbyEquipmemtUI::BtnWeaponCallback);
		std::wstring wstr;
		wstr = TEXT("Lv.") + std::to_wstring(Info.Status->Level);
		Text->SetText(wstr.c_str());
		m_vecWeaponItemInfo.push_back(Info);
		
		ItemButton->SetSize(144.f, 160.f);
		ItemButton->SetPos(200.f + 170.f * i, 470.f);
		ItemButton->SetStateTexture(Button_State::Normal, "UI_4", TEXT("UI/Share/UI_4.png"));
		ItemButton->SetStateTexture(Button_State::MouseOn, "UI_4", TEXT("UI/Share/UI_4.png"));
		ItemButton->SetStateTexture(Button_State::Disabled, "UI_4", TEXT("UI/Share/UI_4.png"));
		ItemButton->SetStateTexture(Button_State::Click, "UI_4", TEXT("UI/Share/UI_4.png"));
		ItemButton->SetZOrder(2);

		ItemImage->SetSize(140.f, 130.f);
		ItemImage->SetPos(202.f + 170.f * i, 500.f);
		ItemImage->SetCollision(false);
		ItemImage->SetZOrder(3);
		ItemImage->SetTexture(Info.Status->FileName, Info.Status->FilePath.c_str());

		Text->SetSize(100.f, 25.f);
		Text->SetPos(225.f + 170.f * i, 470.f);
		Text->SetFontSize(30.f);
		Text->SetCollision(false);
		Text->SetAlignH(TEXT_ALIGN_H::Center);
		Text->SetAlignV(TEXT_ALIGN_V::Bottom);
		Text->SetZOrder(3);
		Text->SetColor(0.f, 0.f, 0.f);
		i++;
	}
	i = 0;

	Data = CPublicData::GetInst()->GetItemDataTable()->FindvecData(ItemType::PlayerUpgradeItem);
	iter = Data->begin();
	iterEnd = Data->end();
	for (; iter != iterEnd; ++iter)
	{
		//무기는 i 강화아이템은 j
		std::string str;
		str = std::to_string(i);
		CButton* ItemButton = CreateWidget<CButton>("ItemButton" + str);
		CImage* ItemImage = CreateWidget<CImage>("ItemImage" + str);
		CText* Text = CreateWidget<CText>("ItemText" + str);

		EquipItemInfo Info;
		Info.Button = ItemButton;
		Info.ItemImage = ItemImage;
		Info.Text = Text;
		Info.Status = (*iter);
		ItemButton->SetClickCallback(this, &CLobbyEquipmemtUI::BtnUpgradeItemCallback);
		Text->SetText(std::to_wstring(Info.Status->Count).c_str());
		m_vecUpgradeItemInfo.push_back(Info);
		ItemButton->SetSize(144.f, 160.f);
		ItemButton->SetPos(200.f + 170.f * i, 470.f);
		ItemButton->SetStateTexture(Button_State::Normal, "UI_4", TEXT("UI/Share/UI_4.png"));
		ItemButton->SetStateTexture(Button_State::MouseOn, "UI_4", TEXT("UI/Share/UI_4.png"));
		ItemButton->SetStateTexture(Button_State::Disabled, "UI_4", TEXT("UI/Share/UI_4.png"));
		ItemButton->SetStateTexture(Button_State::Click, "UI_4", TEXT("UI/Share/UI_4.png"));
		ItemButton->SetZOrder(2);

		ItemImage->SetSize(140.f, 130.f);
		ItemImage->SetPos(202.f + 170.f * i, 500.f);
		ItemImage->SetCollision(false);
		ItemImage->SetZOrder(3);
		ItemImage->SetTexture(Info.Status->FileName, Info.Status->FilePath.c_str());
		Text->SetSize(100.f, 25.f);
		Text->SetPos(225.f + 170.f * i, 470.f);
		Text->SetFontSize(30.f);
		Text->SetCollision(false);
		Text->SetAlignH(TEXT_ALIGN_H::Center);
		Text->SetAlignV(TEXT_ALIGN_V::Bottom);
		Text->SetZOrder(3);
		Text->SetColor(0.f, 0.f, 0.f);
		
		i++;
	}

	Data = CPublicData::GetInst()->GetItemDataTable()->FindvecData(ItemType::WeaponUpgradeItem);
	iter = Data->begin();
	iterEnd = Data->end();
	for (; iter != iterEnd; ++iter)
	{
		//무기는 i 강화아이템은 j
		std::string str;
		str = std::to_string(i);
		CButton* ItemButton = CreateWidget<CButton>("ItemButton" + str);
		CImage* ItemImage = CreateWidget<CImage>("ItemImage" + str);
		CText* Text = CreateWidget<CText>("ItemText" + str);

		EquipItemInfo Info;
		Info.Button = ItemButton;
		Info.ItemImage = ItemImage;
		Info.Text = Text;
		Info.Status = (*iter);
		ItemButton->SetClickCallback(this, &CLobbyEquipmemtUI::BtnUpgradeItemCallback);
		Text->SetText(std::to_wstring(Info.Status->Count).c_str());
		m_vecUpgradeItemInfo.push_back(Info);
		ItemButton->SetSize(144.f, 160.f);
		ItemButton->SetPos(200.f + 170.f * i, 470.f);
		ItemButton->SetStateTexture(Button_State::Normal, "UI_4", TEXT("UI/Share/UI_4.png"));
		ItemButton->SetStateTexture(Button_State::MouseOn, "UI_4", TEXT("UI/Share/UI_4.png"));
		ItemButton->SetStateTexture(Button_State::Disabled, "UI_4", TEXT("UI/Share/UI_4.png"));
		ItemButton->SetStateTexture(Button_State::Click, "UI_4", TEXT("UI/Share/UI_4.png"));
		ItemButton->SetZOrder(2);

		ItemImage->SetSize(140.f, 130.f);
		ItemImage->SetPos(202.f + 170.f * i, 500.f);
		ItemImage->SetCollision(false);
		ItemImage->SetZOrder(3);
		ItemImage->SetTexture(Info.Status->FileName, Info.Status->FilePath.c_str());
		Text->SetSize(100.f, 25.f);
		Text->SetPos(225.f + 170.f * i, 470.f);
		Text->SetFontSize(30.f);
		Text->SetCollision(false);
		Text->SetAlignH(TEXT_ALIGN_H::Center);
		Text->SetAlignV(TEXT_ALIGN_V::Bottom);
		Text->SetZOrder(3);
		Text->SetColor(0.f, 0.f, 0.f);

		i++;
	}
	return true;
}

void CLobbyEquipmemtUI::Update(float DeltaTime)
{
	CWidgetWindow::Update(DeltaTime);
	size_t Size = m_vecWeaponItemInfo.size();
	for (size_t i = 0; i < Size; ++i)
	{
		std::wstring wstr;
		wstr = TEXT("Lv.") + std::to_wstring(m_vecWeaponItemInfo[i].Status->Level);
		m_vecWeaponItemInfo[i].Text->SetText(wstr.c_str());
	}
	Size = m_vecUpgradeItemInfo.size();
	for (size_t i = 0; i < Size; ++i)
	{
		int Count = m_vecUpgradeItemInfo[i].Status->Count;
		m_vecUpgradeItemInfo[i].Text->SetText(std::to_wstring(Count).c_str());

	}
	m_CrystalText->SetText(std::to_wstring(CPublicData::GetInst()->GetCrystal()).c_str());

}

void CLobbyEquipmemtUI::PostUpdate(float DeltaTime)
{
	CWidgetWindow::PostUpdate(DeltaTime);
}

void CLobbyEquipmemtUI::Render()
{
	CWidgetWindow::Render();
}

CLobbyEquipmemtUI* CLobbyEquipmemtUI::Clone()
{
	return new CLobbyEquipmemtUI(*this);
}


void CLobbyEquipmemtUI::BtnBackCallback()
{
	CSound* Sound = m_Scene->GetResource()->FindSound2D("ButtonClick");
	Sound->Play();
	CUIManager::GetInst()->FindWidgetWindow("LobbyMainUI")->Enable(true);
	Enable(false);
	Vector3 Pos = CLobbyManager::GetInst()->GetShipCameraPos();
	m_Scene->GetCameraManager()->GetCurrentCamera()->SetWorldPos(Pos);
}

void CLobbyEquipmemtUI::BtnWeaponInventoryCallback()
{
	CSound* Sound = m_Scene->GetResource()->FindSound2D("ButtonClick");
	Sound->Play();
	m_BtnWeaponInventory->SetStateTexture(Button_State::Click, "UI_Btn_Blue", TEXT("UI/Share/UI_Btn_Blue.png"));
	m_BtnWeaponInventory->SetStateTexture(Button_State::Normal, "UI_Btn_Blue", TEXT("UI/Share/UI_Btn_Blue.png"));
	m_BtnWeaponInventory->SetStateTexture(Button_State::MouseOn, "UI_Btn_Blue", TEXT("UI/Share/UI_Btn_Blue.png"));
	m_BtnWeaponInventory->SetStateTexture(Button_State::Disabled, "UI_Btn_Blue", TEXT("UI/Share/UI_Btn_Blue.png"));

	m_BtnUpgradeItemInventory->SetStateTexture(Button_State::Normal, "UI_Btn_BlueAlpha", TEXT("UI/Share/UI_Btn_BlueAlpha.png"));
	m_BtnUpgradeItemInventory->SetStateTexture(Button_State::MouseOn, "UI_Btn_BlueAlpha", TEXT("UI/Share/UI_Btn_BlueAlpha.png"));
	m_BtnUpgradeItemInventory->SetStateTexture(Button_State::Disabled, "UI_Btn_BlueAlpha", TEXT("UI/Share/UI_Btn_BlueAlpha.png"));
	m_BtnUpgradeItemInventory->SetStateTexture(Button_State::Click, "UI_Btn_Blue", TEXT("UI/Share/UI_Btn_Blue.png"));
	m_Weapon = true;
	m_UpgradeItem = false;

	size_t Size = m_vecWeaponItemInfo.size();
	for (size_t i = 0; i < Size; ++i)
	{
		m_vecWeaponItemInfo[i].Enable(true);
	}
	Size = m_vecUpgradeItemInfo.size();
	for (size_t i = 0; i < Size; ++i)
	{
		m_vecUpgradeItemInfo[i].Enable(false);
	}

}

void CLobbyEquipmemtUI::BtnUpgradeItemInventoryCallback()
{
	CSound* Sound = m_Scene->GetResource()->FindSound2D("ButtonClick");
	Sound->Play();
	m_BtnWeaponInventory->SetStateTexture(Button_State::Click, "UI_Btn_BlueAlpha", TEXT("UI/Share/UI_Btn_BlueAlpha.png"));
	m_BtnWeaponInventory->SetStateTexture(Button_State::Normal, "UI_Btn_BlueAlpha", TEXT("UI/Share/UI_Btn_BlueAlpha.png"));
	m_BtnWeaponInventory->SetStateTexture(Button_State::MouseOn, "UI_Btn_BlueAlpha", TEXT("UI/Share/UI_Btn_BlueAlpha.png"));
	m_BtnWeaponInventory->SetStateTexture(Button_State::Disabled, "UI_Btn_Blue", TEXT("UI/Share/UI_Btn_Blue.png"));

	m_BtnUpgradeItemInventory->SetStateTexture(Button_State::Normal, "UI_Btn_Blue", TEXT("UI/Share/UI_Btn_Blue.png"));
	m_BtnUpgradeItemInventory->SetStateTexture(Button_State::MouseOn, "UI_Btn_Blue", TEXT("UI/Share/UI_Btn_Blue.png"));
	m_BtnUpgradeItemInventory->SetStateTexture(Button_State::Disabled, "UI_Btn_Blue", TEXT("UI/Share/UI_Btn_Blue.png"));
	m_BtnUpgradeItemInventory->SetStateTexture(Button_State::Click, "UI_Btn_Blue", TEXT("UI/Share/UI_Btn_Blue.png"));

	m_Weapon = false;
	m_UpgradeItem = true;

	size_t Size = m_vecWeaponItemInfo.size();
	for (size_t i = 0; i < Size; ++i)
	{
		m_vecWeaponItemInfo[i].Enable(false);
	}
	Size = m_vecUpgradeItemInfo.size();
	for (size_t i = 0; i < Size; ++i)
	{
		m_vecUpgradeItemInfo[i].Enable(true);
	}
}

void CLobbyEquipmemtUI::BtnWeaponCallback()
{
	CSound* Sound = m_Scene->GetResource()->FindSound2D("ButtonClick");
	Sound->Play();
	size_t Size = m_vecWeaponItemInfo.size();
	for (size_t i = 0; i < Size; i++)
	{
		if (m_vecWeaponItemInfo[i].Button->IsClick())
		{

			CLobbyWeaponInfoUI* InfoUI = (CLobbyWeaponInfoUI*)CUIManager::GetInst()->FindWidgetWindow("LobbyWeaponInfoUI");
			InfoUI->SetItemData(m_vecWeaponItemInfo[i].Status);
			InfoUI->SetEquip();
			InfoUI->Enable(true);
			Enable(false);
			return;
		}
	}
}

void CLobbyEquipmemtUI::BtnUpgradeItemCallback()
{
	size_t Size = m_vecUpgradeItemInfo.size();
	for (size_t i = 0; i < Size; i++)
	{
		if (m_vecUpgradeItemInfo[i].Button->IsClick())
		{
			//정보를 받아와서화면 업데이트
			CLobbyItemInfoDialog* LobbyItemInfoDialog =(CLobbyItemInfoDialog*)CUIManager::GetInst()->FindWidgetWindow("LobbyItemInfoDialog");
			LobbyItemInfoDialog->SetItemInfoDialog(stringToWstring(m_vecUpgradeItemInfo[i].Status->Name).c_str(), m_vecUpgradeItemInfo[i].ItemImage->GetTexture(),
				stringToWstring(m_vecUpgradeItemInfo[i].Status->Info).c_str(), m_vecUpgradeItemInfo[i].Status->Count);
			LobbyItemInfoDialog->Enable(true);
			return;
		}
	}
}
