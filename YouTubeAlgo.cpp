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
			cout << "  -Video ID: https://www.youtube.com/watch?v=" << traverse->ID << endl;
			cout << endl;
			traverse = traverse->next;
	}
};
//  HELPER FUNCTIONS  //
string convertlowercases(string keyword){
		int length = keyword.length();
		string lowercase = "";
		char c;
		for(int i = 0; i < length; i++)
		{
				if(isupper(keyword[i]))
				{
						c = tolower(keyword[i]);
						lowercase = lowercase + c;
				}
				else
				{
					lowercase = lowercase + keyword[i];
				}
		}
		return lowercase;
};
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
int searchalgo::totalvideokeywords(string videotitle){
	int videotitlewords = 0;
	string storingkeyword = videotitle;
	int length = storingkeyword.length();
	for(int i = 0; i < length; i++){
			if(storingkeyword[i] == ' '){
					videotitlewords++;
			}
	}
	videotitlewords++;
	return videotitlewords;
};
//  CLASS FUNCTIONS  //
videokeywords* searchalgo::getkeywords(string videotitle, int videotitlewords){
		string storingkeyword = videotitle;
		stringstream s(storingkeyword);
		int i = 0;
		keyword = new videokeywords[videotitlewords];
		while(i < videotitlewords){
			getline(s,storingkeyword,' ');
			bool stopcheck = isStopWord(storingkeyword);
			if(!stopcheck){
				keyword[i].key = storingkeyword;
			}
			i++;
		}
		/*
		for(int i = 0; i < videotitlewords; i++){
				cout << keyword[i].key << endl;
		}
		*/
		return keyword;
};
struct videoll* addvideo(videoll *theHead, string thecreator, string thedop, string thetitle, float ratio, int theduration, int theviews, string theID){
		//Creator|Subscriptions|DOP|Title|Likes|Dislikes|Duration|Views|SubCount|ID
		videoll* insertintoll = new videoll(thecreator, thedop, thetitle, ratio, theduration, theviews, theID);
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
string wordhelper(string keyword){
		string word = "";
		if(keyword[0] == ' ')
		{
			int length = keyword.length();
			bool removefrontspace = false;
			for(int i=0;i<length;i++)
			{
					if(i != 0)
					{
							word = word + keyword[i];
					}
			}
			return word;
		}
		else
		{
			return keyword;
		}
};
searchalgo::searchalgo(string filename){
  // 1. SET PRIVATE MEMBER DEFAULTS  //
  root = NULL;
  videocount = 0;
	videowatched = 0;
  keywordcount = 0;
	match = false;
	getstopwords("YTignoreWords.txt");
  // 2. READ IN THE FILE  //
  ifstream data;
  data.open(filename);
	//int getlinecounter = 0;
  //Data: Keywords|Creator|DOP|Title|Likes|Dislikes|Duration|Views|ID
  string datainput, thekeywords, thecreator, thedop, thetitle, thelikes, thedislikes, theduration, theviews, theID;
  string tempkeywords[100];
	bool matchfound;
	bool setroot = false;
  if(data.is_open()){
			//while there is data to read
      while(getline(data,datainput)){
					int i = 0;
					int j = 1;
          stringstream s(datainput);
          //2.1 KEYWORDS FOR BST
          getline(s,datainput,'"');
					getline(s,datainput,'"');
          thekeywords = datainput;
					//cout << thekeywords << endl;
					stringstream k(thekeywords);
					while(i < j){
							getline(k,thekeywords,',');
							if(thekeywords[0] == ' ')
							{
									thekeywords = wordhelper(thekeywords);
							}
							//cout << thekeywords << endl;
							if(thekeywords != ""){
								thekeywords = convertlowercases(thekeywords);
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
									thekeywords = "";
									match = false;		//Sets match used in findmatching() to false for next word
									j++;
									}
							}
							i++;
					}
          //2.2 DATA FOR LL
          getline(s,datainput,',');
					getline(s,datainput,',');
          thecreator = datainput;
          getline(s,datainput,',');
          thedop = datainput;
					getline(s,datainput,',');
          thetitle = datainput;
          getline(s,datainput,',');
          thelikes = datainput;
					getline(s,datainput,',');
          thedislikes = datainput;
					float ratio = ((stof(thelikes) / (stof(thelikes) + stof(thedislikes))) * 100);
          getline(s,datainput,',');
          theduration = datainput;
					getline(s,datainput,',');
          theviews = datainput;
					getline(s,datainput);
          theID = datainput;
					//2.3 INSERT FOR LL
					for(int i = 0; i < j; i++){
						//if the word is not an empty string
						if(tempkeywords[i] != ""){
								keywordsbst *nodeptr = findnode(root, tempkeywords[i]);					//find the bstNode equal to the keyword
								//below, the function adds the information to the ll and returns the head ptr of the ll at that node
								nodeptr->head = addvideo(nodeptr->head, thecreator, thedop, thetitle, ratio, stoi(theduration), stoi(theviews), theID);
						}
						tempkeywords[i] = "";			//sets tempkeyword to empty string since it is no longer needed
      		}
					//getlinecounter++;
					//cout << getlinecounter << endl;
  		}
	}
	data.close();
	dispInOrd(root);		//DEBUG ONLY: Shows the BST and LL of Each Node
};
