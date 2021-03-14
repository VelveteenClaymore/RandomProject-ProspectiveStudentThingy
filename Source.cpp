#include <iostream>
#include <vector>
#include <cassert>
#include <iomanip>
#include <string>

class ProspectiveStudent
{
public:
	// constructors
	ProspectiveStudent()
		: name(""), uGPA(0.0), SATscore(0), ACTscore(0), age(0), AdmissionStatus("Applied"), ID(0 + IDcount) {
		++IDcount;
	}
	ProspectiveStudent(std::string _name, unsigned int _age, double _uGPA)
		: name(_name), age(_age), uGPA(_uGPA), SATscore(0), ACTscore(0), AdmissionStatus("Applied"), ID(0 + IDcount)
	{
		assert(_age >= 0);
		assert(_uGPA >= 0.0);
		++IDcount;
	}
	ProspectiveStudent(std::string _name, unsigned int _age, double _uGPA, unsigned int _SATscore, unsigned int _ACTscore)
		: name(_name), age(_age), uGPA(_uGPA), SATscore(_SATscore), ACTscore(_ACTscore), AdmissionStatus("Applied"), ID(0 + IDcount)
	{
		assert(_age >= 0);
		assert(_uGPA >= 0);
		assert(_SATscore >= 0);
		assert(_ACTscore >= 0);
		++IDcount;
	}

	// getters
	std::string get_name() const { return name; }
	double get_uGPA() const { return uGPA; }
	unsigned int get_SATscore()const { return SATscore; }
	unsigned int get_ACTscore() const { return ACTscore; }
	unsigned int get_age() const { return age; }
	std::string check_status() const { return AdmissionStatus; }
	const int get_ID() const { return ID; }

	//setters
	void change_name(std::string new_name) { name = new_name; }
	void change_age(unsigned int new_age) { age = new_age; }
	void submit_SAT(unsigned int new_score)
	{
		assert(new_score >= 0);
		SATscore = new_score;
	}
	void submit_ACT(unsigned int new_score)
	{
		assert(new_score >= 0);
		ACTscore = new_score;
	}
	void update_status(std::string update)
	{
		AdmissionStatus = update;
	}
	void filter(double GPAthreshold, unsigned int SATthreshold, unsigned int ACTthreshold)
	{
		assert(GPAthreshold >= 0);
		assert(SATthreshold >= 0);
		assert(ACTthreshold >= 0);

		if ((uGPA >= GPAthreshold) && (SATscore >= SATthreshold) && (ACTscore >= ACTthreshold))
		{
			update_status("Admitted");
		}
		else
		{
			update_status("Rejected");
		}
	}

private:
	std::string name;
	double uGPA;
	unsigned int SATscore;
	unsigned int ACTscore;
	unsigned int age;
	std::string AdmissionStatus;
	static int IDcount;
	const int ID;
};

int ProspectiveStudent::IDcount = 0;

const int g_IDfieldsize{ 9 };

void Decision(std::vector<ProspectiveStudent>& pool, double GPAcriterion, unsigned int SATcriterion, unsigned int ACTcriterion)
{
	assert(GPAcriterion >= 0);
	assert(SATcriterion >= 0);
	assert(ACTcriterion >= 0);
	std::size_t N = pool.size();
	for (std::size_t i = 0; i < N; ++i)
	{
		pool[i].filter(GPAcriterion, SATcriterion, ACTcriterion);
	}
}

void ReleaseDecisions(const std::vector<ProspectiveStudent>& pool)
{
	std::size_t N = pool.size();
	for (std::size_t i = 0; i < N; ++i)
	{
		std::cout << pool[i].get_name() << " " << pool[i].check_status() <<
			" ID #: " << std::setw(g_IDfieldsize) << std::setfill('0') << pool[i].get_ID() << std::endl;
	}
	std::cout << '\n';
}

void DisplayProfile(const ProspectiveStudent& student)
{
	std::cout << "Student Name: " << student.get_name() << '\n';
	std::cout << "Student Age: " << student.get_age() << '\n';
	std::cout << "Student ID: " << std::setw(g_IDfieldsize) << std::setfill('0') << student.get_ID() << '\n';
	std::cout << "Student Admission Status: " << student.check_status() << '\n';
	std::cout << "Student SAT Score: " << student.get_SATscore() << '\n';
	std::cout << "Student ACT Score: " << student.get_ACTscore() << '\n';
	std::cout << "Student GPA (Unweighted): " << student.get_uGPA() << '\n\n';
}

int main()
{
	std::ios coutDefaultState(NULL);
	coutDefaultState.copyfmt(std::cout);

	ProspectiveStudent s1("Andy", 18, 3.67, 1520, 32);
	ProspectiveStudent s2("Jarl", 18, 4.31, 1480, 31);
	ProspectiveStudent s3("Candice", 17, 4.17, 1470, 32);
	ProspectiveStudent s4("Robert", 19, 4.02, 1520, 33);
	ProspectiveStudent s5("Jon", 18, 4.15, 1490, 31);

	std::vector<ProspectiveStudent> pool;
	pool.push_back(s1);
	pool.push_back(s2);
	pool.push_back(s3);
	pool.push_back(s4);
	pool.push_back(s5);

	Decision(pool, 4.0, 1500, 30);

	std::cout.precision(2);

	ReleaseDecisions(pool);

	DisplayProfile(s4);

	//" ID #: " << 

	/*std::cout << pool[0].get_name() << " " << pool[0].check_status() << " ID #: " << std::setw(9) << std::setfill('0') << pool[0].get_ID()<< std::endl;

	std::cout << pool[1].get_name() << " " << pool[1].check_status() << " ID #: " << std::setw(9) << std::setfill('0') << pool[1].get_ID() << std::endl;

	std::cout << pool[2].get_name() << " " << pool[2].check_status() << " ID #: " << std::setw(9) << std::setfill('0') << pool[2].get_ID() << std::endl;

	std::cout << pool[3].get_name() << " " << pool[3].check_status() << " ID #: " << std::setw(9) << std::setfill('0') << pool[3].get_ID() << std::endl;

	std::cout << pool[4].get_name() << " " << pool[4].check_status() << " ID #: " << std::setw(9) << std::setfill('0') << pool[4].get_ID() << std::endl;*/
	return 0;
}