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
  videoll *getsuggestions(vector <std::string> keywordTab);
  //Helpers
  videoll* getVideoPointer(std::string title);
  searchalgo::getKeyWordPoint(keywordbst* root ,std::string keyword)  
  void getstopwords();  //constructs array of stop words
  private:
  int videocount;
  int videowatched;
  vector <videoll> watchedvideo;
  int keywordcount;
  keywordsbst *root;    //bst root
  videoll* VideoHash[26];
  ignoreWord* stopWordHash[26];
}
#endif
