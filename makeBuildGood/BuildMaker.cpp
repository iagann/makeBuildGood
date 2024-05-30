#include "BuildMaker.h"
#include "PassiveCombination.h"

#include <iostream>

#include <set>


BuildMaker::BuildMaker() {
	init();
}

void BuildMaker::init() {
	initPassives();
	initSkills();
}

void BuildMaker::initPassives() {
	// BASE CLASS
	passives.insert(std::make_pair(
		PASSIVE_NAME::SWIFT_ASSASSIN, Passive<PASSIVE_NAME>(PASSIVE_CLASS_NAME::BASE, 8)
			.withStat(STAT_NAME::FLAT_PHYSICAL_DAMAGE, 1)
	));
	passives.insert(std::make_pair(
		PASSIVE_NAME::STEADY_HAND, Passive<PASSIVE_NAME>(PASSIVE_CLASS_NAME::BASE, 8)
		.withStat(STAT_NAME::DEXTERITY, 1)
	));
	passives.insert(std::make_pair(
		PASSIVE_NAME::GUILE, Passive<PASSIVE_NAME>(PASSIVE_CLASS_NAME::BASE, 1)
	));
	passives.insert(std::make_pair(
		PASSIVE_NAME::EVASION, Passive<PASSIVE_NAME>(PASSIVE_CLASS_NAME::BASE, 1)
		.withMinimumClassPoints(PASSIVE_CLASS_NAME::BASE, 5)
		.withDependency(PASSIVE_NAME::GUILE, 1)
	));
	passives.insert(std::make_pair(
		PASSIVE_NAME::AGILITY, Passive<PASSIVE_NAME>(PASSIVE_CLASS_NAME::BASE, 5)
		.withStat(STAT_NAME::INCREASED_DAMAGE_PER_MOVEMENT_SPEED, 5)
		.withMinimumClassPoints(PASSIVE_CLASS_NAME::BASE, 10)
		.withDependency(PASSIVE_NAME::EVASION, 1)
	));
	// BLADEDANCER
	passives.insert(std::make_pair(
		PASSIVE_NAME::CLOAK_OF_SHADOWS, Passive<PASSIVE_NAME>(PASSIVE_CLASS_NAME::BLADEDANCER, 8)
		.withStat(STAT_NAME::DEXTERITY, 1)
		.withMinimumClassPoints(PASSIVE_CLASS_NAME::BASE, 20)
	));
	passives.insert(std::make_pair(
		PASSIVE_NAME::PURSUIT, Passive<PASSIVE_NAME>(PASSIVE_CLASS_NAME::BLADEDANCER, 5)
		.withThresholdStat(5, STAT_NAME::MOVEMENT_SPEED, 5)
		.withMinimumClassPoints(PASSIVE_CLASS_NAME::BASE, 20)
		.withAbsoluteMinimum(5)
	));
	// MARKSMAN
	passives.insert(std::make_pair(
		PASSIVE_NAME::FOCUS_FIRE, Passive<PASSIVE_NAME>(PASSIVE_CLASS_NAME::MARKSMAN, 8)
		.withStat(STAT_NAME::DEXTERITY, 1)
		.withMinimumClassPoints(PASSIVE_CLASS_NAME::BASE, 20)
	));
	passives.insert(std::make_pair(
		PASSIVE_NAME::ASSASSINS_QUIVER, Passive<PASSIVE_NAME>(PASSIVE_CLASS_NAME::MARKSMAN, 5)
		.withStat(STAT_NAME::FLAT_PHYSICAL_DAMAGE, 1)
		.withStat(STAT_NAME::INCREASED_CRITICAL_STRIKE_CHANCE, 5)
		.withMinimumClassPoints(PASSIVE_CLASS_NAME::BASE, 20)
		.withAbsoluteMinimum(1)
	));
	passives.insert(std::make_pair(
		PASSIVE_NAME::MISSILE_MASTERY, Passive<PASSIVE_NAME>(PASSIVE_CLASS_NAME::MARKSMAN, 10)
		.withStat(STAT_NAME::INCREASED_DAMAGE, 5)
		.withStat(STAT_NAME::ARMOUR_SHRED_CHANCE, 5)
		.withMinimumClassPoints(PASSIVE_CLASS_NAME::MARKSMAN, 5)
	));
	passives.insert(std::make_pair(
		PASSIVE_NAME::CONCENTRATION, Passive<PASSIVE_NAME>(PASSIVE_CLASS_NAME::MARKSMAN, 8)
		.withStat(STAT_NAME::INCREASED_DAMAGE, 15)
		.withMinimumClassPoints(PASSIVE_CLASS_NAME::MARKSMAN, 5)
	));
	passives.insert(std::make_pair(
		PASSIVE_NAME::WOUND_MAKER, Passive<PASSIVE_NAME>(PASSIVE_CLASS_NAME::MARKSMAN, 2)
		.withStat(STAT_NAME::CRITICAL_VULNERABILITY_CHANCE, 10)
		.withMinimumClassPoints(PASSIVE_CLASS_NAME::MARKSMAN, 10)
		.withDependency(PASSIVE_NAME::ASSASSINS_QUIVER, 1)
		.withAbsoluteMinimum(2)
	));
	passives.insert(std::make_pair(
		PASSIVE_NAME::HEIGHTENED_SENCES, Passive<PASSIVE_NAME>(PASSIVE_CLASS_NAME::MARKSMAN, 5)
		.withStat(STAT_NAME::CRITICAL_STRIKE_AVOIDANCE, 7)
		.withStat(STAT_NAME::INCREASED_CRITICAL_STRIKE_MULTIPLIER, 5)
		.withMinimumClassPoints(PASSIVE_CLASS_NAME::MARKSMAN, 20)
		.withDependency(PASSIVE_NAME::WOUND_MAKER, 1)
		.withAbsoluteMinimum(5)
	));
	// FALCONER
	passives.insert(std::make_pair(
		PASSIVE_NAME::HANDLER, Passive<PASSIVE_NAME>(PASSIVE_CLASS_NAME::FALCONER, 8)
		.withStat(STAT_NAME::INCREASED_MINION_DAMAGE, 6)
		.withThresholdStat(5, STAT_NAME::BASE_MINION_CRITICAL_STRIKE_CHANCE, 5)
		.withMinimumClassPoints(PASSIVE_CLASS_NAME::BASE, 20)
		.withAbsoluteMinimum(8)
	));
	passives.insert(std::make_pair(
		PASSIVE_NAME::AGILE_HUNT, Passive<PASSIVE_NAME>(PASSIVE_CLASS_NAME::FALCONER, 8)
		.withStat(STAT_NAME::DEXTERITY, 1)
		.withMinimumClassPoints(PASSIVE_CLASS_NAME::FALCONER, 5)
		.withAbsoluteMinimum(8)
	));
	passives.insert(std::make_pair(
		PASSIVE_NAME::RANGERS_MARK, Passive<PASSIVE_NAME>(PASSIVE_CLASS_NAME::FALCONER, 7)
		.withStat(STAT_NAME::INCREASED_DAMAGE, 6)
		.withMinimumClassPoints(PASSIVE_CLASS_NAME::FALCONER, 10)
		.withAbsoluteMinimum(3)
	));
	passives.insert(std::make_pair(
		PASSIVE_NAME::TACTITIAN, Passive<PASSIVE_NAME>(PASSIVE_CLASS_NAME::FALCONER, 6)
		.withStat(STAT_NAME::FLAT_MINION_PHYSICAL_DAMAGE, 3)
		.withMinimumClassPoints(PASSIVE_CLASS_NAME::FALCONER, 15)
		.withDependency(PASSIVE_NAME::HANDLER, 1)
		.withAbsoluteMinimum(6)
	));
	// FALCONER part 2
	passives.insert(std::make_pair(
		PASSIVE_NAME::COORDINATED_FADE, Passive<PASSIVE_NAME>(PASSIVE_CLASS_NAME::FALCONER, 1)
		.withMinimumClassPoints(PASSIVE_CLASS_NAME::FALCONER, 25)
		.withAbsoluteMinimum(1)
	));
	passives.insert(std::make_pair(
		PASSIVE_NAME::EVASION_TACTICS, Passive<PASSIVE_NAME>(PASSIVE_CLASS_NAME::FALCONER, 6)
		.withStat(STAT_NAME::DEXTERITY, 1)
		.withMinimumClassPoints(PASSIVE_CLASS_NAME::FALCONER, 25)
		.withAbsoluteMinimum(4)
	));
	passives.insert(std::make_pair(
		PASSIVE_NAME::INTUITIVE_CONNECTION, Passive<PASSIVE_NAME>(PASSIVE_CLASS_NAME::FALCONER, 1)
		.withMinimumClassPoints(PASSIVE_CLASS_NAME::FALCONER, 30)
		.withAbsoluteMinimum(1)
	));
	passives.insert(std::make_pair(
		PASSIVE_NAME::RELENTLESS_TALONS, Passive<PASSIVE_NAME>(PASSIVE_CLASS_NAME::FALCONER, 5)
		.withStat(STAT_NAME::INCREASED_DAMAGE, 6)
		.withStat(STAT_NAME::INCREASED_MINION_DAMAGE, 6)
		.withMinimumClassPoints(PASSIVE_CLASS_NAME::FALCONER, 30)
		.withDependency(PASSIVE_NAME::EVASION_TACTICS, 1)
		.withAbsoluteMinimum(2)
	));
	passives.insert(std::make_pair(
		PASSIVE_NAME::NEEDLE_LIKE_PRECISION, Passive<PASSIVE_NAME>(PASSIVE_CLASS_NAME::FALCONER, 6)
		.withStat(STAT_NAME::INCREASED_CRITICAL_STRIKE_CHANCE, 6)
		.withStat(STAT_NAME::INCREASED_CRITICAL_STRIKE_MULTIPLIER, 6)
		.withStat(STAT_NAME::INCREASED_MINION_CRITICAL_STRIKE_CHANCE, 6)
		.withStat(STAT_NAME::INCREASED_MINION_CRITICAL_STRIKE_MULTIPLIER, 6)
		.withMinimumClassPoints(PASSIVE_CLASS_NAME::FALCONER, 35)
		.withAbsoluteMinimum(5)
	));
	passives.insert(std::make_pair(
		PASSIVE_NAME::EXPEDIENCY, Passive<PASSIVE_NAME>(PASSIVE_CLASS_NAME::FALCONER, 5)
		.withMinimumClassPoints(PASSIVE_CLASS_NAME::FALCONER, 40)
		.withAbsoluteMinimum(5)
	));
	passives.insert(std::make_pair(
		PASSIVE_NAME::FINESSE_THEM, Passive<PASSIVE_NAME>(PASSIVE_CLASS_NAME::FALCONER, 7)
		.withStat(STAT_NAME::CRITICAL_STRIKE_AVOIDANCE, 5)
		.withThresholdStat(0, STAT_NAME::INCREASED_MINION_CRITICAL_STRIKE_MULTIPLIER_PER_CRITICAL_STRIKE_AVOIDANCE, 1.5)
		.withMinimumClassPoints(PASSIVE_CLASS_NAME::FALCONER, 40)
		.withDependency(PASSIVE_NAME::NEEDLE_LIKE_PRECISION, 2)
		.withAbsoluteMinimum(5)
	));
	passives.insert(std::make_pair(
		PASSIVE_NAME::TAILWIND, Passive<PASSIVE_NAME>(PASSIVE_CLASS_NAME::FALCONER, 6)
		.withStat(STAT_NAME::MOVEMENT_SPEED, 2)
		.withMinimumClassPoints(PASSIVE_CLASS_NAME::FALCONER, 40)
		.withAbsoluteMinimum(6)
	));
}

void BuildMaker::initSkills() {
	//BASE
	{
		skills.insert(std::make_pair(
			SKILL_PASSIVE_NAME::SHARED_ENHANCEMENTS, Passive<SKILL_PASSIVE_NAME>(PASSIVE_CLASS_NAME::BASE, 3)
			.withStat(STAT_NAME::DAMAGE_STAT_RATIO, 25)
			.withAbsoluteMinimum(3)
		));
		skills.insert(std::make_pair(
			SKILL_PASSIVE_NAME::AGILE_ENGENEERING, Passive<SKILL_PASSIVE_NAME>(PASSIVE_CLASS_NAME::BASE, 1)
			.withStat(STAT_NAME::ATTACK_SPEED_PER_5_DEXTERITY, 1)
			.withAbsoluteMinimum(1)
		));
		skills.insert(std::make_pair(
			SKILL_PASSIVE_NAME::AGILE_ENGENEERING, Passive<SKILL_PASSIVE_NAME>(PASSIVE_CLASS_NAME::BASE, 1)
			.withStat(STAT_NAME::ATTACK_SPEED_PER_5_DEXTERITY, 1)
			.withAbsoluteMinimum(1)
		));
		skills.insert(std::make_pair(
			SKILL_PASSIVE_NAME::EFFICIENT_CONSTRUCTION, Passive<SKILL_PASSIVE_NAME>(PASSIVE_CLASS_NAME::BASE, 2)
			.withAbsoluteMinimum(2)
		));
		skills.insert(std::make_pair(
			SKILL_PASSIVE_NAME::PRACTICAL_BUILD, Passive<SKILL_PASSIVE_NAME>(PASSIVE_CLASS_NAME::BASE, 1)
			.withDependency(SKILL_PASSIVE_NAME::EFFICIENT_CONSTRUCTION, 2)
			.withAbsoluteMinimum(1)
		));
		skills.insert(std::make_pair(
			SKILL_PASSIVE_NAME::LIGHT_BOLTS, Passive<SKILL_PASSIVE_NAME>(PASSIVE_CLASS_NAME::BASE, 3)
			.withDependency(SKILL_PASSIVE_NAME::EFFICIENT_CONSTRUCTION, 1)
			.withStat(STAT_NAME::MORE_ATTACK_SPEED, 12)
			.withStat(STAT_NAME::MORE_DAMAGE, -5)
			.withAbsoluteMinimum(1)
		));
		skills.insert(std::make_pair(
			SKILL_PASSIVE_NAME::SHARPENED_TIPS, Passive<SKILL_PASSIVE_NAME>(PASSIVE_CLASS_NAME::BASE, 2)
			.withDependency(SKILL_PASSIVE_NAME::LIGHT_BOLTS, 1)
			.withStat(STAT_NAME::BASE_MINION_CRITICAL_STRIKE_CHANCE, 3)
			.withAbsoluteMinimum(1)
		));
		skills.insert(std::make_pair(
			SKILL_PASSIVE_NAME::PERFECT_AIM, Passive<SKILL_PASSIVE_NAME>(PASSIVE_CLASS_NAME::BASE, 4)
			.withDependency(SKILL_PASSIVE_NAME::SHARPENED_TIPS, 1)
			.withStat(STAT_NAME::CRITICAL_STAT_RATIO, 25)
			.withAbsoluteMinimum(4)
		));

		skills.insert(std::make_pair(
			SKILL_PASSIVE_NAME::RAPID_FIRE, Passive<SKILL_PASSIVE_NAME>(PASSIVE_CLASS_NAME::BASE, 4)
			.withDependency(SKILL_PASSIVE_NAME::AGILE_ENGENEERING, 1)
			.withStat(STAT_NAME::ATTACK_SPEED, 6)
			.withAbsoluteMinimum(1)
		));
		skills.insert(std::make_pair(
			SKILL_PASSIVE_NAME::CONTAMINATING_SHOTS, Passive<SKILL_PASSIVE_NAME>(PASSIVE_CLASS_NAME::BASE, 3)
			.withDependency(SKILL_PASSIVE_NAME::RAPID_FIRE, 2)
			.withStat(STAT_NAME::AILMENT_STAT_RATIO, 25)
			.withAbsoluteMinimum(0)
		));
		skills.insert(std::make_pair(
			SKILL_PASSIVE_NAME::STURDY_FOUNDATION, Passive<SKILL_PASSIVE_NAME>(PASSIVE_CLASS_NAME::BASE, 3)
			.withDependency(SKILL_PASSIVE_NAME::RAPID_FIRE, 1)
			.withAbsoluteMinimum(2)
		));
		skills.insert(std::make_pair(
			SKILL_PASSIVE_NAME::CARE_PACKAGE, Passive<SKILL_PASSIVE_NAME>(PASSIVE_CLASS_NAME::BASE, 2)
			.withDependency(SKILL_PASSIVE_NAME::STURDY_FOUNDATION, 1)
			.withAbsoluteMinimum(2)
		));
		skills.insert(std::make_pair(
			SKILL_PASSIVE_NAME::ELIXIR_OF_CONSTRUCTION, Passive<SKILL_PASSIVE_NAME>(PASSIVE_CLASS_NAME::BASE, 5)
			.withDependency(SKILL_PASSIVE_NAME::CARE_PACKAGE, 2)
			.withStat(STAT_NAME::MORE_DAMAGE, 20)
			.withAbsoluteMinimum(3)
		));
	}

	std::set<PassiveCombination<SKILL_PASSIVE_NAME>> basePassiveCombinationSet;
	auto initCombo = PassiveCombination<SKILL_PASSIVE_NAME>();
	for (auto skill : skills) {
		initCombo.setPassivePoints(skill.first, skill.second.getClass(), skill.second.getAbsoluteMinimum());
	}

	auto shared1 = initCombo;
	shared1.setPassivePoints(SKILL_PASSIVE_NAME::RAPID_FIRE, PASSIVE_CLASS_NAME::BASE, 2); // 1
	shared1.setPassivePoints(SKILL_PASSIVE_NAME::CONTAMINATING_SHOTS, PASSIVE_CLASS_NAME::BASE, 1); // 1
	shared1.setPassivePoints(SKILL_PASSIVE_NAME::ELIXIR_OF_CONSTRUCTION, PASSIVE_CLASS_NAME::BASE, 4); // 1
	skillSet.insert(shared1);
	shared1.setPassivePoints(SKILL_PASSIVE_NAME::ELIXIR_OF_CONSTRUCTION, PASSIVE_CLASS_NAME::BASE, 5); // 2
	skillSetKestrel.insert(shared1);

	auto shared2 = initCombo;
	shared2.setPassivePoints(SKILL_PASSIVE_NAME::RAPID_FIRE, PASSIVE_CLASS_NAME::BASE, 2); // 1
	shared2.setPassivePoints(SKILL_PASSIVE_NAME::CONTAMINATING_SHOTS, PASSIVE_CLASS_NAME::BASE, 2); //2
	skillSet.insert(shared2);
	shared2.setPassivePoints(SKILL_PASSIVE_NAME::ELIXIR_OF_CONSTRUCTION, PASSIVE_CLASS_NAME::BASE, 4); // 1
	skillSetKestrel.insert(shared2);

	auto shared0 = initCombo;
	shared0.setPassivePoints(SKILL_PASSIVE_NAME::ELIXIR_OF_CONSTRUCTION, PASSIVE_CLASS_NAME::BASE, 5); //2
	shared0.setPassivePoints(SKILL_PASSIVE_NAME::HEAVY_BOLTS, PASSIVE_CLASS_NAME::BASE, 1); // 1
	skillSet.insert(shared0);
	shared0.setPassivePoints(SKILL_PASSIVE_NAME::HEAVY_BOLTS, PASSIVE_CLASS_NAME::BASE, 0); // 0
	shared0.setPassivePoints(SKILL_PASSIVE_NAME::LIGHT_BOLTS, PASSIVE_CLASS_NAME::BASE, 2); // 1
	skillSet.insert(shared0);
	shared0.setPassivePoints(SKILL_PASSIVE_NAME::HEAVY_BOLTS, PASSIVE_CLASS_NAME::BASE, 1); // 1
	skillSetKestrel.insert(shared0);
}

bool BuildMaker::tests() {
	auto combo = PassiveCombination<PASSIVE_NAME>();

	// actual spent skill points < minimum
	combo.addPassivePoint(PASSIVE_NAME::EVASION, passives.at(PASSIVE_NAME::EVASION).getClass());
	if (true == passiveCombinationOk(passives, combo))
		return false;

	// dependency not satistied
	combo = PassiveCombination<PASSIVE_NAME>();
	for (int i = 0; i < 5; ++i)
		combo.addPassivePoint(PASSIVE_NAME::STEADY_HAND, passives.at(PASSIVE_NAME::EVASION).getClass());
	combo.addPassivePoint(PASSIVE_NAME::EVASION, passives.at(PASSIVE_NAME::EVASION).getClass());
	if (true == passiveCombinationOk(passives, combo))
		return false;

	return true;
}

unsigned int BuildMaker::totalAbsoluteMinimum() {
	unsigned int result = 0;
	for (auto passive : passives) {
		result += passive.second.getAbsoluteMinimum();
	}
	return result;
}

int BuildMaker::get_num_threads() {
	int num_threads = 1;
#pragma omp parallel
	{
#pragma omp single
		num_threads = omp_get_num_threads();
	}
	return num_threads;
}