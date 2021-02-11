#pragma once
#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <cstdlib>
#include<typeinfo>
using namespace std;



class Task {
protected:
	std::string name;

public:
	Task(std::string name = "default") : name(name) { };

	virtual ~Task() {};

	//TO DO - zaimplementuj
	virtual void complete() {
		cout << typeid(this).name() << name << "completed";
	}

	std::string getName() {
		return name;
	}
};

class BugFix : public Task {
private:
	std::string info;

public:
	BugFix(std::string name = "default") : Task(name) {};
	void fix() {
		info = std::to_string(std::rand() % 100);
		std::cout << "Bug fix \"" << name << "\" - fixing" << std::endl;
	}

	//TO DO - zaimplementuj
	void complete() override {

		cout << typeid(this).name() << name << "completed";
		cout << "[Solution Code]:" << this->info;
	};


	std::string getInfo() {
		return info;
	}

};

class Test : public Task {
private:
	bool testPassed;
public:

	Test(std::string name, bool result) : Task(name), testPassed(result) {	};

	void test() {
		std::cout << "Test \"" << name << "\" - testing" << std::endl;
		testPassed = std::rand() % 2;
	}

	//TO DO - zaimplementuj
	void complete() override {

		cout << typeid(this).name() << name << "completed";
		cout<< "[TestPassed]:" <<this->testPassed;
	};


	bool getTestPassed() {
		return testPassed;
	}

};

class TaskManager {
private:

	std::vector<Task*> tasks;

public:
	TaskManager(int amount) {
		createRandomTasks(amount);
		std::cout << std::endl;
	}

	~TaskManager() {
		for (Task* task : tasks) {
			delete task;
		}
	}

	void createRandomTasks(int amount) {
		std::srand(std::time(0));
		for (int i = 0; i < amount; i++) {
			Task* randomTask = getRandomTask();
			tasks.push_back(randomTask);
		}
	}

	Task* getRandomTask() {
		Task* task = nullptr;
		switch (std::rand() % 3) {
		case 0: {
			std::cout << "Creating task" << std::endl;
			task = new Task("Random task #" + std::to_string(std::rand() % 26)); break;
		}

		case 1: {
			std::cout << "Creating bug fix" << std::endl;
			task = new BugFix("Random bug #" + std::to_string(std::rand() % 26)); break;
		}

		case 2: {
			std::cout << "Creating test" << std::endl;
			task = new Test("Random test #" + std::to_string(std::rand() % 26), std::rand() % 2); break;
		}

		}
		return task;
	}

	//TO DO - zaimplementuj
	void processTask(Task* task) {
		
		if (task != nullptr) {
			BugFix* ptr1 = dynamic_cast<BugFix*>(task);
			if (ptr1 != nullptr) {
				ptr1->complete();
				ptr1->fix();
				return;
			}
			Test* ptr2 = dynamic_cast<Test*>(task);
			if (ptr2 != nullptr) {
				ptr2->complete();
				ptr2->test();
				return;

			}
			task->complete();
		}
	};

	//TO DO - zaimplementuj
	std::vector<BugFix*> selectBugFixes() {
	

		vector<BugFix*> taskscorrected;
		for (Task* task : tasks) {

			if (BugFix* ptr2 = dynamic_cast<BugFix*>(task)) {

				taskscorrected.push_back(ptr2);
			}
		}


	}
	;

	//TO DO - zaimplementuj
	std::vector<Test*> selectTests() {
	
		vector<Test*> taskscorrected;
		for (Task* task : tasks) {

			if (Test* ptr2 = dynamic_cast<Test*>(task)){

				taskscorrected.push_back(ptr2);
			}
		}

		return taskscorrected;
	
	};

	std::vector<Task*> getTasks() {
		return tasks;
	}

};

/*
Zadania:
I. Zaimplementowac metode complete, wypisujaca na konsoli
teskt zgodnie z nastepujacym szablonem:
Task::complete()
<Nazwa klasy>: "<nazwa taska>" - completed

BugFix,Test::complete()
<Nazwa klasy>: "<nazwa taska>" - completed

[<TEST PASSED/SOLUTION CODE>]: info/testPased.

W zadaniu 1 nalezy wykorzystac operator typeid do okreslenia nazwy

II. Zaimplementowac funkcje TaskManger::processTask(). Funkcja powinna przetwarzac task w nastepujacy sposob:
1) Dla Taska typu BugFix, funkcja powinna wywolac funckje fix i complete
2) Dla Taska typu Test, funkcja powinna wywolac funckje test i complete

III. Zaimplemetnowac funckje TaskManger::selectBugFixes() i TaskManger::selectTests() tak, by ze zbioru wszystkich taskow,
zwracane byly jedynie BugFixy lub Testy

W calym rozwiazaniu powinny zostac uzyte zarowno operatory dynamic_cast oraz typeid (przynajmniej raz)
*/


