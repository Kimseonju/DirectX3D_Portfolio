
#include "PlayerUI.h"
#include "UI/Image.h"
#include "UI/Button.h"
#include <Device.h>
#include "../Object/Player.h"
#include "UIManager.h"
#include "Resource/Animation.h"
#include "../PublicData.h"
#include "../Object/Player.h"
#include "../StageManager.h"
CPlayerUI::CPlayerUI()
{
}

CPlayerUI::CPlayerUI(const CPlayerUI& widget)
{
}

CPlayerUI::~CPlayerUI()
{
}

bool CPlayerUI::Init()
{
	CWidgetWindow::Init();

	m_MonsterHP = CreateWidget<CMultiProgressBar>("MonsterHPBar");
	m_MonsterHP->SetBarCount(3);
	m_MonsterHP->SetBackTint(255.f/255.f, 145.f/255.f, 65.f/255.f, 1.f);
	m_MonsterHP->SetTexture("UI_HPBar", TEXT("UI/In Game/UI_HPBar.png"));
	m_MonsterHP->SetBackTexture("UI_HPBar", TEXT("UI/In Game/UI_HPBar.png"));
	m_MonsterHP->SetTint(1.f, 0.f, 1.f, 1.f);
	m_MonsterHP->SetBackTint(0.1f, 0.1f, 0.1f, 0.5f);
	m_MonsterHP->SetPos(370.f, 695);
	m_MonsterHP->SetSize(160.f, 15.f);
	m_MonsterHP->SetCollision(false);
	m_MonsterHP->SetZOrder(2);

	m_MonsterName = CreateWidget<CText>("MonsterName");
	m_MonsterName->SetPos(765.f, 670.f);
	m_MonsterName->SetSize(150.f, 20.f);
	m_MonsterName->SetFontSize(20.f);
	m_MonsterName->SetCollision(false);
	m_MonsterName->SetText(TEXT("몬스터이름"));
	m_MonsterName->SetZOrder(2);
	m_MonsterName->SetAlignH(TEXT_ALIGN_H::Left);
	m_MonsterName->SetAlignV(TEXT_ALIGN_V::Bottom);

	m_Timer = CreateWidget<CText>("GameTimer");
	m_Timer->SetPos(1105.f, 680.f);
	m_Timer->SetSize(65.f, 30.f);
	m_Timer->SetFontSize(20.f);
	m_Timer->SetCollision(false);
	m_Timer->SetText(TEXT("00:00"));
	m_Timer->SetZOrder(2);
	m_Timer->SetAlignH(TEXT_ALIGN_H::Left);
	m_Timer->SetAlignV(TEXT_ALIGN_V::Bottom);

	m_Stick = CreateWidget<CImage>("Stick");
	m_Stick->SetPos(150.f, 150.f);
	m_Stick->SetSize(232.f, 232.f);
	m_Stick->SetCenter();
	m_Stick->SetCollision(false);
	m_Stick->SetZOrder(2);
	m_Stick->SetTexture("UI_MoveKey", TEXT("UI/In Game/UI_MoveKey.png"));


	m_HP = CreateWidget<CText>("HP");

	m_HP->SetPos(375.f, 50.f);
	m_HP->SetSize(150.f, 40.f);
	m_HP->SetFontSize(20.f);
	m_HP->SetCollision(false);
	m_HP->SetText(TEXT("66/66"));
	m_HP->SetZOrder(2);
	m_HP->SetAlignH(TEXT_ALIGN_H::Left);
	m_HP->SetAlignV(TEXT_ALIGN_V::Bottom);



	m_HPBar = CreateWidget<CMultiProgressBar>("HPBar");
	m_HPBar->SetBarCount(3);
	m_HPBar->SetTexture("UI_HPBar", TEXT("UI/In Game/UI_HPBar.png"));
	m_HPBar->SetBackTexture("UI_HPBar", TEXT("UI/In Game/UI_HPBar.png"));
	m_HPBar->SetTint(1.f, 1.f, 1.f, 1.f);
	m_HPBar->SetBackTint(0.1f, 0.1f, 0.1f, 0.5f);
	m_HPBar->SetPos(370.f, 40.f);
	m_HPBar->SetSize(160.f, 13.f);
	m_HPBar->SetCollision(false);
	m_HPBar->SetZOrder(2);

	m_SP = CreateWidget<CText>("SP");
	m_SP->SetPos(800.f, 10.f);
	m_SP->SetSize(55.f, 20.f);
	m_SP->SetFontSize(18.f);
	m_SP->SetCollision(false);
	m_SP->SetText(TEXT("66/66"));
	m_SP->SetZOrder(3);
	m_SP->SetAlignH(TEXT_ALIGN_H::Left);
	m_SP->SetAlignV(TEXT_ALIGN_V::Bottom);

	m_SPBar = CreateWidget<CProgressBar>("SPBar");
	m_SPBar->SetTexture("UI_CannonSpColor", TEXT("UI/In Game/UI_CannonSpColor.png"));
	m_HPBar->SetBackTint(0.1f, 0.1f, 0.1f, 0.5f);
	m_SPBar->SetTint(1.f, 1.f, 1.f, 0.6f);
	m_SPBar->SetPos(370.f, 20.f);
	m_SPBar->SetSize(420.f, 9.f);
	m_SPBar->SetCollision(false);
	m_SPBar->SetZOrder(2);


	m_EvadeImage = CreateWidget<CImage>("EvadeImage");
	m_EvadeImage->SetPos(1035.f, 60.f);
	m_EvadeImage->SetSize(80.f, 80.f);
	m_EvadeImage->SetCollision(false);
	m_EvadeImage->SetZOrder(3);
	m_EvadeImage->SetTexture("UI_Skill_Sakura_YS_003", TEXT("UI/In Game/UI_Skill_Sakura_YS_003.png"));
	
	m_EvadeButton = CreateWidget<CButton>("AttackButton");
	m_EvadeButton->SetPos(1030.f, 55.f);
	m_EvadeButton->SetSize(90.f, 90.f);
	m_EvadeButton->SetCollision(true);
	m_EvadeButton->SetZOrder(2);
	m_EvadeButton->SetStateTexture(Button_State::Normal, "UI_Attack", TEXT("UI/In Game/UI_Attack.png"));
	m_EvadeButton->SetStateTexture(Button_State::MouseOn, "UI_Attack", TEXT("UI/In Game/UI_Attack.png"));
	m_EvadeButton->SetStateTexture(Button_State::Disabled, "UI_Attack", TEXT("UI/In Game/UI_Attack.png"));
	m_EvadeButton->SetStateTexture(Button_State::Click, "UI_Attack_Active", TEXT("UI/In Game/UI_Attack_Active.png"));
	m_EvadeButton->SetClickCallback<CPlayerUI>(this, &CPlayerUI::EvadeBtnCallback);

	m_AttackImage = CreateWidget<CImage>("AttackImage");
	m_AttackImage->SetPos(1155.f, 60.f);
	m_AttackImage->SetSize(85.f, 85.f);
	m_AttackImage->SetCollision(false);
	m_AttackImage->SetZOrder(3);
	m_AttackImage->SetTexture("UI_Skill_Sakura_YS_001", TEXT("UI/In Game/UI_Skill_Sakura_YS_001.png"));

	m_AttackButton = CreateWidget<CButton>("AttackButton");
	m_AttackButton->SetPos(1150.f, 55.f);
	m_AttackButton->SetSize(95.f, 95.f);
	m_AttackButton->SetCollision(true);
	m_AttackButton->SetZOrder(2);
	m_AttackButton->SetStateTexture(Button_State::Normal, "UI_Attack", TEXT("UI/In Game/UI_Attack.png"));
	m_AttackButton->SetStateTexture(Button_State::MouseOn, "UI_Attack", TEXT("UI/In Game/UI_Attack.png"));
	m_AttackButton->SetStateTexture(Button_State::Disabled, "UI_Attack", TEXT("UI/In Game/UI_Attack.png"));
	m_AttackButton->SetStateTexture(Button_State::Click, "UI_Attack_Active", TEXT("UI/In Game/UI_Attack_Active.png"));
	m_AttackButton->SetClickCallback<CPlayerUI>(this, &CPlayerUI::AttackBtnCallback);

	m_UltraSkillImage = CreateWidget<CImage>("UltraSkillImage");
	m_UltraSkillImage->SetPos(1155.f, 180.f);
	m_UltraSkillImage->SetSize(90.f, 90.f);
	m_UltraSkillImage->SetCollision(false);
	m_UltraSkillImage->SetZOrder(3);
	m_UltraSkillImage->SetTexture("UI_Skill_Sakura_YS_004", TEXT("UI/In Game/UI_Skill_Sakura_YS_004.png"));
	
	m_UltraSkillButton = CreateWidget<CButton>("UltraSkillButton");
	m_UltraSkillButton->SetPos(1150.f, 175.f);
	m_UltraSkillButton->SetSize(100.f, 100.f);
	m_UltraSkillButton->SetCollision(true);
	m_UltraSkillButton->SetZOrder(2);
	m_UltraSkillButton->SetStateTexture(Button_State::Normal, "UI_Ult", TEXT("UI/In Game/UI_Ult.png"));
	m_UltraSkillButton->SetStateTexture(Button_State::MouseOn, "UI_Ult", TEXT("UI/In Game/UI_Ult.png"));
	m_UltraSkillButton->SetStateTexture(Button_State::Disabled, "UI_Ult", TEXT("UI/In Game/UI_Ult.png"));
	m_UltraSkillButton->SetStateTexture(Button_State::Click, "UI_Ult_Active", TEXT("UI/In Game/UI_Ult_Active.png"));
	m_UltraSkillButton->SetClickCallback<CPlayerUI>(this, &CPlayerUI::UltraSkillBtnCallback);
	//
	//m_SkillImage = CreateWidget<CImage>("SkillImage");
	//m_SkillImage->SetPos(1035.f, 180.f);
	//m_SkillImage->SetSize(70.f, 70.f);
	//m_SkillImage->SetCollision(false);
	//m_SkillImage->SetZOrder(3);
	//m_SkillImage->SetTexture("UI_Skill_Sakura_YS_004", TEXT("UI/In Game/UI_Skill_Sakura_YS_004.png"));
	//
	//m_SkillButton = CreateWidget<CButton>("SkillButton");
	//m_SkillButton->SetPos(1030.f, 175.f);
	//m_SkillButton->SetSize(80.f, 80.f);
	//m_SkillButton->SetCollision(true);
	//m_SkillButton->SetZOrder(2);
	//m_SkillButton->SetStateTexture(Button_State::Normal, "UI_Attack", TEXT("UI/In Game/UI_Attack.png"));
	//m_SkillButton->SetStateTexture(Button_State::MouseOn, "UI_Attack", TEXT("UI/In Game/UI_Attack.png"));
	//m_SkillButton->SetStateTexture(Button_State::Disabled, "UI_Attack", TEXT("UI/In Game/UI_Attack.png"));
	//m_SkillButton->SetStateTexture(Button_State::Click, "UI_Attack_Active", TEXT("UI/In Game/UI_Attack_Active.png"));
	//m_SkillButton->SetClickCallback<CPlayerUI>(this, &CPlayerUI::AttackBtnCallback);

	//발키리 체인지버튼
	m_BtnChangeValkyrie = CreateWidget<CButton>("BtnChangeValkyrie");
	m_BtnChangeValkyrie->SetPos(1184.f, 428.f);
	m_BtnChangeValkyrie->SetSize(80.f, 80.f);
	m_BtnChangeValkyrie->SetCollision(true);
	m_BtnChangeValkyrie->SetZOrder(2);
	m_BtnChangeValkyrie->SetStateTexture(Button_State::Normal, "AvatarButtonFrame", TEXT("UI/In Game/AvatarButtonFrame.png"));
	m_BtnChangeValkyrie->SetStateTexture(Button_State::MouseOn, "AvatarButtonFrame", TEXT("UI/In Game/AvatarButtonFrame.png"));
	m_BtnChangeValkyrie->SetStateTexture(Button_State::Disabled, "AvatarButtonFrame", TEXT("UI/In Game/AvatarButtonFrame.png"));
	m_BtnChangeValkyrie->SetStateTexture(Button_State::Click, "AvatarButtonFrame", TEXT("UI/In Game/AvatarButtonFrame.png"));
	m_BtnChangeValkyrie->SetClickCallback<CPlayerUI>(this, &CPlayerUI::BtnChangeValkyrieCallback);
	
	m_ImgChangeValkyrie = CreateWidget<CImage>("ImgChangeValkyrie");
	m_ImgChangeValkyrie->SetPos(1174.f, 433.f);
	m_ImgChangeValkyrie->SetSize(87.f, 90.f);
	m_ImgChangeValkyrie->SetCollision(false);
	m_ImgChangeValkyrie->SetZOrder(3);
	m_ImgChangeValkyrie->SetTexture("Sakura_Battle", TEXT("UI/In Game/Sakura_Battle.png"));

	//CImage* Image = CreateWidget<CImage>("Image");
	//Image->SetPos(1184.f, 458.f);
	//Image->SetSize(80.f, 80.f);
	//Image->SetCollision(false);
	//Image->SetZOrder(4);
	//Image->SetTexture("AvatarButtonHP_Bar", TEXT("UI/In Game/AvatarButtonHP_Bar.png"));

	return true;
}

void CPlayerUI::Update(float DeltaTime)
{
	CWidgetWindow::Update(DeltaTime);
	CPlayer* Player=CPublicData::GetInst()->GetCurPlayer();
	
	if (!Player)
		return;

	ClientClassType Type = Player->GetClientClassType();

	switch (Type)
	{
	case ClientClassType::Kiana:
	{
		//m_EvadeImage->SetTexture("UI_Skill_Sakura_YS_003", TEXT("UI/In Game/UI_Skill_Sakura_YS_003.tga"));
		m_AttackImage->SetTexture("Skill_Kiana_FX_001", TEXT("UI/In Game/Skill_Kiana_FX_001.tga"));
		m_UltraSkillImage->SetTexture("Skill_Kiana_FX_004", TEXT("UI/In Game/Skill_Kiana_FX_004.tga"));
		break;
	}
	case ClientClassType::Sakura:
	{
		m_EvadeImage->SetTexture("UI_Skill_Sakura_YS_003", TEXT("UI/In Game/UI_Skill_Sakura_YS_003.png"));
		m_AttackImage->SetTexture("UI_Skill_Sakura_YS_001", TEXT("UI/In Game/UI_Skill_Sakura_YS_001.png"));
		m_UltraSkillImage->SetTexture("UI_Skill_Sakura_YS_004", TEXT("UI/In Game/UI_Skill_Sakura_YS_004.png"));
		//m_SkillImage->SetTexture("UI_Skill_Sakura_YS_004", TEXT("UI/In Game/UI_Skill_Sakura_YS_004.png"));
		break;
	}
	}

	PlayerStatus* Status = Player->GetStatus();
	std::wstring wstr;
	wstr = std::to_wstring(Status->HP) + TEXT(" / ") + std::to_wstring(Status->HPMax);
	m_HP->SetText(wstr.c_str());
	wstr.clear();

	m_HPBar->SetPercent((float)Status->HP / (float)Status->HPMax);
	wstr = std::to_wstring(Status->SP) + TEXT(" / ") + std::to_wstring(Status->SPMax);
	m_SP->SetText(wstr.c_str());
	m_SPBar->SetPercent((float)Status->SP / (float)Status->SPMax);

	//조이스틱
	if (Player->IsKeyPush())
	{
		m_Stick->SetTexture("UI_MoveKeyClick", TEXT("UI/In Game/UI_MoveKeyClick.png"));
		m_Stick->SetRotation(Player->GetFinshMoveDirAngle()*-1.f+180.f);
	}
	else
	{
		m_Stick->SetTexture("UI_MoveKey", TEXT("UI/In Game/UI_MoveKey.png"));
		m_Stick->SetRotation(0.f);
	}
	//몬스터타겟
	CMonster* MonsterTarget = (CMonster*)Player->GetMonsterTarget();
	if (MonsterTarget)
	{
		m_MonsterHP->Enable(true);
		m_MonsterName->Enable(true);
		m_MonsterHP->SetPercent((float)MonsterTarget->GetHp() / (float)MonsterTarget->GetHpMax());

		std::string Name = MonsterTarget->GetName();
		std::wstring WhName;
		WhName.assign(Name.begin(), Name.end());

		m_MonsterName->SetText(WhName.c_str());
	}
	else
	{
		m_MonsterHP->Enable(false);
		m_MonsterName->Enable(false);
	}

	Player=CPublicData::GetInst()->GetNextPlayer();
	if (Player)
	{
		if (Player->GetStatus()->Name == "Kiana")
		{
			m_ImgChangeValkyrie->SetTexture("Kiana_Battle", TEXT("UI/In Game/Kiana_Battle.png"));
		}
		else if (Player->GetStatus()->Name == "Sakura")
		{
			m_ImgChangeValkyrie->SetTexture("Sakura_Battle", TEXT("UI/In Game/Sakura_Battle.png"));
		}
		else
		{
			m_ImgChangeValkyrie->Enable(false);
		}
	}
	else
	{
		m_ImgChangeValkyrie->Enable(false);
		m_BtnChangeValkyrie->Enable(false);
	}

	SetTimer((int)CStageManager::GetInst()->GetPlayTime());
}

void CPlayerUI::PostUpdate(float DeltaTime)
{
	CWidgetWindow::PostUpdate(DeltaTime);
}

void CPlayerUI::Render()
{
	CWidgetWindow::Render();
}

CPlayerUI* CPlayerUI::Clone()
{
	return new CPlayerUI(*this);
}

void CPlayerUI::SetTimer(int Time)
{
	int Minute = Time / 60.f;
	Time %= 60;
	std::wstring str;
	if (Minute < 10)
	{
		str += TEXT("0");
	}
	str += std::to_wstring(Minute)+TEXT(":");
	if (Time < 10)
	{
		str += TEXT("0");
	}
	str += std::to_wstring(Time);
	m_Timer->SetText(str.c_str());
}

void CPlayerUI::EvadeBtnCallback()
{
	CPlayer* Player = CPublicData::GetInst()->GetCurPlayer();
	Player->Evade(0);
}

void CPlayerUI::AttackBtnCallback()
{
	CPlayer* Player=CPublicData::GetInst()->GetCurPlayer();
	Player->Attack(0);
}

void CPlayerUI::UltraSkillBtnCallback()
{
	CPlayer* Player = CPublicData::GetInst()->GetCurPlayer();
	Player->UltraSkill(0);
}

void CPlayerUI::SkillBtnCallback()
{
}

void CPlayerUI::BtnChangeValkyrieCallback()
{
	CPlayer* NextPlayer = CPublicData::GetInst()->GetNextPlayer();
	CPlayer* pPlayer = CPublicData::GetInst()->GetCurPlayer();
	if (pPlayer == NextPlayer)
		return;

	pPlayer->PlayerWait();
	NextPlayer->PlayerAppear();
	NextPlayer->SetWorldPos(pPlayer->GetWorldPos());
	NextPlayer->SetWorldRotation(pPlayer->GetWorldRotation());
	CPublicData::GetInst()->SetCurPlayer(NextPlayer);
}
