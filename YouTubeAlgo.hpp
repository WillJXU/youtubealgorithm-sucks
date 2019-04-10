#include YOUTUBEALGO_HPP
#define YOUTUBEALGO_HPP

struct keywordsbst
{
    string keyword; //node keyword
    videoll *head; //points to head of the list
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
    videoll *next;
}

class searchalgo
{
  public:
  searchalgo(std::string filename);   //constructor, builds bst
  ~searchalgo();    //deconstructor
  string getkeywords(std::string videotitle, std::string keywordTab[]);
  videoll *getsuggestions(std::string keywordTab[]);
  void getstopwords();  //constructs array of stop words
  private:
  int videocount;
  int videowatched;
  vector <videoll> watchedvideo;
  int keywordcount;
}
