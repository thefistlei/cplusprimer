 

#ifndef IOTEST_H 
#define IOTEST_H
  
#include <vector> 
#include <iostream> 
#include <fstream>
#include <sstream>
#include <istream>

using std::string;  
using std::vector;


using std::cin; using std::cout; using std::endl;

class ioTest {
public:
	ioTest(){}

	virtual ~ioTest() {}
	 
	void static testIO()
	{
		cout << "cout TEST";

		unsigned grade;
		cin >> grade;

		//cin.tie(&cout); // illustration only: the library ties cin and cout for us 
	}

	void static testFile1()
	{
		ofstream file;
		file.open("example.txt", ios::out | ios::app);// | ios::binary);
		file.write("testFile1", strlen("testFile1"));
	}

	void static testFile2()
	{
		ofstream file("example.txt", ios::out | ios::app);// | ios::binary);
		file.write("testFile2", strlen("testFile2"));
	}

	//void static testFile2()
	//{
	//	ofstream file("example.txt", ios::out | ios::app);// | ios::binary);
	//	file.write("testFile2", strlen("testFile2"));
	//}

	void static process(ifstream& is)
	{
		string s;
		while (is >> s)
			cout << s << endl;
	}

	void static ioFile()
	{
		ifstream input("sstream");   // create input and open the file
		if (input) {          // if the file is ok, ``process'' this file
			process(input);
		}
		else
			cerr << "couldn't open: sstream" ;
	}
	 
	void static ioString1()
	{
		double n;
		string str = "12.5";
		stringstream stream;

		stream << str;
		stream >> n;
		cout << " " << n;
	}

	void static ioString2()
	{
		istringstream istr;
		string line, str;
		while (getline(cin, line))//从终端接收一行字符串，并放入字符串line中   
		{
			istr.str(line);//把line中的字符串存入字符串流中   
			while (istr >> str)//每次读取一个单词（以空格为界），存入str中   
			{
				cout << str << endl;
			}
		} 
	} 

	void static ioString3()
	{
		//初始化输出字符串流ostr   
		ostringstream ostr("1234");
		cout << ostr.str() << endl;//输出1234   

		ostr.put('5');//字符4顶替了1的位置   
		cout << ostr.str() << endl;//输出5234   

		ostr << "67";//字符串67替代了23的位置，输出5674   
		string str = ostr.str();
		cout << str << endl;
	}

	struct PersonInfo {
		string name;
		vector<string> phones;
	};

	// we'll see how to reformat phone numbers in chapter 17
	// for now just return the string we're given
	static string format(const string& s) { return s; }


	vector<PersonInfo> static getData(istream& is)
	{
		// will hold a line and word from input, respectively
		string line, word;

		// will hold all the records from the input
		vector<PersonInfo> people;

		// read the input a line at a time until end-of-file (or other error)
		while (getline(is, line)) {
			if (line.length() < 2)
				break;
			PersonInfo info;            // object to hold this record's data
			istringstream record(line); // bind record to the line we just read
			record >> info.name;        // read the name
			while (record >> word)      // read the phone numbers 
				info.phones.push_back(word);  // and store them
			people.push_back(info); // append this record to people
		}

		return people;
	}

	static ostream&  processOS(ostream& os, vector<PersonInfo> people)
	{
		for (const auto& entry : people) {    // for each entry in people
			ostringstream formatted, badNums; // objects created on each loop
			for (const auto& nums : entry.phones) {  // for each number  
				// ``writes'' to formatted's string
				formatted << " " << format(nums);
			}
			if (badNums.str().empty())      // there were no bad numbers
				os << entry.name << " "     // print the name 
				<< formatted.str() << endl; // and reformatted numbers 
			else                   // otherwise, print the name and bad numbers
				cerr << "input error: " << entry.name
				<< " invalid number(s) " << badNums.str() << endl;
		} 
		return os;
	}

	static void  ioString4()
	{    
		vector<PersonInfo> vec = getData(cin);
		processOS(cout, vec);  
	}
}; 
#endif
