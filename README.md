# LestaAcademyTestTask

## Build instructions

~~~
git clone https://github.com/PENDOSOS/LestaAcademyTestTask.git
~~~

~~~
cd LestaAcademyTestTask
mkdir build
cd build
cmake ..
cmake --build .
~~~

## Main Game Cycle

1. At the beginning, the player chooses a character class (warrior, barbarian, or bandit).

2. The character fights a random monster:
* Battles are turn-based.
* The character and the monster attack in turns until one of them's health reaches 0.

3. If the character wins, they level up, their health is restored to maximum, and they are offered to replace their current weapon with the one dropped by the monster.

4. If the character loses, the player is prompted to create a new character. Return to step 1.

5. If the character defeats 3 monsters in a row, inform the player that the game is completed.

## Character Creation

The character has 3 attributes:

* **Strength**: The strength value is added to weapon damage.
* **Agility**: Increases the chance to hit or dodge an attack. See the Combat section for details.
* **Stamina**: The stamina value is added to health at each level up.

For a new character, these attributes are a random number between 1 and 3, inclusive.

At the start of the game, the player selects a character class.

### Class Table

| Class | Health per Level | Starting Weapon | Level 1 Bonus | Level 2 Bonus | Level 3 Bonus |
|-----------|-----------------|-----------------|--------------------------------------|--------------------------------------|---------------|
| Bandit | 4 | Dagger | Hidden Attack: +1 damage if character's agility is higher than the target's | Agility +1 | Poison: Deals additional +1 damage on the second turn, +2 on the third, and so on. |
| Warrior | 5 | Sword | Rush: Double weapon damage on the first turn | Shield: -3 to received damage if character's strength is higher than the attacker's | Strength +1 |
| Barbarian | 6 | Cudgel | Fury: +2 damage for the first 3 turns, then -1 damage | Stone Skin: Received damage is reduced by the stamina value | Stamina +1 |

### Weapon Table

| Name | Damage | Damage Type |
|----------------|--------|-------------|
| Sword | 3 | Chopping |
| Cudgel | 3 | Crushing |
| Dagger | 2 | Stabbing |
| Axe | 4 | Chopping |
| Lance | 3 | Stabbing |
| Legendary Sword| 5 | Chopping |

## Example

The player gets initial stats: Strength 1, Agility 3, Stamina 2. They choose the Bandit class: they have 6 health points (4 for the Bandit's first level and 2 from stamina), they are armed with a dagger dealing 3 piercing damage per attack (2 from the dagger itself + 1 from strength), and their damage increases by 1 if their target's agility is lower than theirs.

## Combat

For each battle, a random opponent is chosen from the list:

| Opponent | Health | Weapon Damage | Strength | Agility | Stamina | Features                                                   | Reward for Victory |
|----------|--------|---------------|-----------|----------|------------|------------------------------------------------------------|-------------------|
| Goblin   | 5      | 2             | 1         | 1        | 1          |                                                            | Dagger            |
| Skeleton | 10     | 2             | 2         | 2        | 1          | Takes double damage from bludgeoning weapons               | Cudgel              |
| Slime    | 8      | 1             | 3         | 1        | 2          | Slashing weapons do no damage (but damage from strength and other features, even the Warrior's Rush, works) | Lance             |
| Ghost    | 6      | 3             | 1         | 3        | 1          | Has the Hidden Attack ability like a Level 1 Bandit         | Sword             |
| Golem | 10 | 1 | 3 | 1 | 3 | Has the Stone Skin ability like a Barbarian's second level | Axe |
| Dragon | 20 | 4 | 3 | 3 | 3 | Every 3rd turn breathes fire, dealing an additional 3 damage | Legendary Sword |

## Combat

The battle proceeds in turns, with the character and the monster attacking each other in sequence. The one with higher **Agility** goes first. If their Agility is equal, the character attacks first.

1. When attacking, the hit chance is calculated first: a random number between 1 and the sum of the attacker's and target's Agility is generated. If this number is less than or equal to the target's Agility, the attack misses.

2. If the attack hits, the base damage is calculated as the attacker's weapon damage plus their **Strength**.

3. All damage effects of the attacker are applied.

4. All damage effects of the target are applied.

5. If the final damage is greater than 0, it is subtracted from the target's health.

6. If the target's health drops to 0 or below, the battle ends with the attacker's victory.

7. If the target survives, it is now their turn to attack. Go to step 1.

## After the Battle

After each battle, the character’s health is restored to maximum. Then the player is offered to level up their character.

Like in serious RPGs, we have the option of multiclassing: when leveling up, the player can choose not only the class they started the game with, but any other class as well. In this case, they will receive +1 level in that class and all the bonuses associated with that level.

For example, if a player initially chose Barbarian and then selected Warrior after defeating the first monster, their character would now be Barbarian 1 / Warrior 1. On their first turn, they would deal both additional damage equal to their weapon damage (Warrior’s level 1 bonus) and +2 damage from Barbarian’s Rage.
