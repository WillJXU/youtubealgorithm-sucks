#include YOUTUBEALGO_HPP
#define YOUTUBEALGO_HPP

struct keywordsbst
{
    videoll *head = NULL; //points to head of the list
    string keyword; //node keyword
    keywordsbst *parent = NULL;
    keywordsbst *l = NULL;
    keywordsbst *r = NULL;
}

struct videoll
{
    string creator;
    string subs[80];
    int date;
    string title;
    float likeratio;
    int duration;
    int usersubs;
    struct videoll *next;
}

struct ignoreWord{
    std::string word = "";
    ignoreWord* next = NULL;
}

class searchalgo
{
  public:
  searchalgo(std::string filename);   //constructor, builds bst
  ~searchalgo();    //deconstructor
  string getkeywords(std::string videotitle, std::string keywordTab[]);
  videoll *getsuggestions(vector <std::string> keywordTab); // Goes through the bst and finds best suggestions
  //Helpers
  videoll* getVideoPointer(std::string title); // Returns the pointer of a videoll through title
  searchalgo::getKeyWordPoint(keywordbst* root ,std::string keyword) // Returns pointer of a keyword node
  void getstopwords(std::string filename);  //constructs hashtable of stop words
  bool isStopWord(std::string word); // Checks if the word is a stop work
  private:
  int videocount; // Total number of video in archive
  int videowatched; // Number of videos seen by user
  vector <videoll> watchedvideo; //Vector of the videos seen by user in the session
  int keywordcount; // Number of Keywords
  keywordsbst *root;    //bst root
  videoll* VideoHash[26];
  ignoreWord* stopWordHash[26];
}
#endif
