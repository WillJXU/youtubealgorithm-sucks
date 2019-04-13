bool searchalgo::findmatching(keywordsbst *n, string keyword)
{
	if(n->l != nullptr)
	{
		findmatching(n->l, keyword);
	}
	if(n->keyword == keyword)
  {
    return true;
  }
	if(n->r != nullptr)
	{
		findmatching(n->r, keyword);
	}
  return false;
};
struct videoll* addvideo(videoll *theHead, string thecreator, string thesubs[], int thedop, string thetitle, float ratio, int theduration, int theviews, int thesubcount, string theID)
{
		//Creator|Subscriptions|DOP|Title|Likes|Dislikes|Duration|Views|SubCount|ID
		videoll* insertintoll = new videoll(thecreator, thesubs, thedop, thetitle, ratio, theduration, theviews, thesubcount, theID);
		if(theHead == NULL)
	  {
	    theHead = insertintoll;
	    return theHead;
	  }
	  else if(theHead != NULL)
	  {
	  	if(insertintoll->thetitle < insertintoll->thetitle)
	    {
	      	insertintoll->next = theHead;
	      	return insertintoll;
	    }
	  	else if(theHead->next == NULL)
	    {
	        theHead->next = insertintoll;
	        insertintoll->next = NULL;
	        return theHead;
	    }
	    else
	    {
	        videoll* current = theHead;
	        videoll* prev;
	        videoll* traverse = theHead->next;
	        bool placement = false;
	        while(traverse != NULL && placement == false)
	        {
	            if(insertintoll->thetitle > current->thetitle)
	            {
	                prev = current;
	                current = current->next;
	                traverse = traverse->next;
	            }
	            else
	            {
	                placement = true;
	            }
	        }
	        insertintoll->next = current->next;
	        current->next = insertintoll;
	    }
	  }
	  return theHead;
};
void searchalgo::addkeyword(string keyword)
{
  keywordsbst *prev = nullptr;
	keywordsbst *temp = root;
	keywordsbst *newkeyword = new keywordsbst;
	newkeyword->keyword = keyword;
	while(temp != nullptr)
	{
		//set previous to temp to keep track of last node
		prev = temp;
		//check which way to look for empty spot
		if(newkeyword->keyword < temp->keyword)
		{
			temp = temp->l;
		}
		else
		{
			// if greater than or equal to
			temp = temp->r;
		}
	}
	if(prev == nullptr)
	{
		root = newkeyword;
	}
	else if(newkeyword->keyword < prev->keyword)
	{
		prev->l = newkeyword;
		newkeyword->parent = prev;
	}
	else
	{
		prev->r = newkeyword;
		newkeyword->parent = prev;
	}
};
searchalgo::searchalgo(string filename)
{
  root = NULL;
  // READ IN THE FILE
  ifstream data;
  data.open(filename);
  //Data: Keywords|Creator|Subscriptions|DOP|Title|Likes|Dislikes|Duration|Views|SubCount|ID
  string datainput, thekeywords, thecreator, thesubs, thedop, thetitle, thelikes, thedislikes, theduration, theviews, thesubcount, theID;
  string tempkeywords[10];
  int i = 0;
  if(data.is_open())
  {
      while(getline(data,datainput))
      {
	  stringstream s(datainput);
          //2.1 KEYWORDS FOR BST
          getline(s,datainput,'|');
          thekeywords = datainput;
          stringstream k(thekeywords);
          bool matchfound = false;
          while(i < 10)
          {
              getline(k,thekeywords,',');
              tempkeywords[i] = thekeywords;
              if(i != 0)   //only check for duplicates after the root is declared
              {
                matchfound = findmatching(root, thekeywords);
              }
              if(!matchfound)
              {
                addkeyword(thekeywords);
              }
              i++;
          }
          //2. DATA FOR LL
          getline(s,datainput,'|');
          thecreator = datainput;
          getline(s,datainput,'|');
          thesubs = datainput;
          getline(s,datainput,'|');
          thedop = datainput;
          getline(s,datainput,'|');
          thetitle = datainput;
          getline(s,datainput,'|');
          thelikes = datainput;
          getline(s,datainput,'|');
          thedislikes = datainput;
          getline(s,datainput,'|');
          theduration = datainput;
          getline(s,datainput,'|');
          theviews = datainput;
          getline(s,datainput,'|');
          thesubcount = datainput;
          getline(s,datainput);
          theID = datainput;

          /*
          //debugging
          cout << thecreator << endl;
          cout << thesubs << endl;
          cout << thedop << endl;
          cout << thetitle << endl;
          cout << thelikes << endl;
          cout << thedislikes << endl;
          cout << theduration << endl;
          cout << theviews << endl;
          cout << thesubcount << endl;
          cout << theID << endl;
          */
      }
  }
}


void searchalgo::getstopwords(std::string filename){
	std::ifstream f;
	f.open(filename);
	std::string s;
	while (getline(f,s)){
		int index = ((s[0]>=97)*s[0]+(s[0]<97)*(s[0]+32))-97;
		std::cout<<"Inserting Stop word: '"<<s <<"' in hash #"<<index<<std::endl;
		ignoreWord* iW = new ignoreWord;
		iW->word = s;
		iW->next = stopWordHash[index];
		stopWordHash[index] = iW;
	}
}
bool searchalgo::isStopWord(std::string s){
	for (int i = 0;i<s.length();i++){
		s[i] = ((s[i]>=97)*s[i]+(s[i]<97)*(s[i]+32));
	}
	int index = ((s[0]>=97)*s[0]+(s[0]<97)*(s[0]+32))-97;
	std::cout<<s<<": searching in "<<index<<" hash"<<std::endl;
	ignoreWord* head= stopWordHash[index];
	if (head == NULL){
		return false;
	}
	bool found = false;
	while (head!= NULL) {
		std::cout<<s<<std::endl;
		if (head->word == s){
			found = true;
			break;
		}
		head = head->next;
	}
	return found;
}
