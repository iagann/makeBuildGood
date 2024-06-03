#include "BuildMaker.h"

#include <iostream>

#define PERFECT 0

#define JULRA_STARDIAL 0

void testGear() {
    BuildMaker buildMaker;
    buildMaker.stacks = true;
    bool peak = true;
    double rollPercent = 1;
    // HELM
    {
        buildMaker.addItemCandidate(
            Item(ITEM_TYPE::HELM, "Peak of the Mountain")
            .withStat(STAT_NAME::INTELLIGENCE, 8 * rollPercent)
            .withStat(STAT_NAME::DEXTERITY, 16)
            .withStat(STAT_NAME::CRITICAL_STRIKE_AVOIDANCE, 37 * rollPercent)
            .withStat(STAT_NAME::ALL_ATRIBUTES, 5 * rollPercent)
            .withStat(STAT_NAME::INCREASED_CRITICAL_STRIKE_CHANCE, 290 * rollPercent)
        );
    }
    // AMULET
    {
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
            Item(ITEM_TYPE::BODY, "Woven Flesh")
            .withStat(STAT_NAME::INCREASED_ATTACK_SPEED, 48)
            .withStat(STAT_NAME::DEXTERITY, 12 * rollPercent)
            .withStat(STAT_NAME::CRITICAL_STRIKE_AVOIDANCE, 100)
        );
    }
    // QUIVER
    {
        buildMaker.addItemCandidate(
            Item(ITEM_TYPE::QUIVER, "Zeural's Hunt")
            .withStat(STAT_NAME::DEXTERITY, 16)
            .withStat(STAT_NAME::FLAT_PHYSICAL_DAMAGE, 12 * rollPercent)
            .withStat(STAT_NAME::ARMOUR_SHRED_CHANCE, 100 * rollPercent)
            .withStat(STAT_NAME::INCREASED_CRITICAL_STRIKE_MULTIPLIER, 35 * rollPercent)
            .withStat(STAT_NAME::FLAT_LIGHTNING_DAMAGE, 32 * rollPercent)
        );
    }
    // RING
    {
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
    }
    //logic.tests();
    buildMaker.makeGoodBuild();
}


void perfectGear() {
    BuildMaker buildMaker;
    buildMaker.stacks = true;
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
            .withStat(STAT_NAME::INCREASED_MINION_DAMAGE, 140)
            .withStat(STAT_NAME::INCREASED_CRITICAL_STRIKE_MULTIPLIER, 29 * rollPercent)
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
    }
    // BOW
    {
        /*
        // 3% less
        buildMaker.addItemCandidate(
            Item(ITEM_TYPE::BOW, "Uethrin's Stand")
            .withStat(STAT_NAME::INCREASED_DAMAGE, 210)
            .withStat(STAT_NAME::FLAT_PHYSICAL_DAMAGE, 21 * rollPercent)
            .withStat(STAT_NAME::FLAT_MINION_PHYSICAL_DAMAGE, 17 * rollPercent)
            .withStat(STAT_NAME::FLAT_MINION_PHYSICAL_DAMAGE_FALCON, 17 * rollPercent)
            .withStat(STAT_NAME::PHYSICAL_PENETRATION, 12 * rollPercent)
            .withStat(STAT_NAME::FLAT_PHYSICAL_DAMAGE, 18 * rollPercent)
            .withStat(STAT_NAME::BASE_CRITICAL_STRIKE_CHANCE, 3 * rollPercent)
            .withStat(STAT_NAME::FLAT_MINION_PHYSICAL_DAMAGE, 25 * rollPercent)
        );
        */
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
        /*
        2.31% less
        buildMaker.addItemCandidate(
            Item(ITEM_TYPE::BODY, "The Kestrel")
            .withStat(STAT_NAME::INCREASED_ATTACK_SPEED, 48)
            .withStat(STAT_NAME::DEXTERITY, 12 * rollPercent)
            .withStat(STAT_NAME::LEVEL_OF_BALLISTA, 1)
            .withStat(STAT_NAME::INCREASED_MOVEMENT_SPEED, 16)
        );
        */
        /*
        3% less
        buildMaker.addItemCandidate(
            Item(ITEM_TYPE::BODY, "The Kestrel")
            .withStat(STAT_NAME::INCREASED_ATTACK_SPEED, 48)
            .withStat(STAT_NAME::DEXTERITY, 12 * rollPercent)
            .withStat(STAT_NAME::LEVEL_OF_BALLISTA, 1)
        );
        */
        buildMaker.addItemCandidate(
            Item(ITEM_TYPE::BODY, "Woven Flesh")
            .withStat(STAT_NAME::INCREASED_ATTACK_SPEED, 48)
            .withStat(STAT_NAME::DEXTERITY, 12 * rollPercent)
            .withStat(STAT_NAME::CRITICAL_STRIKE_AVOIDANCE, 100)
        );
    }
    // QUIVER
    {
        /*
        // 7.3% less
        buildMaker.addItemCandidate(
            Item(ITEM_TYPE::QUIVER, "Exalted Skalnir Quiver")
            .withStat(STAT_NAME::DEXTERITY, 16)
            .withStat(STAT_NAME::FLAT_PHYSICAL_DAMAGE, 12 * rollPercent)
            .withStat(STAT_NAME::ARMOUR_SHRED_CHANCE, 100 * rollPercent)
            .withStat(STAT_NAME::SHOCK_CHANCE, 30 * rollPercent)
            .withStat(STAT_NAME::INCREASED_CRITICAL_STRIKE_MULTIPLIER, 35 * rollPercent)
        );
        buildMaker.addItemCandidate(
            Item(ITEM_TYPE::QUIVER, "Exalted Skalnir Quiver")
            .withStat(STAT_NAME::DEXTERITY, 16)
            .withStat(STAT_NAME::INCREASED_MINION_DAMAGE, 60 * rollPercent)
            .withStat(STAT_NAME::ARMOUR_SHRED_CHANCE, 100 * rollPercent)
            .withStat(STAT_NAME::SHOCK_CHANCE, 30 * rollPercent)
            .withStat(STAT_NAME::INCREASED_CRITICAL_STRIKE_MULTIPLIER, 35 * rollPercent)
        );
        */
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
            .withStat(STAT_NAME::ARMOUR_SHRED_CHANCE, 100 * rollPercent)
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
            .withStat(STAT_NAME::INCREASED_MINION_DAMAGE, 60 * rollPercent)
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
        if (JULRA_STARDIAL) {
            buildMaker.addItemCandidate(
                Item(ITEM_TYPE::RING, "Julra's Stardial")
                .withStat(STAT_NAME::INTELLIGENCE, 16 * 3)
                .withStat(STAT_NAME::DEXTERITY, 8 * 3)
            );
            buildMaker.addItemCandidate(
                Item(ITEM_TYPE::RING, "Julra's Stardial")
                .withStat(STAT_NAME::INTELLIGENCE, 8 * 3)
                .withStat(STAT_NAME::DEXTERITY, 16 * 3)
            );
        }
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
        /*
        // 1.6% less
        buildMaker.addItemCandidate(
            Item(ITEM_TYPE::BIG_IDOL, "Adorned")
            .withStat(STAT_NAME::FLAT_MINION_PHYSICAL_DAMAGE, 10)
            .withStat(STAT_NAME::ARMOUR_SHRED_EFFECT, 86 * rollPercent)
        );
        */
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

void realGearPassives() {
    BuildMaker buildMaker;
    buildMaker.allowSameItems = false;
    buildMaker.stacks = true;
    // ITEMS
    {
        // HELM
        {
            buildMaker.addItemCandidate(
                Item(ITEM_TYPE::HELM, "Peak of the Mountain")
                .withStat(STAT_NAME::ALL_ATRIBUTES, 4)
                .withStat(STAT_NAME::INCREASED_CRITICAL_STRIKE_CHANCE, 253)
            );
        }
        // AMULET
        {
            buildMaker.addItemCandidate(
                Item(ITEM_TYPE::AMULET, "Death rattle")
                .withStat(STAT_NAME::INCREASED_MINION_DAMAGE, 104)
                .withStat(STAT_NAME::INCREASED_MINION_DAMAGE, 9)
                .withStat(STAT_NAME::INCREASED_MINION_CRITICAL_STRIKE_CHANCE, 13)
                .withStat(STAT_NAME::INCREASED_MINION_CRITICAL_STRIKE_MULTIPLIER, 27)
                .withStat(STAT_NAME::INTELLIGENCE, 9)
            );
        }
        // BOW
        {
            buildMaker.addItemCandidate(
                Item(ITEM_TYPE::BOW, "Uethrin's Stand")
                .withStat(STAT_NAME::FLAT_MINION_PHYSICAL_DAMAGE, 31)
                .withStat(STAT_NAME::FLAT_MINION_PHYSICAL_DAMAGE_FALCON, 31)
                .withStat(STAT_NAME::FLAT_PHYSICAL_DAMAGE, 18)
                .withStat(STAT_NAME::BASE_CRITICAL_STRIKE_CHANCE, 3)
                .withStat(STAT_NAME::FLAT_MINION_PHYSICAL_DAMAGE, 17)
            );
        }
        // BODY
        {

            buildMaker.addItemCandidate(
                Item(ITEM_TYPE::BODY, "Urzil's pride")
                .withStat(STAT_NAME::INCREASED_ATTACK_SPEED, 49)
            );
        }
        // QUIVER
        {
            buildMaker.addItemCandidate(
                Item(ITEM_TYPE::QUIVER, "Rare Skalnir Quiver")
                .withStat(STAT_NAME::DEXTERITY, 7)
                .withStat(STAT_NAME::FLAT_PHYSICAL_DAMAGE, 11)
                .withStat(STAT_NAME::ARMOUR_SHRED_CHANCE, 64)
                .withStat(STAT_NAME::INCREASED_CRITICAL_STRIKE_MULTIPLIER, 34)
            );
        }
        // RINGS
        {
            buildMaker.addItemCandidate(
                Item(ITEM_TYPE::RING, "Rare Turquoise Ring")
                .withStat(STAT_NAME::INCREASED_MINION_DAMAGE, 56)
                .withStat(STAT_NAME::INCREASED_MINION_DAMAGE, 34)
                .withStat(STAT_NAME::INCREASED_MINION_CRITICAL_STRIKE_MULTIPLIER, 34)
            );
            buildMaker.addItemCandidate(
                Item(ITEM_TYPE::RING, "Rare Turquoise Ring")
                .withStat(STAT_NAME::INTELLIGENCE, 7)
                .withStat(STAT_NAME::CRITICAL_STRIKE_AVOIDANCE, 37)
                .withStat(STAT_NAME::INCREASED_MINION_DAMAGE, 35)
                .withStat(STAT_NAME::INCREASED_MINION_CRITICAL_STRIKE_MULTIPLIER, 35)
            );
        }
        //BELT
        {
            buildMaker.addItemCandidate(
                Item(ITEM_TYPE::BELT, "Jungle Queen's Chaps of Holding")
                .withStat(STAT_NAME::INCREASED_PHYSICAL_DAMAGE, 36)
                .withStat(STAT_NAME::INCREASED_MINION_PHYSICAL_DAMAGE, 36)
                .withStat(STAT_NAME::DEXTERITY, 8)
            );
        }
        //GLOVES
        {
            buildMaker.addItemCandidate(
                Item(ITEM_TYPE::GLOVES, "Rare")
                .withStat(STAT_NAME::INTELLIGENCE, 7)
                .withStat(STAT_NAME::DEXTERITY, 8)
            );
        }
        //BOOTS
        {
            buildMaker.addItemCandidate(
                Item(ITEM_TYPE::BOOTS, "Mourningfrost")
                .withStat(STAT_NAME::INTELLIGENCE, 15)
                .withStat(STAT_NAME::FLAT_COLD_PER_DEX, 1)
            );
        }
        //RELIC
        {
            buildMaker.addItemCandidate(
                Item(ITEM_TYPE::RELIC, "Exalted")
                .withStat(STAT_NAME::INCREASED_ATTACK_SPEED, 19)
                .withStat(STAT_NAME::DEXTERITY, 14)
            );
        }
        //IDOLS
        {
            buildMaker.addItemCandidate(
                Item(ITEM_TYPE::BIG_IDOL, "Adorned")
                .withStat(STAT_NAME::INCREASED_CRITICAL_STRIKE_MULTIPLIER, 22)
                .withStat(STAT_NAME::INCREASED_MINION_CRITICAL_STRIKE_MULTIPLIER, 22)
            );
            buildMaker.addItemCandidate(
                Item(ITEM_TYPE::BIG_IDOL, "Adorned")
                .withStat(STAT_NAME::INCREASED_CRITICAL_STRIKE_MULTIPLIER, 24)
                .withStat(STAT_NAME::INCREASED_MINION_CRITICAL_STRIKE_MULTIPLIER, 24)
            );
            buildMaker.addItemCandidate(
                Item(ITEM_TYPE::BIG_IDOL, "Adorned")
                .withStat(STAT_NAME::INCREASED_CRITICAL_STRIKE_MULTIPLIER, 24)
                .withStat(STAT_NAME::INCREASED_MINION_CRITICAL_STRIKE_MULTIPLIER, 24)
                .withStat(STAT_NAME::INCREASED_CRITICAL_STRIKE_CHANCE, 48)
            );
            buildMaker.addItemCandidate(
                Item(ITEM_TYPE::BIG_IDOL, "Adorned")
                .withStat(STAT_NAME::INCREASED_CRITICAL_STRIKE_MULTIPLIER, 21)
                .withStat(STAT_NAME::INCREASED_MINION_CRITICAL_STRIKE_MULTIPLIER, 21)
                .withStat(STAT_NAME::ARMOUR_SHRED_EFFECT, 76)
            );
            buildMaker.addItemCandidate(
                Item(ITEM_TYPE::BIG_IDOL, "Adorned")
                .withStat(STAT_NAME::FLAT_MINION_PHYSICAL_DAMAGE, 10)
                .withStat(STAT_NAME::ARMOUR_SHRED_EFFECT, 86)
            );
            buildMaker.addItemCandidate(
                Item(ITEM_TYPE::SMALL_IDOL, "Eterran")
                .withStat(STAT_NAME::INCREASED_PHYSICAL_DAMAGE, 8)
                .withStat(STAT_NAME::INCREASED_MINION_PHYSICAL_DAMAGE, 8)
            );
            buildMaker.addItemCandidate(
                Item(ITEM_TYPE::SMALL_IDOL, "Eterran")
                .withStat(STAT_NAME::INCREASED_PHYSICAL_DAMAGE, 7)
                .withStat(STAT_NAME::INCREASED_MINION_PHYSICAL_DAMAGE, 7)
            );
            buildMaker.addItemCandidate(
                Item(ITEM_TYPE::SMALL_IDOL, "Eterran")
                .withStat(STAT_NAME::INCREASED_PHYSICAL_DAMAGE, 7)
                .withStat(STAT_NAME::INCREASED_MINION_PHYSICAL_DAMAGE, 7)
            );
            buildMaker.addItemCandidate(
                Item(ITEM_TYPE::SMALL_IDOL, "Eterran")
                .withStat(STAT_NAME::INCREASED_PHYSICAL_DAMAGE, 6)
                .withStat(STAT_NAME::INCREASED_MINION_PHYSICAL_DAMAGE, 6)
            );
        }
        //BLESSINGS
        {
            buildMaker.addItemCandidate(
                Item(ITEM_TYPE::BLESSING_BLACK_SUN, "Grand Emptiness of Ash")
                .withStat(STAT_NAME::INCREASED_CRITICAL_STRIKE_MULTIPLIER, 34)
            );
            buildMaker.addItemCandidate(
                Item(ITEM_TYPE::BLESSING_REIGN_OF_DRAGONS, "Grand Survival of Might")
                .withStat(STAT_NAME::CRITICAL_STRIKE_AVOIDANCE, 68)
            );
            buildMaker.addItemCandidate(
                Item(ITEM_TYPE::BLESSING_SPIRITS_OF_FIRE, "Grand Spirit of Command")
                .withStat(STAT_NAME::INCREASED_MINION_DAMAGE, 93)
            );
            /*buildMaker.addItemCandidate(
                Item(ITEM_TYPE::BLESSING_THE_AGE_OF_WINTER, "Grand Fury of the North")
                .withStat(STAT_NAME::CHANCE_TO_SHRED_PHYS_RES, 0)
            );
            buildMaker.addItemCandidate(
                Item(ITEM_TYPE::BLESSING_ENDING_THE_STORM, "Grand Mysteries of the Deep")
                .withStat(STAT_NAME::CHANCE_TO_SHRED_LIGHTNING_RES, 50)
            );*/
        }
    }
    // PASSIVES
    {
        PassiveCombination<PASSIVE_NAME> realPassives;
        // UNCHANGED 
        {
            realPassives.setPassivePoints(PASSIVE_NAME::GUILE, PASSIVE_CLASS_NAME::BASE, 1);
            realPassives.setPassivePoints(PASSIVE_NAME::EVASION, PASSIVE_CLASS_NAME::BASE, 1);
            realPassives.setPassivePoints(PASSIVE_NAME::PURSUIT, PASSIVE_CLASS_NAME::BLADEDANCER, 5);
            realPassives.setPassivePoints(PASSIVE_NAME::WOUND_MAKER, PASSIVE_CLASS_NAME::MARKSMAN, 2);
            realPassives.setPassivePoints(PASSIVE_NAME::HANDLER, PASSIVE_CLASS_NAME::FALCONER, 8);
            realPassives.setPassivePoints(PASSIVE_NAME::AGILE_HUNT, PASSIVE_CLASS_NAME::FALCONER, 8);
            realPassives.setPassivePoints(PASSIVE_NAME::TACTITIAN, PASSIVE_CLASS_NAME::FALCONER, 6);
            realPassives.setPassivePoints(PASSIVE_NAME::COORDINATED_FADE, PASSIVE_CLASS_NAME::FALCONER, 1);
            realPassives.setPassivePoints(PASSIVE_NAME::INTUITIVE_CONNECTION, PASSIVE_CLASS_NAME::FALCONER, 1);
            realPassives.setPassivePoints(PASSIVE_NAME::EXPEDIENCY, PASSIVE_CLASS_NAME::FALCONER, 5);
            realPassives.setPassivePoints(PASSIVE_NAME::TACTITIAN, PASSIVE_CLASS_NAME::FALCONER, 6);
        }
        // BASE
        realPassives.setPassivePoints(PASSIVE_NAME::SWIFT_ASSASSIN, PASSIVE_CLASS_NAME::BASE, 5);
        realPassives.setPassivePoints(PASSIVE_NAME::STEADY_HAND, PASSIVE_CLASS_NAME::BASE, 8);
        realPassives.setPassivePoints(PASSIVE_NAME::AGILITY, PASSIVE_CLASS_NAME::BASE, 5);
        // BLADEDAMCER
        realPassives.setPassivePoints(PASSIVE_NAME::CLOAK_OF_SHADOWS, PASSIVE_CLASS_NAME::BLADEDANCER, 0);
        // MARKSMAN
        realPassives.setPassivePoints(PASSIVE_NAME::FOCUS_FIRE, PASSIVE_CLASS_NAME::MARKSMAN, 0);
        realPassives.setPassivePoints(PASSIVE_NAME::ASSASSINS_QUIVER, PASSIVE_CLASS_NAME::MARKSMAN, 5);
        realPassives.setPassivePoints(PASSIVE_NAME::MISSILE_MASTERY, PASSIVE_CLASS_NAME::MARKSMAN, 5);
        realPassives.setPassivePoints(PASSIVE_NAME::CONCENTRATION, PASSIVE_CLASS_NAME::MARKSMAN, 8);
        realPassives.setPassivePoints(PASSIVE_NAME::PURSUIT, PASSIVE_CLASS_NAME::MARKSMAN, 5);
        realPassives.setPassivePoints(PASSIVE_NAME::HEIGHTENED_SENCES, PASSIVE_CLASS_NAME::MARKSMAN, 5);
        // FALCONER
        realPassives.setPassivePoints(PASSIVE_NAME::RANGERS_MARK, PASSIVE_CLASS_NAME::FALCONER, 3);
        realPassives.setPassivePoints(PASSIVE_NAME::EVASION_TACTICS, PASSIVE_CLASS_NAME::FALCONER, 6);
        realPassives.setPassivePoints(PASSIVE_NAME::RELENTLESS_TALONS, PASSIVE_CLASS_NAME::FALCONER, 5);
        realPassives.setPassivePoints(PASSIVE_NAME::NEEDLE_LIKE_PRECISION, PASSIVE_CLASS_NAME::FALCONER, 6);
        realPassives.setPassivePoints(PASSIVE_NAME::FINESSE_THEM, PASSIVE_CLASS_NAME::FALCONER, 7);

        buildMaker.realPassives = realPassives;
    }
    buildMaker.makeGoodBuild();
}

int main()
{
    //testGear();
    //return 0;

    if (PERFECT)
        perfectGear();
    else
        realGearPassives();
}