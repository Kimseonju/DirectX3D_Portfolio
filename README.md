# DirectX3D Portfolio — 붕괴3rd 모작

DirectX 11 자체 엔진 기반 3D 액션 게임.
Player, Animation, Camera, UI, Editor, Effect 영역 전반 구현.

## 시연 영상

https://youtu.be/HO_MjW86Ys0

## 프로젝트 정보

| 항목    | 내용                                                                    |
| ----- | --------------------------------------------------------------------- |
| 프로젝트명 | 붕괴3rd 모작                                                              |
| 기간    | 2022.02 ~ 2022.04                                                     |
| 환경    | Visual Studio 2019                                                    |
| 도구    | DirectX 11, HLSL, DirectInput, FMOD, ImGui, ImGuizmo, ImGuiFileDialog |
| 협업    | Azure DevOps                                                          |
| 담당    | Player / Animation / Camera / UI / Editor / Effect                    |

## 씬 흐름

```
LoadingScene → LobbyScene → MainScene → StageScene1 / StageScene2
```

전환 시점에 `LoadingThread1` / `LoadingThread2`로 리소스를 비동기 로드.

---

# Player

## CPlayer 베이스 + FSM

플레이어 베이스 클래스. 자체 FSM에 상태별 핸들러를 등록.

```cpp
class CPlayer : public CClientObject
{
protected:
    CSharedPtr<CSceneComponent>         m_Root;
    CSharedPtr<CAnimationMeshComponent> m_Mesh;
    CSharedPtr<CStaticMeshComponent>    m_WeaponMesh;
    CSharedPtr<CStaticMeshComponent>    m_WeaponMesh2;
    CSharedPtr<CCamera>                 m_Camera;
    CSharedPtr<CSpringArm3D>            m_Arm;
    CSharedPtr<CColliderBox3D>          m_Body;
    CSharedPtr<CColliderBox3D>          m_EvadeBody;     // 회피 상태 콜리전
    CSharedPtr<CMonster>                m_Target;

    FSM<CPlayer> PlayerFSM;

    CPlayerAnimation* m_Animation;
    PlayerStatus*     m_PlayerStatus;
    PlayerState       m_State;
    int               m_AttackCombo;
    bool              m_AttackChargeCombo;
    float             m_CombatDelay;
    float             m_CombatDelayMax;
    bool              m_UltraSkillEffect1;
    bool              m_UltraSkillEffect2;
    bool              m_UltraSkillAttack;
    std::vector<PlayerDir> m_KeyPush;

public:
    // 입력 처리
    virtual void MoveFront(float Time);
    virtual void MoveBack(float Time);
    virtual void LeftMove(float Time);
    virtual void RightMove(float Time);
    virtual void Attack(float Time);
    virtual void UltraSkill(float Time);
    virtual void Evade(float Time);
    virtual void UltraSkillAttack();

    // FSM 상태별 Start / Stay / End 핸들러 (전체 12개 상태)
    virtual void IdleStart();      virtual void IdleStay();      virtual void IdleEnd();
    virtual void AttackStart();    virtual void AttackStay();    virtual void AttackEnd();
    virtual void MoveStart();      virtual void MoveStay();      virtual void MoveEnd();
    virtual void Hit_LStart();     virtual void Hit_LStay();     virtual void Hit_LEnd();
    virtual void Hit_HStart();     virtual void Hit_HStay();     virtual void Hit_HEnd();
    virtual void AppearStart();    virtual void AppearStay();    virtual void AppearEnd();
    virtual void CombatStart();    virtual void CombatStay();    virtual void CombatEnd();
    virtual void UltraSkillStart();virtual void UltraSkillStay();virtual void UltraSkillEnd();
    virtual void EvadeStart();     virtual void EvadeStay();     virtual void EvadeEnd();
    virtual void SwitchInStart();  ...   // 캐릭터 교체 진입
    virtual void SwitchOutStart(); ...   // 캐릭터 교체 퇴장
    virtual void VictoryStart();   ...
    virtual void VictoryIdleStart(); ...

    virtual void AnimationNotify(const std::string& Name);
};
```

- `FSM<CPlayer>` — 멤버 함수 포인터 기반 콜백 등록 FSM
- 상태별 `Start / Stay / End` 3-페이즈
- 콤보 카운트(`m_AttackCombo`) + 차지 콤보(`m_AttackChargeCombo`) + Combat 딜레이 관리
- 회피용 별도 콜리전 (`m_EvadeBody`)
- `AnimationNotify` — 애니메이션 키프레임 이벤트 콜백
- 캐릭터 교체(SwitchIn/Out) → 발키리 변경

## KianaPlayer (발키리 - 총기)

```cpp
class CKianaPlayer : public CPlayer
{
private:
    int m_IdleCount;
    CSharedPtr<CSceneComponent> m_LeftGunPoint;    // 좌측 총구
    CSharedPtr<CSceneComponent> m_RightGunPoint;   // 우측 총구

public:
    virtual void IdleStart();
    virtual void IdleStay();
    virtual void AnimationNotify(const std::string& Name);
};
```

- 양손 총기 캐릭터
- 좌/우 GunPoint 위치에서 총구 화염(`CKianaFire`) 스폰
- 다중 Idle 모션 (랜덤 / 카운트 기반)

## SakuraPlayer (발키리 - 검 + 트레일)

```cpp
class CSakuraPlayer : public CPlayer
{
private:
    CSharedPtr<CTrailComponent> m_TrailComponent;          // 일반 트레일
    CSharedPtr<CTrailComponent> m_TrailComponentCharge;    // 차지 트레일
    bool  m_PoseCopy;
    float m_PoseCopyTimer;

public:
    virtual void AttackStart();
    virtual void MoveStart();
    virtual void Hit_LStart();
    virtual void Hit_HStart();
    virtual void CombatStart();
    virtual void UltraSkillStart();
    virtual void EvadeStart();
    virtual void SwitchInStart();
    virtual void SwitchOutStart();
    virtual void VictoryStart();
    virtual void VictoryIdleStart();

    virtual void UltraSkillAttack();
    virtual void UltraSkillEffect1();
    virtual void UltraSkillEffect2();
};
```

- 검 캐릭터, **TrailComponent로 검 궤적 표현** (일반 / 차지 공격용 분리)
- **PoseCopy** — 궁극기 발동 시 잔상 효과 (타이머 기반)
- 거의 모든 상태에서 자체 Start 핸들러 오버라이드 — Kiana 대비 검 액션이 많음

---

# 적 캐릭터

## CMonster 베이스

플레이어 추적용 `m_Target`, 데미지 처리, 사망 시 PaperBurn 셰이더 페이드아웃 흐름을 공통화한 베이스.

## CWendy (보스)

```cpp
class CWendy : public CMonster
{
private:
    Wendy_State       m_State;
    Wendy_AttackState m_AttackState;
    int               m_RandomCount;
    FSM<CWendy>       m_FSM;

    CWendyAnimation*  m_Animation;
    CTornadoEffect*   m_Effect;

    // 사망 PaperBurn 7단계 컴포넌트
    CSharedPtr<CPaperBurnComponent> m_PaperBurn0;
    CSharedPtr<CPaperBurnComponent> m_PaperBurn1;
    // ... m_PaperBurn6

public:
    void CreateFSM();
    void IsFSMPlay(bool _Play);

    // Spawn / Idle / Move / AttackHub / Death
    void Wendy_Spawn_Start();      void Wendy_Spawn_Stay();      void Wendy_Spawn_End();
    void Wendy_Idle_Start();       void Wendy_Idle_Stay();       void Wendy_Idle_End();
    void Wendy_Move_Start();       void Wendy_Move_Stay();       void Wendy_Move_End();
    void Wendy_AttackHub_Start();  void Wendy_AttackHub_Stay();  void Wendy_AttackHub_End();
    void Wendy_Death_Start();      void Wendy_Death_Stay();      void Wendy_Death_End();
};
```

- `AttackHub` 상태에서 `m_AttackState` + `m_RandomCount`로 다음 스킬 선택
- 사망 시 7단계 `PaperBurn` 셰이더 컴포넌트로 부위별 페이드아웃
- 보스 전용 토네이도 이펙트 (`CTornadoEffect`) 보유

## CSniper (저격 적)

```cpp
class CSniper : public CMonster
{
private:
    FSM<CSniper>        m_FSM;
    CSniperAnimation*   m_Animation;
    Sniper_State        m_SniperCurState;
    Sniper_AttState     m_SniperCurAttState;
    Sniper_AttState     m_SniperPrevAttState;
    Sniper_AttState     m_NextAttack;
    Sniper_HitState     m_HitState;
    Sniper_HitAniState  m_HitAniState;

    CMonsterSpawnEffect* m_SpawnEffect;
    bool                 m_DeadGradientOn;
    float                m_DeadGradientTimer;

    CSharedPtr<CPaperBurnComponent> m_PaperBurn0;
    CSharedPtr<CPaperBurnComponent> m_PaperBurn1;
};
```

- 다중 enum 상태머신 — **현재/이전/다음 공격 상태** 분리 추적
- 히트 상태 (`HitState`) + 히트 애니메이션 상태 (`HitAniState`) 별개 관리
- 저격용 투사체: `CSniperBillet`, `CSniperGrenade`
- 사망 그라데이션 타이머 + PaperBurn 2단계

## CAxeSoldier (도끼 근접 적)

```cpp
class CAxeSoldier : public CMonster
{
private:
    FSM<CAxeSoldier>      m_FSM;
    CAxeSoldierAnimation* m_Animation;
    Axe_State             m_AxeCurState;
    Axe_AttState          m_AxeCurAttState;
    Axe_AttState          m_NextAttack;
    Axe_MoveState         m_MoveState;
    Axe_MoveState         m_BMoveState;       // 이전 이동 상태
    Axe_HitState          m_HitState;
    Axe_HitAniState       m_HitAniState;

    CSharedPtr<CColliderBox3D> m_AttackColl;   // 근접 공격 콜리전
    bool                       m_AttackRun;
    bool                       m_FAttackOn;

    CSharedPtr<CPaperBurnComponent> m_PaperBurn0;
    CSharedPtr<CPaperBurnComponent> m_PaperBurn1;
    CSharedPtr<CPaperBurnComponent> m_PaperBurn2;
};
```

- 근접 공격용 별도 콜리전 (`m_AttackColl`)
- 이동 상태(`MoveState`) + 직전 이동 상태(`BMoveState`) 분리 → 회피·반격 패턴
- 무기: `CAxe_Weapon` (본 소켓 부착)
- PaperBurn 3단계 사망 연출

---

# FSM (콜백 기반)

캐릭터·몬스터의 모든 행동을 자체 FSM으로 관리.
**상태 진입 / 유지 / 종료 시점에 멤버 함수를 콜백으로 등록**해 동작 실행.

```
캐릭터별 FSM:
 ├── FSM<CPlayer>        (PlayerFSM 내장)
 ├── FSM<CWendy>         (FSM_Wendy.cpp 핸들러 등록)
 ├── FSM<CSniper>        (FSM_Sniper.cpp)
 └── FSM<CAxeSoldier>    (FSM_AxeSoldier.cpp)
```

**핸들러 등록 패턴**: `Start / Stay / End` 3-페이즈 + AnimationNotify 콜백
**다음 상태 선택**: 현재/이전/다음 enum + RandomCount로 패턴 결정

---

# Animation (콜백 + Root Motion)

`CAnimation` 상속 + **종료 콜백 함수 포인터**를 노출하는 패턴.
캐릭터마다 별도 클래스로 분리 — `PlayerAnimation`, `WendyAnimation`, `SniperAnimation`, `AxeSoldierAnimation`.

```cpp
class CWendyAnimation : public CAnimation
{
public:
    class CWendy* m_Owner;
    void (CWendy::* m_AnimationEndFunc)(std::string);   // 종료 콜백 함수 포인터

    void SetAnimationEndFunc(void (CWendy::* EndFunc)(std::string))
    {
        m_AnimationEndFunc = EndFunc;
    }

    void AddAnimationSequence(
        const std::string& Name,
        bool Loop = false,
        int  iFrame = 60,
        bool RootMotion = false,
        int  RootLastFrame = 0,
        bool RootMotionX = false,
        bool RootMotionY = true,
        bool RootMotionZ = false);
};
```

- 애니메이션 종료 시점에 등록된 `m_AnimationEndFunc` 호출 → FSM 다음 상태 전환
- **Root Motion 옵션** — 본 위치 변화량을 캐릭터 트랜스폼에 반영

## Root Motion 흐름

```
이전 본 위치  →  현재 본 위치  →  차이만큼 캐릭터 이동
```

- `RootMotionX/Y/Z` 축별 ON/OFF
- `RootLastFrame` — Root Motion 종료 프레임 지정
- 검 휘두름·돌진·궁극기 등에서 애니메이션 데이터 그대로의 모션 거리 사용

---

# Camera

## PlayerMainCamera (추적 카메라)

```cpp
class CPlayerMainCamera : public CClientObject
{
protected:
    CCamera*                  m_Camera;
    class CPlayer*            m_Target;
    CSharedPtr<CClientObject> m_MonsterTarget;
    Vector3                   m_PrevTargetPos;
    Vector3                   m_Offset;
    float                     m_Length;

public:
    void SetTarget(CPlayer* Target);
    void SetLength(float Length)        { m_Length = Length; }
    void SetOffset(const Vector3& Off)  { m_Offset = Off; }

    void CameraWheel(float Time);       // 줌
    void MouseClick(float Time);
    void MouseRelease(float Time);

private:
    float Lerp(float percent, float max);
    float Lerp(float percent, float min, float max);
};
```

- 플레이어 위치 → Offset / Length 적용 → Lerp 보간
- 마우스 휠 줌, 우클릭 자유 회전
- 몬스터 타겟이 잡힌 경우 위치 추적 보조

## CameraMoveObject (시네마틱 카메라)

스폰 컷씬·궁극기 컷씬 등에서 카메라 위치/회전을 스크립트로 이동.
편집 도구로는 자체 에디터의 `IMGUICameraMoveComponent` 인스펙터 제공.

## PoseCopy (시네마틱 포즈 복사)

시네마틱 중 캐릭터의 본 포즈를 별도 액터로 복사 → 카메라 컷이 캐릭터에서 떨어져도 정지된 자세 유지.

---

# WorldToScreen

월드 좌표 기반 UI 위치 계산.

```
World Position
  → View × Projection  (카메라 좌표)
  → NDC 좌표 (Normalized Device Coordinates)
  → Screen 좌표
```

데미지 텍스트 위젯 예시:

```cpp
class CUIDamageText : public CWidgetWindow
{
private:
    CSharedPtr<CImage> m_Image100;    // 100의 자리
    CSharedPtr<CImage> m_Image10;     // 10의 자리
    CSharedPtr<CImage> m_Image1;      // 1의 자리
    Vector3            m_TargetPos;   // 월드 좌표
    float              m_Alpha;
    float              m_LifeTime;

public:
    virtual void Update(float DeltaTime);
    void SetDamage(int Damage);
    void SetTargetPos(const Vector3& Pos) { m_TargetPos = Pos; }
    void SetNumberImage(CImage* Image, int Number);
};
```

- `m_TargetPos`를 매 프레임 WorldToScreen 변환해 위젯 위치 갱신
- 자리수별 숫자 이미지 3장 합성 (100/10/1)
- `m_Alpha`와 `m_LifeTime`으로 페이드아웃

---

# Effect

`CGameObject` 베이스 + 종류별 이펙트 클래스.

| 클래스 | 표현 |
|---|---|
| `CExplosionEffect` | 폭발 |
| `CHitEffect` | 피격 |
| `CKnifeEffect` | 검 휘두름 트레일 (빌보드) |
| `CTornadoEffect` / `CTornadoTrailObject` | 토네이도 (Wendy 보스 전용) |
| `CMonsterSpawnEffect` | 몬스터 스폰 |
| `CKianaFire` | 총구 화염 (Kiana 발사 시) |
| `CDecalWind` | 바닥 바람 데칼 |
| `CDecalMonsterDir` | 몬스터 방향 표시 데칼 |

투사체 라이프사이클:
`CSniperBillet`, `CSniperGrenade`, `CWendy_AirBullet`

---

# Sword Trail (KnifeEffect)

검 휘두름 궤적 표현. 빌보드 + 2D 텍스처 시퀀스 애니메이션 기반.

```cpp
class CKnifeEffect : public CGameObject
{
protected:
    CSharedPtr<CBillboardComponent> m_Effect;
    CAnimation3D_Tex*               m_Animation;

    bool m_WendyAtt;
    bool m_AxeAtt;

public:
    void SetWendyAtt() { m_WendyAtt = true; }
    void SetAxeAtt()   { m_AxeAtt   = true; }

    void AddEffectPos(Vector3 Pos)
    {
        m_Effect->AddWorldPos(Pos);
    }

    void EffectDeath() { m_Enable = false; }
};
```

- `CBillboardComponent` + Y축 빌보드 모드 — 카메라 회전과 무관하게 검 궤적 노출
- `CAnimation3D_Tex` 시퀀스 — 트레일 텍스처 애니메이션
- 캐릭터(Wendy / Axe / 기본)별로 다른 베이스 컬러
- `AnimationNotify`에서 검 본 위치를 누적

SakuraPlayer는 별도로 `CTrailComponent` 두 개 (일반 / 차지)를 보유해 정밀한 검 궤적도 지원.

---

# Shader (붕괴3 카툰 렌더링)

붕괴3rd 스타일 캐릭터 표현을 위해 **Shadow Threshold 기반 카툰 렌더링** + Outline + FXAA를 적용.
에디터에서 체크박스로 각 효과를 런타임 ON/OFF 토글 가능하도록 구성.

| 효과 | 표현 |
|---|---|
| **Toon Shader** | 붕괴3 방식 — Shadow Threshold 가변 임계값 |
| **Outline** | 캐릭터 외곽선 |
| **FXAA** | Fast Approximate Anti-Aliasing |

> **참고 자료**
> - Unite 2018, Jack He — "붕괴3 렌더링" 강연
> - 마둠파 (Madumpa) 네이버 블로그 (2019.05.19) — 강연 분석 및 구현
>   `https://m.blog.naver.com/mnpshino/221541025516`

## 붕괴3 카툰 렌더링 핵심 아이디어

붕괴3 인게임 셰이더의 핵심은 **Lightmap (Mask 텍스처)** —
스펙큘러 정보와 Shadow Threshold를 RGB 채널에 압축해서 사용.

| 채널 | 역할 |
|---|---|
| **R** | Specular Glossiness (Power) — 한 재질 내 모든 픽셀에 동일 |
| **G** | **Shadow Threshold** — 픽셀별 명암 임계값 (중간 회색 0.5 베이스) |
| **B** | Specular Masking — 면이 꺾이는 부분 강조 |

일반적인 IF 기반 카툰 렌더링은 `HalfLambert < 0.5` 같은 **고정 임계값**으로 명암을 나누지만,
붕괴3는 **Lightmap의 G채널**에 픽셀별 임계값을 미리 그려두고 HalfLambert를 그 값과 비교.

```
일반 카툰:  if (HalfLambert < 0.5)             → 그림자
붕괴3 방식:  if (HalfLambert < LightmapG)       → 그림자
```

머리카락이 만드는 얼굴 그림자, 옷 주름의 음영 등을 임계값 텍스처로 직접 그려넣어
원하는 모양의 그림자를 컨트롤할 수 있는 게 핵심. 일부 노멀맵과 유사한 효과.

## 블로그 원본 코드 vs 본 프로젝트 적용

마둠파 블로그의 원본 (Forward Rendering, Unity HLSL):

```hlsl
half4 LightTex = tex2D(_LightTex, i.texcoord);
if (halfLambert < LightTex.g)
{
    MainTex *= _ShadowColor;
}
```

본 프로젝트는 **Deferred Rendering** 파이프라인이므로,
Lightmap의 G채널 값을 **GBuffer 5번의 W 채널**에 미리 저장해두고
라이트 패스에서 비교에 사용.

```
LightTex.g  ─→  GBuffer5.w   (Deferred Rendering 적용)
```

## 데이터 흐름

```
[에디터 체크박스]
        ↓ Callback
[CRenderManager::SetToonShader]
        ↓
[CPostProcessCBuffer::SetToonShader]   // m_BufferData.ToonShader = 0/1
        ↓ UpdateCBuffer
[HLSL: g_PostProcessToonShader]        // Light.fx 분기
        + GBuffer5.w (Shadow Threshold)
```

### 1. 에디터 체크박스 (`IMGUIRenderOptionComponent`)

```cpp
class CIMGUIRenderOptionComponent : public CIMGUIWidgetComponent
{
private:
    class CIMGUICheckBox* m_OutLine;
    class CIMGUICheckBox* m_ToonShader;
    class CIMGUICheckBox* m_FXAA;
    class CRenderManager* m_RenderManager;

public:
    void OutLineCheckBoxClick(bool Enable)   { m_RenderManager->SetOutLine(Enable); }
    void ToonShaderCheckBoxClick(bool Enable){ m_RenderManager->SetToonShader(Enable); }
    void FXAACheckBoxClick(bool Enable)      { m_RenderManager->SetFXAA(Enable); }
};
```

### 2. RenderManager — 런타임 셰이더 옵션 게이트웨이

```cpp
class CRenderManager
{
private:
    class CPostProcessCBuffer* m_PostProcessCBuffer;
public:
    void SetOutLine(bool Enable);
    void SetToonShader(bool Enable);
    void SetFXAA(bool Enable);
};
```

### 3. PostProcess CBuffer — 셰이더에 전달되는 데이터

```cpp
class CPostProcessCBuffer : public CConstantBufferData
{
public:
    void SetOutLine(bool Enable)    { m_BufferData.OutLine    = Enable ? 1 : 0; }
    void SetToonShader(bool Enable) { m_BufferData.ToonShader = Enable ? 1 : 0; }
    void SetFXAA(bool Enable)       { m_BufferData.FXAA       = Enable ? 1 : 0; }
    virtual void UpdateCBuffer();
};
```

### 4. HLSL — Shadow Threshold 비교 (`Light.fx`)

```hlsl
result.Dif = g_LightDiffuse * MtrlDif * Intensity * Attn;
result.Amb = g_LightAmbient * MtrlAmb * Attn;

if (g_PostProcessToonShader == 1)
{
    // GBuffer5.w = Shadow Threshold (붕괴3 Lightmap G채널 역할)
    if (result.Dif.x / 2.f > GBuffer5.w)
    {
        float Toon = GBuffer5.w;
        result.Dif = float4(GBuffer5.w, GBuffer5.w, GBuffer5.w, result.Dif.w);
        // ...
    }
}
```

- 일반 디퓨즈 라이팅 계산 후
- `g_PostProcessToonShader == 1`이면 **픽셀별 Shadow Threshold (`GBuffer5.w`)** 와 비교
- 임계값을 넘는지 여부로 명/암 영역 결정 → 끊어진 명암 표현
- 머리카락이 만드는 얼굴 그림자 등 디테일 컨트롤 가능

---

# UI

`UIManager`로 위젯 흐름 관리. 인게임 / 로비 / 가챠 풀세트.

## 인게임 (9종)

| 위젯 | 기능 |
|---|---|
| `PlayerUI` | 체력 / SP / 스킬 슬롯 |
| `PlayerHitComboUI` | 콤보 카운트 |
| `UIDamageText` | 데미지 텍스트 (WorldToScreen) |
| `TargetImageWidget` | 타겟 마커 |
| `Stage1StoryUI` | 스토리 컷씬 |
| `GameClearUI` | 게임 클리어 |
| `FadeInOutUI` / `FadeInOut_White` | 페이드 전환 |
| `LoadingUI` / `LoadingUI_Resource` | 로딩 화면 (멀티스레드 로딩과 연동) |

## 로비 / 가챠 / 육성 (12종)

| 위젯 | 기능 |
|---|---|
| `LobbyMainUI` | 로비 메인 화면 |
| `LobbyValkyrieSelectUI` / `LobbyValkyrieInfoUI` / `ValkyrieImageButton` | 캐릭터 선택·정보 |
| `LobbyStageSelectUI` | 스테이지 선택 |
| `LobbyEquipmemtUI` | 장비 화면 |
| `LobbyItemInfoDialog` | 아이템 상세 다이얼로그 |
| `LobbyWeaponInfoUI` / `LobbyWeaponLevelUpDialog` | 무기 정보·강화 |
| `LobbyLevelUpDialog` | 캐릭터 레벨업 |
| `LobbySupplyUI` / `LobbySupplyResultUI` | 보급 (가챠) 및 결과 |

---

# 자체 에디터 (GameEditor)

ImGui + ImGuizmo 기반 컴포넌트 인스펙터.
본 프로젝트용으로 추가한 인스펙터 5종:

| 인스펙터 | 용도 |
|---|---|
| `IMGUIRenderOptionComponent` | Toon Shader / Outline / FXAA ON/OFF 토글 (Shader 섹션 참조) |
| `IMGUIBossSpawnObjectComponent` | 보스 스폰 트리거 설정 (출현 조건·위치) |
| `IMGUIMonsterSpawnObjectComponent` | 일반 몬스터 스폰 설정 (몬스터 종류·수량·간격) |
| `IMGUIColliderSpawnObjectComponent` | 콜리전 스폰 트리거 설정 |
| `IMGUICameraMoveComponent` | 시네마틱 카메라 트랙 편집 (위치·회전·시간) |

---

# 보스 (Wendy) 스킬 패턴

`AttackHub` FSM 상태에서 `m_AttackState` + `m_RandomCount`로 다음 스킬 선택.
각 스킬은 별도 게임 오브젝트로 스폰.

| 스킬 액터 | 표현 |
|---|---|
| `Wendy_Storm` | 폭풍 광역기 |
| `Wendy_Brandish` | 검 휘두르기 (근접) |
| `Wendy_AirBall` + `Wendy_AirBullet` + `Wendy_AirBallEffect` + `Wendy_AirHitEffect` | 에어볼 발사 |
| `Wendy_AirHole` + `Wendy_AirHoleEffect` | 에어홀 (광역 흡입) |
| `Wendy_AirStar` | 에어 스타 (다단 히트) |
| `Wendy_Shoot` | 발사 패턴 |

스킬 발동 시 카메라 컷 (`CameraMoveObject`) + 토네이도 이펙트 (`CTornadoEffect`) 연동.

---

# 멀티스레드 리소스 로딩

씬 전환 시 별도 스레드에서 리소스 로드, 진행률을 `LoadingUI`로 표시해 로딩 끊김 제거.

```cpp
class CLoadingThread : public CThread
{
private:
    int m_LoadingCount;
    int m_LoadingMaxCount;

public:
    virtual void Run();         // 백그라운드 로딩 실행
    class CScene* nextScene;

    void  SetLoadingMaxCount(int Value) { m_LoadingMaxCount = Value; }
    void  SetLoadingCount(int num);
    float GetPersent() const;
    void  NextScene();
};
```

- `LoadingThread1`, `LoadingThread2` 분리해 단계별 로드
- `GetPersent()` 값을 `LoadingUI`에 전달해 진행률 표시
- 로드 완료 후 `NextScene()` 호출

---

# DataTable

```cpp
class CItemDataTable
{
private:
    std::unordered_map<ItemType, std::vector<ItemData*>> m_vecData;

public:
    void Init();
    std::vector<ItemData*>* FindvecData(ItemType Type);
    ItemData* FindData(ItemType Type, const std::string& Name);

    void AddExp(ItemType Type, const std::string& Name, int Exp);
    void AddItemCount(ItemType Type, const std::string& Name);
    void PushData(ItemData* Data);
};
```

- `unordered_map<ItemType, vector<ItemData*>>` — 타입별 아이템 그룹
- 강화 경험치 / 보유 수량 관리
- `CPlayerDataTable`도 동일 패턴 (캐릭터 레벨·스탯 관리)

---

# 매니저 / 맵 오브젝트

## 매니저

| 매니저 | 역할 |
|---|---|
| `CClientManager` | 클라이언트 전체 흐름 |
| `CLobbyManager` | 로비 상태 관리 (캐릭터 선택, 가챠 결과) |
| `CStageManager` | 스테이지 진행 (적 스폰 카운트, 보스 트리거) |
| `CUIManager` | UI 위젯 흐름 관리 |

## 맵 오브젝트

| 오브젝트 | 기능 |
|---|---|
| `MainLandScape` | 지형 |
| `MapCollision` | 맵 충돌체 |
| `MapItem` (`Coin` / `Heal` / `SPHeal`) | 픽업 아이템 |
| `BossSpawnObject` / `MonsterSpawnObject` / `ColliderSpawnObject` | 스폰 트리거 |
| `LobbyShip` / `LobbyValkyrieSelectZone` | 로비 오브젝트 |
| `LoadingStartObject` | 로딩 화면 진입 오브젝트 |

---

# 기술 스택

- C++, DirectX 11, HLSL
- FMOD, ImGui, ImGuizmo, ImGuiFileDialog
- 자체 FSM (멤버 함수 포인터 콜백) — 캐릭터·보스·잡몹별 분리
- AnimationEndFunc 콜백, Root Motion (RootMotionX/Y/Z)
- WorldToScreen UI 연동
- TrailComponent 기반 검 궤적 (SakuraPlayer)
- 붕괴3 Shadow Threshold 카툰 렌더링 (Deferred Rendering 통합)
- 멀티스레드 리소스 로딩 (CThread)
- ImGui 인스펙터 5종 자체 추가
