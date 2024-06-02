#include "BuildMaker.h"

#include <iostream>


int main()
{
    BuildMaker buildMaker;
    buildMaker.stacks = false;
    bool peak = true;
    double rollPercent = 1;
    // HELM
    {
        if (peak) {
            buildMaker.addItemCandidate(
                Item(ITEM_TYPE::HELM, "Peak of the Mountain")
                .withStat(STAT_NAME::INTELLIGENCE, 8 * rollPercent)
                .withStat(STAT_NAME::DEXTERITY, 16)
                .withStat(STAT_NAME::CRITICAL_STRIKE_AVOIDANCE, 37 * rollPercent)
                .withStat(STAT_NAME::ALL_ATRIBUTES, 5 * rollPercent)
                .withStat(STAT_NAME::INCREASED_CRITICAL_STRIKE_CHANCE, 290 * rollPercent)
            );
            buildMaker.addItemCandidate(
                Item(ITEM_TYPE::HELM, "Peak of the Mountain")
                .withStat(STAT_NAME::INTELLIGENCE, 16)
                .withStat(STAT_NAME::DEXTERITY, 8 * rollPercent)
                .withStat(STAT_NAME::CRITICAL_STRIKE_AVOIDANCE, 37 * rollPercent)
                .withStat(STAT_NAME::ALL_ATRIBUTES, 5 * rollPercent)
                .withStat(STAT_NAME::INCREASED_CRITICAL_STRIKE_CHANCE, 290 * rollPercent)
            );
        }
        else {
            buildMaker.addItemCandidate(
                Item(ITEM_TYPE::HELM, "Boneclamor Barbute")
                .withStat(STAT_NAME::INTELLIGENCE, 8 * rollPercent)
                .withStat(STAT_NAME::DEXTERITY, 16)
                .withStat(STAT_NAME::INTELLIGENCE, 13 * rollPercent)
                .withStat(STAT_NAME::DEXTERITY, 13 * rollPercent)
            );
            buildMaker.addItemCandidate(
                Item(ITEM_TYPE::HELM, "Boneclamor Barbute")
                .withStat(STAT_NAME::INTELLIGENCE, 16)
                .withStat(STAT_NAME::DEXTERITY, 8 * rollPercent)
                .withStat(STAT_NAME::INTELLIGENCE, 13 * rollPercent)
                .withStat(STAT_NAME::DEXTERITY, 13 * rollPercent)
            );
        }
    }
    // AMULET
    {
        buildMaker.addItemCandidate(
            Item(ITEM_TYPE::AMULET, "Death rattle")
            .withStat(STAT_NAME::INCREASED_MINION_DAMAGE, 70 * rollPercent)
            .withStat(STAT_NAME::ARMOUR_SHRED_CHANCE, 234)
            .withStat(STAT_NAME::INCREASED_MINION_DAMAGE, 35 * rollPercent)
            .withStat(STAT_NAME::INCREASED_MINION_CRITICAL_STRIKE_CHANCE, 35 * rollPercent)
            .withStat(STAT_NAME::INCREASED_MINION_CRITICAL_STRIKE_MULTIPLIER, 65 * rollPercent)
            .withStat(STAT_NAME::INTELLIGENCE, 10 * rollPercent)
        );
        buildMaker.addItemCandidate(
            Item(ITEM_TYPE::AMULET, "Death rattle")
            .withStat(STAT_NAME::INCREASED_MINION_DAMAGE, 140)
            .withStat(STAT_NAME::ARMOUR_SHRED_CHANCE, 117 * rollPercent)
            .withStat(STAT_NAME::INCREASED_MINION_DAMAGE, 35 * rollPercent)
            .withStat(STAT_NAME::INCREASED_MINION_CRITICAL_STRIKE_CHANCE, 35 * rollPercent)
            .withStat(STAT_NAME::INCREASED_MINION_CRITICAL_STRIKE_MULTIPLIER, 65 * rollPercent)
            .withStat(STAT_NAME::INTELLIGENCE, 10 * rollPercent)
        );
        buildMaker.addItemCandidate(
            Item(ITEM_TYPE::AMULET, "Death rattle")
            .withStat(STAT_NAME::INCREASED_MINION_DAMAGE, 70 * rollPercent)
            .withStat(STAT_NAME::INCREASED_CRITICAL_STRIKE_MULTIPLIER, 58)
            .withStat(STAT_NAME::INCREASED_MINION_DAMAGE, 35 * rollPercent)
            .withStat(STAT_NAME::INCREASED_MINION_CRITICAL_STRIKE_CHANCE, 35 * rollPercent)
            .withStat(STAT_NAME::INCREASED_MINION_CRITICAL_STRIKE_MULTIPLIER, 65 * rollPercent)
            .withStat(STAT_NAME::INTELLIGENCE, 10 * rollPercent)
        );
        buildMaker.addItemCandidate(
            Item(ITEM_TYPE::AMULET, "Death rattle")
            .withStat(STAT_NAME::INCREASED_MINION_DAMAGE, 140)
            .withStat(STAT_NAME::INCREASED_CRITICAL_STRIKE_MULTIPLIER, 29 * rollPercent)
            .withStat(STAT_NAME::INCREASED_MINION_DAMAGE, 35 * rollPercent)
            .withStat(STAT_NAME::INCREASED_MINION_CRITICAL_STRIKE_CHANCE, 35 * rollPercent)
            .withStat(STAT_NAME::INCREASED_MINION_CRITICAL_STRIKE_MULTIPLIER, 65 * rollPercent)
            .withStat(STAT_NAME::INTELLIGENCE, 10 * rollPercent)
        );
    }
    // BOW
    {
        buildMaker.addItemCandidate(
            Item(ITEM_TYPE::BOW, "Uethrin's Stand")
            .withStat(STAT_NAME::INCREASED_DAMAGE, 105 * rollPercent)
            .withStat(STAT_NAME::FLAT_PHYSICAL_DAMAGE, 21 * rollPercent)
            .withStat(STAT_NAME::FLAT_MINION_PHYSICAL_DAMAGE, 32)
            .withStat(STAT_NAME::FLAT_MINION_PHYSICAL_DAMAGE_FALCON, 32 * rollPercent)
            .withStat(STAT_NAME::PHYSICAL_PENETRATION, 12 * rollPercent)
            .withStat(STAT_NAME::FLAT_PHYSICAL_DAMAGE, 18 * rollPercent)
            .withStat(STAT_NAME::BASE_CRITICAL_STRIKE_CHANCE, 3 * rollPercent)
            .withStat(STAT_NAME::FLAT_MINION_PHYSICAL_DAMAGE, 25 * rollPercent)
        );
    }
    // BODY
    {
        buildMaker.addItemCandidate(
            Item(ITEM_TYPE::BODY, "The Kestrel")
            .withStat(STAT_NAME::INCREASED_ATTACK_SPEED, 48)
            .withStat(STAT_NAME::DEXTERITY, 12 * rollPercent)
            .withStat(STAT_NAME::LEVEL_OF_BALLISTA, 1)
        );
    }
    // QUIVER
    {
        buildMaker.addItemCandidate(
            Item(ITEM_TYPE::QUIVER, "Zeural's Hunt")
            .withStat(STAT_NAME::DEXTERITY, 16)
            .withStat(STAT_NAME::INCREASED_MINION_DAMAGE, 60 * rollPercent)
            .withStat(STAT_NAME::ARMOUR_SHRED_CHANCE, 100 * rollPercent)
            .withStat(STAT_NAME::INCREASED_CRITICAL_STRIKE_MULTIPLIER, 35 * rollPercent)
            .withStat(STAT_NAME::FLAT_LIGHTNING_DAMAGE, 32 * rollPercent)
        );
        buildMaker.addItemCandidate(
            Item(ITEM_TYPE::QUIVER, "Zeural's Hunt")
            .withStat(STAT_NAME::DEXTERITY, 16)
            .withStat(STAT_NAME::FLAT_PHYSICAL_DAMAGE, 12 * rollPercent)
            .withStat(STAT_NAME::ARMOUR_SHRED_CHANCE, 100 * rollPercent)
            .withStat(STAT_NAME::INCREASED_CRITICAL_STRIKE_MULTIPLIER, 35 * rollPercent)
            .withStat(STAT_NAME::FLAT_LIGHTNING_DAMAGE, 32 * rollPercent)
        );
        buildMaker.addItemCandidate(
            Item(ITEM_TYPE::QUIVER, "Zeural's Hunt")
            .withStat(STAT_NAME::DEXTERITY, 16)
            .withStat(STAT_NAME::INCREASED_MINION_DAMAGE, 60 * rollPercent)
            .withStat(STAT_NAME::SHOCK_CHANCE, 30 * rollPercent)
            .withStat(STAT_NAME::INCREASED_CRITICAL_STRIKE_MULTIPLIER, 35 * rollPercent)
            .withStat(STAT_NAME::FLAT_LIGHTNING_DAMAGE, 32 * rollPercent)
        );
        buildMaker.addItemCandidate(
            Item(ITEM_TYPE::QUIVER, "Zeural's Hunt")
            .withStat(STAT_NAME::DEXTERITY, 16)
            .withStat(STAT_NAME::FLAT_PHYSICAL_DAMAGE, 12 * rollPercent)
            .withStat(STAT_NAME::SHOCK_CHANCE, 30 * rollPercent)
            .withStat(STAT_NAME::INCREASED_CRITICAL_STRIKE_MULTIPLIER, 35 * rollPercent)
            .withStat(STAT_NAME::FLAT_LIGHTNING_DAMAGE, 32 * rollPercent)
        );
    }
    // RING
    {
        buildMaker.addItemCandidate(
            Item(ITEM_TYPE::RING, "Hollow Finger")
            .withStat(STAT_NAME::INTELLIGENCE, 16)
            .withStat(STAT_NAME::DEXTERITY, 8 * rollPercent)
            .withStat(STAT_NAME::CRITICAL_STRIKE_AVOIDANCE, 37 * rollPercent)
            .withStat(STAT_NAME::INCREASED_MINION_DAMAGE, 35 * rollPercent)
            .withStat(STAT_NAME::INCREASED_MINION_CRITICAL_STRIKE_MULTIPLIER, 35 * rollPercent)
        );
        buildMaker.addItemCandidate(
            Item(ITEM_TYPE::RING, "Hollow Finger")
            .withStat(STAT_NAME::DEXTERITY, 16)
            .withStat(STAT_NAME::INTELLIGENCE, 8 * rollPercent)
            .withStat(STAT_NAME::CRITICAL_STRIKE_AVOIDANCE, 37 * rollPercent)
            .withStat(STAT_NAME::INCREASED_MINION_DAMAGE, 35 * rollPercent)
            .withStat(STAT_NAME::INCREASED_MINION_CRITICAL_STRIKE_MULTIPLIER, 35 * rollPercent)
        );
    }
    //BELT
    {
        buildMaker.addItemCandidate(
            Item(ITEM_TYPE::BELT, "Jungle Queen's Chaps of Holding")
            .withStat(STAT_NAME::INCREASED_MINION_DAMAGE, 60 * rollPercent)
            .withStat(STAT_NAME::INCREASED_PHYSICAL_DAMAGE, 50 * rollPercent)
            .withStat(STAT_NAME::INCREASED_MINION_PHYSICAL_DAMAGE, 50 * rollPercent)
            .withStat(STAT_NAME::DEXTERITY, 10 * rollPercent)
        );
    }
    //GLOVES
    {
        buildMaker.addItemCandidate(
            Item(ITEM_TYPE::GLOVES, "Swaddling of the Erased")
            .withStat(STAT_NAME::INTELLIGENCE, 16)
            .withStat(STAT_NAME::DEXTERITY, 16)
            .withStat(STAT_NAME::ALL_ATRIBUTES, 6 * rollPercent)
        );
        buildMaker.addItemCandidate(
            Item(ITEM_TYPE::GLOVES, "Blood Roost")
            .withStat(STAT_NAME::INTELLIGENCE, 16)
            .withStat(STAT_NAME::DEXTERITY, 8 * rollPercent)
            .withStat(STAT_NAME::DEXTERITY, 15 * rollPercent)
        );
        buildMaker.addItemCandidate(
            Item(ITEM_TYPE::GLOVES, "Blood Roost")
            .withStat(STAT_NAME::DEXTERITY, 16)
            .withStat(STAT_NAME::INTELLIGENCE, 8 * rollPercent)
            .withStat(STAT_NAME::DEXTERITY, 15 * rollPercent)
        );
    }
    //BOOTS
    {
        buildMaker.addItemCandidate(
            Item(ITEM_TYPE::BOOTS, "Mourningfrost")
            .withStat(STAT_NAME::INTELLIGENCE, 16)
            .withStat(STAT_NAME::DEXTERITY, 8 * rollPercent)
            .withStat(STAT_NAME::FLAT_COLD_PER_DEX, 1)
        );
        buildMaker.addItemCandidate(
            Item(ITEM_TYPE::BOOTS, "Mourningfrost")
            .withStat(STAT_NAME::DEXTERITY, 16)
            .withStat(STAT_NAME::INTELLIGENCE, 8 * rollPercent)
            .withStat(STAT_NAME::FLAT_COLD_PER_DEX, 1)
        );
    }
    //RELIC
    {
        buildMaker.addItemCandidate(
            Item(ITEM_TYPE::RELIC, "Melvern's Writ")
            .withStat(STAT_NAME::INCREASED_ATTACK_SPEED, 30)
            .withStat(STAT_NAME::DEXTERITY, 8)
            .withStat(STAT_NAME::INCREASED_MINION_DAMAGE, 90)
            .withStat(STAT_NAME::BASE_MINION_CRITICAL_STRIKE_CHANCE, 3)
            .withStat(STAT_NAME::DEXTERITY, 8)
        );
    }
    //IDOLS
    {
        if (!peak) {
            buildMaker.addItemCandidate(
                Item(ITEM_TYPE::BIG_IDOL, "Adorned")
                .withStat(STAT_NAME::INCREASED_CRITICAL_STRIKE_MULTIPLIER, 25 * rollPercent)
                .withStat(STAT_NAME::INCREASED_MINION_CRITICAL_STRIKE_MULTIPLIER, 25 * rollPercent)
                .withStat(STAT_NAME::INCREASED_CRITICAL_STRIKE_CHANCE, 62 * rollPercent)
            );
        }
        buildMaker.addItemCandidate(
            Item(ITEM_TYPE::BIG_IDOL, "Adorned")
            .withStat(STAT_NAME::INCREASED_CRITICAL_STRIKE_MULTIPLIER, 25 * rollPercent)
            .withStat(STAT_NAME::INCREASED_MINION_CRITICAL_STRIKE_MULTIPLIER, 25 * rollPercent)
            .withStat(STAT_NAME::ARMOUR_SHRED_EFFECT, 86 * rollPercent)
        );
        buildMaker.addItemCandidate(
            Item(ITEM_TYPE::SMALL_IDOL, "Eterran")
            .withStat(STAT_NAME::INCREASED_PHYSICAL_DAMAGE, 8)
            .withStat(STAT_NAME::INCREASED_MINION_PHYSICAL_DAMAGE, 8)
        );
    }
    //BLESSINGS
    {
        buildMaker.addItemCandidate(
            Item(ITEM_TYPE::BLESSING_BLACK_SUN, "Grand Emptiness of Ash")
            .withStat(STAT_NAME::INCREASED_CRITICAL_STRIKE_MULTIPLIER, 40 * rollPercent)
        );
        buildMaker.addItemCandidate(
            Item(ITEM_TYPE::BLESSING_REIGN_OF_DRAGONS, "Grand Survival of Might")
            .withStat(STAT_NAME::CRITICAL_STRIKE_AVOIDANCE, 70 * rollPercent)
        );
        buildMaker.addItemCandidate(
            Item(ITEM_TYPE::BLESSING_SPIRITS_OF_FIRE, "Grand Spirit of Command")
            .withStat(STAT_NAME::INCREASED_MINION_DAMAGE, 100 * rollPercent)
        );
        buildMaker.addItemCandidate(
            Item(ITEM_TYPE::BLESSING_THE_AGE_OF_WINTER, "Grand Fury of the North")
            .withStat(STAT_NAME::CHANCE_TO_SHRED_PHYS_RES, 50 * rollPercent)
        );
        buildMaker.addItemCandidate(
            Item(ITEM_TYPE::BLESSING_ENDING_THE_STORM, "Grand Mysteries of the Deep")
            .withStat(STAT_NAME::CHANCE_TO_SHRED_LIGHTNING_RES, 50 * rollPercent)
        );
        buildMaker.addItemCandidate(
            Item(ITEM_TYPE::BLESSING_ENDING_THE_STORM, "Grand Might of the Sea Titan")
            .withStat(STAT_NAME::INCREASED_COLD_DAMAGE, 100 * rollPercent)
        );
    }
    //logic.tests();
    buildMaker.makeGoodBuild();
}