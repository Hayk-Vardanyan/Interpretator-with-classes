#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <map>
#include <iterator>

std::ofstream fout;
std::ifstream fin;

struct all
{
  int x;
  double d;
  bool b;
  std::string type;
};

class Interpretator
{
  public:
  void what_to_do();  

  Interpretator() {
  set_keys("Digit");
  set_keys("Point");
  set_keys("Logic");
  fin.open("ban.txt");
  if(!fin.is_open()) std::cout << "cant";
  
  }
  ~Interpretator() {fin.close();}
 
  private:
  std::streampos oldpos;
  std::vector<std::string> keys;
  std::map<std::string, all> mymap;
  std::vector <std::string> vec;
  void set_keys(std::string);
  void do_declaration(std::vector<std::string>& vec, std::string);
  void do_cast(std::string, std::vector<std::string>&);
  void print_foo();
  void check();
  double if_foo(int);
  void condition_foo();
  void clear_if();
  void for_foo();
  double for_cast(std::string);
};

double Interpretator::for_cast(std::string str)
{
	if(vec[2] == "Digit")
	{	       
         int x;
         std::istringstream s(str);
         s >> x;
	 return x;
	}
	else if(vec[2] == "Point")
	{	       
         double x;
         std::istringstream s(str);
         s >> x;
	 return x;
	}
	else if(vec[2] == "Logic")
	{	       
         bool x;
         std::istringstream s(str);
         s >> x;
	 return x;
	}


}

void Interpretator::for_foo()
{  
   double first = for_cast(vec[5]); 
   double second = for_cast(vec[9]);
   //double third = for_cast(vec[12]);
   std::string act = vec[13];

   vec.clear();
   std::string str = "";
   fin >> str;
   oldpos = fin.tellg();   
if(vec[11] == "++")
{	
   for(int i = first; i < second; ++i)
   {
	   if(vec[0] == "}")
	    break;
	   fin.seekg(oldpos);
	   what_to_do();
	   
   }
}
else if(vec[11] == "--")
{	
   for(int i = first; i < second; --i)
   {
	   if(vec[0] == "}")
	    break;
	   fin.seekg(oldpos);
	   what_to_do();
	   
   }
}





//////
}
void Interpretator::clear_if()
{
	while(vec[0] != "}")
	{
		  std::string str;
    std::getline(fin, str);
    std::stringstream s(str);
    while(!s.eof())
 
{
    s >> str;
    vec.push_back(str);
}  

  vec.clear();
	}
}




void Interpretator::condition_foo()
{
      if(vec[3] == "==")
      {
	if(if_foo(2) == if_foo(4))
	{
		vec.clear();
		what_to_do();
	}
	else clear_if();
      }
      else if(vec[3] == "!=")
      {
	if(if_foo(2) != if_foo(4))
	{
		vec.clear();
		what_to_do();
	}
	else clear_if();
      }
      else if(vec[3] == ">")
      {
	if(if_foo(2) > if_foo(4))
	{
		vec.clear();
		what_to_do();
	}
	else clear_if();
      }

      else if(vec[3] == "<")
      {
	if(if_foo(2) < if_foo(4))
	{
		vec.clear();
		what_to_do();
	}
	else clear_if();
      }
      else exit(5);
}

/////////////////////////////////////////////

void Interpretator::print_foo()
{
if(vec.size() == 2)
{
 std::cout << if_foo(1);
 vec.clear();
}

else if(vec.size() > 2 && vec[2] == "+")
{
 std::cout << if_foo(1) + if_foo(3);
 
}

else if(vec.size() > 2 && vec[2] == "-")
{
 std::cout << if_foo(1) - if_foo(3);

}

else if(vec.size() > 2 && vec[2] == "/")
{
 std::cout << if_foo(1) / if_foo(3);

}

else if(vec.size() > 2 && vec[2] == "*")
{
 std::cout << if_foo(1) * if_foo(3);

}
else exit(5);


} 
/////////////

double Interpretator::if_foo(int i)
{
  for(std::map<std::string, all>::iterator it = mymap.begin(); it != mymap.end(); ++it)
  if(vec[i] == it->first)
 {
  if(it->second.type == "Digit")
    return it->second.x;

  else if(it->second.type == "Point")
    return  it->second.d;

   if(it->second.type == "Logic")
    return it->second.b;
 }
  else exit(5);
}

////////////////////////////////////////////////
void Interpretator::check()
{
 
 for(std::vector<std::string>::iterator it = keys.begin(); it != keys.end(); ++it)
{
  
  if(vec[1] == *it)
{
  std::cout << "\nComplie error\n";
  exit(8);
  }  }  }

void Interpretator::set_keys(std::string str)
{
  keys.push_back(str);

}


void Interpretator::do_declaration(std::vector<std::string>& vec,std::string str)
{
 check(); 
 do_cast(str, vec); 
 vec.clear();
}
/////////////////////////////////////////////////////////////////
void Interpretator::what_to_do()
{
    std::string str;
    std::getline(fin, str);
    std::stringstream s(str);
    while(!s.eof())
 
{
    s >> str;
    vec.push_back(str);
}  
 
for(int i = 0; i < vec.size(); ++i)
{
   if(vec[i] == "Digit" || vec[i] == "Point" || vec[i] == "Logic")
  {
     //  auto it = vec.begin();
     //  vec.erase(it + 0);
       do_declaration(vec, vec[i]);
  }

  else if(vec[i] == "Print")
{
   print_foo();
}
///////////////////////////////////////////////
  else if(vec[0] == "ete")
{
	condition_foo();
}

  else if(vec[0] == "round")
{
	std::cout << "round";
	for_foo();
}

  else vec.clear();

}

}

void Interpretator::do_cast(std::string str, std::vector<std::string>& vec)
{
  if(str == "Digit")
{
  int x;
  std::istringstream s(vec[3]);
  s >> x;
  all obj;
  obj.x = x;
  obj.type = "Digit";
  mymap.insert(std::pair<std::string, all> (vec[1], obj));
  keys.push_back(vec[1]);
}
else if(str == "Logic")
{
  bool x;
  std::istringstream s(vec[3]);
  s >> x;
  all obj;
  obj.d = x;
  obj.type = "Logic";
  mymap.insert(std::pair<std::string, all> (vec[1], obj));
  keys.push_back(vec[1]);
}

else if(str == "Point")
{
  double x;
  std::istringstream s(vec[3]);
  s >> x;
  all obj;
  obj.d = x;
  obj.type = "Point";
  mymap.insert(std::pair<std::string, all> (vec[1], obj));
  keys.push_back(vec[1]);
}
}
 
int main()
{
  Interpretator inter;

while(!fin.eof())
  inter.what_to_do();
  
}

