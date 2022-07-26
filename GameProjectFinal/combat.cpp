#include <string>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstdio>
#include <windows.h>
#include <conio.h>
#include <cstdlib>
#include <random>

using namespace std;

bool isNumber(const string& str)
{
	for (char const& c : str) {
		if (std::isdigit(c) == 0) return false;
	}
	return true;
}

class Skill {
public:
	string name;
	int damageType;
	//1 for MAG 0 for PHYS for determining which to add to damage.
	int damageBonus;
	int useCase;
	// 1 for healing allies, 0 for damaging enemies.
	int SP_COST;
	int specialThing;
	//to be differenciated later, different things can be implimented this way
	//1 is Starstrike -> 5 attacks
	//2 is restore All -> cures all bad status conditions on allys.
	//3 is fortify -> Player chars get +10 to DEF/MDEF. 
	//4 is give excited condition.
	string desc;
	Skill()
	{
		name = "shall not be named";
		specialThing = 0;
		damageType = 0;
		damageBonus = 0;
		useCase = 0;
		SP_COST = 0;
		desc = "undescribable";
	};

	Skill(int dType, int coolThing, int damageBonus1, int heal, int SP_COSTI, string Name, string Description)
	{
		name = Name;
		specialThing = coolThing;
		damageType = dType;
		damageBonus = damageBonus1;
		useCase = heal;
		SP_COST = SP_COSTI;
		desc = Description;
	};

};

class Klass {
public:
	Skill s[4];
	string name;
	string desc;
	
	Klass()
	{
		
	}

};

class Condition { //pending rework of conditions
	//may not actually do it, but basic framework is here
public:
	string name;
	string desc;
	int duration;
	int str;
	Condition(string n, string d, int a, int b) {
		name = n;
		desc = d;
		duration = a;
		str = b;
	}
}
;
class Unit {
public:
	int HP_MAX;
	int HP_CURR;
	int SP_MAX;
	int SP_CURR;
	int ATK;
	int M_ATK;
	int DEF;
	int M_DEF;
	int LUK;
	int EXP;
	int LVL;
	int condition=0; 
	int tDEF=0;
	int tM_DEF=0;
	int tATK=0;
	int tM_ATK=0;
	//temporary bonuses that end when combat does. (not saved or read from csv)
	int specAi[4] = {0,0,0,0};
	//only enemys care about this.
	Klass c[2];
	//class normal
	//change possible?
	string name;
	int cExp1;
	int cExp2;
	//class experience -> unimplimented now.

	Unit()
	{
		HP_MAX = 0;
		HP_CURR = 0;
		ATK = 0;
		M_ATK = 0;
		DEF = 0;
		M_DEF = 0;
		name = "";
		SP_MAX = 0;
		SP_CURR = 0;
		LVL = 0;
		EXP = 0;
		condition = 0;
	
	}; //constructor basic
	Unit(int hpSet, int spSet, int baseATK, int baseM_ATK, int base_DEF, int base_M_DEF, int base_LUK, string name1, int lvel, int expp)
	{ //constructor with all important PLAYER characteristics
		HP_MAX = hpSet;
		HP_CURR = hpSet;
		ATK = baseATK;
		M_ATK = baseM_ATK;
		DEF = base_DEF;
		M_DEF = base_M_DEF;
		name = name1;
		SP_MAX = spSet;
		SP_CURR = spSet;
		LVL = lvel;
		EXP = expp;
		condition = 0;

	};
	Unit dealDamage(Unit t)
	{
		int damage = 1;
		//can do conditions for resist here.

		damage = ATK + tATK - t.DEF - t.tDEF;
		damage = max(damage, 1);
		t.HP_CURR = max(0, t.HP_CURR - damage);

		srand(time(NULL));
		int critNumber = rand() % 100 + 1;

		if (critNumber > 95) {
			damage = damage * 3;

			cout << name << " critically strikes for " << damage << "  damage to " << t.name << "!\n";
			t.HP_CURR = t.HP_CURR - damage;

		}
		else {
			t.HP_CURR = t.HP_CURR - damage;
			cout << name << " deals " << damage << " damage to "<< t.name <<"!\n";

		}
		return t;
	}
	void setName(string s)
	{
		name = s; //not really neaded
	}
	void printStats(Unit s)
	{ //helpful, but needs expansion
		cout << name << "\nHP: " << s.HP_CURR << "\n";
	}
	void gainExp(Unit a)
	{         
		//checks if EXP is enough ot level up.
		int seed = time(NULL);
		EXP = max((-LVL + a.LVL), 1) * a.EXP;
		while (EXP >= 100)
		{
			LVL++;
			cout << name << " Leveled up to "<< LVL << "!\n";
		  	srand(seed);
	int critNumber = rand() % 2*LUK + LUK/2;
	// LUK as a stat determines level ups. Thats it. Thats all it does
	//Maybe a skill could use it for dmg or something but atm no.

	if (critNumber > ATK) {
		ATK++;
		cout << name << " gained 1 ATK.\n";
		seed = seed * .132123;
		}
		seed = seed* rand();

	if (critNumber > M_ATK) {
		M_ATK++;
		cout << name << " gained 1 MGC.\n";
		seed = seed * .132123;
	}
	if (critNumber > DEF) {
		DEF++;
		cout << name << " gained 1 DEF.\n";
		seed = seed * .132123;

	}
	if (critNumber > M_DEF) {
		M_DEF++;
		cout << name << " gained 1 RES.\n";
		seed = seed * .132123;
	}
	if (critNumber > LUK) {
		LUK++;
		cout << name << " gained 1 LUK.\n";
		seed = seed * .132123;

	}
	if (critNumber > SP_MAX *1.5) {
		SP_MAX = SP_MAX + 10;
		cout << name << " gained 10 MAX SP.\n";
		seed = seed * .132123;

	}
	if (critNumber > HP_MAX *1.2) {
		HP_MAX = HP_MAX + (HP_MAX)/10;
		cout << name << " gained "<< (HP_MAX) / 10<< " MAX HP.\n";
		seed = seed * .132123;

	}
		
	EXP = EXP - 100;
	
	seed = 2 * seed;

	}
		
	}

};

class Item {
public:
	string name;
	string desc;
	int uses;
	//not working atm. Might make it work, might not
	int changeInStat;
	//0 for HP_MAX, 1 for HP_CURR, 2 for ATK, 3 for M_ATK, 4 for DEF, 5 for M_DEF, 6 for LUK, 7 for SP_MAX, 8 for SP_CURR
	int magnitude;
	//how much does it change the stat by?
	Item()
	{
		name = "";
		desc = "";
		uses = 0;
		changeInStat = 0;
		magnitude = 0;
	}
	Item(string nam, string des, int use, int stat, int mag)
	{
		name = nam;
		desc = des;
		uses = use;
		changeInStat = stat;
		magnitude = mag;
	}
	void destroyItem()
	{
		name = "";
		desc = "";
		uses = 0;
		changeInStat = 0;
		magnitude = 0;
	}
};

class Convoy {
public:
	Item i[20];
};

class Party
{
public:
	Unit u[4];
	Unit Enemy;
	Convoy con;
	Convoy allItems;
	
	Party()
	{
	};
	Party(Unit a, Unit b, Unit c, Unit d, Unit Enemy1)
	{
		u[0] = a;
		u[1] = b;
		u[2] = c;
		u[3] = d;
		Enemy = Enemy1;
	};
	void printPartyCombatInfo()
	{
		//bread and butter of the display
		Unit u1 = u[0];
		Unit u2 = u[1];
		Unit u3 = u[2];
		Unit u4 = u[3];
		string partyCombatInfo[4] = { u1.name +"       " + u2.name + "        "+ u3.name + "        " + u4.name +"\n",
			" HP: " + to_string(u1.HP_CURR) +"/" + to_string(u1.HP_MAX)+ " HP: " + to_string(u2.HP_CURR) + "/" + to_string(u2.HP_MAX)+ " HP: " + to_string(u3.HP_CURR) + "/" + to_string(u3.HP_MAX) +  " HP: " + to_string(u4.HP_CURR) + "/" + to_string(u4.HP_MAX) + "\n",
			" SP: " + to_string(u1.SP_CURR) + "/" + to_string(u1.SP_MAX) + " SP: " + to_string(u2.SP_CURR) + "/" + to_string(u2.SP_MAX) + " SP: " + to_string(u3.SP_CURR) + "/" + to_string(u3.SP_MAX)+ " SP: " + to_string(u4.SP_CURR) + "/" + to_string(u4.SP_MAX) + "\n", " "};
		cout << partyCombatInfo[0];
		cout << partyCombatInfo[1];
		cout << partyCombatInfo[2];
		cout << partyCombatInfo[3];
	}
	int getHighestHPUnitID()
	{	//useful for enemy targeting -> have enemy ai target highest hp in party
		int alpha = 0;
		int b = 0;
		
		alpha = max(u[0].HP_CURR, u[1].HP_CURR);

		b = max(u[2].HP_CURR, u[3].HP_CURR);
		alpha = max(alpha, b);
		for (int i = 0; i < 4; i++)
		{
			if (u[i].HP_CURR == alpha)
			{
				return i;
			}
		}
		return 0;
	}
	Party useSkill(Skill s, int activeUnit) {
		//attempt to push all skills into one function to use.
		int damage = 0; //to be displayed afterwards.
		Unit t = u[activeUnit];
		string name1 = u[activeUnit].name;
		string name2 = s.name;
		int critNumber = 0;
		if (t.SP_CURR >= s.SP_COST) { //check SP
			u[activeUnit].SP_CURR = t.SP_CURR - s.SP_COST;
			switch (s.specialThing) //Skills that don't fit the Skill templete mold.
			{//Astra
			case 1:
				for (int i = 5; i != 0; i--)
				{
					damage = 1;

					damage = u[activeUnit].ATK + u[activeUnit].tATK - Enemy.DEF - Enemy.tDEF;
					damage = max(damage, 1);

					srand(time(NULL));
					 critNumber = rand() % 100 + 1;

					if (critNumber > 50) {
						damage = damage * 3;
							
						cout << u[activeUnit].name << " critically strikes for " << damage << " damage!\n";
						Enemy.HP_CURR = Enemy.HP_CURR - damage;

					}
					else {
						Enemy.HP_CURR = Enemy.HP_CURR - damage;
						cout << u[activeUnit].name << " deals " << damage << " damage!\n";

					}
				}
				return Party(u[0], u[1], u[2], u[3], Enemy);
			case 2:
				//Stand Firm -> Double's self defence.
				u[activeUnit].tDEF = u[activeUnit].DEF;

				return Party(u[0], u[1], u[2], u[3], Enemy);
			case 3:
				// Shatter -> tDEf and TMDEF penalties
				Enemy.tDEF = -10;
				Enemy.tM_DEF = -10;

				return Party(u[0], u[1], u[2], u[3], Enemy);
			case 4:
				//restores all allies with bad conditions to safe condition.
				for (int i = 0; i < 4;i++)
				{
					if (u[i].condition == 1 || u[i].condition == 2 || u[i].condition == 3)
					{
						u[i].condition = 0;
					}
				}
				return Party(u[0], u[1], u[2], u[3], Enemy);
			case 5:
				//Excite -> grant all allys the Excite buff
				for (int i = 0; i < 4;i++)
				{
					u[i].condition = 4;
				}
				return Party(u[0], u[1], u[2], u[3], Enemy);
			case 6:
				//heal for % of damage dealt
				 damage = 1;

				damage = u[activeUnit].ATK + u[activeUnit].tATK - Enemy.DEF - Enemy.tDEF;
				damage = max(damage, 1);

				srand(time(NULL));
				 critNumber = rand() % 100 + 1;

				if (critNumber > 90) {
					damage = damage * 3;
					cout << u[activeUnit].name << " critically strikes for " << damage << " damage!\n";
					Enemy.HP_CURR = Enemy.HP_CURR - damage;
					u[activeUnit].HP_CURR = min(u[activeUnit].HP_MAX, u[activeUnit].HP_CURR + damage);
					cout << u[activeUnit].name << " heals for " << damage << " damage!\n";
				}
				else {
					Enemy.HP_CURR = Enemy.HP_CURR - damage;
					u[activeUnit].HP_CURR = min(u[activeUnit].HP_MAX, u[activeUnit].HP_CURR + damage);

					cout << u[activeUnit].name << " deals " << damage << " damage!\n";
					cout << u[activeUnit].name << " heals for " << damage << " damage!\n";
				}

				return Party(u[0], u[1], u[2], u[3], Enemy);
			case 7:
				//luna -> neg defences
				 damage = 1;

				damage = u[activeUnit].ATK + u[activeUnit].tATK;
				damage = max(damage, 1);

				srand(time(NULL));
				 critNumber = rand() % 100 + 1;

				if (critNumber > 90) {
					damage = damage * 3;
					cout << u[activeUnit].name << " critically strikes for " << damage << " damage!\n";
					Enemy.HP_CURR = Enemy.HP_CURR - damage;


				}
				else {
					Enemy.HP_CURR = Enemy.HP_CURR - damage;
					cout << u[activeUnit].name << " deals " << damage << " damage!\n";

				}
				return Party(u[0], u[1], u[2], u[3], Enemy);
			case 8:
				u[activeUnit].tDEF = 5;
				u[activeUnit].tM_DEF = 5;

				break;
			case 9:
				s.damageBonus = u[activeUnit].HP_MAX - u[activeUnit].HP_CURR;
				break;
			case 10:
				//heal for % of damage dealt
				 damage = 1;

				damage = u[activeUnit].ATK + u[activeUnit].tATK - Enemy.DEF - Enemy.tDEF;
				damage = max(damage, 1);

				srand(time(NULL));
				 critNumber = rand() % 100 + 1;

				if (critNumber > 90) {
					damage = damage * 3;
					cout << u[activeUnit].name << " critically strikes for " << damage << " damage!\n";
					Enemy.HP_CURR = Enemy.HP_CURR - damage;
					u[activeUnit].HP_CURR = min(u[activeUnit].HP_MAX, u[activeUnit].HP_CURR + damage);
					cout << u[activeUnit].name << " heals for " << damage << " damage!\n";
				}
				else {
					Enemy.HP_CURR = Enemy.HP_CURR - damage;
					u[activeUnit].HP_CURR = min(u[activeUnit].HP_MAX, u[activeUnit].HP_CURR + damage);

					cout << u[activeUnit].name << " deals " << damage << " damage!\n";
					cout << u[activeUnit].name << " heals for " << damage << " damage!\n";
				}

				//luna -> neg defences
				damage = u[activeUnit].ATK + u[activeUnit].tATK;
				damage = max(damage, 1);

				srand(time(NULL));
				 critNumber = rand() % 200 + 1;

				if (critNumber > 180) {
					damage = damage * 3;
					cout << u[activeUnit].name << " critically strikes for " << damage << " damage!\n";
					Enemy.HP_CURR = Enemy.HP_CURR - damage;


				}
				else {
					Enemy.HP_CURR = Enemy.HP_CURR - damage;
					cout << u[activeUnit].name << " deals " << damage << " damage!\n";

				}
				return Party(u[0], u[1], u[2], u[3], Enemy);

			case 11:
				for (int i = 0; i < 4;i++)
				{
					u[i].tATK = u[activeUnit].ATK;
				}
				return Party(u[0], u[1], u[2], u[3], Enemy);
		}
		

			if (s.useCase == 0)
			{ //Damages Enemies
				if (s.damageType == 1) {
					//deals magic damage
					damage = u[activeUnit].M_ATK + u[activeUnit].tM_ATK + s.damageBonus  - Enemy.tM_DEF - Enemy.M_DEF;
					damage = max(damage, 1);
					Enemy.HP_CURR = Enemy.HP_CURR - damage;
			}
				else
				{// deals physical damage
			
					damage = u[activeUnit].ATK + u[activeUnit].tATK +s.damageBonus- Enemy.DEF - Enemy.tDEF;
					damage = max(damage, 1);
					Enemy.HP_CURR = Enemy.HP_CURR - damage;
				}
			 if (s.useCase ==1)
				 //heals allies
			{ 
				 if (s.specialThing == 1) //targeted ally
				 {
					 cout << "Target which ally? 1, 2, 3, or 4 \n";
					 int pInput3 = 1;
					 scanf_s("%d", &pInput3);
					int  heal = u[activeUnit].M_ATK +u[activeUnit].tM_ATK+ s.damageBonus;
					u[pInput3].HP_CURR = min(u[pInput3].HP_CURR + heal, u[pInput3].HP_MAX); 
					//can't heal over max HP
				 }
				 else {
					 for (int i = 0; i < 4; i++) //heal all
					 {
						 int  heal = u[activeUnit].M_ATK + u[activeUnit].tM_ATK + s.damageBonus;
						 u[i].HP_CURR = min(u[i].HP_CURR + heal, u[i].HP_MAX);
					 }
				 }
			   }
			}
		}
		else
		{ // generally lack of SP
			cout << name1 << " tried to use " << name2 << " but it failed!\n";
		}
		cout << name1 << " dealt " << damage << "!\n";
		return Party(u[0], u[1], u[2], u[3], Enemy);
	}
	int AverageLevel()
	{ //not working correctly atm, but a way to fetch good enemies!
		int rollSum = 0;
		for (int i = 0; i < 4; i++)
		{
			rollSum += u[i].LVL;
		}
		return rollSum / 4;
	}
	Party useItem(int unit, int itemPos, Party p)
	{
		switch (p.con.i[itemPos].changeInStat) {
		case 0:
			p.u[unit].HP_MAX = p.u[unit].HP_MAX + p.con.i[itemPos].magnitude;
			p.u[unit].HP_CURR = p.u[unit].HP_CURR + p.con.i[itemPos].magnitude;
		case 1:

			p.u[unit].HP_CURR = min(p.u[unit].HP_CURR + p.con.i[itemPos].magnitude, p.u[unit].HP_MAX);

		case 2:
			p.u[unit].ATK = p.u[unit].ATK + p.con.i[itemPos].magnitude;

		case 3:
			p.u[unit].M_ATK = p.u[unit].M_ATK + p.con.i[itemPos].magnitude;

		case 4:
			p.u[unit].DEF = p.u[unit].DEF + p.con.i[itemPos] .magnitude;

		case 5:
			p.u[unit].M_DEF = p.u[unit].M_DEF + p.con.i[itemPos].magnitude;

		case 6:
			p.u[unit].LUK = p.u[unit].LUK + p.con.i[itemPos].magnitude;

		case 7:
			p.u[unit].SP_CURR = p.u[unit].SP_CURR + p.con.i[itemPos].magnitude;
			p.u[unit].SP_MAX = p.u[unit].SP_MAX + p.con.i[itemPos].magnitude;

		case 8:
			p.u[unit].SP_CURR = min(p.u[unit].SP_CURR + p.con.i[itemPos].magnitude, p.u[unit].SP_MAX);

		default:
			return p;
		}
		if (p.con.i[itemPos].uses == 0)
		{
			p.con.i[itemPos].destroyItem();
		}
		return p;
	}
};

Party attack(Party p, int activeUnit)
{
	p.Enemy = p.u[activeUnit].dealDamage(p.Enemy);
	return p;
}

Party skill(Party p, float sa)
{
	int c = 0;
	//this determines which class to draw skills from.
	int activeUnit = sa;
	//kinda smart for this solution, ngl
	if (sa - activeUnit != 0)
	{
		c = 1;
	}
	Unit a = p.u[activeUnit];
	cout << a.name << " can use: \n";
	
	for (int i = 0; i < 4; i++)
	{
		cout << i + 1<<": " << a.c[c].s[i].name <<" \n"<< a.c[c].s[i].desc << " \n";
	}
	int pInput3 = 1;
	scanf_s("%d", &pInput3);
	return p.useSkill(p.u[activeUnit].c[0].s[pInput3-1], activeUnit);
}

Party item(Party p, int activeUnit)
{
	//item implimentation is tbd
	return p;

}

Party condition(Party p, int activeUnit)
{
	//pending rework
	int damage = 1;
	srand(time(NULL));
	int critNumber = rand() % 100 + 1;
	int randUnit = rand() %4;
	switch (p.u[activeUnit].condition)
	{
	case 1: 
		//poison -> take maxHP % damage

		damage =  p.u[activeUnit].HP_MAX * .20;
		p.u[activeUnit].HP_CURR = p.u[activeUnit].HP_CURR - damage;
		cout << p.u[activeUnit].name << " takes " << damage << " damage from poison!\n";
		break;


	case 2:
		//Sleep/Freeze (Same thing, just skip the turn)
		cout << p.u[activeUnit].name << " is sleeping... \n";
		break;


	case 3:
		//berzerked

		damage = p.u[activeUnit].ATK + p.u[activeUnit].tATK + - p.u[randUnit].DEF - p.u[randUnit].tDEF;
		damage = max(damage, 1);
		if (randUnit == activeUnit)
		{
			if (critNumber > 95) {
				damage = damage * 3;
				cout << p.u[activeUnit].name << " critically strikes themself for " << damage << " damage!\n";
				p.u[activeUnit].HP_CURR = p.u[activeUnit].HP_CURR - damage;
				return p;
			}
			cout << p.u[activeUnit].name << " deals " << damage << " damage to themself!\n";
		}

		if (critNumber > 90) {
			damage = damage * 3;
			cout << p.u[activeUnit].name << " critically strikes " <<p.u[randUnit].name << " for " << damage << " damage!\n";
			p.Enemy.HP_CURR = p.Enemy.HP_CURR - damage;
			return p;
		}

		p.Enemy.HP_CURR = p.Enemy.HP_CURR - damage;
		cout << p.u[activeUnit].name << " strikes " << p.u[randUnit].name << " for " << damage << " damage!\n";

		return p;
	case 4:
		//excited -> double turns -> handeled in playerTurn
	
		break;
	default:
		break;
		//normal

	}
	return p;
}

Party playerTurn(int activeUnit, Party p) {
	float pa = 0;
	p = condition(p, activeUnit);
	if (p.u[activeUnit].condition == 2)
	{
		srand(time(NULL));
		int nomNum = rand() % 100 + 1;
		if (nomNum > 80) { // ~ 80% chance to remove sleep.
			p.u[activeUnit].condition = 0;
			return p;
		}
		return p; //skips unit's turn.
	}
	int turns = 1;
	if ((p.u[activeUnit].condition == 2))
	{ 
		turns = p.u[activeUnit].condition;
	}

	for (int i = 0; i < turns;i++)
	{
		Unit a = p.u[activeUnit];
		cout << a.name << "'s Turn: \n1: Attack \n2: " << a.c[0].name<<" \n3: " << a.c[1].name<< "\n4 : Rest \n";

		int pInput6 = 0;
		scanf_s("%d", &pInput6);

		switch (pInput6) {
		case 1:
			//basic stuff, really.
			p = attack(p, activeUnit);
			return p;

		case 2:
			//skills are mostly finished!
			p = skill(p, activeUnit);
			return p;

		case 3:
			//items are difficult -> maybe remove/replace?
			pa = float(activeUnit) + .2;
			//the float allows me to differenciate between which class to draw skills from
			p = skill(p, pa);
			return p;

		case 4:
			p.u[activeUnit].HP_CURR = min(p.u[activeUnit].HP_MAX, p.u[activeUnit].HP_CURR + p.u[activeUnit].LUK);
			p.u[activeUnit].SP_CURR = min(p.u[activeUnit].SP_MAX, p.u[activeUnit].SP_CURR + p.u[activeUnit].LUK);
			//resting restores both HP and SP by units LUK.	
			//either replace this with items or something else
			//pending condition rework, might implement a DEFEND that reduces damage taken
			return p;

		default:
			return p;
		}
	}
	return p;
}
void printStatus(int p, string n)
{ //pending status rework
	switch (p)
	{
	case 0: 
		cout << n << " is in normal condition!\n";
		break;
	case 1:
		cout << n<< " is poisoned! \n";
		break;
	case 2: 
		cout << n << " is sleeping. \n";
		break;
	case 3: 
		cout << n << " is berserked! \n";
		break;
	case 4:
		cout << n << " is excited! \n";
		break;
	default:
		break;

	}
}
Party enemyTurn(Party p){
	//really basic AI
	//advance action count to determine type of attack.

	//can add more actions to add more difficult/easy bosses and enemies

	int total = 0;
	p.Enemy.specAi[3]= p.Enemy.specAi[3]+1; 
	srand(time(NULL));
	int damage;
	int randUnit = rand() % 4;
	int switchCase = p.Enemy.specAi[3] % 3;
	int randomStatus = rand() % 3;
	int target = p.getHighestHPUnitID();
	cout << p.Enemy.specAi[3]<< "\n";
	switch (switchCase)
	{
	case 0:
		//attacks a random ally
		while (p.u[randUnit].HP_CURR <= 0)
		{
			randUnit = rand() % 4;
		}

		p.u[randUnit] = p.Enemy.dealDamage(p.u[randUnit]);


		return p;

	case 1:
		switch (p.Enemy.specAi[0]) //specAI for different attacks.
		{
		case 0:
			for (int i = 0; i < 4; i++) //deal MAG damage to all
			{
				p.u[i] = p.Enemy.dealDamage(p.u[i]);
			}

		case 1:
			p.Enemy.HP_CURR = min(p.Enemy.HP_CURR + p.Enemy.HP_MAX * .20, p.Enemy.HP_MAX);
			return p;
			//regens 20% maxHP
		case 2://give a party member a random status.
			
			cout << target;
			cout << p.u[target].condition;
			p.u[target].condition = randomStatus;
			printStatus(randomStatus, p.u[target].name);
			return p;
		}
	case 2:
		switch (p.Enemy.specAi[1])
		{
		case 0: //deals damage to whole party and heals that amount
			total = 0;
			for (int i = 0; i < 4; i++) //deal MAG damage to all
			{
				damage = p.Enemy.M_ATK - p.u[i].M_DEF;
				damage = max(damage, 1);
				p.u[i].HP_CURR = max(p.u[i].HP_CURR - damage, 0);
				cout << p.Enemy.name << " strikes " << p.u[i].name << " for " << damage << " damage!\n";
				total = damage + total;
			}
			p.Enemy.HP_CURR = min(p.Enemy.HP_CURR + total, p.Enemy.HP_MAX);
			return p;
		case 1:
			//sucks SP from party and restores HP equal to that amount
			total = 0;
			for (int i = 0; i < 4; i++) //deal MAG damage to all
			{
				damage = 5;

				p.u[i].SP_CURR = max(p.u[i].SP_CURR - damage, 0);
				cout << p.Enemy.name << " drains " << p.u[i].name << " for " << damage << " SP!\n";
				total = damage + total;
			}
			p.Enemy.HP_CURR = min(p.Enemy.HP_CURR + total, p.Enemy.HP_MAX);
			return p;
		case 2:
		{
			//strenthen's Defences
			p.Enemy.DEF = p.Enemy.tDEF + 5;
			p.Enemy.M_DEF = p.Enemy.tM_DEF + 5;
			cout << "Enemy Strengthened its defences! \n";
			return p;
		}

		}
	}

	return p;
}

bool saveParty(Party p, string filename) {
	ofstream wrfile(filename);
	string content[4][16];

		for (int i = 0;i < 4;i++)
		{
			content[i][0] = p.u[i].name;
			content[i][1] = to_string(p.u[i].HP_CURR);
			content[i][2] = to_string(p.u[i].HP_MAX);
			content[i][3] = to_string(p.u[i].SP_CURR);
			content[i][4] = to_string(p.u[i].SP_MAX);
			content[i][5] = to_string(p.u[i].ATK);
			content[i][6] = to_string(p.u[i].M_ATK);
			content[i][7] = to_string(p.u[i].DEF);
			content[i][8] = to_string(p.u[i].M_DEF);
			content[i][9] = to_string(p.u[i].LUK);
			content[i][10] = to_string(p.u[i].LVL);
			content[i][11] = to_string(p.u[i].EXP);
			content[i][12] = (p.u[i].c[0].name);
			content[i][13] = (p.u[i].c[1].name);
			content[i][14] = to_string(p.u[i].cExp1);
			content[i][15] = to_string(p.u[i].cExp2);
		}
		
		for (int i = 0;i < 4;i++)
		{
			for (int j = 0;j < 16;j++)
			{
				wrfile << content[i][j]<< ",";
			}
			wrfile << endl;
		
		}
		wrfile.close();
	return true;
}

Party combatRoutine(Party AllUnits) {
	cout << (AllUnits.Enemy.HP_CURR);
	int currentUnit = 0;
	bool alive= false;
	for (int i = 0; i < 4; i++) //check if any alive
	{
		if (AllUnits.u[i].HP_CURR > 0)
		{
			alive = true;
		}
	}
	while (AllUnits.Enemy.HP_CURR > 0 || !alive)
	{
		Unit s;

		AllUnits.printPartyCombatInfo();

		if (AllUnits.u[currentUnit].HP_CURR > 0)
		{
			AllUnits = playerTurn(currentUnit, AllUnits);
		}
		AllUnits.Enemy.printStats(AllUnits.Enemy);
		//Enemy TurnS


		if (AllUnits.u[1].name == s.name)
		{
			currentUnit = 0;
		}
		if (AllUnits.u[2].name == s.name)
		{
			currentUnit++;
			if ((currentUnit == 2) && (AllUnits.u[3].name == s.name))
			{
				currentUnit = 0;
			}

		}
		else
		{
			currentUnit++;
			if (currentUnit == 4)
			{
				currentUnit = 0;
			}
		}
		AllUnits = enemyTurn(AllUnits);
	}
	
	if (AllUnits.u[0].HP_CURR > 0 || AllUnits.u[1].HP_CURR > 0 || AllUnits.u[2].HP_CURR > 0 || AllUnits.u[3].HP_CURR > 0) {

		for (int i = 0; i < 4; i++)
		{
			AllUnits.u[i].gainExp(AllUnits.Enemy);
		}
		AllUnits.printPartyCombatInfo();
	}
	return AllUnits;
}

Unit loadCurrEnemy(int choice) {
	Unit u[20];
	fstream fin;

	fin.open("enemylist.csv", ios::in);


	vector<vector<string>> content;
	vector<string> row;
	string line, word;

	while (getline(fin, line))
	{
		row.clear();
		stringstream str(line);

		while (getline(str, word, ',')) {
			row.push_back(word);
		}
		content.push_back(row);
	}
	for (int i = 0;i < content.size();i++)
	{
		for (int j = 0; j < content[i].size();j++)
		{

			std::cout << content[i][j] << " ";
		}
	}

	for (int i = 0;i < 9;i++)
	{
		u[i].name = content[i][0];
		u[i].HP_CURR = atoi(content[i][1].c_str());
		u[i].HP_MAX = atoi(content[i][2].c_str());
		u[i].SP_CURR = atoi(content[i][3].c_str());
		u[i].SP_MAX = atoi(content[i][4].c_str());
		u[i].ATK = atoi(content[i][5].c_str());
		u[i].M_ATK = atoi(content[i][6].c_str());
		u[i].DEF = atoi(content[i][7].c_str());
		u[i].M_DEF = atoi(content[i][8].c_str());
		u[i].LUK = atoi(content[i][9].c_str());
		u[i].LVL = atoi(content[i][10].c_str());
		u[i].EXP = atoi(content[i][11].c_str());
		u[i].specAi[0] = atoi(content[i][12].c_str());
		u[i].specAi[1] = atoi(content[i][13].c_str());
		u[i].specAi[2] = atoi(content[i][14].c_str());
	
	
	}
	return u[choice];
}

Party loadParty(string filename)
{
	Party p;
	// File pointer
	fstream fin;

	// Open an existing file
	if (1 == 1)
	{
		//doing each file in its own scope.
		fin.open(filename, ios::in);


		vector<vector<string>> content;
		vector<string> row;
		string line, word;

		while (getline(fin, line))
		{
			row.clear();
			stringstream str(line);

			while (getline(str, word, ',')) {
				row.push_back(word);
			}
			content.push_back(row);
		}

		for (int i = 0;i < 4;i++)
		{
			p.u[i].name = content[i][0];
			p.u[i].HP_CURR = atoi(content[i][1].c_str());
			p.u[i].HP_MAX = atoi(content[i][2].c_str());
			p.u[i].SP_CURR = atoi(content[i][3].c_str());
			p.u[i].SP_MAX = atoi(content[i][4].c_str());
			p.u[i].ATK = atoi(content[i][5].c_str());
			p.u[i].M_ATK = atoi(content[i][6].c_str());
			p.u[i].DEF = atoi(content[i][7].c_str());
			p.u[i].M_DEF = atoi(content[i][8].c_str());
			p.u[i].LUK = atoi(content[i][9].c_str());
			p.u[i].LVL = atoi(content[i][10].c_str());
			p.u[i].EXP = atoi(content[i][11].c_str());
			p.u[i].c[0].name = content[i][12];
			p.u[i].c[1].name = content[i][13];
			p.u[i].cExp1 = atoi(content[i][14].c_str());
			p.u[i].cExp2 = atoi(content[i][15].c_str());
		}

		cout << "... Characters loaded ...\n";
		fin.close();
	}
	if (2 == 2) { //doing each file in its own scope.
		fin.open("skills.csv", ios::in);
		Klass c[4];

		vector<vector<string>> content;
		vector<string> row;
		string line, word;

		while (getline(fin, line))
		{
			row.clear();
			stringstream str(line);

			while (getline(str, word, ',')) {
				row.push_back(word);
			}
			content.push_back(row);
		}

		int j = 0;
		int k = 0;
		for (int i = 0;i <	16;i++)
		{
				Skill s(atoi(content[i][0].c_str()), atoi(content[i][1].c_str()), atoi(content[i][2].c_str()), atoi(content[i][3].c_str()), atoi(content[0][4].c_str()), content[i][5], content[i][6]);
				c[k].s[j] = s;
				j++;
				if (j == 4)
				{
					j = 0;
					k++;
				}
		}
		j = 0;
		k = 0;
		
		for (int i = 16; i < 20; i++)
		{ 

			c[k].name = content[i][0];
			c[k].desc = content[i][1];
			
			cout << c[k].desc << c[k].name <<" \n";
			k++;
		}
		string name1;
		string name2;
		string name3;
		for (int i = 0;i < 4;i++)
		{
			for (int k = 0; k < 4; k++)
			{
				cout << i;
				name1 = p.u[i].c[0].name.c_str();
				name2 = c[k].name.c_str();
				name3 = p.u[i].c[1].name.c_str();


				if (name1 == name2)
				{
					p.u[i].c[0] = c[k];
				}
				if (name3 == name2)
				{
					p.u[i].c[1] = c[k];
				}
			}
		}
	}

	cout << "Skills Loaded... \n";
	return p;
}

Convoy loadConvoy()
{
	//unused rn.

	Convoy c;
	// File pointer
	fstream fin;

	// Open an existing file
	if (1 == 1)
	{
		//doing each file in its own scope.
		fin.open("convoy.csv", ios::in);


		vector<vector<string>> content;
		vector<string> row;
		string line, word;

		while (getline(fin, line))
		{
			row.clear();
			stringstream str(line);

			while (getline(str, word, ',')) {
				row.push_back(word);
			}
			content.push_back(row);
		}
	
		for (int i = 0;i<20;i++)
		{
			c.i[i].name = content[i][0];
			c.i[i].desc = content[i][1];
			c.i[i].changeInStat = atoi(content[i][2].c_str());
			c.i[i].magnitude = atoi(content[i][3].c_str());
			c.i[i].uses = atoi(content[i][4].c_str());
		
		}



		fin.close();
	}


	return c;
}

int main() {

	Party p;
	Convoy c;
	bool cont = true;
	int playerIn = 0;
	int play = 0;
	string filename = "charstats.csv";
	while (cont) {
		cout << "Press 1 to load from your save, press any other key to load from a save. \n";
		cin >> playerIn;
		cout << "Are you sure? \n1 for yes, anything else for no.\n";
		cin >> play;
		if ((play == 1 ) && (playerIn  ==1))
		{
			filename = "save1.csv";
			cont = false;
		}
		if (play == 1)
		{
			cont = false;
		}
	}
	p = loadParty(filename);
	c = loadConvoy();
	p.Enemy = loadCurrEnemy(p.u[0].cExp1);
	p.u[0].cExp1++;
	//cExp1 on u[0] is progression
	p =combatRoutine(p);
	saveParty(p, "save1.csv");

	return 0;

}

