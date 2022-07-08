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
	string name;
	Skill s[4];
	Unit()
	{
	};
	Unit(int hpSet, int spSet, int baseATK, int baseM_ATK, int base_DEF, int base_M_DEF, int base_LUK, string name1, int lvel, int expp)
	{
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
	};
	void setName(string s)
	{
		name = s;
	}
	void printStats(Unit s)
	{
		cout << name << "\nHP: " << s.HP_CURR << "\n";
	}
	void gainEXP(Unit a)
	{
		EXP = (LVL - a.LVL) * a.EXP;
		while (EXP >= 100)
		{
		  	srand(time(NULL));
	int critNumber = rand() % 2*LUK + 1;

	if (critNumber > ATK) {
		ATK++;
		cout << name << " gained 1 ATK.\n";

		}
	if (critNumber > M_ATK) {
		M_ATK++;
		cout << name << " gained 1 MGC.\n";
	}
	if (critNumber > DEF) {
		DEF++;
		cout << name << " gained 1 DEF.\n";

	}
	if (critNumber > M_DEF) {
		M_DEF++;
		cout << name << " gained 1 RES.\n";
	}
	if (critNumber > LUK) {
		LUK++;
		cout << name << " gained 1 LUK.\n";

	}
	if (critNumber > SP_MAX *1.5) {
		SP_MAX = SP_MAX + 10;
		cout << name << " gained 10 MAX SP.\n";

	}
	if (critNumber > HP_MAX *1.2) {
		HP_MAX = HP_MAX + (HP_MAX)/10;
		cout << name << " gained "<< (HP_MAX) / 10<< " MAX HP.\n";

	}
		
	
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
		Unit u1 = u[0];
		Unit u2 = u[1];
		Unit u3 = u[2];
		Unit u4 = u[3];
		string partyCombatInfo[4] = { u1.name +"           " + u2.name + "            "+ u3.name + "            " + u4.name +"\n",
			" HP: " + to_string(u1.HP_CURR) +"/" + to_string(u1.HP_MAX)+ " HP: " + to_string(u2.HP_CURR) + "/" + to_string(u2.HP_MAX)+ " HP: " + to_string(u4.HP_CURR) + "/" + to_string(u4.HP_MAX) +  " HP: " + to_string(u4.HP_CURR) + "/" + to_string(u4.HP_MAX) + "\n",
			" SP: " + to_string(u1.SP_CURR) + "/" + to_string(u1.SP_MAX) + " SP: " + to_string(u2.SP_CURR) + "/" + to_string(u2.SP_MAX) + " SP: " + to_string(u4.SP_CURR) + "/" + to_string(u4.SP_MAX)+ " SP: " + to_string(u4.SP_CURR) + "/" + to_string(u4.SP_MAX) + "\n", " "};
		cout << partyCombatInfo[0];
		cout << partyCombatInfo[1];
		cout << partyCombatInfo[2];
		cout << partyCombatInfo[3];
	}

	Party useSkill(Skill s, int activeUnit) {
		int damage = 0; //to be displayed afterwards.
		Unit t = u[activeUnit];
		string name1 = u[activeUnit].name;
		string name2 = s.name;

		if (t.SP_CURR >= s.SP_COST) {
			u[activeUnit].SP_CURR = t.SP_CURR - s.SP_COST;
			if (s.useCase == 0)
			{ //Damages Enemies
				if (s.damageType == 1) {
					//deals magic damage
					damage = u[activeUnit].M_ATK + s.damageBonus - Enemy.M_DEF;
					damage = max(damage, 1);
					Enemy.HP_CURR = Enemy.HP_CURR - damage;
			

				}
				else
				{// deals physical damage
			
					damage = u[activeUnit].ATK + s.damageBonus - Enemy.DEF;
					damage = max(damage, 1);
					Enemy.HP_CURR = Enemy.HP_CURR - damage;
				

				}

			}
		}
		else
		{
		
			cout << name1 << " tried to use " << name2 << " but it failed!\n";
		}

		cout << name1 << " dealt " << damage << "!\n";
		
		return Party(u[0], u[1], u[2], u[3], Enemy);
	}
};

class Item {
public:
	string name;
	string desc;
	int uses;
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
	void destroyItem()
	{
		name = "";
		desc = "";
		uses = 0;
		changeInStat = 0;
		magnitude = 0;
	}
	Party useItem(int unit, Party p)
	{
		switch (changeInStat) {
		case 0:
			p.u[unit].HP_MAX = p.u[unit].HP_MAX + magnitude;
			p.u[unit].HP_CURR = p.u[unit].HP_CURR + magnitude;
		case 1:

			p.u[unit].HP_CURR = min(p.u[unit].HP_CURR + magnitude, p.u[unit].HP_MAX);

		case 2:
			p.u[unit].ATK = p.u[unit].ATK + magnitude;

		case 3:
			p.u[unit].M_ATK = p.u[unit].M_ATK + magnitude;

		case 4: 
			p.u[unit].DEF = p.u[unit].DEF + magnitude;

		case 5:
			p.u[unit].M_DEF = p.u[unit].M_DEF + magnitude;

		case 6: 
			p.u[unit].LUK = p.u[unit].LUK + magnitude;

		case 7: 
			p.u[unit].SP_CURR = p.u[unit].SP_CURR + magnitude;
			p.u[unit].SP_MAX = p.u[unit].SP_MAX + magnitude;

		case 8:
			p.u[unit].SP_CURR = min(p.u[unit].SP_CURR + magnitude, p.u[unit].SP_MAX);

		default:
			return p;
		}
		if (uses == 0)
		{
			destroyItem();
		}
		return p;
	}
};
// HP_MAX, HP_CURR, ATK, M ATK, DEF, MDEF, LUK, SP_MAX, SP_CURR, charID

//Name, Job/Klass, Skill, Skill1, Skill2, Skill3 

char combatArena[100][100] = {
	"|__________________________________________________|\n",
	"|__________________________________________________|\n",
	"|__________________________________________________|\n",
	"|__________________________________________________|\n",
	"|__________________________________________________|\n",
	"|__________________________________________________|\n"

};


Party attack(Party p, int activeUnit)
{
	
	int damage = 1;

	damage = p.u[activeUnit].ATK  - p.Enemy.DEF;
	damage = max(damage, 1);

	srand(time(NULL));
	int critNumber = rand() % 100 + 1;

	if (critNumber > 90) {
		damage = damage * 3;
		cout << p.u[activeUnit].name << " critically strikes for " << damage << " damage!\n";
		p.Enemy.HP_CURR = p.Enemy.HP_CURR - damage;
		return p;
	}

	p.Enemy.HP_CURR = p.Enemy.HP_CURR - damage;
	cout << p.u[activeUnit].name << " deals " << damage << " damage!\n";

	return p;
}

Party skill(Party p, int activeUnit)
{
	Unit a = p.u[activeUnit];
	cout << a.name << " can use: \n1:" << a.s[0].name << " 2:" << a.s[1].name << " 3:" << a.s[2].name << " 4:" << a.s[3].name <<"\n";
	
	for (int i = 0; i < 4; i++)
	{
		cout << a.s[i].desc<<" ";
	}
	int pInput3 = 1;
	scanf_s("%d", &pInput3);
	return p.useSkill(p.u[activeUnit].s[pInput3-1], activeUnit);
}

Party item(Party p, int activeUnit)
{
	
	return p;

}

void run()
{

}

Party playerTurn(int activeUnit, Party p) {

	Unit a = p.u[activeUnit];
	cout << a.name << "'s Turn: \n1: Attack \n2: Skill \n3: Item \n4: Run \n";

	int pInput = 0;
	scanf_s("%d", &pInput);

	switch (pInput) {
	case 1:
		p = attack(p, activeUnit);
		return p;

	case 2:
		p = skill(p, activeUnit);
		return p;

	case 3:
		p = item(p, activeUnit);
		return p;

	case 4:
		run();
		return p;

	default:
		return p;
	}

}

void combatRoutine(Party AllUnits) {
	cout << (AllUnits.Enemy.HP_CURR);
	while (AllUnits.Enemy.HP_CURR > 0)
	{
		
		for (int i = 0; i != 5; i++)
		{
			cout<< combatArena[i];
		}
		AllUnits.printPartyCombatInfo();

		//Logic to determine Which units turn to come here....
	
		AllUnits = playerTurn(0, AllUnits);

		AllUnits.Enemy.printStats(AllUnits.Enemy);
		//Enemy TurnS

	




	}
}

Party loadParty()
{
	Party p;
	// File pointer
	fstream fin;

	// Open an existing file
	if (1 == 1)
	{
		//doing each file in its own scope.
		fin.open("charstats.csv", ios::in);


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
		}

		cout << "\n";
		cout << content[2][1].c_str() << content[2][2] << content[3][1] << content[3][2];
		fin.close();
	}
	if (2 == 2) { //doing each file in its own scope.
		fin.open("skills.csv", ios::in);


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
		int j = 0;
		for (int i = 0;i < 12;i++)
		{
				Skill s(atoi(content[i][0].c_str()), atoi(content[i][1].c_str()), atoi(content[i][2].c_str()), atoi(content[i][3].c_str()), atoi(content[0][4].c_str()), content[i][5], content[i][6]);
				p.u[i/4].s[j] = s;
				j++;
				if (j == 4)
				{
					j = 0;
				}
		}
		





	}

	return p;
}


int main() {

	Party p;
	p = loadParty();
	p.Enemy = p.u[3];
	combatRoutine(p);


	return 0;

}

