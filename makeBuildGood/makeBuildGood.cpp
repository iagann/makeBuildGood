#include "BuildMaker.h"

#include <iostream>


int main()
{
    BuildMaker buildMaker;
    // HELM
    {
        buildMaker.addItemCandidate(
            Item(ITEM_TYPE::HELM, "Boneclamor Barbute")
            .withStat(STAT_NAME::INTELLIGENCE, 16)
            .withStat(STAT_NAME::DEXTERITY, 8)
            .withStat(STAT_NAME::INTELLIGENCE, 13)
            .withStat(STAT_NAME::DEXTERITY, 13)
        );
        buildMaker.addItemCandidate(
            Item(ITEM_TYPE::HELM, "Boneclamor Barbute")
            .withStat(STAT_NAME::INTELLIGENCE, 16)
            .withStat(STAT_NAME::CRITICAL_STRIKE_AVOIDANCE, 37)
            .withStat(STAT_NAME::INTELLIGENCE, 13)
            .withStat(STAT_NAME::DEXTERITY, 13)
        );
    }
    // AMULET
    {
        buildMaker.addItemCandidate(
            Item(ITEM_TYPE::AMULET, "Death rattle")
            .withStat(STAT_NAME::INCREASED_MINION_DAMAGE, 140)
            .withStat(STAT_NAME::ARMOUR_SHRED_CHANCE, 117)
            .withStat(STAT_NAME::INCREASED_MINION_DAMAGE, 35)
            .withStat(STAT_NAME::INCREASED_MINION_CRITICAL_STRIKE_CHANCE, 35)
            .withStat(STAT_NAME::INCREASED_MINION_CRITICAL_STRIKE_MULTIPLIER, 65)
            .withStat(STAT_NAME::INTELLIGENCE, 10)
        );
        buildMaker.addItemCandidate(
            Item(ITEM_TYPE::AMULET, "Death rattle")
            .withStat(STAT_NAME::INCREASED_MINION_DAMAGE, 70)
            .withStat(STAT_NAME::ARMOUR_SHRED_CHANCE, 234)
            .withStat(STAT_NAME::INCREASED_MINION_DAMAGE, 35)
            .withStat(STAT_NAME::INCREASED_MINION_CRITICAL_STRIKE_CHANCE, 35)
            .withStat(STAT_NAME::INCREASED_MINION_CRITICAL_STRIKE_MULTIPLIER, 65)
            .withStat(STAT_NAME::INTELLIGENCE, 10)
        );
    }
    // BOW
    {
        buildMaker.addItemCandidate(
            Item(ITEM_TYPE::BOW, "Uethrin's Stand")
            .withStat(STAT_NAME::INCREASED_DAMAGE, 105)
            .withStat(STAT_NAME::FLAT_PHYSICAL_DAMAGE, 21)
            .withStat(STAT_NAME::FLAT_MINION_PHYSICAL_DAMAGE, 32)
            .withStat(STAT_NAME::PHYSICAL_PENETRATION, 12)
            .withStat(STAT_NAME::FLAT_PHYSICAL_DAMAGE, 18)
            .withStat(STAT_NAME::BASE_CRITICAL_STRIKE_CHANCE, 3)
            .withStat(STAT_NAME::FLAT_MINION_PHYSICAL_DAMAGE, 25)
        );
        buildMaker.addItemCandidate(
            Item(ITEM_TYPE::BOW, "Uethrin's Stand")
            .withStat(STAT_NAME::INCREASED_DAMAGE, 210)
            .withStat(STAT_NAME::FLAT_PHYSICAL_DAMAGE, 21)
            .withStat(STAT_NAME::FLAT_MINION_PHYSICAL_DAMAGE, 17)
            .withStat(STAT_NAME::PHYSICAL_PENETRATION, 12)
            .withStat(STAT_NAME::FLAT_PHYSICAL_DAMAGE, 18)
            .withStat(STAT_NAME::BASE_CRITICAL_STRIKE_CHANCE, 3)
            .withStat(STAT_NAME::FLAT_MINION_PHYSICAL_DAMAGE, 25)
        );
    }
    // BODY
    {
        buildMaker.addItemCandidate(
            Item(ITEM_TYPE::BODY, "The Kestrel")
            .withStat(STAT_NAME::ATTACK_SPEED, 48)
            .withStat(STAT_NAME::INCREASED_MINION_DAMAGE, 90)
            .withStat(STAT_NAME::LEVEL_OF_BALLISTA, 1)
        );
        buildMaker.addItemCandidate(
            Item(ITEM_TYPE::BODY, "Woven Flesh")
            .withStat(STAT_NAME::ATTACK_SPEED, 48)
            .withStat(STAT_NAME::INCREASED_MINION_DAMAGE, 90)
            .withStat(STAT_NAME::CRITICAL_STRIKE_AVOIDANCE, 100)
        );
    }
    // QUIVER
    {
        buildMaker.addItemCandidate(
            Item(ITEM_TYPE::QUIVER, "Zeural's Hunt")
            .withStat(STAT_NAME::INCREASED_MINION_DAMAGE, 120)
            .withStat(STAT_NAME::FLAT_PHYSICAL_DAMAGE, 12)
            .withStat(STAT_NAME::SHOCK_CHANCE, 30)
            .withStat(STAT_NAME::INCREASED_CRITICAL_STRIKE_MULTIPLIER, 35)
            .withStat(STAT_NAME::FLAT_LIGHTNING_DAMAGE, 32)
        );
        buildMaker.addItemCandidate(
            Item(ITEM_TYPE::QUIVER, "Zeural's Hunt")
            .withStat(STAT_NAME::INCREASED_MINION_DAMAGE, 120)
            .withStat(STAT_NAME::FLAT_PHYSICAL_DAMAGE, 12)
            .withStat(STAT_NAME::ARMOUR_SHRED_CHANCE, 100)
            .withStat(STAT_NAME::INCREASED_CRITICAL_STRIKE_MULTIPLIER, 35)
            .withStat(STAT_NAME::FLAT_LIGHTNING_DAMAGE, 32)
        );
        buildMaker.addItemCandidate(
            Item(ITEM_TYPE::QUIVER, "Zeural's Hunt")
            .withStat(STAT_NAME::INCREASED_MINION_DAMAGE, 60)
            .withStat(STAT_NAME::FLAT_PHYSICAL_DAMAGE, 24)
            .withStat(STAT_NAME::SHOCK_CHANCE, 30)
            .withStat(STAT_NAME::INCREASED_CRITICAL_STRIKE_MULTIPLIER, 35)
            .withStat(STAT_NAME::FLAT_LIGHTNING_DAMAGE, 32)
        );
        buildMaker.addItemCandidate(
            Item(ITEM_TYPE::QUIVER, "Zeural's Hunt")
            .withStat(STAT_NAME::INCREASED_MINION_DAMAGE, 60)
            .withStat(STAT_NAME::FLAT_PHYSICAL_DAMAGE, 24)
            .withStat(STAT_NAME::ARMOUR_SHRED_CHANCE, 100)
            .withStat(STAT_NAME::INCREASED_CRITICAL_STRIKE_MULTIPLIER, 35)
            .withStat(STAT_NAME::FLAT_LIGHTNING_DAMAGE, 32)
        );


        buildMaker.addItemCandidate(
            Item(ITEM_TYPE::QUIVER, "Exalted Skalnir Quiver")
            .withStat(STAT_NAME::INCREASED_MINION_DAMAGE, 120)
            .withStat(STAT_NAME::FLAT_PHYSICAL_DAMAGE, 12)
            .withStat(STAT_NAME::INCREASED_CRITICAL_STRIKE_MULTIPLIER, 35)
            .withStat(STAT_NAME::SHOCK_CHANCE, 30)
            .withStat(STAT_NAME::ARMOUR_SHRED_CHANCE, 100)
        );
        buildMaker.addItemCandidate(
            Item(ITEM_TYPE::QUIVER, "Exalted Skalnir Quiver")
            .withStat(STAT_NAME::INCREASED_MINION_DAMAGE, 50)
            .withStat(STAT_NAME::FLAT_PHYSICAL_DAMAGE, 24)
            .withStat(STAT_NAME::INCREASED_CRITICAL_STRIKE_MULTIPLIER, 35)
            .withStat(STAT_NAME::SHOCK_CHANCE, 30)
            .withStat(STAT_NAME::ARMOUR_SHRED_CHANCE, 100)
        );
    }
    // RING
    {
        buildMaker.addItemCandidate(
            Item(ITEM_TYPE::RING, "Hollow Finger")
            .withStat(STAT_NAME::INTELLIGENCE, 16)
            .withStat(STAT_NAME::INCREASED_MINION_DAMAGE, 60)
            .withStat(STAT_NAME::CRITICAL_STRIKE_AVOIDANCE, 37)
            .withStat(STAT_NAME::INCREASED_MINION_DAMAGE, 35)
            .withStat(STAT_NAME::INCREASED_MINION_CRITICAL_STRIKE_MULTIPLIER, 35)
        );
        buildMaker.addItemCandidate(
            Item(ITEM_TYPE::RING, "Hollow Finger")
            .withStat(STAT_NAME::INTELLIGENCE, 16)
            .withStat(STAT_NAME::DEXTERITY, 8)
            .withStat(STAT_NAME::CRITICAL_STRIKE_AVOIDANCE, 37)
            .withStat(STAT_NAME::INCREASED_MINION_DAMAGE, 35)
            .withStat(STAT_NAME::INCREASED_MINION_CRITICAL_STRIKE_MULTIPLIER, 35)
        );
    }
    //BELT
    {
        buildMaker.addItemCandidate(
            Item(ITEM_TYPE::BELT, "Jungle Queen's Chaps of Holding")
            .withStat(STAT_NAME::INCREASED_MINION_DAMAGE, 60)
            .withStat(STAT_NAME::INCREASED_PHYSICAL_DAMAGE, 50)
            .withStat(STAT_NAME::INCREASED_MINION_PHYSICAL_DAMAGE, 50)
            .withStat(STAT_NAME::DEXTERITY, 10)
            .withStat(STAT_NAME::CRITICAL_STRIKE_AVOIDANCE, 37)
        );
    }
    //GLOVES
    {
        buildMaker.addItemCandidate(
            Item(ITEM_TYPE::GLOVES, "Blood Roost")
            .withStat(STAT_NAME::INTELLIGENCE, 16)
            .withStat(STAT_NAME::DEXTERITY, 8)
            .withStat(STAT_NAME::DEXTERITY, 15)
        );
        buildMaker.addItemCandidate(
            Item(ITEM_TYPE::GLOVES, "Blood Roost")
            .withStat(STAT_NAME::INTELLIGENCE, 16)
            .withStat(STAT_NAME::INCREASED_MINION_DAMAGE, 60)
            .withStat(STAT_NAME::DEXTERITY, 15)
        );
        buildMaker.addItemCandidate(
            Item(ITEM_TYPE::GLOVES, "Stormhide Paws")
            .withStat(STAT_NAME::INTELLIGENCE, 16)
            .withStat(STAT_NAME::DEXTERITY, 8)
            .withStat(STAT_NAME::INCREASED_COLD_DAMAGE, 45)
            .withStat(STAT_NAME::ALL_ATRIBUTES, 1)
            .withStat(STAT_NAME::CRITICAL_STRIKE_AVOIDANCE, 37)
        );
        buildMaker.addItemCandidate(
            Item(ITEM_TYPE::GLOVES, "Stormhide Paws")
            .withStat(STAT_NAME::INTELLIGENCE, 16)
            .withStat(STAT_NAME::INCREASED_MINION_DAMAGE, 60)
            .withStat(STAT_NAME::INCREASED_COLD_DAMAGE, 45)
            .withStat(STAT_NAME::ALL_ATRIBUTES, 1)
            .withStat(STAT_NAME::CRITICAL_STRIKE_AVOIDANCE, 37)
        );
        buildMaker.addItemCandidate(
            Item(ITEM_TYPE::GLOVES, "Stormhide Paws")
            .withStat(STAT_NAME::INTELLIGENCE, 16)
            .withStat(STAT_NAME::DEXTERITY, 8)
            .withStat(STAT_NAME::INCREASED_COLD_DAMAGE, 45)
            .withStat(STAT_NAME::ALL_ATRIBUTES, 1)
            .withStat(STAT_NAME::ARMOUR_SHRED_CHANCE, 100)
        );
        buildMaker.addItemCandidate(
            Item(ITEM_TYPE::GLOVES, "Stormhide Paws")
            .withStat(STAT_NAME::INTELLIGENCE, 16)
            .withStat(STAT_NAME::INCREASED_MINION_DAMAGE, 60)
            .withStat(STAT_NAME::INCREASED_COLD_DAMAGE, 45)
            .withStat(STAT_NAME::ALL_ATRIBUTES, 1)
            .withStat(STAT_NAME::ARMOUR_SHRED_CHANCE, 100)
        );
        buildMaker.addItemCandidate(
            Item(ITEM_TYPE::GLOVES, "Swaddling of the Erased")
            .withStat(STAT_NAME::INTELLIGENCE, 16)
            .withStat(STAT_NAME::DEXTERITY, 16)
            .withStat(STAT_NAME::ALL_ATRIBUTES, 6)
        );
        buildMaker.addItemCandidate(
            Item(ITEM_TYPE::GLOVES, "Swaddling of the Erased")
            .withStat(STAT_NAME::INTELLIGENCE, 16)
            .withStat(STAT_NAME::INCREASED_MINION_DAMAGE, 120)
            .withStat(STAT_NAME::ALL_ATRIBUTES, 6)
        );
        buildMaker.addItemCandidate(
            Item(ITEM_TYPE::GLOVES, "Exalted Ascetic Gloves")
            .withStat(STAT_NAME::INTELLIGENCE, 16)
            .withStat(STAT_NAME::DEXTERITY, 8)
            .withStat(STAT_NAME::ALL_ATRIBUTES, 6)
            .withStat(STAT_NAME::CRITICAL_STRIKE_AVOIDANCE, 37)
            .withStat(STAT_NAME::ARMOUR_SHRED_CHANCE, 100)
        );
        buildMaker.addItemCandidate(
            Item(ITEM_TYPE::GLOVES, "Exalted Ascetic Gloves")
            .withStat(STAT_NAME::INTELLIGENCE, 16)
            .withStat(STAT_NAME::INCREASED_MINION_DAMAGE, 60)
            .withStat(STAT_NAME::ALL_ATRIBUTES, 6)
            .withStat(STAT_NAME::CRITICAL_STRIKE_AVOIDANCE, 37)
            .withStat(STAT_NAME::ARMOUR_SHRED_CHANCE, 100)
        );
    }
    //BOOTS
    {
        buildMaker.addItemCandidate(
            Item(ITEM_TYPE::BOOTS, "Mourningfrost")
            .withStat(STAT_NAME::INTELLIGENCE, 16)
            .withStat(STAT_NAME::INCREASED_MINION_DAMAGE, 70)
            .withStat(STAT_NAME::FLAT_COLD_PER_DEX, 1)
        );
    }
    //RELIC
    {
        buildMaker.addItemCandidate(
            Item(ITEM_TYPE::RELIC, "Melvern's Writ")
            .withStat(STAT_NAME::ATTACK_SPEED, 30)
            .withStat(STAT_NAME::INCREASED_MINION_DAMAGE, 60)
            .withStat(STAT_NAME::INCREASED_MINION_DAMAGE, 90)
            .withStat(STAT_NAME::BASE_MINION_CRITICAL_STRIKE_CHANCE, 3)
            .withStat(STAT_NAME::DEXTERITY, 8)
        );
        buildMaker.addItemCandidate(
            Item(ITEM_TYPE::RELIC, "Melvern's Writ")
            .withStat(STAT_NAME::ATTACK_SPEED, 30)
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
            .withStat(STAT_NAME::INCREASED_CRITICAL_STRIKE_MULTIPLIER, 25)
            .withStat(STAT_NAME::INCREASED_MINION_CRITICAL_STRIKE_MULTIPLIER, 25)
            .withStat(STAT_NAME::INCREASED_CRITICAL_STRIKE_CHANCE, 62)
        );
        buildMaker.addItemCandidate(
            Item(ITEM_TYPE::BIG_IDOL, "Adorned")
            .withStat(STAT_NAME::INCREASED_CRITICAL_STRIKE_MULTIPLIER, 25)
            .withStat(STAT_NAME::INCREASED_MINION_CRITICAL_STRIKE_MULTIPLIER, 25)
            .withStat(STAT_NAME::ARMOUR_SHRED_EFFECT, 86)
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
            .withStat(STAT_NAME::INCREASED_CRITICAL_STRIKE_MULTIPLIER, 40)
        );
        buildMaker.addItemCandidate(
            Item(ITEM_TYPE::BLESSING_REIGN_OF_DRAGONS, "Grand Survival of Might")
            .withStat(STAT_NAME::CRITICAL_STRIKE_AVOIDANCE, 70)
        );
        buildMaker.addItemCandidate(
            Item(ITEM_TYPE::BLESSING_SPIRITS_OF_FIRE, "Grand Spirit of Command")
            .withStat(STAT_NAME::INCREASED_MINION_DAMAGE, 100)
        );
        buildMaker.addItemCandidate(
            Item(ITEM_TYPE::BLESSING_THE_AGE_OF_WINTER, "Grand Fury of the North")
            .withStat(STAT_NAME::CHANCE_TO_SHRED_PHYS_RES, 50)
        );
        buildMaker.addItemCandidate(
            Item(ITEM_TYPE::BLESSING_ENDING_THE_STORM, "Grand Might of the Sea Titan")
            .withStat(STAT_NAME::INCREASED_COLD_DAMAGE, 100)
        );
        buildMaker.addItemCandidate(
            Item(ITEM_TYPE::BLESSING_ENDING_THE_STORM, "Grand Mysteries of the Deep")
            .withStat(STAT_NAME::CHANCE_TO_SHRED_LIGHTNING_RES, 50)
        );
    }
    //logic.tests();
    buildMaker.makeGoodBuild();
}