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
  CTFWearableRazorback = 340,
  CTFWearableDemoShield = 337,
  CTFWearableLevelableItem = 339,
  CTFWearableCampaignItem = 336,
  CTFBaseRocket = 184,
  CTFWeaponBaseMerasmusGrenade = 324,
  CTFWeaponBaseMelee = 323,
  CTFWeaponBaseGun = 322,
  CTFWeaponBaseGrenadeProj = 321,
  CTFWeaponBase = 320,
  CTFWearableRobotArm = 341,
  CTFRobotArm = 286,
  CTFWrench = 343,
  CTFProjectile_ThrowableBreadMonster = 278,
  CTFProjectile_ThrowableBrick = 279,
  CTFProjectile_ThrowableRepel = 280,
  CTFProjectile_Throwable = 277,
  CTFThrowable = 318,
  CTFSyringeGun = 314,
  CTFKatana = 224,
  CTFSword = 313,
  CSniperDot = 117,
  CTFSniperRifleClassic = 307,
  CTFSniperRifleDecap = 308,
  CTFSniperRifle = 306,
  CTFChargedSMG = 196,
  CTFSMG = 305,
  CTFSlap = 304,
  CTFShovel = 303,
  CTFShotgunBuildingRescue = 302,
  CTFPEPBrawlerBlaster = 240,
  CTFSodaPopper = 309,
  CTFShotgun_Revenge = 300,
  CTFScatterGun = 296,
  CTFShotgun_Pyro = 299,
  CTFShotgun_HWG = 298,
  CTFShotgun_Soldier = 301,
  CTFShotgun = 297,
  CTFRocketPack = 295,
  CTFCrossbow = 200,
  CTFRocketLauncher_Mortar = 294,
  CTFRocketLauncher_AirStrike = 292,
  CTFRocketLauncher_DirectHit = 293,
  CTFRocketLauncher = 291,
  CTFRevolver = 285,
  CTFDRGPomson = 201,
  CTFRaygun = 283,
  CTFPistol_ScoutSecondary = 245,
  CTFPistol_ScoutPrimary = 244,
  CTFPistol_Scout = 243,
  CTFPistol = 242,
  CTFPipebombLauncher = 241,
  CTFWeaponPDA_Spy = 331,
  CTFWeaponPDA_Engineer_Destroy = 330,
  CTFWeaponPDA_Engineer_Build = 329,
  CTFWeaponPDAExpansion_Teleporter = 333,
  CTFWeaponPDAExpansion_Dispenser = 332,
  CTFWeaponPDA = 328,
  CTFParticleCannon = 238,
  CTFParachute_Secondary = 237,
  CTFParachute_Primary = 236,
  CTFParachute = 235,
  CTFMinigun = 233,
  CTFMedigunShield = 230,
  CWeaponMedigun = 351,
  CTFProjectile_MechanicalArmOrb = 262,
  CTFMechanicalArm = 229,
  CTFLunchBox_Drink = 228,
  CTFLunchBox = 227,
  CLaserDot = 78,
  CTFLaserPointer = 226,
  CTFKnife = 225,
  CTFGasManager = 211,
  CTFProjectile_JarGas = 260,
  CTFJarGas = 222,
  CTFProjectile_Cleaver = 253,
  CTFProjectile_JarMilk = 261,
  CTFProjectile_Jar = 259,
  CTFCleaver = 197,
  CTFJarMilk = 223,
  CTFJar = 221,
  CTFWeaponInvis = 327,
  CTFCannon = 195,
  CTFGrenadeLauncher = 215,
  CTFGrenadePipebombProjectile = 216,
  CTFGrapplingHook = 214,
  CTFFlareGun_Revenge = 209,
  CTFFlareGun = 208,
  CTFFlameRocket = 206,
  CTFFlameThrower = 207,
  CTFFists = 204,
  CTFFireAxe = 203,
  CTFWeaponFlameBall = 326,
  CTFCompoundBow = 199,
  CTFClub = 198,
  CTFBuffItem = 194,
  CTFStickBomb = 311,
  CTFBreakableSign = 193,
  CTFBottle = 191,
  CTFBreakableMelee = 192,
  CTFBonesaw = 189,
  CTFBall_Ornament = 181,
  CTFStunBall = 312,
  CTFBat_Giftwrap = 187,
  CTFBat_Wood = 188,
  CTFBat_Fish = 186,
  CTFBat = 185,
  CTFProjectile_EnergyRing = 255,
  CTFDroppedWeapon = 202,
  CTFWeaponSapper = 334,
  CTFWeaponBuilder = 325,
  C_TFWeaponBuilder = 0,
  CTFProjectile_Rocket = 263,
  CTFProjectile_Flare = 256,
  CTFProjectile_EnergyBall = 254,
  CTFProjectile_GrapplingHook = 257,
  CTFProjectile_HealingBolt = 258,
  CTFProjectile_Arrow = 251,
  CMannVsMachineStats = 80,
  CTFTankBoss = 315,
  CTFBaseBoss = 182,
  CBossAlpha = 0,
  NextBotCombatCharacter = 356,
  CTFProjectile_SpellKartBats = 267,
  CTFProjectile_SpellKartOrb = 268,
  CTFHellZap = 219,
  CTFProjectile_SpellLightningOrb = 269,
  CTFProjectile_SpellTransposeTeleport = 276,
  CTFProjectile_SpellMeteorShower = 270,
  CTFProjectile_SpellSpawnBoss = 273,
  CTFProjectile_SpellMirv = 271,
  CTFProjectile_SpellPumpkin = 272,
  CTFProjectile_SpellSpawnHorde = 274,
  CTFProjectile_SpellSpawnZombie = 275,
  CTFProjectile_SpellBats = 265,
  CTFProjectile_SpellFireball = 266,
  CTFSpellBook = 310,
  CHightower_TeleportVortex = 74,
  CTeleportVortex = 159,
  CZombie = 353,
  CMerasmusDancer = 83,
  CMerasmus = 82,
  CHeadlessHatman = 73,
  CEyeballBoss = 48,
  CTFBotHintEngineerNest = 190,
  CBotNPCMinion = 0,
  CBotNPC = 0,
  CPasstimeGun = 94,
  CTFViewModel = 319,
  CRobotDispenser = 111,
  CTFRobotDestruction_Robot = 287,
  CTFReviveMarker = 284,
  CTFPumpkinBomb = 281,
  CTFProjectile_BallOfFire = 252,
  CTFBaseProjectile = 183,
  CTFPointManager = 249,
  CBaseObjectUpgrade = 11,
  CTFRobotDestructionLogic = 290,
  CTFRobotDestruction_RobotGroup = 288,
  CTFRobotDestruction_RobotSpawn = 289,
  CTFPlayerDestructionLogic = 247,
  CPlayerDestructionDispenser = 101,
  CTFMinigameLogic = 232,
  CTFHalloweenMinigame_FallingPlatforms = 218,
  CTFHalloweenMinigame = 217,
  CTFMiniGame = 231,
  CTFPowerupBottle = 250,
  CTFItem = 220,
  CHalloweenSoulPack = 71,
  CTFGenericBomb = 212,
  CBonusRoundLogic = 23,
  CTFGameRulesProxy = 210,
  CTETFParticleEffect = 178,
  CTETFExplosion = 177,
  CTETFBlood = 176,
  CTFFlameManager = 205,
  CHalloweenGiftPickup = 69,
  CBonusDuckPickup = 21,
  CHalloweenPickup = 70,
  CCaptureFlagReturnIcon = 27,
  CCaptureFlag = 26,
  CBonusPack = 22,
  CTFTeam = 317,
  CTFTauntProp = 316,
  CTFPlayerResource = 248,
  CTFPlayer = 246,
  CTFRagdoll = 282,
  CTEPlayerAnimEvent = 164,
  CTFPasstimeLogic = 239,
  CPasstimeBall = 93,
  CTFObjectiveResource = 234,
  CTFGlow = 213,
  CTEFireBullets = 151,
  CTFBuffBanner = 0,
  CTFAmmoPack = 180,
  CObjectTeleporter = 89,
  CObjectSentrygun = 88,
  CTFProjectile_SentryRocket = 264,
  CObjectSapper = 87,
  CObjectCartDispenser = 85,
  CObjectDispenser = 86,
  CMonsterResource = 84,
  CFuncRespawnRoomVisualizer = 64,
  CFuncRespawnRoom = 63,
  CFuncPasstimeGoal = 61,
  CFuncForceField = 57,
  CCaptureZone = 28,
  CCurrencyPack = 31,
  CBaseObject = 10,
  CTestTraceline = 175,
  CTEWorldDecal = 179,
  CTESpriteSpray = 173,
  CTESprite = 172,
  CTESparks = 171,
  CTESmoke = 170,
  CTEShowLine = 168,
  CTEProjectedDecal = 166,
  CTEPlayerDecal = 165,
  CTEPhysicsProp = 163,
  CTEParticleSystem = 162,
  CTEMuzzleFlash = 161,
  CTELargeFunnel = 158,
  CTEKillPlayerAttachments = 157,
  CTEImpact = 156,
  CTEGlowSprite = 155,
  CTEShatterSurface = 167,
  CTEFootprintDecal = 153,
  CTEFizz = 152,
  CTEExplosion = 150,
  CTEEnergySplash = 149,
  CTEEffectDispatch = 148,
  CTEDynamicLight = 147,
  CTEDecal = 145,
  CTEClientProjectile = 144,
  CTEBubbleTrail = 143,
  CTEBubbles = 142,
  CTEBSPDecal = 141,
  CTEBreakModel = 140,
  CTEBloodStream = 139,
  CTEBloodSprite = 138,
  CTEBeamSpline = 137,
  CTEBeamRingPoint = 136,
  CTEBeamRing = 135,
  CTEBeamPoints = 134,
  CTEBeamLaser = 133,
  CTEBeamFollow = 132,
  CTEBeamEnts = 131,
  CTEBeamEntPoint = 130,
  CTEBaseBeam = 129,
  CTEArmorRicochet = 128,
  CTEMetalSparks = 160,
  CSteamJet = 122,
  CSmokeStack = 116,
  DustTrail = 354,
  CFireTrail = 50,
  SporeTrail = 361,
  SporeExplosion = 360,
  RocketTrail = 358,
  SmokeTrail = 359,
  CPropVehicleDriveable = 107,
  ParticleSmokeGrenade = 357,
  CParticleFire = 90,
  MovieExplosion = 355,
  CTEGaussExplosion = 154,
  CEnvQuadraticBeam = 43,
  CEmbers = 36,
  CEnvWind = 47,
  CPrecipitation = 106,
  CBaseTempEntity = 17,
  CWeaponIFMSteadyCam = 350,
  CWeaponIFMBaseCamera = 349,
  CWeaponIFMBase = 348,
  CTFWearableVM = 342,
  CTFWearable = 335,
  CTFWearableItem = 338,
  CEconWearable = 35,
  CBaseAttributableItem = 3,
  CEconEntity = 34,
  CHandleTest = 72,
  CTeamplayRoundBasedRulesProxy = 125,
  CTeamRoundTimer = 126,
  CSpriteTrail = 121,
  CSpriteOriented = 120,
  CSprite = 119,
  CRagdollPropAttached = 110,
  CRagdollProp = 109,
  CPoseController = 105,
  CGameRulesProxy = 68,
  CInfoLadderDismount = 75,
  CFuncLadder = 58,
  CEnvDetailController = 40,
  CWorld = 352,
  CWaterLODControl = 347,
  CWaterBullet = 346,
  CVoteController = 345,
  CVGuiScreen = 344,
  CPropJeep = 0,
  CPropVehicleChoreoGeneric = 0,
  CTest_ProxyToggle_Networkable = 174,
  CTesla = 169,
  CTeamTrainWatcher = 127,
  CBaseTeamObjectiveResource = 16,
  CTeam = 124,
  CSun = 123,
  CParticlePerformanceMonitor = 91,
  CSpotlightEnd = 118,
  CSlideshowDisplay = 115,
  CShadowControl = 114,
  CSceneEntity = 113,
  CRopeKeyframe = 112,
  CRagdollManager = 108,
  CPhysicsPropMultiplayer = 98,
  CPhysBoxMultiplayer = 96,
  CBasePropDoor = 15,
  CDynamicProp = 33,
  CPointCommentaryNode = 104,
  CPointCamera = 103,
  CPlayerResource = 102,
  CPlasma = 100,
  CPhysMagnet = 99,
  CPhysicsProp = 97,
  CPhysBox = 95,
  CParticleSystem = 92,
  CMaterialModifyControl = 81,
  CLightGlow = 79,
  CInfoOverlayAccessor = 77,
  CFuncTrackTrain = 67,
  CFuncSmokeVolume = 66,
  CFuncRotating = 65,
  CFuncReflectiveGlass = 62,
  CFuncOccluder = 60,
  CFuncMonitor = 59,
  CFunc_LOD = 54,
  CTEDust = 146,
  CFunc_Dust = 53,
  CFuncConveyor = 56,
  CBreakableSurface = 25,
  CFuncAreaPortalWindow = 55,
  CFish = 51,
  CEntityFlame = 38,
  CFireSmoke = 49,
  CEnvTonemapController = 46,
  CEnvScreenEffect = 44,
  CEnvScreenOverlay = 45,
  CEnvProjectedTexture = 42,
  CEnvParticleScript = 41,
  CFogController = 52,
  CEntityParticleTrail = 39,
  CEntityDissolve = 37,
  CDynamicLight = 32,
  CColorCorrectionVolume = 30,
  CColorCorrection = 29,
  CBreakableProp = 24,
  CBasePlayer = 13,
  CBaseFlex = 8,
  CBaseEntity = 7,
  CBaseDoor = 6,
  CBaseCombatCharacter = 4,
  CBaseAnimatingOverlay = 2,
  CBoneFollower = 20,
  CBaseAnimating = 1,
  CInfoLightingRelative = 76,
  CAI_BaseNPC = 0,
  CBeam = 19,
  CBaseViewModel = 18,
  CBaseProjectile = 14,
  CBaseParticleEntity = 12,
  CBaseGrenade = 9,
  CBaseCombatWeapon = 5,
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
};