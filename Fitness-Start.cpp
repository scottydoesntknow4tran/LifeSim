// Fitness.cpp : This file contains the 'main' function. Program execution begins and ends there.
// Final Project Scott Tornquist 6/18

#include <iostream>
#include <map>
#include <stdio.h>
#include <string.h>

using namespace std;
class Activity;

enum Days // used as the the key to the Day Map when running through loops to simulate the weekly activity
{
	Sun,
	Mon,
	Tue,
	Wed,
	Thr,
	Fri,
	Sat,
	invalid_day
};

string dayMap[] = { "Sun", "Mon", "Tue", "Wed", "Thr", "Fri", "Sat" }; // Map used when looping through each days acttivities for the week

enum class Activities // keys used for the skills map in the Person class, this determines which activity code is run
{
	WorkAtStore,
	WorkInTech,
	Run,
	SitUps,
	Elliptical,
	WeightLift,
	Eat,
	GoToLibrary,
	CustomActivity,
	Invalid
};

class goal {
public:
	int* goalptr;
	int _goal;

	goal* nextgoalptr = nullptr;
};

class Person // this class creates the object for the person that we are simulating, it defines at the parameters and their starting values
{
public:
	int strength; 
	int fitness; // this is our goal, to raise this to a certain level
	int calories;
	int wealth;
	int knowledge;
	int* goal;
	map <Activities, Activity*> skills;
	
	

	Person()
	{
		strength = 20;
		fitness = 0;
		calories = 6000;
		wealth = 250;
		knowledge = 7;
	}
};


class Activity // this is the base class that defines the virtual functions and where we derive from to create the different functions for every activity
{
	string _name;
public:
	Activity(string name) { _name = name; }
	virtual void askforname(){
		cout << "What is the name of your Custom Activity?" << endl;
		cin>>_name;
	}
	virtual bool perform(Person& p) = 0; // what happens when the activity is put into the weekly schedule and occurs
	virtual bool developSkill(Person& p) = 0; // adding the skill to the list of available skills
	virtual int costToAquireSkill() = 0; //  what it costs to develop the skill for future use
	string getName() { return _name; } // returns the name of the activity which is defined in the constructor
};

class CustomActivity : public Activity
{
public :
	string _CustomName;
	int CStrength;
	int CFitness;
	int CCalories;
	int CWealth;
	int CKnowledge;
	int LearningCost;
	CustomActivity():Activity("bob"){
		askforname();
		creation();
	};

	void creation(){
		cout << "What is the Strength change due to the " << _CustomName << " activity? (postive or negative integer)" << endl;
		cin >> CStrength;
		cout << "What is the Fitness change due to the " << _CustomName << " activity? (postive or negative integer)" << endl;
		cin >> CFitness;
		cout << "What is the Calorie change due to the " << _CustomName << " activity? (postive or negative integer)" << endl;
		cin >> CCalories;
		cout << "What is the Wealth change due to the " << _CustomName << " activity? (postive or negative integer)" << endl;
		cin >> CWealth;
		cout << "What is the Knowledge change due to the " << _CustomName << " activity? (postive or negative integer)" << endl;
		cin >> CKnowledge;
		cout << "What is the cost to learn the " << _CustomName << " activity? (postive integer)" << endl;
		cin >> LearningCost;
	};
	
	bool perform(Person& p) {
		if (0 == p.skills.count(Activities::CustomActivity)) {
			cout << "You do not have the skill to " << getName() << endl;
			return false;
		}
		if (p.wealth < (-1 * CWealth))
		{
			cout << "You do not have enough Wealth to " << getName() << endl;
			return false;
		}
		if (p.calories < (-1 * CCalories))
		{
			cout << "You do not have enough calories to " << getName() << endl;
			return false;
		}
		if (p.strength < (-1 * CStrength))
		{
			cout << "You do not have enough strength to " << getName() << endl;
			return false;
		}
		if (p.fitness < (-1 * CFitness)) {
			cout << "You do not have enough Fitness to " << getName() << endl;
			return false;
		}
		if (p.knowledge < (-1 * CKnowledge)) {
			cout << "You do not have enough Knowledge to " << getName() << endl;
			return false;
		}
		p.wealth = p.wealth + CWealth; // if all the minimun requirements are met then the custom activity;; is preformed and the changes to the person object occur
		p.calories = p.calories + CCalories;
		p.strength = p.strength + CStrength;
		p.knowledge = p.knowledge + CKnowledge;
		p.fitness = p.fitness + CFitness;
		return true;
	}
	
	int costToAquireSkill() { return LearningCost; }

	bool developSkill(Person& p)
	{
		p.skills.insert(make_pair(Activities::CustomActivity, (Activity*)this)); // the derived activities 
		p.wealth -= costToAquireSkill();

		if (p.wealth < 0)
		{
			throw ("Wealth went negative");
		}
		return true;
	};
	
};

class GoToLibrary : public Activity // this the Go To Library function that is derived from the base activity class
{
public:
	GoToLibrary() : Activity("GoToLibrary") {}; // derived constructor that defines the name of the activity

	bool perform(Person& p) // virtual perform funtion is defined and the requirements to Eat are layed out
	{
		if (0 == p.skills.count(Activities::GoToLibrary))
		{
			cout << "You do not have the skill to " << getName() << endl;
			return false;
		}
		if (p.wealth < 10)
		{
			cout << "You do not have enough Wealth to " << getName() << endl;
			return false;
		}
		if (p.calories < 100)
		{
			cout << "You do not have enough Calories to " << getName() << endl;
			return false;
		}
		if (0 == p.strength)
		{
			cout << "You do not have enough strength to " << getName() << endl;
			return false;
		}
		p.wealth -= 10; // if all the minimun requirements are met then the Go to library;; is preformed and the changes to the person object occur
		p.calories -= 100;
		p.strength--;
		p.knowledge += 20;
		return true;
	}

	int costToAquireSkill() { return 25; } 

	bool developSkill(Person& p)
	{
		p.skills.insert(make_pair(Activities::GoToLibrary, (Activity*)this)); // the derived activities 
		p.wealth -= costToAquireSkill();

		if (p.wealth < 0)
		{
			throw ("Wealth went negative");
		}
		return true;
	};
};

class Eat : public Activity // this the Eat function that is derived from the base activity class
{
public:
	Eat() : Activity("Eat") {}; // derived constructor that defines the name of the activity

	bool perform(Person& p) // virtual perform funtion is defined and the requirements to Eat are layed out
	{
		if (0 == p.skills.count(Activities::Eat))
		{
			cout << "You do not have the skill to " << getName() << endl;
			return false;
		}
		if (p.wealth < 40)
		{
			cout << "You do not have enough money to " << getName() << endl;
			return false;
		}
		if (0 == p.strength)
		{
			cout << "You do not have enough strength to " << getName() << endl;
			return false;
		}
		p.wealth -= 40; // if all the minimun requirements are met then Eat is preformed and the changes to the person object occur
		p.calories += 2000;
		p.strength--;
		return true;
	}

	int costToAquireSkill() { return 0; } // the cost to learn the eat skill is nothing

	bool developSkill(Person& p) 
	{
		p.skills.insert(make_pair(Activities::Eat, (Activity *)this)); // the derived activities 
		p.wealth -= costToAquireSkill();

		if (p.wealth < 0)
		{
			throw ("Wealth went negative");
		}
		return true; 
	};	
};

class WorkAtStore : public Activity
{
public:
	WorkAtStore() : Activity("Work at store") {};

	bool perform(Person& p)
	{
		if (0 == p.skills.count(Activities::WorkAtStore))
		{
			cout << "You do not have the skill to " << getName() << endl;
			return false;
		}
		if (p.strength < 1)
		{
			cout << "You do not have enough strength to " << getName() << endl;
			return false;
		}
		if (p.calories < 1000) {
			cout << "You do not have enough calories to " << getName() << endl;
			return false;
		}
		if (p.fitness < 5) {
			cout << "You do not have enough fitness to " << getName() << endl;
			return false;
		}
		p.fitness -= 5;
		p.wealth += 120;
		p.calories -= 1000;
		p.strength--;
		return true;
	}

	int costToAquireSkill() { return 0; }

	bool developSkill(Person& p)
	{
		p.skills.insert(make_pair(Activities::WorkAtStore, (Activity*)this));
		p.wealth -= costToAquireSkill();

		if (p.wealth < 0)
		{
			throw ("Wealth went negative");
		}
		return true;
	};
};


class WorkInTech : public Activity
{
public:
	WorkInTech() : Activity("Work in tech") {};
	bool perform(Person& p)
	{
		if (0 == p.skills.count(Activities::WorkInTech)){
			cout << "You do not have the skill to " << getName() << endl;
			return false;
		}
		if (p.calories < 750) {
			cout << "You do not have enough calories to " << getName() << endl;
			return false;
		}
		if (p.fitness < 30) {
			cout << "You do not have enough calories to " << getName() << endl;
			return false;
		}
		p.fitness -= 30;
		p.wealth += 250;
		p.calories -= 750;
		return true;
	}

	int costToAquireSkill() { return 1000; }

	bool developSkill(Person& p)
	{
		p.skills.insert(make_pair(Activities::WorkInTech, (Activity*)this));
		p.wealth -= costToAquireSkill();

		if (p.wealth < 0)
		{
			throw ("Wealth went negative");
		}
		return true;
	};
};

class Run :public Activity
{
public:
	Run() : Activity("Run") {};
	bool perform(Person& p)
	{
		if (0 == p.skills.count(Activities::Run))
		{
			cout << "You do not have the skill to " << getName() << endl;
			return false;
		}
		if (p.calories < 300) {
			cout << "You do not have enough calories to " << getName() << endl;
			return false;
		}
		if (p.strength < 2) {
			cout << "You do not have enough strength to " << getName() << endl;
			return false;
		}
		p.fitness +=20;
		p.strength -= 2;
		p.calories -= 300;
		return true;
	}

	int costToAquireSkill() { return 100; }

	bool developSkill(Person& p)
	{
		p.skills.insert(make_pair(Activities::Run, (Activity*)this));
		p.wealth -= costToAquireSkill();

		if (p.wealth < 0)
		{
			throw ("Wealth went negative");
		}
		return true;
	};
};


class SitUp :public Activity
{
public:
	SitUp() : Activity("Sit-up") {};
	bool perform(Person& p)
	{
		if (0 == p.skills.count(Activities::SitUps)){
			cout << "You do not have the skill to " << getName() << endl;
			return false;
		}
		if (p.calories < 100) {
			cout << "You do not have enough calories to " << getName() << endl;
			return false;
		}
		p.fitness += 4;
		p.strength += 15;
		p.calories -= 100;
		return true;
	}

	int costToAquireSkill() { return 0; }

	bool developSkill(Person& p)
	{
		p.skills.insert(make_pair(Activities::SitUps, (Activity*)this));
		p.wealth -= costToAquireSkill();

		if (p.wealth < 0)
		{
			throw ("Wealth went negative");
		}
		return true;
	};
};


class Elliptical : public Activity
{
public:
	Elliptical() : Activity("Elliptical") {};
	bool perform(Person& p)
	{
		if (0 == p.skills.count(Activities::Elliptical)){
			cout << "You do not have the skill to " << getName() << endl;
			return false;
		}
		if (p.calories < 60) {
			cout << "You do not have enough calories to " << getName() << endl;
			return false;
		}
		if (p.strength < 1) {
			cout << "You do not have enough strength to " << getName() << endl;
			return false;
		}
		if (p.wealth < 4) {
			cout << "You do not have enough wealth to " << getName() << endl;
			return false;
		}
		p.fitness += 20;
		p.wealth -= 4;
		p.strength -= 1;
		p.calories -= 60;
		return true;
	}

	int costToAquireSkill() { return 1500; }

	bool developSkill(Person& p)
	{
		p.skills.insert(make_pair(Activities::Elliptical, (Activity*)this));
		p.wealth -= costToAquireSkill();

		if (p.wealth < 0)
		{
			throw ("Wealth went negative");
		}
		return true;
	};
};


class WeightLift : public Activity
{
public:
	WeightLift() : Activity("Weight Lift") {};
	bool perform(Person& p)
	{
		if (0 == p.skills.count(Activities::WeightLift)){
			cout << "You do not have the skill to " << getName() << endl;
			return false;
		}
		if (p.calories < 150) {
			cout << "You do not have enough calories to " << getName() << endl;
			return false;
		}
		if (p.wealth < 10) {
			cout << "You do not have enough wealth to " << getName() << endl;
			return false;
		}
		p.fitness += 8;
		p.wealth -= 10;
		p.strength += 30;
		p.calories -= 150;
		return true;
	}

	int costToAquireSkill() { return 250; }

	bool developSkill(Person& p)
	{
		p.skills.insert(make_pair(Activities::WeightLift, (Activity*)this));
		p.wealth -= costToAquireSkill();

		if (p.wealth < 0)
		{
			throw ("Wealth went negative");
		}
		return true;
	};
};


void displaySchedule(Activity *schedule[7])
{
	cout << "Your schedule:" << endl; 
	for (int d = Sun; d <= Sat; d++)// runs through the days printing the schedule of activities for each day
	{
		cout << dayMap[d] << ": ";
		if (schedule[d] != nullptr) {
			cout << (schedule[d])->getName();
		}
		cout << endl;
	}
	cout << endl;
}

void displaySkills(Person* p)
{
	cout << "Your current skills are:\n";
	if (p->skills.empty())
	{
		cout << "  None" << endl;
	}
	else
	{
		map <Activities, Activity*>::iterator iter;
		for (iter = p->skills.begin(); iter != p->skills.end(); iter++)
		{
			cout << "  " << iter->second->getName() << endl;
		}
		cout << endl;
	}
}

void displayStats(Person* p, Activity *schedule[7])
{
	cout << "=====================================================\n";
	cout << "Your stats:" << endl;
	cout << "  wealth: " << p->wealth << endl;
	cout << "  fitness: " << p->fitness << endl;
	cout << "  calories: " << p->calories << endl;
	cout << "  strength: " << p->strength << endl;
	cout << "  knowledge: " << p->knowledge << endl;

	cout << endl;

	displaySchedule(schedule);
	displaySkills(p);
};


void runWeek(Person* p, Activity* schedule[7])
{
	for (int d = Sun; d <= Sat; d++)
	{
		if (schedule[d] != nullptr) {
			schedule[d]->perform(*p);
		}
	}
}

void aquireSkill(Person *p)
{
	char answer;

	cout << "\n\nWhich skill would you like to aquire:" << endl;
	cout << "  (E)at --> -40 Wealth, +2000 Calories, -1 Strength\n";
	cout << "  Work at (S)tore --> -5 Fitness, +120 Wealth, -1000 Calories, -1 Strength \n";
	cout << "  Work in (T)ech --> -30 Fitness, + 250 Wealth, -750 Calories \n";
	cout << "  Go for a (R)un --> +20 Fitness, -2 Strength, -300 Calories \n";
	cout << "  Do sit-(U)ps--> +4 fitness, +15 Strength, -100 calories \n";
	cout << "  Exercise on the e(l)liptical --> +20 Fitness, -4 Wealth, -1 Strength, -60 Calories\n";
	cout << "  (W)eight Lift --> +8 Fitness, -10 Wealth, +30 Strength, -150 Calories \n";
	cout << "  (G)o To Library --> -10 Wealth, -100 Calories, -1 Strength, +20 Knowledge \n";
	cout << "  (C)ustom Activity --> (create your own actvity to learn)";
	cout << "\nEnter your choice here --> ";

	cin >> answer;

	Activities newActivity;
	Activity* aPtr = nullptr;

	switch (toupper(answer)) // takes the answer and creates an activity object accordingly
	{
	case 'E':
		aPtr = new Eat(); 
		break;
	case 'S':
		aPtr = new WorkAtStore();
		break;
	case 'T':
		aPtr = new WorkInTech();
		break;
	case 'R':
		aPtr = new Run();
		break;
	case 'U':
		aPtr = new SitUp();
		break;
	case 'L':
		aPtr = new Elliptical();
		break;
	case 'W':
		aPtr = new WeightLift();
		break;
	case 'G':
		aPtr = new GoToLibrary();
		break;
	case 'C':
		aPtr = new CustomActivity();
		break;

	default:
		cout << "Ignoring invalid response " << answer << endl;
	}

	// verifies skill isn't already aquired
	if (0 != p->skills.count(newActivity)){
		cout << "You already have the " << aPtr->getName() << " skill" << endl;
		delete aPtr;
		aPtr = nullptr;
		return;
	}

	// makes sure person has enough money to aquire skill
	if ((p->wealth) < (aPtr->costToAquireSkill())) {
		cout << "You dont have enough money to aquire the " << aPtr->getName() << " skill" << endl;
		delete aPtr;
		aPtr = nullptr;
		return;
	}

	// invokes the approparet virtual function to add the skill
	aPtr->developSkill(*p);
}

int main()
{
	Person p;


	int nweeks = 0;

	Activity* weeklySchedule[7] = { nullptr };
	char response = 'Y';
	goal* lastgoal = nullptr;
	goal* head = nullptr;
	while (response == 'Y'){
		char goalAnswer;
		cout << "what is your goal?" << endl; // this is where you set your life goal and the amount needed to win
		cout << "(S)trength" << endl;
		cout << "(F)itness" << endl;
		cout << "(W)ealth" << endl;
		cout << "or" << endl;
		cout << "(K)nowledge" << endl;
		cin >> goalAnswer;
		
		goal* ptr = new goal();

		if (lastgoal != nullptr) {
			lastgoal->nextgoalptr = ptr;
		}
		else {
			head = ptr;
		}

		switch (toupper(goalAnswer))
		{
		case 'S':
			ptr->goalptr = &p.strength;
			break;
		case 'F':
			ptr->goalptr = &p.fitness;
			break;
		case 'W':
			ptr->goalptr = &p.wealth;
			break;
		case 'K':
			ptr->goalptr = &p.knowledge;
			break;

		default:
			cout << "Ignoring invalid response " << goalAnswer << endl;
		}

		cout << "What is your goal level? (50-500)" << endl;
		cin >> ptr->_goal;
		if ((ptr->_goal > 500) or (ptr->_goal < 50)) {
			ptr->_goal = 100;
			cout << "Response out of bounds, goal set to 300"<< endl;
		}
		cout << "Want to add another goal?(Y/N)" << endl;
		cin >> response;
		if (response == 'Y') {
			lastgoal = ptr;
		}
		ptr = nullptr;

	}
	int _goal = 0;

	
	
	for(;;)
	{
		goal* ptr = head;

		while (ptr != nullptr) {
			if (*ptr->goalptr >= ptr->_goal) {
				ptr = ptr->nextgoalptr;
			}
			else {
				break;
			}
		}
		if (ptr == nullptr) {
			break;
		}

		string answer;
		displayStats(&p, weeklySchedule);

		cout << "What day would you like to change (Mon, Tue, Wed...) or enter \'(s)kill\' to aquire a skill or \'(p)erform\' to peform all the activites in the week --> "<< endl;
		cin >> answer;

		if ("s" == answer)
		{
			aquireSkill (&p);
			continue;
		}
		
		else if ("p" == answer)
		{
			runWeek(&p, weeklySchedule);
			nweeks++;
			continue;
		}
		else
		{
			for (int d = Sun; d <= Sat; d++)
			{
				if (answer == dayMap[d])
				{
					cout << "Choose an activity to do on " << dayMap[d] << ":" << endl;
					cout << "  (E)at --> -40 Wealth, +2000 Calories, -1 Strength\n";
					cout << "  Work at (S)tore --> -5 Fitness, +120 Wealth, -1000 Calories, -1 Strength \n";
					cout << "  Work in (T)ech --> -30 fitness, + 250 Wealth, -750 Calories \n";
					cout << "  Go for a (R)un --> +20 fitness, -2 strength, -300 calories \n";
					cout << "  Do sit-(U)ps--> +4 fitness, +15 strength, -100 calories \n";
					cout << "  Exercise on the e(l)liptical --> +20 fitness, -4 wealth, -1 strength, -60 calories\n";
					cout << "  (W)eight Lift --> +8 Fitness, -10 Wealth, +30 Strength, -150 Calories \n";
					cout << "  (G)o To Library --> -10 Wealth, -100 Calories, -1 Strength, +20 Knowledge \n";
					cout << "  (C)ustom Activity-->\n\n";
					cout << " Enter your choice --> ";
					char c;

					cin >> c;
					Activities a = Activities::Invalid;

					switch (toupper(c))
					{
					case 'E':
						a = Activities::Eat;
						break;
					case 'S':
						a = Activities::WorkAtStore;
						break;
					case 'T':
						a = Activities::WorkInTech;
						break;
					case 'R':
						a = Activities::Run;
						break;
					case 'U':
						a = Activities::SitUps;
						break;
					case 'L':
						a = Activities::Elliptical;
						break;
					case 'W':
						a = Activities::WeightLift;
						break;
					case 'G':
						a = Activities::GoToLibrary;
						break;
					case 'C':
						a = Activities::CustomActivity;
						break;
					default:
						cout << "Ignoring invalid response " << c << endl;
					}
					if (Activities::Invalid != a)
					{
						if (0 == p.skills.count(a))
						{
							cout << "Please aquire the necessary skill before adding it to your schedule\n\n";
						}
						else
						{
							weeklySchedule[d] = p.skills[a];
						}
					}
				}
			}
			cout << "Ignoring invalid response " << answer << endl; // if nothing else then the answer must be invalid
		}
	}
	
	cout << "\n\n**** Congradulations: you acheived your goal in " << nweeks << " weeks ****\n";
	cout << " Your final stat were :  " << endl;
	displayStats(&p, weeklySchedule);


	char k;
	cout << "Press any key to exit" << endl;
	cin >> k;

	return 0;
}