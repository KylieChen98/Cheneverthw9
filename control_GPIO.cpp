#include<iostream>
#include<fstream>
#include<string>
#include<sstream>

using namespace std;

#define GPIO_PATH "/sys/class/gpio/"

void writeGPIO(string path, string filename, string value)
{
  fstream fs;
  fs.open((path+filename).c_str(), fstream::out);
  fs << value;
  fs.close();
}

string readGPIO(string path, string filename)
{
  fstream fs;
  fs.open((path + filename).c_str(), fstream::in);
  string value;
  getline(fs,value);
  fs.close();
  return value;
}

int main(int argc, char* argv[])
{
  if(argc != 4)
  {
    cout << "Usage is: control_GPIO number hi/low number2." << endl;
    cout << "Number is GPIO number to change hi or low." << endl;
    cout << "./control_GPIO 60 hi 46 -- Sets GPIO60 hi and reads GPIO46." <<
    endl;
    return 2;
  }

  int number = stoi(argv[1]);
  string output = argv[2];
  int number2 = stoi(argv[3]);

  ostringstream s;
  s << "gpio" << number;
  string name = string(s.str());
  string path = GPIO_PATH + name + "/";
  writeGPIO(path, "/direction", "out");

  if(output == "hi")
  {
    writeGPIO(path, "/value", "1");
  }
  else if(output == "low")
  {
    writeGPIO(path, "/value", "0");
  }
  else
  {
    cout << "Command is not correct. Proper usage: ./control_GPIO int hi/low int" << endl;
    return 2;
  }

  s.str("");
  s.clear();
  s << "gpio" << number2;
  name = string(s.str());
  path = GPIO_PATH + name + "/";
  writeGPIO(path, "/direction", "in");
  cout << "Pushbutton value is: " << readGPIO(path, "value") << endl;
}
