#pragma once

// partial credits for minifying these classes goes to cleric @ ateris.tech

// ================
// dt_common.hpp
// ================
typedef enum {
  DPT_Int = 0,
  DPT_Float,
  DPT_Vector,
  DPT_VectorXY,
  DPT_String,
  DPT_Array,
  DPT_DataTable,
  DPT_NUMSendPropTypes
} SendPropType;

class DVariant {
public:
  DVariant() { m_Type = DPT_Float; }
  DVariant(float val) {
    m_Type = DPT_Float;
    m_Float = val;
  }

  union {
    float       m_Float;
    int         m_Int;
    const char* m_pString;
    void*       m_pData; // For DataTables.
    float       m_Vector[3];
  };
  SendPropType m_Type;
};

// ================
// dt_recv.hpp
// ================

class RecvTable;
class RecvProp;
class CRecvProxyData {
public:
  const RecvProp* m_pRecvProp; // The property it's receiving.
  DVariant        m_Value;     // The value given to you to store.
  int             m_iElement;  // Which array element you're getting.
  int             m_ObjectID;  // The object being referred to.
};

class CRecvDecoder;

typedef void (*RecvVarProxyFn)(const CRecvProxyData* pData, void* pStruct, void* pOut);
typedef void (*ArrayLengthRecvProxyFn)(void* pStruct, int objectID, int currentArrayLength);
typedef void (*DataTableRecvVarProxyFn)(const RecvProp* pProp, void** pOut, void* pData,
                                        int objectID);

class RecvProp {
public:
  const char*             m_pVarName;
  SendPropType            m_RecvType;
  int                     m_Flags;
  int                     m_StringBufferSize;
  bool                    m_bInsideArray;

  const void*             m_pExtraData;

  RecvProp*               m_pArrayProp;
  ArrayLengthRecvProxyFn  m_ArrayLengthProxy;

  RecvVarProxyFn          m_ProxyFn;
  DataTableRecvVarProxyFn m_DataTableProxyFn;

  RecvTable*              m_pDataTable;
  int                     m_Offset;

  int                     m_ElementStride;
  int                     m_nElements;

  const char*             m_pParentArrayPropName;
};

class RecvTable {
public:
  typedef RecvProp PropType;

  RecvProp*        m_pProps;
  int              m_nProps;
  CRecvDecoder*    m_pDecoder;
  const char*      m_pNetTableName;

  bool             m_bInitialized;
  bool             m_bInMainList;
};

// ================
// Class IDs
// ================
enum struct e_class_ids : int {
  CAI_BaseNPC,
  CBaseAnimating,
  CBaseAnimatingOverlay,
  CBaseAttributableItem,
  CBaseCombatCharacter,
  CBaseCombatWeapon,
  CBaseDoor,
  CBaseEntity,
  CBaseFlex,
  CBaseGrenade,
  CBaseObject,
  CBaseObjectUpgrade,
  CBaseParticleEntity,
  CBasePlayer,
  CBaseProjectile,
  CBasePropDoor,
  CBaseTeamObjectiveResource,
  CBaseTempEntity,
  CBaseViewModel,
  CBeam,
  CBoneFollower,
  CBonusDuckPickup,
  CBonusPack,
  CBonusRoundLogic,
  CBreakableProp,
  CBreakableSurface,
  CCaptureFlag,
  CCaptureFlagReturnIcon,
  CCaptureZone,
  CColorCorrection,
  CColorCorrectionVolume,
  CCurrencyPack,
  CDynamicLight,
  CDynamicProp,
  CEconEntity,
  CEconWearable,
  CEmbers,
  CEntityDissolve,
  CEntityFlame,
  CEntityParticleTrail,
  CEnvDetailController,
  CEnvParticleScript,
  CEnvProjectedTexture,
  CEnvQuadraticBeam,
  CEnvScreenEffect,
  CEnvScreenOverlay,
  CEnvTonemapController,
  CEnvWind,
  CEyeballBoss,
  CFireSmoke,
  CFireTrail,
  CFish,
  CFogController,
  CFunc_Dust,
  CFunc_LOD,
  CFuncAreaPortalWindow,
  CFuncConveyor,
  CFuncForceField,
  CFuncLadder,
  CFuncMonitor,
  CFuncOccluder,
  CFuncPasstimeGoal,
  CFuncReflectiveGlass,
  CFuncRespawnRoom,
  CFuncRespawnRoomVisualizer,
  CFuncRotating,
  CFuncSmokeVolume,
  CFuncTrackTrain,
  CGameRulesProxy,
  CHalloweenGiftPickup,
  CHalloweenPickup,
  CHalloweenSoulPack,
  CHandleTest,
  CHeadlessHatman,
  CHightower_TeleportVortex,
  CInfoLadderDismount,
  CInfoLightingRelative,
  CInfoOverlayAccessor,
  CLaserDot,
  CLightGlow,
  CMannVsMachineStats,
  CMaterialModifyControl,
  CMerasmus,
  CMerasmusDancer,
  CMonsterResource,
  CObjectCartDispenser,
  CObjectDispenser,
  CObjectSapper,
  CObjectSentrygun,
  CObjectTeleporter,
  CParticleFire,
  CParticlePerformanceMonitor,
  CParticleSystem,
  CPasstimeBall,
  CPasstimeGun,
  CPhysBox,
  CPhysBoxMultiplayer,
  CPhysicsProp,
  CPhysicsPropMultiplayer,
  CPhysMagnet,
  CPlasma,
  CPlayerDestructionDispenser,
  CPlayerResource,
  CPointCamera,
  CPointCommentaryNode,
  CPointWorldText,
  CPoseController,
  CPrecipitation,
  CPropVehicleDriveable,
  CRagdollManager,
  CRagdollProp,
  CRagdollPropAttached,
  CRobotDispenser,
  CRopeKeyframe,
  CSceneEntity,
  CShadowControl,
  CSlideshowDisplay,
  CSmokeStack,
  CSniperDot,
  CSpotlightEnd,
  CSprite,
  CSpriteOriented,
  CSpriteTrail,
  CSteamJet,
  CSun,
  CTeam,
  CTeamplayRoundBasedRulesProxy,
  CTeamRoundTimer,
  CTeamTrainWatcher,
  CTEArmorRicochet,
  CTEBaseBeam,
  CTEBeamEntPoint,
  CTEBeamEnts,
  CTEBeamFollow,
  CTEBeamLaser,
  CTEBeamPoints,
  CTEBeamRing,
  CTEBeamRingPoint,
  CTEBeamSpline,
  CTEBloodSprite,
  CTEBloodStream,
  CTEBreakModel,
  CTEBSPDecal,
  CTEBubbles,
  CTEBubbleTrail,
  CTEClientProjectile,
  CTEDecal,
  CTEDust,
  CTEDynamicLight,
  CTEEffectDispatch,
  CTEEnergySplash,
  CTEExplosion,
  CTEFireBullets,
  CTEFizz,
  CTEFootprintDecal,
  CTEGaussExplosion,
  CTEGlowSprite,
  CTEImpact,
  CTEKillPlayerAttachments,
  CTELargeFunnel,
  CTeleportVortex,
  CTEMetalSparks,
  CTEMuzzleFlash,
  CTEParticleSystem,
  CTEPhysicsProp,
  CTEPlayerAnimEvent,
  CTEPlayerDecal,
  CTEProjectedDecal,
  CTEShatterSurface,
  CTEShowLine,
  CTesla,
  CTESmoke,
  CTESparks,
  CTESprite,
  CTESpriteSpray,
  CTest_ProxyToggle_Networkable,
  CTestTraceline,
  CTETFBlood,
  CTETFExplosion,
  CTETFParticleEffect,
  CTEWorldDecal,
  CTFAmmoPack,
  CTFBall_Ornament,
  CTFBaseBoss,
  CTFBaseProjectile,
  CTFBaseRocket,
  CTFBat,
  CTFBat_Fish,
  CTFBat_Giftwrap,
  CTFBat_Wood,
  CTFBonesaw,
  CTFBotHintEngineerNest,
  CTFBottle,
  CTFBreakableMelee,
  CTFBreakableSign,
  CTFBuffItem,
  CTFCannon,
  CTFChargedSMG,
  CTFCleaver,
  CTFClub,
  CTFCompoundBow,
  CTFCrossbow,
  CTFDRGPomson,
  CTFDroppedWeapon,
  CTFFireAxe,
  CTFFists,
  CTFFlameManager,
  CTFFlameRocket,
  CTFFlameThrower,
  CTFFlareGun,
  CTFFlareGun_Revenge,
  CTFGameRulesProxy,
  CTFGasManager,
  CTFGenericBomb,
  CTFGlow,
  CTFGrapplingHook,
  CTFGrenadeLauncher,
  CTFGrenadePipebombProjectile,
  CTFHalloweenMinigame,
  CTFHalloweenMinigame_FallingPlatforms,
  CTFHellZap,
  CTFItem,
  CTFJar,
  CTFJarGas,
  CTFJarMilk,
  CTFKatana,
  CTFKnife,
  CTFLaserPointer,
  CTFLunchBox,
  CTFLunchBox_Drink,
  CTFMechanicalArm,
  CTFMedigunShield,
  CTFMiniGame,
  CTFMinigameLogic,
  CTFMinigun,
  CTFObjectiveResource,
  CTFParachute,
  CTFParachute_Primary,
  CTFParachute_Secondary,
  CTFParticleCannon,
  CTFPasstimeLogic,
  CTFPEPBrawlerBlaster,
  CTFPipebombLauncher,
  CTFPistol,
  CTFPistol_Scout,
  CTFPistol_ScoutPrimary,
  CTFPistol_ScoutSecondary,
  CTFPlayer,
  CTFPlayerDestructionLogic,
  CTFPlayerResource,
  CTFPointManager,
  CTFPowerupBottle,
  CTFProjectile_Arrow,
  CTFProjectile_BallOfFire,
  CTFProjectile_Cleaver,
  CTFProjectile_EnergyBall,
  CTFProjectile_EnergyRing,
  CTFProjectile_Flare,
  CTFProjectile_GrapplingHook,
  CTFProjectile_HealingBolt,
  CTFProjectile_Jar,
  CTFProjectile_JarGas,
  CTFProjectile_JarMilk,
  CTFProjectile_MechanicalArmOrb,
  CTFProjectile_Rocket,
  CTFProjectile_SentryRocket,
  CTFProjectile_SpellBats,
  CTFProjectile_SpellFireball,
  CTFProjectile_SpellKartBats,
  CTFProjectile_SpellKartOrb,
  CTFProjectile_SpellLightningOrb,
  CTFProjectile_SpellMeteorShower,
  CTFProjectile_SpellMirv,
  CTFProjectile_SpellPumpkin,
  CTFProjectile_SpellSpawnBoss,
  CTFProjectile_SpellSpawnHorde,
  CTFProjectile_SpellSpawnZombie,
  CTFProjectile_SpellTransposeTeleport,
  CTFProjectile_Throwable,
  CTFProjectile_ThrowableBreadMonster,
  CTFProjectile_ThrowableBrick,
  CTFProjectile_ThrowableRepel,
  CTFPumpkinBomb,
  CTFRagdoll,
  CTFRaygun,
  CTFReviveMarker,
  CTFRevolver,
  CTFRobotArm,
  CTFRobotDestruction_Robot,
  CTFRobotDestruction_RobotGroup,
  CTFRobotDestruction_RobotSpawn,
  CTFRobotDestructionLogic,
  CTFRocketLauncher,
  CTFRocketLauncher_AirStrike,
  CTFRocketLauncher_DirectHit,
  CTFRocketLauncher_Mortar,
  CTFRocketPack,
  CTFScatterGun,
  CTFShotgun,
  CTFShotgun_HWG,
  CTFShotgun_Pyro,
  CTFShotgun_Revenge,
  CTFShotgun_Soldier,
  CTFShotgunBuildingRescue,
  CTFShovel,
  CTFSlap,
  CTFSMG,
  CTFSniperRifle,
  CTFSniperRifleClassic,
  CTFSniperRifleDecap,
  CTFSodaPopper,
  CTFSpellBook,
  CTFStickBomb,
  CTFStunBall,
  CTFSword,
  CTFSyringeGun,
  CTFTankBoss,
  CTFTauntProp,
  CTFTeam,
  CTFThrowable,
  CTFViewModel,
  CTFWeaponBase,
  CTFWeaponBaseGrenadeProj,
  CTFWeaponBaseGun,
  CTFWeaponBaseMelee,
  CTFWeaponBaseMerasmusGrenade,
  CTFWeaponBuilder,
  CTFWeaponFlameBall,
  CTFWeaponInvis,
  CTFWeaponPDA,
  CTFWeaponPDA_Engineer_Build,
  CTFWeaponPDA_Engineer_Destroy,
  CTFWeaponPDA_Spy,
  CTFWeaponPDAExpansion_Dispenser,
  CTFWeaponPDAExpansion_Teleporter,
  CTFWeaponSapper,
  CTFWearable,
  CTFWearableCampaignItem,
  CTFWearableDemoShield,
  CTFWearableItem,
  CTFWearableLevelableItem,
  CTFWearableRazorback,
  CTFWearableRobotArm,
  CTFWearableVM,
  CTFWrench,
  CVGuiScreen,
  CVoteController,
  CWaterBullet,
  CWaterLODControl,
  CWeaponIFMBase,
  CWeaponIFMBaseCamera,
  CWeaponIFMSteadyCam,
  CWeaponMedigun,
  CWorld,
  CZombie,
  DustTrail,
  MovieExplosion,
  NextBotCombatCharacter,
  ParticleSmokeGrenade,
  RocketTrail,
  SmokeTrail,
  SporeExplosion,
  SporeTrail,
};

// ================
// client_class.hpp
// ================
typedef void* (*CreateClientClassFn)(int entnum, int serialNum);
typedef void* (*CreateEventFn)();
class ClientClass {
public:
  CreateClientClassFn m_pCreateFn;
  CreateEventFn       m_pCreateEventFn; // Only called for event objects.
  const char*         m_pNetworkName;
  RecvTable*          m_pRecvTable;
  ClientClass*        m_pNext;
  int                 m_ClassID; // Managed by the engine.

  e_class_ids get_class() {
    return static_cast<e_class_ids>(m_ClassID);
  }
};