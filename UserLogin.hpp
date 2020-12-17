#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <sstream>

using namespace std;

class UserLogin {
private:

    unordered_map< string, string > table;


public:
    UserLogin(); // default constructor

    void readIn(const string& filename); // add data from file to hash table

    size_t numberOfUsers(); // return the number of users

    string passWordCheck(const string& userName); // returns the passWord of the given user

    size_t wordBucketIdMethod1(const string& userName); // return the bucket number where the given user is located

    size_t wordBucketIdMethod2(const string& userName); // another way to find the bucket number where the given user is located

    bool validateUser(const string& userName); // look up given user

    bool authenticateUser(const string& userName, const string& passWord);// authenticate given user and password

};

UserLogin::UserLogin() {
}

// COMPLETE THE FOLLOWING FUNCTIONS

void UserLogin::readIn(const string& filename)
{
  ifstream fin;
  fin.open(filename);
  if(!fin.is_open())
  {
    return;
  }
  string line;
  while (getline(fin,line))
  {
    stringstream ss(line);
    string userName, password;
    ss >> userName >> password;
    table[userName] = password;
  }
}

size_t UserLogin::numberOfUsers()
{
  return table.size();
}

string UserLogin::passWordCheck(const string& userName)
{
  return table.find(userName) != table.end() ? table[userName] : "Non-existent User";
}

size_t UserLogin::wordBucketIdMethod1(const string& userName)
{
  return table.bucket(userName);
}

size_t UserLogin::wordBucketIdMethod2(const string& userName)
{
  unsigned n = table.bucket_count();

  for (unsigned i = 0; i < n; i++)
  {
    for (auto it = table.begin(i); it != table.end(i); ++it)
         if (it->first == userName)
           return i;
   }
}
bool UserLogin::validateUser(const string& userName)
{
  return table.find(userName) != table.end();
}

bool UserLogin::authenticateUser(const string& userName, const string& passWord)
{
  auto userExists = table.find(userName) != table.end();

  if (userExists)
    return (table.find(userName)->second == passWord);
   return false;
}
