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

class searchalgo
{
  public:
  searchalgo(std::string filename);   //constructor, builds bst
  ~searchalgo();    //deconstructor
  string getkeywords(std::string videotitle, std::string keywordTab[]);
  videoll *getsuggestions(vector <std::string> keywordTab);
  void getstopwords();  //constructs array of stop words
  private:
  int videocount;
  int videowatched;
  vector <videoll> watchedvideo;
  int keywordcount;
  keywordsbst *root;    //bst root
}
#endif
