#include <iostream>

using namespace std;

// used to empty a given string A of length n
void emptyString (char* A, int n) {
	for (int i=0; i < n; i++) {
		A[i] = '\0';
	}
}

// copy a string A to B of length n
void stringCopy (char* A, int n, char* B) {
	for (int i=0; i < n; i++) {
		B[i] = A[i];
	}
}

// return the length of a given string A
int stringLength (char* A) {
	int size = 0;
	while (A[size] != '\0') size++;
	return size; //size is the last index position
}

class myString;

class myString {
	friend ostream& operator << (ostream& s, myString& A);
protected:
	char* strArray;
	int size;
	void strCpy (char* A, char* B, int n);
public:
	myString ();
	myString(char* inpStr);
	myString (myString& B);
	int Size();
	char* getWord();
	bool operator == (myString& B);
	bool operator > (myString& B);
	bool operator < (myString& B);
	myString& operator = (myString& B);
	myString& operator = (char* B);
};

// outputs a given string A
ostream& operator << (ostream& s, myString& A) {
	s << A.strArray;
	return s;
}

// default constructor - initializes with a NULL as the first character
myString::myString () {
	size = 0;
	strArray = new char[1];
	strArray[0] = '\0';
}

// non default constructor - initialize object with an existing string
myString::myString (char* inpStr) {
	int i = 0;
	while (inpStr[i] != '\0')
		i++;
	size = i;
	strArray = new char[size];
	emptyString (strArray, size+1);
	for (int j=0; j < size; j++)
		strArray[j] = inpStr[j];
}

// non default constructor - initialize object with an existing mystring object
myString::myString (myString& B) {
	delete [] strArray;
	strArray = NULL;
	size = B.size;
	strArray = new char[size];
	emptyString(strArray, size+1);
	stringCopy (B.strArray, size, strArray);
}

// getter for string of myString
char* myString::getWord()
{
	return strArray;
}

// getter for size of myString
int myString::Size () {
	return size;
}

// overloading = operator - initialize object with an existing string
myString& myString::operator = (char* B) {

	this->strArray = B;

	return NULL;
}

// overloading = operator - initialize object with an existing myString object
myString& myString::operator = (myString& B) {

	this->strArray = B->strArray;

	return NULL;
}

// checking if two myString objects are the same - return true or false
bool myString::operator == (myString& B) {

	bool same = True;
	if (this->size == B->size) {
		for (int i=0;i<size;i++) {
			if (this->strArray[i] != B->strArray[i]) {
				same = False;
				break;
			}
		}
	} else {
		same = False;
	}

	return same;
}

// comparison of myString A if less than myString B - return true or false
bool myString::operator < (myString& B) {

	bool lessThan = False;
	if (this->size < B->size) {
		lessThan = True;
	}

	return lessThan;
}

// comparison of myString A if greater than myString B - return true or false
bool myString::operator > (myString& B) {

	bool greaterThan = False;
	if (this->size > B->size) {
		greaterThan = True;
	}

	return greaterThan;
}

// get one URL from redirected input and return it as a string
char* getNextURL () {
	char* str = new char[50]; //assumes a max URL size of 50
	emptyString (str, 50);

	char c;
	int i = 0;
	bool cont;
	char diffChar;
	//read until the next white space or line-break 
	//modify the following line of code, so that the function returns only the URLs (i.e., it ignores everything that does not start with http:// or https:// )

	while (!cin.eof()) {
		cont = False;
		if (cin.get(c) == 'h') {
			if (cin.get(c) == 't') {
				if (cin.get(c) == 't') {
					if (cin.get(c) == 'p') {
						diffChar = cin.get(c);
						if (diffChar == 's') {
							if (cin.get(c) == ':') {
								if (cin.get(c) == '/') {
									if (cin.get(c) == '/') {
										cont = True;
									}
								}
							}
						} else if (diffChar == ':') {
							if (cin.get(c) == '/') {
								if (cin.get(c) == '/') {
									cont = True;
								}
							}
						}
					}
				}
			}
		}
		cin.get(c);
		if (cont && !cin.eof() ) {
			if ((c != '\n') && (c != ' ')) {
				if ( ((c >= 'a') && (c <= 'z')) ||
					 ((c >= 'A') && (c <= 'Z')) ||
					 ((c >= '0') && (c <= '9')) ||
					 (c >= ':') || (c >= '/') || (c >= '.') || (c >= '_'))
					str[i++] = c;
			}
			else if ((c == '\n') && (i > 0))
				return str;
			else if ((c == ' ') && (i > 0))
				return str;
		}
	}
	if (i > 0) return str;
	else return NULL;
}



// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
class setOfURLs {
private:
	int binarySearchAndInsert (myString& u);
protected:
	myString* _URLs;
	int* _frequencies;
	int _size;

public:
	setOfURLs ();
	setOfURLs (int numOfWords);

	myString* get_Words();
	int* get_Freq();
	int get_size();

	void setSize(int i);

	void addURL (myString& u);//insert word w into the array _URLs - keep it sorted alphabetically
	void sortFreq(); //sort words array based on frequency
	void sortURLs(); //sort words array alphabetically
	void display(); //print word followed by a colon followed by a single space and frequencuy
	setOfURLs* removeURLs(myString* URLsToFilterOut, int numURLsToFilterOut); //URLsToFilterOut from _URLs array
	~setOfURLs();
};

// default constructor - initializes with no URLs
setOfURLs::setOfURLs()
{
	_size = 0;
	_URLs = new myString[0];
	_frequencies = new int[0];
}

// non default constructor - initializes with a known number of URLs
setOfURLs::setOfURLs (int numOfWords)
{
	_size = numOfWords;
	_URLs = new myString[numOfWords];
	_frequencies = new int[numOfWords];
}

// getter for the array of URLs of the setOfURLs
myString* setOfURLs::get_Words()
{
	return _URLs;
}

// getter for the array of frequencies of the setOfURLs
int* setOfURLs::get_Freq()
{
	return _frequencies;
}

// getter for the size of the setOfURLs
int setOfURLs::get_size()
{
	return _size;
}

// store the value of the size of the setOfURLs
void setOfURLs::setSize(int i)
{
	_size = i;
}

// print the set of URLs in dictionary format (i.e., in alphabetical order)
void setOfURLs::display()
{

	// TODO

}

// sort the _URLs and _frequencies arrays, based on the frequencies
void setOfURLs::sortFreq()
{
	myString words = get_Words();
	int size = get_size();
	int count = 0;

	while (count < size) {

	}
}

// sort the _URLs and _frequencies arrays, alphabetically
void setOfURLs::sortURLs()
{
	// TODO
}

// remove from the setOfURLs object, the URLs that have to be filtered out 
setOfURLs* setOfURLs::removeURLs(myString* URLsToFilterOut, int numURLsToFilterOut)
{

	// TODO

	return NULL;
}

// search for a given URL in _URLs - if found, update the setOfURLs object accordingly, if not, return the position where the URL has to be inserted
int setOfURLs::binarySearchAndInsert (myString& wordToFind)
{

	// TODO

	return NULL;
}

// method to store URLs to the setOfURLs object
void setOfURLs::addURL(myString & newWord)
{
	// TODO
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

class URLLinks {

	friend ostream& operator << (ostream& s, URLLinks& A);

protected:
	myString URL;
	int numLinks;
	URLLinks** hyperLinks;

public:
	URLLinks();
	URLLinks(myString& x, int n);
	~URLLinks();

	int getNumLinks();
	URLLinks* getHyperLink(int i);
	myString& getURL();

	void addSite(myString& t);
	void addNeighbor(URLLinks& link);
	void setNeighbors(int nei);
};

// add the information about URL A to the output stream s 
ostream& operator << (ostream& s, URLLinks& A)
{
	//TODO
}

// create an empty URLLinks object
URLLinks::URLLinks()
{
	//TODO
}

// create a URLLinks object for URL x with n neighbors
URLLinks::URLLinks(myString& x, int n)
{
	//TODO
}

// return the URL of the URLLinks object
myString& URLLinks::getURL()
{
	//TODO
}

// returm the number of links of the URLLinks object
int URLLinks::getNumLinks()
{
	//TODO
}

// return a URLLinks object
URLLinks* URLLinks::getHyperLink(int i)
{
	//TODO
}

// destructor fot the URLLinks class
URLLinks::~URLLinks()
{
	//TODO
}

// store t as the URL of the URLLinks object
void URLLinks::addSite(myString& t)
{
	//TODO
}

// store the number of neighboring URLs of the specific URL, and create the space needed to store these URLs in the future
void URLLinks::setNeighbors(int nei)
{
	//TODO
}

// store the neighboring URLs of the specific URL
void URLLinks::addNeighbor(URLLinks& link)
{
	//TODO
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
int main () {

	cout << setOfURLs.get_Words() << endl;

}
