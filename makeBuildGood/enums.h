#pragma once

#include <map>
#include <string>

enum STAT_NAME  {
	FLAT_PHYSICAL_DAMAGE,
	FLAT_MINION_PHYSICAL_DAMAGE,
	FLAT_MINION_PHYSICAL_DAMAGE_FALCON,
	FLAT_LIGHTNING_DAMAGE,
	PHYSICAL_PENETRATION,
	DEXTERITY,
	INTELLIGENCE,
	ALL_ATRIBUTES,
	INCREASED_MOVEMENT_SPEED,
	INCREASED_ATTACK_SPEED,
	LEVEL_OF_BALLISTA,
	INCREASED_DAMAGE,
	INCREASED_BOW_DAMAGE,
	INCREASED_PHYSICAL_DAMAGE,
	INCREASED_COLD_DAMAGE,
	INCREASED_MINION_PHYSICAL_DAMAGE,
	INCREASED_MINION_DAMAGE,
	INCREASED_DAMAGE_PER_MOVEMENT_SPEED,
	INCREASED_CRITICAL_STRIKE_CHANCE,
	INCREASED_MINION_CRITICAL_STRIKE_CHANCE,
	INCREASED_CRITICAL_STRIKE_MULTIPLIER,
	INCREASED_MINION_CRITICAL_STRIKE_MULTIPLIER,
	BASE_CRITICAL_STRIKE_CHANCE,
	BASE_MINION_CRITICAL_STRIKE_CHANCE,
	CRITICAL_STRIKE_AVOIDANCE,
	ARMOUR_SHRED_CHANCE,
	ARMOUR_SHRED_EFFECT,
	CHANCE_TO_SHRED_PHYS_RES,
	CHANCE_TO_SHRED_COLD_RES,
	CHANCE_TO_SHRED_LIGHTNING_RES,
	CRITICAL_VULNERABILITY_CHANCE,
	SHOCK_CHANCE,
	COOLDOWN_RECOVERY_SPEED,

	INCREASED_MINION_CRITICAL_STRIKE_MULTIPLIER_PER_CRITICAL_STRIKE_AVOIDANCE,
	FLAT_COLD_PER_DEX,

	MORE_DAMAGE,
	MORE_DAMAGE_PER_INTELLIGENCE,
	MORE_ATTACK_SPEED,
	DAMAGE_STAT_RATIO,
	CRITICAL_STAT_RATIO,
	AILMENT_STAT_RATIO,
	INCREASED_MINION_DAMAGE_PER_DEXTERITY,
	INCREASED_ATTACK_SPEED_PER_DEXTERITY
};

enum PASSIVE_NAME {
	BASE_STATS,

	SWIFT_ASSASSIN,
	STEADY_HAND,
	GUILE,
	EVASION,
	AGILITY,

	CLOAK_OF_SHADOWS,
	PURSUIT,

	FOCUS_FIRE,
	ASSASSINS_QUIVER,
	MISSILE_MASTERY,
	CONCENTRATION,
	WOUND_MAKER,
	MEDITAION,
	REFLECTION,
	HEIGHTENED_SENCES,

	HANDLER,
	AGILE_HUNT,
	RANGERS_MARK,
	TACTITIAN,
	COORDINATED_FADE,
	EVASION_TACTICS,
	INTUITIVE_CONNECTION,
	RELENTLESS_TALONS,
	NEEDLE_LIKE_PRECISION,
	EXPEDIENCY,
	FINESSE_THEM,
	TAILWIND
};

enum PASSIVE_CLASS_NAME {
	BASE,
	BLADEDANCER,
	MARKSMAN,
	FALCONER,
};

enum ITEM_TYPE {
	HELM,
	AMULET,
	BOW,
	QUIVER,
	BODY,
	RING,
	BELT,
	GLOVES,
	BOOTS,
	RELIC,
	BIG_IDOL,
	SMALL_IDOL,
	BLESSING_BLACK_SUN,
	BLESSING_REIGN_OF_DRAGONS,
	BLESSING_SPIRITS_OF_FIRE,
	BLESSING_THE_AGE_OF_WINTER,
	BLESSING_ENDING_THE_STORM,
};

enum ITEM_SLOT {
	HELM_SLOT,
	AMULET_SLOT,
	BOW_SLOT,
	QUIVER_SLOT,
	BODY_SLOT,
	RING_LEFT_SLOT,
	RING_RIGHT_SLOT,
	BELT_SLOT,
	GLOVES_SLOT,
	BOOTS_SLOT,
	RELIC_SLOT,
	BIG_IDOL_1_SLOT,
	BIG_IDOL_2_SLOT,
	BIG_IDOL_3_SLOT,
	BIG_IDOL_4_SLOT,
	SMALL_IDOL_1_SLOT,
	SMALL_IDOL_2_SLOT,
	SMALL_IDOL_3_SLOT,
	SMALL_IDOL_4_SLOT,
	BLESSING_BLACK_SUN_SLOT,
	BLESSING_REIGN_OF_DRAGONS_SLOT,
	BLESSING_SPIRITS_OF_FIRE_SLOT,
	BLESSING_THE_AGE_OF_WINTER_SLOT,
	BLESSING_ENDING_THE_STORM_SLOT,
};

enum SKILL_PASSIVE_NAME {
	BASE_SKILL,
	AGILE_ENGENEERING,
	EFFICIENT_CONSTRUCTION,
	PRACTICAL_BUILD,
	LIGHT_BOLTS,
	SHARPENED_TIPS,
	PERFECT_AIM,
	TWINNED_BOLTS,
	HEAVY_BOLTS,
	SHARED_ENHANCEMENTS,
	RAPID_FIRE,
	CONTAMINATING_SHOTS,
	STURDY_FOUNDATION,
	CARE_PACKAGE,
	ELIXIR_OF_CONSTRUCTION,
	QUICKLOAD,
	SIEGE_COMMANDER
};

enum DEPENDENCY {
	DEPENDENCY_OK,
	DEPENDENCY_OVER_MAX,
	DEPENDENCY_MASTERY,
	DEPENDENCY_PARENT
};

class STRINGS {
private:
	static bool inited;
public:
	static void init();
	static const std::map<PASSIVE_NAME, std::string> PASSIVE_NAME_MAP;
	static std::map< std::string, PASSIVE_NAME> PASSIVE_NAME_REVERSE_MAP;
	static const std::map<PASSIVE_CLASS_NAME, std::string> PASSIVE_CLASS_NAME_MAP;
	static const std::map<ITEM_TYPE, std::string> ITEM_TYPE_MAP;
	static std::map<std::string, ITEM_TYPE> ITEM_TYPE_REVERSE_MAP;
	static const std::map<ITEM_SLOT, std::string> ITEM_SLOT_MAP;
	static const std::map<SKILL_PASSIVE_NAME, std::string> SKILL_PASSIVE_NAME_MAP;
	static std::map<std::string, SKILL_PASSIVE_NAME> SKILL_PASSIVE_NAME_REVERSE_MAP;
	static const std::map<STAT_NAME, std::string> STAT_NAME_MAP;
	static std::map<std::string, STAT_NAME> STAT_NAME_REVERSE_MAP;
};