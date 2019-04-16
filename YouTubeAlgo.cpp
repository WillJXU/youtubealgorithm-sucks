//  FOR DEBUGGING ONLY  //
void searchalgo::dispInOrd(keywordsbst *n){
	//prints BST Nodes (In Order)
	if(n->l != nullptr){
		dispInOrd(n->l);
	}
	cout << "========= KEYWORD NODE ============" << endl;
	cout << n->keyword << endl;
	printll(n->head);
	if(n->r != nullptr){
		dispInOrd(n->r);
	}
};
void searchalgo::printll(videoll *n){
	videoll *traverse = n;
	cout << "========= LINKED LIST VIDEOS ============" << endl;
	while(traverse != NULL){
			cout << "- " << traverse->title << endl;
			cout << "  -By: " << traverse->creator << endl;
			cout << "  -DOP: " << traverse->date << endl;
			cout << "  -Like ratio: " << traverse->likeratio << endl;
			cout << "  -Duration: " << traverse->duration << endl;
			cout << "  -Total views on this video: " << traverse->views << endl;
			cout << "  -Creator's Sub Count: " << traverse->usersubs << endl;
			cout << "  -Video ID: https://www.youtube.com/watch?v=" << traverse->ID << endl;
			traverse = traverse->next;
	}
	cout << endl;
};
//  HELPER FUNCTIONS  //
bool searchalgo::findmatching(keywordsbst *n, string keyword){
	//cout << n->keyword << endl;
	if(n->l != nullptr){
		findmatching(n->l, keyword);
	}
	if(n->keyword == keyword){
		//cout << "found" << endl;
		match = true;
  }
	if(n->r != nullptr){
		findmatching(n->r, keyword);
	}
  return match;
};
keywordsbst* findnoderecur(keywordsbst *rootPtr , string keyword){
    keywordsbst* thekeyword = rootPtr;
		if(thekeyword != NULL){
			if(thekeyword->keyword == keyword){
				return thekeyword;
			}
			else if(thekeyword->keyword > keyword){
				return findnoderecur(thekeyword->l, keyword);
			}
			else{
				return findnoderecur(thekeyword->r, keyword);
			}
		}
		else{
			return nullptr;
		}
};
keywordsbst* findnode(keywordsbst *rootPtr, string keyword){
    keywordsbst *ptr = findnoderecur(rootPtr,keyword);
    return ptr;
};
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
};
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
};
//  CLASS FUNCTIONS  //
struct videoll* addvideo(videoll *theHead, string thecreator, string thedop, string thetitle, float ratio, int theduration, int theviews, int thesubcount, string theID){
		//Creator|Subscriptions|DOP|Title|Likes|Dislikes|Duration|Views|SubCount|ID
		videoll* insertintoll = new videoll(thecreator, thedop, thetitle, ratio, theduration, theviews, thesubcount, theID);
		//if LL is empty
	  if(theHead == NULL){
	    theHead = insertintoll;
	    return theHead;
	  }
	  //if LL is not empty
	  else if(theHead != NULL){
	  	if(insertintoll->title < insertintoll->title){
	      	insertintoll->next = theHead;
	      	return insertintoll;
	    }
	  	else if(theHead->next == NULL){
	        theHead->next = insertintoll;
	        insertintoll->next = NULL;
	        return theHead;
	    }
	    else{
	        videoll* current = theHead;
	        videoll* prev;
	        videoll* traverse = theHead->next;
	        bool placement = false;
	        while(traverse != NULL && placement == false){
	            if(insertintoll->title > current->title){
	                prev = current;
	                current = current->next;
	                traverse = traverse->next;
	            }
	            else{
	                placement = true;
	            }
	        }
	        insertintoll->next = current->next;
	        current->next = insertintoll;
	    }
	  }
	  return theHead;
};
void searchalgo::addkeyword(string keyword){
  keywordsbst *prev = nullptr;
	keywordsbst *temp = root;
	keywordsbst *newkeyword = new keywordsbst;
	newkeyword->keyword = keyword;
	while(temp != nullptr){
		//set previous to temp to keep track of last node
		prev = temp;
		//check which way to look for empty spot
		if(newkeyword->keyword < temp->keyword){
			temp = temp->l;
		}
		else{
			// if greater than or equal to
			temp = temp->r;
		}
	}
	if(prev == nullptr){
		root = newkeyword;
	}
	else if(newkeyword->keyword < prev->keyword){
		prev->l = newkeyword;
		newkeyword->parent = prev;
	}
	else{
		prev->r = newkeyword;
		newkeyword->parent = prev;
	}
};
searchalgo::searchalgo(string filename){
  // 1. SET PRIVATE MEMBER DEFAULTS  //
  root = NULL;
  videocount = 0;
videowatched = 0;
  keywordcount = 0;
match = false;
//getstopwords("YTignoreWords.txt");
  // 2. READ IN THE FILE  //
  ifstream data;
  data.open(filename);
  //Data: Keywords|Creator|DOP|Title|Likes|Dislikes|Duration|Views|SubCount|ID
  string datainput, thekeywords, thecreator, thedop, thetitle, thelikes, thedislikes, theduration, theviews, thesubcount, theID;
  string tempkeywords[10];
  int i = 0;
bool matchfound;
bool setroot = false;
  if(data.is_open()){
	//while there is data to read
      while(getline(data,datainput)){
          stringstream s(datainput);
          //2.1 KEYWORDS FOR BST
          getline(s,datainput,'|');
          thekeywords = datainput;
          stringstream k(thekeywords);
	      for(int i = 0; i < 10; i++){
              getline(k,thekeywords,',');
		if(thekeywords != ""){
			bool stopcheck = isStopWord(thekeywords);
			if(!stopcheck){
				tempkeywords[i] = thekeywords;
				//set the root if root is NULL
				if(setroot == false){
					addkeyword(thekeywords);
					setroot = true;
				}
				else{
					matchfound = findmatching(root, thekeywords);
					//IF a match is not found, add it to the LL
					if(!matchfound){
						if(thekeywords != ""){
							addkeyword(thekeywords);
						}
					}
				}
				thekeywords = "";		//Sets thekeywords to empty string in case there are not a total of 10 keywords
				match = false;		//Sets match used in findmatching() to false for next word
			}
	}
	      }
          //2.2 DATA FOR LL
          getline(s,datainput,'|');
          thecreator = datainput;
          getline(s,datainput,'|');
          thedop = datainput;
          getline(s,datainput,'|');
          thetitle = datainput;
          getline(s,datainput,'|');
          thelikes = datainput;
	  getline(s,datainput,'|');
          thedislikes = datainput;
	  float ratio = ((stof(thelikes) / (stof(thelikes) + stof(thedislikes))) * 100);
          getline(s,datainput,'|');
          theduration = datainput;
          getline(s,datainput,'|');
          theviews = datainput;
          getline(s,datainput,'|');
          thesubcount = datainput;
          getline(s,datainput);
          theID = datainput;
	//2.3 INSERT FOR LL
	for(int i = 0; i < 10; i++){
	//if the word is not an empty string
		if(tempkeywords[i] != ""){
			keywordsbst *nodeptr = findnode(root, tempkeywords[i]);	//find the bstNode equal to the keyword
			//below, the function adds the information to the ll and returns the head ptr of the ll at that node
			nodeptr->head = addvideo(nodeptr->head, thecreator, thedop, thetitle, ratio, stoi(theduration), stoi(theviews), stoi(thesubcount), theID);
		}
		tempkeywords[i] = "";			//sets tempkeyword to empty string since it is no longer needed
      	}
  	}
	}
	data.close();
	dispInOrd(root);		//DEBUG ONLY: Shows the BST and LL of Each Node
};
