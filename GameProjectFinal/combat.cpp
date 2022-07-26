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

char matrix[3][3];

void board()
{
	int i;
	int j;

	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 3; j++)
		{
			matrix[i][j] = ' ';
		}
	}
}

void pmove()
{
	int x;
	int y;

	cout << "Enter Y,X coordinates for your move: ";
	cin >> x >> y;

	x--;
	y--;

	if (matrix[x][y] != ' ')
	{
		cout << "Invalid move, try again.\n";
		pmove();
	}
	else
	{
		matrix[x][y] = 'X';
	}
}

void cmove()
{
	int i;
	int j;

	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 3; j++)
		{
			if (matrix[i][j] == ' ')
			{
				break;
			}
		}
		if (matrix[i][j] == ' ')
		{
			break;
		}
	}

	if (i * j == 9)
	{
		cout << "Draw\n";
		exit(0);
	}
	else
	{
		matrix[i][j] = 'O';
	}
}

void dboard()
{
	int t;

	for (t = 0; t < 3; t++)
	{
		cout << " " << matrix[t][0] << " | " << matrix[t][1] << " | " << matrix[t][2] << " ";
		if (t != 2)
		{
			cout << "\n---|---|---\n";
		}
	}
	cout << "\n";
}

char check()
{
	int i;

	for (i = 0; i < 3; i++)
	{
		if (matrix[i][0] == matrix[i][1] && matrix[i][0] == matrix[i][2])
		{
			return matrix[i][0];
		}
	}

	for (i = 0; i < 3; i++)
	{
		if (matrix[0][i] == matrix[1][i] && matrix[0][i] == matrix[2][i])
		{
			return matrix[0][i];
		}
	}

	if (matrix[0][0] == matrix[1][1] && matrix[1][1] == matrix[2][2])
	{
		return matrix[0][0];
	}

	if (matrix[0][2] == matrix[1][1] && matrix[1][1] == matrix[2][0])
	{
		return matrix[0][2];
	}

	return ' ';
}

int tictactoe()
{
	char a;

	cout << "Tic-Tac-Toe" << endl;
	cout << "Worm vs. Sorcerer" << endl;
	cout << "You will be 'X'" << endl;

	a = ' ';
	board();

	while (a == ' ')
	{
		dboard();
		pmove();
		a = check();

		if (a != ' ')
		{
			break;
		}

		cmove();
		a = check();
	}

	if (a == 'X')
	{
		cout << "You win!\n";
	}
	else
	{
		cout << "You lost, Sorcerer wins!" << endl;
	}

	dboard();

	return 0;
}

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

		damage = (ATK + tATK )*(100/(100 + t.DEF + t.tDEF));
		cout << damage;
		damage = max(damage, 1);


		srand(time(NULL));
		int critNumber = rand() % 100 + 1;

		if (critNumber > 95) {
			damage = damage * 3;

			cout << name << " critically strikes for " << damage << "  damage to " << t.name << "!\n";
			

		}
		else {
			
			cout << name << " deals " << damage << " damage to "<< t.name <<"!\n";

		}
		t.HP_CURR = max(0, t.HP_CURR - damage);
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

		EXP = max((-LVL + a.LVL), 1) * a.EXP;
		while (EXP >= 100)
		{
			LVL++;
			cout << name << " Leveled up to "<< LVL << "!\n";
	// LUK as a stat determines level ups. Thats it. Thats all it does

	//Maybe a skill could use it for dmg or something but atm no.

	std::default_random_engine generator;
	std::uniform_int_distribution<int> distribution(LUK/2, 2*LUK);
	int critNumber = distribution(generator);

	if (critNumber > ATK * .8) {
		ATK++;
		cout << name << " gained 1 ATK.\n";
		
		}
	 critNumber = distribution(generator);

	if (critNumber > M_ATK * .8) {
		M_ATK++;
		cout << name << " gained 1 MGC.\n";
		
	}
	 critNumber = distribution(generator);
	if (critNumber > DEF) {
		DEF+=2;
		cout << name << " gained 2 DEF.\n";
		

	}
	critNumber = distribution(generator);
	if (critNumber > M_DEF) {
		M_DEF+=2;
		cout << name << " gained 2 RES.\n";
		
	}
	critNumber = distribution(generator);
	if (critNumber > LUK*.9) {
		LUK++;
		cout << name << " gained 3 LUK.\n";
		

	}
	critNumber = distribution(generator);
	if (critNumber > SP_MAX *.4) {
		SP_MAX = SP_MAX + 10;
		SP_CURR = SP_CURR + 10;
		cout << name << " gained 10 MAX SP.\n";
	

	}
	if (critNumber > HP_MAX *.4) {
		HP_CURR += (HP_MAX) / 10;
		HP_MAX = HP_MAX + (HP_MAX)/10;
		
		cout << name << " gained "<< (HP_MAX) / 10<< " MAX HP.\n";
	

	}
	else
	{
		LUK += 1;
		cout << name << " gained 1 LUK.\n";
	}
		
	EXP = EXP - 100;


	}
		
	}

};

class Party
{
public:
	Unit u[4];
	Unit Enemy;

	
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
	
		std::default_random_engine generator;
		std::uniform_int_distribution<int> distribution(0, 100);
		int critNumber = distribution(generator);
		if (t.SP_CURR >= s.SP_COST) { //check SP
			u[activeUnit].SP_CURR = t.SP_CURR - s.SP_COST;
			switch (s.specialThing) //Skills that don't fit the Skill templete mold.
			{//Astra
			case 1:
				
				for (int i = 5; i != 0; i--)
				{
					damage = 1;

					damage = u[activeUnit].ATK + u[activeUnit].tATK - (100 / (100 + Enemy.DEF + Enemy.tDEF));
					damage = max(damage, 1);

					 critNumber = distribution(generator);

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
				Enemy.tDEF = -50;
				Enemy.tM_DEF = -50;

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

				damage = u[activeUnit].ATK + u[activeUnit].tATK * (100 / (100 + Enemy.DEF + Enemy.tDEF));
				damage = max(damage, 1);

				srand(time(NULL));
				 critNumber = rand() % 100 + 1;

				if (critNumber > 90) {
					damage = damage * 3;
					cout << u[activeUnit].name << " critically strikes for " << damage << " damage!\n";
					Enemy.HP_CURR = max(Enemy.HP_CURR - damage,0);
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
					Enemy.HP_CURR = max(Enemy.HP_CURR - damage, 0);


				}
				else {
					Enemy.HP_CURR = max(Enemy.HP_CURR - damage, 0);
					cout << u[activeUnit].name << " deals " << damage << " damage!\n";

				}
				return Party(u[0], u[1], u[2], u[3], Enemy);
			case 8:
				u[activeUnit].tDEF = s.damageBonus;
				u[activeUnit].tM_DEF = s.damageBonus;

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
			case 12:
				Enemy.tDEF = -s.damageBonus;
				Enemy.tM_DEF = -s.damageBonus;
		}
		
		
		if (s.useCase == 0)
		{ //Damages Enemies
			if (s.damageType == 1) {
				//deals magic damage
				damage = u[activeUnit].M_ATK + u[activeUnit].tM_ATK + s.damageBonus - Enemy.tM_DEF - Enemy.M_DEF;
				damage = max(damage, 1);
				Enemy.HP_CURR = Enemy.HP_CURR - damage;
			}
			else
			{// deals physical damage

				damage = u[activeUnit].ATK + u[activeUnit].tATK + s.damageBonus - Enemy.DEF - Enemy.tDEF;
				damage = max(damage, 1);
				Enemy.HP_CURR = Enemy.HP_CURR - damage;
			}
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
						 cout << u[i].name << " healed for " << heal << "!\n";
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
	cout << "5: Back \n";
	int pInput3 = 1;
	scanf_s("%d", &pInput3);
	if (pInput3 == 5)
	{
		return p;
	}
	return p.useSkill(p.u[activeUnit].c[c].s[pInput3-1], activeUnit);
}


Party condition(Party p, int activeUnit)
{
	//pending rework
	int damage = 1;
	srand(time(NULL));
	int critNumber = rand() % 100 + 1;
	int randUnit = rand() % 4;
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
	int extra = 0; //used for back functionality
	bool finished = false;
	while(true){
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
			cout << a.name << "'s Turn: \n1: Attack \n2: " << a.c[0].name << " \n3: " << a.c[1].name << "\n4: Rest \n";

			int pInput6 = 0;
			scanf_s("%d", &pInput6);

			switch (pInput6) {
			case 1:
				//basic stuff, really.
				p = attack(p, activeUnit);
				return p;

			case 2:
				//skills are mostly finished!
				//the float allows me to differenciate between which class to draw skills from
				extra = p.u[activeUnit].SP_CURR;
				p = skill(p, activeUnit); //used to determine whether or not a skill has been used.
				if (extra != p.u[activeUnit].SP_CURR)
				{
					return p;
				}

				break;
			case 3:
				//items are difficult -> maybe remove/replace?
				pa = float(activeUnit) + .2;
				//the float allows me to differenciate between which class to draw skills from
				extra = 0 + p.u[activeUnit].SP_CURR;
				p = skill(p, pa);
				finished = extra != p.u[activeUnit].SP_CURR;
		
				if (extra != p.u[activeUnit].SP_CURR)
				{
					return p;
				}
				break;
			case 4:
				p.u[activeUnit].HP_CURR = min(p.u[activeUnit].HP_MAX, p.u[activeUnit].HP_CURR + p.u[activeUnit].LUK);
				p.u[activeUnit].SP_CURR = min(p.u[activeUnit].SP_MAX, p.u[activeUnit].SP_CURR + p.u[activeUnit].LUK);
				//resting restores both HP and SP by units LUK.	
				//either replace this with items or something else
				//pending condition rework, might implement a DEFEND that reduces damage taken
				return p;

			case 5:
				break;

			default:
				return p;
			}
		}
	}
}
void printStatus(int p, string n)
{ //each status does different things, and here is an easy def as to which status is which effect.
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
			for (int i = 0; i < 4; i++) //deal damage to all
			{
				p.u[i] = p.Enemy.dealDamage(p.u[i]);
			}

		case 1:
			p.Enemy.HP_CURR = min(p.Enemy.HP_CURR + p.Enemy.HP_MAX * .20, p.Enemy.HP_MAX);
			cout << p.Enemy.name << " heals for " <<p.Enemy.HP_MAX * .20 << " health.\n";
			return p;
			//regens 20% maxHP
		case 2://give a party member a random status.
			
			cout << p.Enemy.name << " gave " << p.u[target].name << " a status! \n";
			
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
				damage = p.Enemy.M_ATK * (100 / (100 + p.u[i].M_DEF + p.u[i].tM_DEF));
				damage = max(damage, 1);
				p.u[i].HP_CURR = max(p.u[i].HP_CURR - damage, 0);
				cout << p.Enemy.name << " strikes " << p.u[i].name << " for " << damage << " damage!\n";
				total = damage + total;
			}
			p.Enemy.HP_CURR = min(p.Enemy.HP_CURR + total, p.Enemy.HP_MAX);
			cout << p.Enemy.name << " heals for " << total << " health\n";
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
			cout << p.Enemy.name << " heals for " << total << " health";
			return p;
		case 2:
		{
			//strenthen's Defences
			p.Enemy.DEF = p.Enemy.tDEF + 25;
			p.Enemy.M_DEF = p.Enemy.tM_DEF + 25;
			cout << "Enemy Strengthened its defences! \n";
			return p;
		}

		}
	}

	return p;
}
void readStory(int integer) {
	switch (integer) {
	case 0:
		cout << "You are a random person exploring the world and come across random people that challenge you." << endl;
		cout << "The goal of this game is to survive all the battles." << endl;
		cout << "There is no storyline." << endl;
		cout << "You begin in a forest. There is a small stream running through the middle of the area." << endl;
		cout << "'Hmm... well, I guess this is the start.'" << endl;
		cout << "A random creature walks up to you." << endl;
		cout << "'Hey, you! Why aren't you doing anything?'" << endl;
		cout << "'I'm just going to sit here and watch.'" << endl;
		cout << "'That's it?'" << endl;
		cout << "The random creature attacks." << endl;
		break;
	case 1:
		cout << "After defeating the random creature," << endl;
		cout << "'Well, at least it's over now...'" << endl;
		cout << "The random creature asks you if you have a name." << endl;
		cout << "'What? What do you mean?'" << endl;
		cout << "'If you don't have a name, then what kind of a person are you?'" << endl;
		cout << "'My name is...'" << endl;
		cout << "'And what does your name sound like?'" << endl;
		cout << "'It sounds like... 'Worm'" << endl;
		cout << "'Well, that's a weird name. Why do you have such an odd name?'" << endl;
		cout << "'I think it's because my mother named me after worms.'" << endl;
		cout << "After a while, you go into the cave." << endl;
		cout << "The cave has a dirt floor and a few stalactites hang from the ceiling." << endl;
		cout << "You enter the cave." << endl;
		cout << "'Wow, this place is dark. Is there any light in here?'" << endl;
		cout << "'No, it's very dark. I can barely see anything around me.'" << endl;
		cout << "You enter the cave and turn on the torch." << endl;
		cout << "'Oh, thank goodness. Now this cave is much more comfortable.'" << endl;
		cout << "'I wonder where this tunnel goes...'" << endl;
		cout << "You walk down the tunnel. It is narrow, but large enough for you to walk comfortably. \nAfter a while, you see a painter aggressively painting a picture." << endl;
		cout << "'Hi. Do you mind if I come in?'" << endl;
		cout << "'Why would you want to do that? \nThis is my painting. Don't you know how rude it is to interrupt someone when they're working on something important?'" << endl;
		cout << "'I just wanted to ask you a question.'" << endl;
		cout << "'Yes?'" << endl;
		cout << "'Is this really what you call art?'" << endl;
		cout << "'Of course not. Do you think I'd be wasting my time \nif I were doing something worthwhile?'" << endl;
		cout << "'Do you think this is what art should look like?'" << endl;
		cout << "'No.'" << endl;
		cout << "The painter attacks." << endl;
		break;
	case 2:
		cout << "After showing the painter what pain is, you are escorted out of the painting by the painter's assistant." << endl;
		cout << "You are back in the forest." << endl;
		cout << "'Well, at least I got my answer.'" << endl;
		cout << "'At least you got your answer. But I think that the painter was right.'" << endl;
		cout << "After a while, you come upon a strange building. It is made entirely of stone and looks like it has been abandoned for many years. A small stream runs through the middle of the area. \nThe trees are tall and green and grow everywhere. The ground is covered with soft moss and carpeted with ferns. \nYou see a large door on the west side of the building." << endl;
		cout << "'Hmm...'" << endl;
		cout << "The door opens easily." << endl;
		cout << "Inside, you find yourself in a dark room. The walls are bare and the only light comes from the open doorway. There is a large table in the center of the room. \nOn the table, there are several books. Each book has a different title on its cover. You can see several other doors leading off into the darkness." << endl;
		cout << "'Well, at least I figured out where I am now.'" << endl;
		cout << "You read a few of the books:" << endl;
		cout << "A Complete Guide to the World of Goblins - a book about goblins" << endl;
		cout << "	A History of the Great War - a book about the war between humans and dragons" << endl;
		cout << "	How to Get Rich Quick - a book about getting rich" << endl;
		cout << "	A Handbook of Spells - a book about magic" << endl;
		cout << "	The Art of Baking Bread - a book about baking bread" << endl;
		cout << "	Goblin Lore - a book about goblins" << endl;
		cout << "	The Art of the Sword - a book about swordsmanship" << endl;
		cout << "	The Art of Writing -" << endl;
		cout << "The Art of Writing comes to life and attacks!" << endl;
		break;
	case 3:
		cout << "After defeating the book," << endl;
		cout << "'Ha! I win! I always knew I could write better than you!'" << endl;
		cout << "'I'm not sure that's true. I think that you're just a very good writer.'" << endl;
		cout << "'I think you're just a very good writer.'" << endl;
		cout << "Afterwards, you decide to fight the main villian." << endl;
		cout << "Your rival approaches." << endl;
		cout << "'Fine. I'll give you a battle for once.'" << endl;
		break;
	case 4:
		cout << "After defeating him," << endl;
		cout << "'Did you win this time, just by chance? No! Because of my ability, The Art of the Sword.'" << endl;
		cout << "He takes one last swing at you," << endl;
		cout << "'HA! Gotcha now. Didn't we both know that was the right answer anyway?'" << endl;
		cout << "Finally, you run into someone you remember." << endl;
		cout << "A giant warrior steps forth before you, towering over the other people nearby." << endl;
		cout << "'Pleased to meet you, young stranger. My name is Tallwood.'" << endl;
		cout << "Tallwood strides over toward you, making every man within his path seem insignificant." << endl;
		cout << "'Let us introduce ourselves to one another.'" << endl;
		cout << "'Let's have no unnecessary niceties or small talk.'" << endl;
		break;
	case 5:
		cout << "After a short fight," << endl;
		cout << "'We fought one another earlier. Let us play some Rock, Paper, Scissors for honor's sake.'" << endl;
		break;
	case 6:
		cout << "After playing rock, paper, scissors, he gets upset." << endl;
		cout << "Cheating, indeed! It isn't honorable. We fought for nothing then!" << endl;
		cout << "Afterwards, he attacks you again!" << endl;
		break;
	case 8:
		cout << "In a strange dream, he forces you to build cities in order for you to have eternal rest.You see some of the same places, as well as new locationsand situations that have yet to take place in reality.After finishing a long series of buildingsand orders, you are granted the honor of resting in the next world, although you still need a few things that you had hoped to obtain in life." << endl;
		cout << "In this dream world, you challenge a sorcerer to tic tac toe. " << endl;
		break;
	case 9:
		cout << "After a battle that takes all day, you gain his armor.It seems quite old and broken, but functional at best.You enter a templeand pay tribute in a room of treasures.Upon receiving the riches, you exit to discover the world transformed into an endless paradise.Your island is surrounded by sparkling turquoise seas, bright coral reefs, and a great many plantsand animals.Everything has never looked more beautiful than this.You lie down to sleep forever, as your work is complete." << endl;
		cout << "Then you wake up, as your work is not complete.You return to your land with fresh perspective, determined to finish your final task in the new world before returning home. " << endl;
		cout << "You enter your mansion's courtyard and gaze upon your throne room for the last time before departing for a more suitable world to live your life in comfort. After sweeping the balcony one last time and enjoying a moment alone, you reach to grab a water jug beside your favorite seat. It's then when you notice someone is in the courtyard; an unfamiliar stranger who isn't from this plane." << endl;
		cout << "You rush into your room.The door swings inward easily.It looks the same, as though no one has entered recently.But as you slowly begin walking, your footsteps cause echoes throughout your own hall.A person steps in from behind, causing an even deeper silence.You turn to confront them, but no one appears to be present.After wandering further inside, you can no longer hear your own voice echoing within your home.There are just whispers all around.You sense that you are being followed.Slowlyand deliberately, you move past empty chambers, looking for a trace of a trail to lead you to whatever presence lurks within your house.You pass rooms until you have come upon nothing, then exitand follow your eyesight across the sky until you spy an orange light shimmering between your old courtyard's pillars and out onto your street, still invisible to you. As you continue forward, a thin film of smoke obscures your vision, causing it to be cloudy and hazy, blocking any detail about the person or where it came from." << endl;
		cout << "You suddenly see a phantom dragon that attacks." << endl;
		break;
	case 10:
		cout << "The phantom dragon uses a whirlwind and traps you. You barely escape death, but can only fall from the sky as a ghost to haunt your haunted land forever." << endl;
		cout << "You are teleported outside of the plane. " << endl;
		break;
	case 11:
		cout << "A short, intense fight ensues. \n";
		cout << "You are knocked off, but quickly pull yourself back on the plane and return home safely." << endl;
		cout << "Your old home is back exactly as it was before your departure. It feels as though time has never passed here since the day you departed. As soon as you walk back in the door, there's a loud crash as the ghost you sensed begins to fight you." << endl;
		cout << "After defeating the ghost, you decide to fight Belihajorniealizipoiqnt, the God of Ghosts and unpronounceable names." << endl;
		break;
	case 12:
		cout << "Beli tries her hardest (and fails) to beat you without cheating so that she doesn't lose respect among ghosts." << endl;
		cout << "She loses again instead and quits. Afterwards, you realize that vampires actually exist despite knowing almost none of them personally.One vampire gives you advice that leads you to defeat multiple powerful creatures that stand against each other in mortal combat.Other undead servants appear to help you overcome the difficulty levels found later on, thanks mainly due to their unique abilities that compliment yours perfectly.When most everyone else dies fighting either monsters, bosses or gods themselves eventually, you triumphantly emerge victorious amidst many high powered foes.You decide that your work is done." << endl;
		cout << "Soon afterward, everything becomes peaceful except for a storm warning signifying danger ahead.Everyone heads towards safety away from this monstrous beast while you bravely remain behind, ready to face it head - on. That night passes peacefully, leaving you plenty of rest afterwards.Then dawn arrives too early as rain falls heavily through blackened skies.Just as fast as the sun rises above it leaves scorched earth underfoot during daytime hours, becoming visible when clouds clear briefly after sunset.Not wanting to get wet along with having nowhere warm to stay dry, you leave town immediately so you won't catch a cold." << endl;
		break;
}


}

void rock_paper_scissors()
{
	int z = 0;
	int x = 0;
	int y = 0;
	string a;
	string b;

	cout << "Rock Paper Scissors" << endl;
	cout << "Worm vs. Tallwood" << endl;
	cout << "Best out of 3" << endl;

	while (z == 0)
	{
		cout << "Rock..Paper..Scissors..GO: ";
		cin >> a;

		srand(time(0));
		int c = (rand() % 3) + 1;
		if (c == 1)
		{
			b = "Rock";
		}
		if (c == 2)
		{
			b = "Paper";
		}
		if (c == 3)
		{
			b = "Scissors";
		}

		cout << "Tallwood plays: " << b << endl;

		if (a == "Rock" && b == "Scissors" || a == "Paper" && b == "Rock" || a == "Scissors" && b == "Paper")
		{
			cout << "Worm wins the round!" << endl;
			x = x + 1;
		}
		if (a == "Rock" && b == "Paper" || a == "Scissors" && b == "Rock" || a == "Paper" && b == "Scissors")
		{
			cout << "Tallwood wins the round!" << endl;
			y = y + 1;
		}

		if (x == y + 2 || x == 3)
		{
			cout << "Worm wins the game!" << endl;
			z = 1;
		}
		if (y == x + 2 || y == 3)
		{
			cout << "Tallwood wins the game!" << endl;
			z = 1;
		}

		cout << "Worm Score: " << x << endl;
		cout << "Tallwood Score: " << y << endl;
	}
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
	

	int currentUnit = 0;
	bool alive= false;
	while (AllUnits.Enemy.HP_CURR > 0)
	{
		if ((AllUnits.u[0].HP_CURR < 0) && (AllUnits.u[1].HP_CURR < 0) &&( AllUnits.u[2].HP_CURR < 0) &&  (AllUnits.u[3].HP_CURR < 0 ))
		{
			break;
		}
		
		AllUnits.Enemy.printStats(AllUnits.Enemy);
		AllUnits.printPartyCombatInfo();

		if (AllUnits.u[currentUnit].HP_CURR > 0)
		{
			AllUnits = playerTurn(currentUnit, AllUnits);
			//
		}
		currentUnit++;
		if (currentUnit == 4)
		{
				currentUnit = 0;
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
	else {
		cout << "Game.... Over........";
	
	}
	return AllUnits;
}

Unit loadCurrEnemy(int choice) {
	Unit u[10];
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
		Klass c[5];

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
		for (int i = 0;i <	20;i++)
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
		
		for (int i = 20; i < 25; i++)
		{ 
			c[k].name = content[i][0];
			c[k].desc = content[i][1];
			

			k++;
		}
		string name1;
		string name2;
		string name3;
		k=0;
		for (int i = 0;i < 4;i++)
		{
			for (int k = 0; k < 5; k++)
			{
		
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

int main() {

	Party p;
	cout << "\n\n\n\n\n\n\n\n\n\nWelcome to a totally Coherent Plot, written by an AI!\n By: Jay Marx, Seth Wilder, Aaron Cambron, Anna Baker \n";



	bool cont = true;
	int playerIn = 0;
	int play = 0;
	string filename = "charstats.csv";
	while (cont) {
		cout << "Press 1 to load from your save, press any other key to load from a save. \n";
		cin >> playerIn;
		cout << "Are you sure? \n1 for yes, anything else for no.\n";
		cin >> play;
		if ((play == 1) && (playerIn == 1))
		{
			filename = "save1.csv";
			cont = false;
		}
		if (play == 1)
		{
			cont = false;
		}
	}
	while (1){
		p = loadParty(filename);

	p.Enemy = loadCurrEnemy(p.u[0].cExp1);
	readStory(p.u[0].cExp1);
	if (p.u[0].cExp1 > 5)
	{
		p.u[0].c[1].name = "Main Character";
	}
	p.u[0].cExp1++;
	//cExp1 on u[0] is progression
	if (p.u[0].cExp1 == 5)
	{
		rock_paper_scissors();
		p.u[0].cExp1++;
	}
	if (p.u[0].cExp1 == 8)
	{
		tictactoe();
		p.u[0].cExp1++;
	}


	p = combatRoutine(p);
	saveParty(p, "save1.csv");
	cout << "Save complete. Click 1 to continue playing!\n";
	filename = "save1.csv";
	cin >> playerIn;
	if (playerIn != 1)
	{
		break;
	}
}
	return 0;

}

