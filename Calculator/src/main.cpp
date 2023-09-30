/**
 * @file    main.cpp
 * @author  Liuchenruo <1816655804@qq.com>
 * @date    Tue Oct 26 15:00:36
 *
 * @brief   Inplementation of calculator.
 *
 */
#include<iostream>
#include<stack>
#include<vector>
#include<cstring>
#include<cstdlib>
#include<fstream>

using namespace std;

/**
 * N is the row number of "input.txt",
 * the default value of row number is 20.
 */
const int N = 20;
bool FLAG = true;
ifstream input("input.txt");
ofstream output("output.txt");


// Output for error conditions.
void exitAbnormal()
{
  output << "Error." << endl;
  FLAG = false;
}


// Calculates the priority of the operator.
int priLevel(const string op)
{
  if (op == "+" || op == "-")
    return 1;
  if (op == "*" || op == "/")
    return 2;
  if (op == "(")
    return 3;
  if (op == ")")
    return 0;
}


int main(int argc, char* argv[])
{
  for (int i = 0; i < N; i++)
  {

    string ori = "";
    getline(input, ori);

    FLAG = true;
    const string Num = "0123456789.";
    const string Op = "+-*/()";

    
    // Fliters invalid characters.
    string exp = "";
    for (int i = 0; i < ori.size(); i++)
    {
      string ss = ori.substr(i, 1);
      if (Num.find(ss) != string::npos || Op.find(ss) != string::npos)
	exp.append(ss);
    }
    exp.append("+"); // Prevents index out of range.

    
    // Reads the infix expression.
    vector<string> Infix;
    int count = 0;
    while (count < exp.size() - 1)
    {
      string ss = exp.substr(count, 1);
      if (Op.find(ss) != string::npos)
      {
	if (ss != ")" && exp.substr(count + 1, 1) == ")")
        {
	  exitAbnormal();
	  break;
	}
	if (ss == "-" && count == 0 ||
	    ss == "-" && exp.substr(count - 1, 1) == "(")
        {
	  int p = exp.find_first_of(Op, count + 1);
	  if (exp.substr(p, 1) == "(")
	  {
	    exitAbnormal();
	    break;
	  }
	  string n = exp.substr(count, p - count);
	  if (n.find(".") != n.rfind("."))
	  {
	    exitAbnormal();
	    break;
	  }
	  if (n.find(".") == 0 || n.find(".") == n.size())
	  {
	    exitAbnormal();
	    break;
	  }
	  Infix.push_back(n);
	  count = p; 
	}
	else
	{
	  Infix.push_back(exp.substr(count, 1));
	  count++;
	}
      }
      else
      {
	int p = exp.find_first_of(Op, count);
	if (exp.substr(p, 1) == "(")
	{
	  exitAbnormal();
	  break;
	}
	string n = exp.substr(count, p - count);
	if (n.find(".") != n.rfind("."))
	{
	  exitAbnormal();
	  break;
	}
	if (n.find(".") == 0 || n.find(".") == n.size())
	{
	  exitAbnormal();
	  break;
	}
	Infix.push_back(n);
	count = p; 
      }
    }
    if (!FLAG)
      continue;
    

    // Infix to Postfix expressions conversion.
    stack<string> IntoPost;
    vector<string> Postfix;
    for (int i = 0; i < Infix.size(); i++)
    {
      if (Op.find(Infix[i]) == string::npos)
	Postfix.push_back(Infix[i]);
      else
      {
	if (IntoPost.empty())
	{
	  if (Infix[i] == ")")
	  {
	    exitAbnormal();
	    break;
	  }
	  IntoPost.push(Infix[i]);
	}
	else
	{
	  if (Infix[i] != ")")
	  {
	    int pri = priLevel(IntoPost.top());
	    while (priLevel(Infix[i]) <= pri && IntoPost.top() != "(")
	    {
	      Postfix.push_back(IntoPost.top());
	      IntoPost.pop();
	      if (!IntoPost.empty())
		pri = priLevel(IntoPost.top());
	      else
		break;
	    }
	    IntoPost.push(Infix[i]);
	  }
	  else
	  {
	    while (IntoPost.top() != "(" )
	    {
	      Postfix.push_back(IntoPost.top());
	      IntoPost.pop();
	      if (IntoPost.empty())
	      {
		exitAbnormal();
		break;
	      }
	    }
	    if (!FLAG)
	      break;	    
	    IntoPost.pop();
	  }
	}
      } 
    }
    if (!FLAG)
      continue;
    while (!IntoPost.empty())
    {
      if (IntoPost.top() == "(")
	{
	  exitAbnormal();
	  break;
	}
      Postfix.push_back(IntoPost.top());
      IntoPost.pop();
    }
    if (!FLAG)
      continue;


    // Calculates postfix expressions and outputs results.
    stack<double> Output;
    for (int i = 0; i < Postfix.size(); i++)
    {
      
      if (Op.find(Postfix[i]) == string::npos)
	Output.push(stod(Postfix[i]));
      else
      {
	double s = Output.top();
	Output.pop();
	if (Output.empty())
	{
	  exitAbnormal();
	  break;
	}
	double f = Output.top();
	Output.pop();
	if (Postfix[i] == "+")
	  Output.push(s + f);
	if (Postfix[i] == "-")
	  Output.push(f - s);
	if (Postfix[i] == "*")
	  Output.push(s * f);
	if (Postfix[i] == "/")
	  if (s != 0)
	    Output.push(f / s);
	  else
	  {
	    exitAbnormal();
	    break;
	  }
      }
    }
    if (!FLAG)
      continue;
    double result = Output.top();
    Output.pop();
    if (!Output.empty())
      exitAbnormal();
    if (!FLAG)
      continue;
    output << result << endl;
  }

  input.close();
  output.close();
  
  return 0;
}
  
