# include <iostream>
# include <thread>
# include <mutex> // семафор



using namespace std;

class Singletone
{

protected:
	static Singletone* _singletone; // сттичечкое поле класса в одном экземпляре
	string title;

	static mutex _mutex;            // семафор блокирует многопоточность

	Singletone(string value) : title(value){}

public:
	Singletone(const Singletone&) = delete;
	void operator=(const Singletone&) = delete;

	static Singletone* GetSingleton(const string& value)
	{
		lock_guard<mutex> lock(_mutex); // семафор

		if (!_singletone)
			_singletone = new Singletone(value);

		return _singletone;
	}


	string GetTttle()
	{
		return title;
	}

};




class StaticClass
{
public:
	static  int  number; 
};

 int StaticClass::number = 0; // сттичечкое поле класса в одном экземпляре

 Singletone* Singletone:: _singletone = nullptr;

 mutex Singletone::_mutex; // семафор

 void Fun1()
 {
	 this_thread::sleep_for(chrono::milliseconds(1000));
	 Singletone* singletone = Singletone::GetSingleton("2222");
	 cout << singletone->GetTttle() << "\n";
 }

 void Fun2()
 {
	 this_thread::sleep_for(chrono::milliseconds(1000));
	 Singletone* singletone = Singletone::GetSingleton("1111");
	 cout << singletone->GetTttle() << "\n";
 }

int main()
{
	thread th1(Fun1);
	thread th2(Fun2);


	th1.join();
	th2.join();

	StaticClass a1, a2;
	a1.number = 100;
	cout << a1.number << " " << a2.number << '\n';
	a2.number = 200;
	cout << a1.number << " " << a2.number << '\n';
	StaticClass::number = 300;
	cout << a1.number << " " << a2.number << '\n';



	Singletone* obj1;
	obj1 = Singletone::GetSingleton("FFFFFF");

	cout << obj1->GetTttle() << "\n";

	Singletone* obj2;

	obj2 = Singletone::GetSingleton("aaaaaa");


	cout << obj2->GetTttle() << "\n";

	return 0;
}