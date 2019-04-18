#ifndef YOUTUBEALGO_HPP
#define YOUTUBEALGO_HPP
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

struct videoll{
    string creator;
    string date;
    string title;
    float likeratio;
    int duration;
    int views;
    string ID;
    struct videoll *next = NULL;

    videoll(){} // default constructor

    // Parametrized constructor
    videoll(string c, string d, string t, float r, int w, int v, string i) : creator(c),
      date(d), title(t), likeratio(r), duration(w), views(v), ID(i), next(NULL) {}
};

struct keywordsbst{
    string keyword; //node keyword
    keywordsbst *parent = NULL;
    keywordsbst *l = NULL;
    keywordsbst *r = NULL;
    videoll* head = NULL; //points to head of the list
};

struct ignoreWord{
    string word = "";
    ignoreWord* next = NULL;
};

struct videokeywords{
    string key;
};

class searchalgo{
  public:
    //Ben
    searchalgo(std::string filename);   //constructor, builds bst
    void addkeyword(string keyword);
    int totalvideokeywords(string videotitle);
    videokeywords* getkeywords(string videotitle, int videotitlewords);
    //Helpers
    bool findmatching(keywordsbst *n, string keyword);
    void getstopwords(string filename);
    bool isStopWord(string s);
    //Debug ONLY
    void dispInOrd(keywordsbst *n);     //DEBUG ONLY
    void printll(videoll *n);
  private:
    int videocount;
    int videowatched;
    videokeywords* keyword; //pointer to the table array
    //vector <videoll> watchedvideo;
    int keywordcount;
    keywordsbst *root;    //bst root
    bool match;
    videoll* VideoHash[26];
    ignoreWord* stopWordHash[26];
};
#endif
