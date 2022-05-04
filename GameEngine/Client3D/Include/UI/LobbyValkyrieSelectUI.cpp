
#include "LobbyValkyrieSelectUI.h"
#include "UI/Image.h"
#include "UI/Button.h"
#include <Device.h>
#include "../Object/Player.h"
#include "UIManager.h"
#include "Resource/Animation.h"
#include "../PublicData.h"
#include "Scene/SceneManager.h"
#include "../PublicData.h"
#include "../DataTable/PlayerDataTable.h"
#include "Device.h"
#include "../LobbyManager.h"
#include "Scene/Scene.h"
#include "Scene/CameraManager.h"
#include "LobbyValkyrieInfoUI.h"
#include "../Object/LobbyValkyrieSelectZone.h"
#include "LobbyWeaponInfoUI.h"
#include "../DataTable/ItemDataTable.h"
CLobbyValkyrieSelectUI::CLobbyValkyrieSelectUI():
	m_CurValkyrja(0)
{
}

CLobbyValkyrieSelectUI::CLobbyValkyrieSelectUI(const CLobbyValkyrieSelectUI& widget) :
	CWidgetWindow(widget)
{
	m_CurValkyrja = widget.m_CurValkyrja;
}

CLobbyValkyrieSelectUI::~CLobbyValkyrieSelectUI()
{
}

void CLobbyValkyrieSelectUI::Start()
{
	CWidgetWindow::Start();
	//첫번째 캐릭터 자동 선택
	PlayerStatus* Status = m_vecValkyrieInfo[0].Status;
	switch (Status->starType)
	{
	case StarType::B:
		m_ImgValkyrjaStar->SetTexture("Star_Avatar_1M", TEXT("UI/Character Select/Star Avatar/Star_Avatar_1M.png"));
		break;
	case StarType::A:
		m_ImgValkyrjaStar->SetTexture("Star_Avatar_2M", TEXT("UI/Character Select/Star Avatar/Star_Avatar_2M.png"));
		break;
	case StarType::S:
		m_ImgValkyrjaStar->SetTexture("Star_Avatar_3M", TEXT("UI/Character Select/Star Avatar/Star_Avatar_3M.png"));
		break;
	case StarType::SS:
		m_ImgValkyrjaStar->SetTexture("Star_Avatar_4M", TEXT("UI/Character Select/Star Avatar/Star_Avatar_4M.png"));
		break;
	case StarType::SSS:
		m_ImgValkyrjaStar->SetTexture("Star_Avatar_5M", TEXT("UI/Character Select/Star Avatar/Star_Avatar_5M.png"));
		break;
	}
	int Level = Status->Level;
	std::wstring str = TEXT("Lv.");
	str += std::to_wstring(Level);
	m_ValkyrjaLevelText->SetText(str.c_str());

	m_ValkyrjaNameText->SetText((Status->PlayerName).c_str());


	if (Status->Name == "Kiana")
	{
		m_WeaponNameText->SetText(TEXT("USP45"));
	}
	else if (Status->Name == "Sakura")
	{
		m_WeaponNameText->SetText(TEXT("세이슈 무라마사"));
	}
	CLobbyManager::GetInst()->ChangeValkyrieSelect(Status->Name);
}

bool CLobbyValkyrieSelectUI::Init()
{
	CWidgetWindow::Init();
	Resolution RS = CDevice::GetInst()->GetResolution();

	CImage* Image;
	//CImage* Image = CreateWidget<CImage>("BG_2");
	//Image->SetSize((float)RS.Width, (float)RS.Height);
	//Image->SetPos(0.f, 0.f);
	//Image->SetCollision(false);
	//Image->SetZOrder(1);
	//Image->SetTexture("BgPicSchool07", TEXT("UI/Character Select/BgPicSchool07.png"));
	//Image->SetColorTint(1.f, 1.f, 1.f, 1.f);
	//금화

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
	m_BtnBack->SetClickCallback<CLobbyValkyrieSelectUI>(this, &CLobbyValkyrieSelectUI::BtnBackCallback);

	CText* Text = CreateWidget<CText>("BackText");
	Text->SetPos(10.f, 660.f);
	Text->SetSize(100.f, 50.f);
	Text->SetFontSize(30.f);
	Text->SetCollision(false);
	Text->SetAlignH(TEXT_ALIGN_H::Left);
	Text->SetAlignV(TEXT_ALIGN_V::Bottom);
	Text->SetZOrder(3);
	Text->SetColor(0.f, 0.f, 0.f);
	Text->SetText(TEXT("< 뒤로"));
#pragma endregion

#pragma region ValkyrjaName


	Image = CreateWidget<CImage>("ValkyrjaNameImage");
	Image->SetPos(30.f, 550.f);
	Image->SetSize(440.f, 50.f);
	Image->SetCollision(false);
	Image->SetZOrder(2);
	Image->SetTexture("Energy_debris", TEXT("UI/Share/Energy_debris.png"));

	m_ValkyrjaNameText = CreateWidget<CText>("ValkyrjaNameText");
	m_ValkyrjaNameText->SetPos(50.f, 560.f);
	m_ValkyrjaNameText->SetSize(470.f, 50.f);
	m_ValkyrjaNameText->SetFontSize(30.f);
	m_ValkyrjaNameText->SetCollision(false);
	m_ValkyrjaNameText->SetAlignH(TEXT_ALIGN_H::Left);
	m_ValkyrjaNameText->SetAlignV(TEXT_ALIGN_V::Bottom);
	m_ValkyrjaNameText->SetZOrder(3);
#pragma endregion

#pragma region BtnLevel

	m_BtnValkyrjaLevel = CreateWidget<CButton>("BtnValkyrjaLevel");
	m_BtnValkyrjaLevel->SetPos(30.f, 440.f);
	m_BtnValkyrjaLevel->SetSize(440.f, 50.f);
	m_BtnValkyrjaLevel->SetCollision(true);
	m_BtnValkyrjaLevel->SetZOrder(2);
	m_BtnValkyrjaLevel->SetStateTexture(Button_State::Normal, "Energy_debris", TEXT("UI/Share/Energy_debris.png"));
	m_BtnValkyrjaLevel->SetStateTexture(Button_State::MouseOn, "Energy_debris", TEXT("UI/Share/Energy_debris.png"));
	m_BtnValkyrjaLevel->SetStateTexture(Button_State::Disabled, "Energy_debris", TEXT("UI/Share/Energy_debris.png"));
	m_BtnValkyrjaLevel->SetStateTexture(Button_State::Click, "Energy_debris", TEXT("UI/Share/Energy_debris.png"));
	m_BtnValkyrjaLevel->SetClickCallback<CLobbyValkyrieSelectUI>(this, &CLobbyValkyrieSelectUI::BtnValkyrjaLevelCallback);


	m_ImgValkyrjaStar = CreateWidget<CImage>("ImgValkyrjaStar");
	m_ImgValkyrjaStar->SetPos(60.f, 440.f);
	m_ImgValkyrjaStar->SetSize(52.f, 50.f);
	m_ImgValkyrjaStar->SetCollision(false);
	m_ImgValkyrjaStar->SetZOrder(3);
	m_ImgValkyrjaStar->SetTexture("Star_Avatar_5M", TEXT("UI/Character Select/Star Avatar/Star_Avatar_5M.png"));

	m_ValkyrjaLevelText = CreateWidget<CText>("ValkyrjaLevelText");
	m_ValkyrjaLevelText->SetPos(120.f, 445.f);
	m_ValkyrjaLevelText->SetSize(470.f, 50.f);
	m_ValkyrjaLevelText->SetFontSize(30.f);
	m_ValkyrjaLevelText->SetCollision(false);
	m_ValkyrjaLevelText->SetAlignH(TEXT_ALIGN_H::Left);
	m_ValkyrjaLevelText->SetAlignV(TEXT_ALIGN_V::Bottom);
	m_ValkyrjaLevelText->SetZOrder(3);
	m_ValkyrjaLevelText->SetText(TEXT(""));
#pragma endregion

#pragma region BtnWeapon
	
	m_BtnWeapon = CreateWidget<CButton>("BtnWeapon");
	m_BtnWeapon->SetPos(910.f, 550.f);
	m_BtnWeapon->SetSize(370.f, 50.f);
	m_BtnWeapon->SetCollision(true);
	m_BtnWeapon->SetZOrder(2);
	m_BtnWeapon->SetStateTexture(Button_State::Normal, "Energy_debris", TEXT("UI/Share/Energy_debris.png"));
	m_BtnWeapon->SetStateTexture(Button_State::MouseOn, "Energy_debris", TEXT("UI/Share/Energy_debris.png"));
	m_BtnWeapon->SetStateTexture(Button_State::Disabled, "Energy_debris", TEXT("UI/Share/Energy_debris.png"));
	m_BtnWeapon->SetStateTexture(Button_State::Click, "Energy_debris", TEXT("UI/Share/Energy_debris.png"));
	m_BtnWeapon->SetClickCallback<CLobbyValkyrieSelectUI>(this, &CLobbyValkyrieSelectUI::BtnWeaponCallback);

	Text = CreateWidget<CText>("WeaponText");
	Text->SetPos(930.f, 550.f);
	Text->SetSize(470.f, 50.f);
	Text->SetFontSize(30.f);
	Text->SetCollision(false);
	Text->SetAlignH(TEXT_ALIGN_H::Left);
	Text->SetAlignV(TEXT_ALIGN_V::Bottom);
	Text->SetZOrder(3);
	Text->SetText(TEXT("무기 /"));


	m_WeaponNameText = CreateWidget<CText>("WeaponNameText");
	m_WeaponNameText->SetPos(1030, 550.f);
	m_WeaponNameText->SetSize(470.f, 50.f);
	m_WeaponNameText->SetFontSize(30.f);
	m_WeaponNameText->SetCollision(false);
	m_WeaponNameText->SetAlignH(TEXT_ALIGN_H::Left);
	m_WeaponNameText->SetAlignV(TEXT_ALIGN_V::Bottom);
	m_WeaponNameText->SetZOrder(3);
	m_WeaponNameText->SetText(TEXT("대검temp"));
#pragma endregion

	std::unordered_map<std::string, PlayerStatus*>&  Data = CPublicData::GetInst()->GetPlayerDataTable()->GetDatas();

	auto iter = Data.begin();
	auto iterEnd = Data.end();

	for (int i=0; iter != iterEnd; ++iter, i++)
	{
		std::string str;
		str = std::to_string(i);
		CValkyrieImageButton* ValkyrieButton;
		ValkyrieButton = CreateWidget<CValkyrieImageButton>("ValkyrieSelectButton" + str);
		ValkyrieButton->SetSize(200.f, 180.f);
		ValkyrieButton->SetPos(10.f + 170.f * i, 50.f);
		ValkyrieButton->SetStateTexture(Button_State::Normal, "Character UI_AvatarIcon_Bg_Yellow", TEXT("UI/Character Select/Frame/UI_AvatarIcon_Bg_Yellow.png"));
		ValkyrieButton->SetStateTexture(Button_State::MouseOn, "UI_AvatarIcon_Bg_Yellow", TEXT("UI/Character Select/Frame/UI_AvatarIcon_Bg_Yellow.png"));
		ValkyrieButton->SetStateTexture(Button_State::Disabled, "Character UI_AvatarIcon_Bg_Yellow", TEXT("UI/Character Select/Frame/UI_AvatarIcon_Bg_Yellow.png"));
		ValkyrieButton->SetStateTexture(Button_State::Click, "UI_AvatarIcon_Bg_Yellow", TEXT("UI/Character Select/Frame/UI_AvatarIcon_Bg_Yellow.png"));
		ValkyrieButton->SetClickCallback(this, &CLobbyValkyrieSelectUI::BtnValkyrjaCallback);
		ValkyrieButton->SetZOrder(2);

		CImage* ImageStar = CreateWidget<CImage>("Valkyriestar" + str);
		ImageStar->SetSize(59.f, 48.f);
		ImageStar->SetPos(15.f + 170.f * i, 50.f);
		ImageStar->SetCollision(false);
		ImageStar->SetZOrder(3);

		CImage* ValkyrieImage = CreateWidget<CImage>("ValkyrieImage" + str);
		ValkyrieImage->SetSize(128.f, 120.f);
		ValkyrieImage->SetPos(50.f + 170.f * i, 100.f);
		ValkyrieImage->SetCollision(false);
		ValkyrieImage->SetZOrder(3);

		Text = CreateWidget<CText>("ValkyrieLevel" + str);
		Text->SetSize(59.f, 48.f);
		Text->SetPos(105.f + 170.f * i, 60.f);
		Text->SetFontSize(30.f);
		Text->SetCollision(false);
		Text->SetAlignH(TEXT_ALIGN_H::Left);
		Text->SetAlignV(TEXT_ALIGN_V::Bottom);
		Text->SetZOrder(3);
		Text->SetText(TEXT("Lv.3"));
		
		if (iter->second->Name == "Kiana")
		{
			ValkyrieImage->SetTexture("UI_AvaterIcon_Kiana_02", TEXT("UI/Character Select/Avatar Icon/UI_AvaterIcon_Kiana_02.png"));
		}
		else if (iter->second->Name == "Sakura")
		{
			ValkyrieImage->SetTexture("UI_AvaterIcon_Sakura_01", TEXT("UI/Character Select/Avatar Icon/UI_AvaterIcon_Sakura_01.png"));
		}

		ValkyrieInfo Info;
		Info.ValkyrieButton = ValkyrieButton;
		Info.Star = ImageStar;
		Info.ValkyrieImage = ValkyrieImage;
		Info.Level = Text;
		Info.Status = iter->second;
		m_vecValkyrieInfo.push_back(Info);
	}


	return true;
}

void CLobbyValkyrieSelectUI::Update(float DeltaTime)
{
	CWidgetWindow::Update(DeltaTime);
	ValkyrieInfoUpdate();
	m_CrystalText->SetText(std::to_wstring(CPublicData::GetInst()->GetCrystal()).c_str());
}

void CLobbyValkyrieSelectUI::PostUpdate(float DeltaTime)
{
	CWidgetWindow::PostUpdate(DeltaTime);
}

void CLobbyValkyrieSelectUI::Render()
{
	CWidgetWindow::Render();
}

CLobbyValkyrieSelectUI* CLobbyValkyrieSelectUI::Clone()
{
	return new CLobbyValkyrieSelectUI(*this);
}

void CLobbyValkyrieSelectUI::BtnValkyrjaCallback()
{
	CSound* Sound = m_Scene->GetResource()->FindSound2D("ButtonClick");
	Sound->Play();
	size_t Size = m_vecValkyrieInfo.size();
	for (size_t i = 0; i < Size; i++)
	{
		if (m_vecValkyrieInfo[i].ValkyrieButton->IsClick())
		{
			m_CurValkyrja = i;
			//정보를 받아와서화면 업데이트
			PlayerStatus* Status = m_vecValkyrieInfo[i].Status;
			switch (Status->starType)
			{
			case StarType::B:
				m_ImgValkyrjaStar->SetTexture("Star_Avatar_1M", TEXT("UI/Character Select/Star Avatar/Star_Avatar_1M.png"));
				break;
			case StarType::A:
				m_ImgValkyrjaStar->SetTexture("Star_Avatar_2M", TEXT("UI/Character Select/Star Avatar/Star_Avatar_2M.png"));
				break;
			case StarType::S:
				m_ImgValkyrjaStar->SetTexture("Star_Avatar_3M", TEXT("UI/Character Select/Star Avatar/Star_Avatar_3M.png"));
				break;
			case StarType::SS:
				m_ImgValkyrjaStar->SetTexture("Star_Avatar_4M", TEXT("UI/Character Select/Star Avatar/Star_Avatar_4M.png"));
				break;
			case StarType::SSS:
				m_ImgValkyrjaStar->SetTexture("Star_Avatar_5M", TEXT("UI/Character Select/Star Avatar/Star_Avatar_5M.png"));
				break;
			}
			int Level = Status->Level;
			std::wstring str = TEXT("Lv.");
			str += std::to_wstring(Level);
			m_ValkyrjaLevelText->SetText(str.c_str());

			m_ValkyrjaNameText->SetText((Status->PlayerName).c_str());
			CLobbyManager::GetInst()->ChangeValkyrieSelect(Status->Name);

			if (Status->Name == "Kiana")
			{
				m_WeaponNameText->SetText(TEXT("USP45"));
			}
			else if (Status->Name == "Sakura")
			{
				m_WeaponNameText->SetText(TEXT("세이슈 무라마사"));
			}
			return;
		}
	}
}

void CLobbyValkyrieSelectUI::BtnBackCallback()
{
	CSound* Sound = m_Scene->GetResource()->FindSound2D("ButtonClick");
	Sound->Play();
	CUIManager::GetInst()->FindWidgetWindow("LobbyMainUI")->Enable(true);
	Enable(false);
	Vector3 Pos = CLobbyManager::GetInst()->GetShipCameraPos();
	m_Scene->GetCameraManager()->GetCurrentCamera()->SetWorldPos(Pos);
}

void CLobbyValkyrieSelectUI::BtnValkyrjaLevelCallback()
{
	CSound* Sound = m_Scene->GetResource()->FindSound2D("ButtonClick");
	Sound->Play();
	Enable(false);
	CLobbyValkyrieInfoUI* InfoUI=(CLobbyValkyrieInfoUI*)CUIManager::GetInst()->FindWidgetWindow("LobbyValkyrieInfoUI");
	InfoUI->Enable(true);
	InfoUI->SetCurStatus(m_vecValkyrieInfo[m_CurValkyrja].Status);
	CLobbyManager::GetInst()->GetValkyrieSelectZone()->Valkyrie_Info();
}

void CLobbyValkyrieSelectUI::BtnWeaponCallback()
{
	CSound* Sound = m_Scene->GetResource()->FindSound2D("ButtonClick");
	Sound->Play();
	Enable(false);
	CLobbyWeaponInfoUI* InfoUI=(CLobbyWeaponInfoUI*)CUIManager::GetInst()->FindWidgetWindow("LobbyWeaponInfoUI");
	ItemData* Data=CPublicData::GetInst()->GetItemDataTable()->FindData(ItemType::Weapon ,m_vecValkyrieInfo[m_CurValkyrja].Status->WeaponName);
	InfoUI->SetItemData(Data);
	InfoUI->SetValkyrieSelect();
	InfoUI->Enable(true);
}

void CLobbyValkyrieSelectUI::ValkyrieInfoUpdate()
{
	size_t Size=m_vecValkyrieInfo.size();
	for (size_t i=0; i<Size; ++i)
	{

		CValkyrieImageButton* Button = m_vecValkyrieInfo[i].ValkyrieButton;
		CText* LevelText = m_vecValkyrieInfo[i].Level;
		CImage* Star = m_vecValkyrieInfo[i].Star;
		PlayerStatus* Status = m_vecValkyrieInfo[i].Status;
		switch (Status->starType)
		{
		case StarType::B:
			Star->SetTexture("Star_Avatar_1M", TEXT("UI/Character Select/Star Avatar/Star_Avatar_1M.png"));
			break;
		case StarType::A:
			Star->SetTexture("Star_Avatar_2M", TEXT("UI/Character Select/Star Avatar/Star_Avatar_2M.png"));
			break;
		case StarType::S:
			Star->SetTexture("Star_Avatar_3M", TEXT("UI/Character Select/Star Avatar/Star_Avatar_3M.png"));
			break;
		case StarType::SS:
			Star->SetTexture("Star_Avatar_4M", TEXT("UI/Character Select/Star Avatar/Star_Avatar_4M.png"));
			break;
		case StarType::SSS:
			Star->SetTexture("Star_Avatar_5M", TEXT("UI/Character Select/Star Avatar/Star_Avatar_5M.png"));
			break;
		}
		int Level=Status->Level;
		std::wstring str = TEXT("Lv.");
		str += std::to_wstring(Level);
		LevelText->SetText(str.c_str());
	}

	{
		PlayerStatus* Status = m_vecValkyrieInfo[m_CurValkyrja].Status;
		switch (Status->starType)
		{
		case StarType::B:
			m_ImgValkyrjaStar->SetTexture("Star_Avatar_1M", TEXT("UI/Character Select/Star Avatar/Star_Avatar_1M.png"));
			break;
		case StarType::A:
			m_ImgValkyrjaStar->SetTexture("Star_Avatar_2M", TEXT("UI/Character Select/Star Avatar/Star_Avatar_2M.png"));
			break;
		case StarType::S:
			m_ImgValkyrjaStar->SetTexture("Star_Avatar_3M", TEXT("UI/Character Select/Star Avatar/Star_Avatar_3M.png"));
			break;
		case StarType::SS:
			m_ImgValkyrjaStar->SetTexture("Star_Avatar_4M", TEXT("UI/Character Select/Star Avatar/Star_Avatar_4M.png"));
			break;
		case StarType::SSS:
			m_ImgValkyrjaStar->SetTexture("Star_Avatar_5M", TEXT("UI/Character Select/Star Avatar/Star_Avatar_5M.png"));
			break;
		}
		int Level = Status->Level;
		std::wstring str = TEXT("Lv.");
		str += std::to_wstring(Level);
		m_ValkyrjaLevelText->SetText(str.c_str());

		m_ValkyrjaNameText->SetText((Status->PlayerName).c_str());
		CLobbyManager::GetInst()->ChangeValkyrieSelect(Status->Name);

		if (Status->Name == "Kiana")
		{
			m_WeaponNameText->SetText(TEXT("USP45"));
		}
		else if (Status->Name == "Sakura")
		{
			m_WeaponNameText->SetText(TEXT("세이슈 무라마사"));
		}

	}
}
