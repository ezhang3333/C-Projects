#include "anagram.h"
#include <iostream>
#include <fstream>
using namespace std;
//This MP was worked on by Akhil Morisetty(akhilm6), Ethan Zhang(ethanjz2), Aashay Soni(asoni29)
/***
An AnagramDict constructor. This Constructor takes in a filepath
and then creates a binary tree out of all the words inside the 
binary tree. 

Input: 
std::string filename - the path to the file

Output:
N/A
***/
AnagramDict::AnagramDict(std::string filename) {
    filename_ = filename;
    std::string path = "dictionaries/" + filename_;
    std::ifstream file;
    file.open(path.c_str());
    string name;
    while(file >> name)
    {
        addWord(name);
    }
    /**
        Your code goes below here
    **/


}

/***
An AnagramDict member function. This function sorts the given word in 
lexicographical order

Input: 
std::string word - the word that needs to be sorted

Output:
std::string - the sorted version of the input
***/
std::string AnagramDict::sortWord(std::string word) {
    /**
        Your code goes below here
    **/
   sort(word.begin(),word.end());
   return word;
}

/***
An AnagramDict member function. This function adds a word to the tree.
If the words sorted version already exists in the tree add it to the linked
list of that node. If the sorted word does not exist in the tree create a new
node and insert it into the tree
Duplicated words should not be added to the tree.
Input: 
std::string word - the word that needs to inserted

Output:
N/A
***/
void AnagramDict::addWord(std::string word) {
    /**
        Your code goes below here
    **/
   string s = sortWord(word);
   string y;
   Node<string,list<string> > *n = this->tree.find_node(s);
   if(n == NULL)
   {
        list<string> new_l;
        new_l.push_back(word);
        Node<string,list<string> > *next = new Node<string,list<string> >(s,new_l);
        this->tree.insert_node(this->tree.getRoot(),next);
   }
   else if(n != NULL)
   {
    list<string> su = n->getData();
    list<string>::iterator x = su.begin();
    for(x = su.begin(); x != su.end();x++)
    {
        if(*x == word)
            return;
    }
    su.push_back(word);
    n->setData(su);
   }
}

/***
An AnagramDict member function. Does a preorder, postorder, or inorder traversal
and then prints out all the anagrams and words.

The output file should be the traversal order of the tree, but only the data on each line. 
View on wiki for more information. 

Input: 
std::string order - The type of order you want to traverse. Can be "pre", "post", "in"

Output:
N/A
***/
void AnagramDict::saveAnagrams(std::string order) {
    
    std::string path = "output/" + order+"_"+ filename_;
    std::ofstream file;
    file.open(path.c_str());
    if(!file.is_open()) {
        //create new file
        file.open(path.c_str(),std::ios::out);
    }
    /**
        Your code goes below here
    **/
   list<Node<string,list<string> > > n;
   if(order == "pre")
   {
        this->tree.pre_order(this->tree.getRoot(),n);
        list<Node<string,list<string> > >::iterator i = n.begin();
        for(i = n.begin();i != n.end();i++)
        {
            list<string> u = i->getData();
            list<string>::iterator v = u.begin();
            for(v = u.begin();v != u.end();v++)
            {
                file<<*v<<" ";
            }
            file<<endl;
        }
   }
   else if(order == "in")
   {
        this->tree.in_order(this->tree.getRoot(),n);
        list<Node<string,list<string> > >::iterator i = n.begin();
        for(i = n.begin();i != n.end();i++)
        {
            list<string> u = i->getData();
            list<string>::iterator v = u.begin();
            for(v = u.begin();v != u.end();v++)
            {
                file<<*v<<" ";
            }
            file<<endl;
        }
   }
   else if(order == "post")
   {
        this->tree.post_order(this->tree.getRoot(),n);
        list<Node<string,list<string> > >::iterator i = n.begin();
        for(i = n.begin();i != n.end();i++)
        {
            list<string> u = i->getData();
            list<string>::iterator v = u.begin();
            for(v = u.begin();v != u.end();v++)
            {
                file<<*v<<" ";
            }
            file<<endl;
        }
   }

   file.close();

}