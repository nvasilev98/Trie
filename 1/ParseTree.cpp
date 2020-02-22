#include <iostream>
#include <string>
#include <vector>

using namespace std;

const int AlphabetSize = 26;

struct TrieNode {
	TrieNode* next[AlphabetSize];
	int NumOfOcc;
	bool isEnd;
	TrieNode() {
		for (int i = 0; i < AlphabetSize; i++) {
			next[i] = NULL;
		}
		NumOfOcc = 0;
		isEnd = false;
	}
	
};
class Trie {
public:
	Trie() {
		root = NULL;
	}
	Trie(const Trie& other) {
		copy(other);
	}
	Trie& operator=(const Trie& other) {
		if (this != &other) {
			del(root);
			copy(other);
		}
		return *this;
	}
	~Trie() {
		del(root);
	}
	void addWord(const string& word) {
		if (root == NULL) root = new TrieNode;
		TrieNode* curr = root;
		for (int i = 0; i < word.length(); i++) {
			int letter = word[i] - 'a';
			if (curr->next[letter] == NULL) {
				curr->next[letter] = new TrieNode();
			}
			curr = curr->next[letter];
		}
		curr->isEnd = true;
		curr->NumOfOcc++;
		

	}
	vector<string> getSuggestions(const string& beginning){
		vector<string> result;
		findSimilar(beginning, result);
		return result;
	}
	bool find(const string& word){
		if (root == NULL) return false;
		TrieNode* curr = root;
		for (int i = 0; i < word.length(); i++) {
			int letter = word[i] - 'a';
			if (curr->next[letter] == NULL) {
				return false;
			}
			curr = curr->next[letter];
		}
		return curr->isEnd;	
	}
	bool remove(const string& word){
		if (!find(word)) {
			return false;
		}
		delWord(word);
		return true;
	}
	int getValue (const string& word){
		TrieNode* curr = root;
		if (curr == NULL) {
			return 0;
		}
		for (int i = 0; i < word.length(); i++) {
			int letter = word[i] - 'a';
			if (curr->next[letter] == NULL) {
				return 0;
			}
			curr = curr->next[letter];
		}
		return curr->NumOfOcc;
	}


private:
	TrieNode* root;
	void del(TrieNode* &p) {
		if (p == NULL) return;
		for (int i = 0; i < AlphabetSize; i++) {
			del(p->next[i]);
		}
		delete p;
		p = NULL;
	}
	void copyRoots(TrieNode* &p, TrieNode* const & other) {
		p = NULL;
		if (other != NULL) {
			p = new TrieNode;
			p->NumOfOcc = other->NumOfOcc;
			p->isEnd = other->isEnd;
			for (int i = 0; i < AlphabetSize; i++) {
				copyRoots(p->next[i], other->next[i]);
			}
		}
	}
	void copy(const Trie& other) {
		copyRoots(root, other.root);
	}
	void delWord(const string& word) {
	TrieNode* curr = root;
	if (curr == NULL) {
		return;
	}
	for (int i = 0; i < word.length(); i++) {
		int letter = word[i] - 'a';
		if (curr->next[letter] == NULL) {
			return;
		}
		curr = curr->next[letter];
	}
	curr->isEnd = false;
	curr->NumOfOcc = 0;
	}
	void findSimilar(const string& beginning, vector<string>& result) {
		TrieNode* curr = root;
		for (int i = 0; i < beginning.length(); i++) {
			int letter = beginning[i] - 'a';
			if (curr->next[letter] == NULL) {
				return;
			}
			curr = curr->next[letter];
			
		}
	
		if (curr->isEnd == true) {
			result.push_back(beginning);
		}
		for (int i = 0; i < AlphabetSize; i++) {
			if (curr->next[i]) {
				int letter = 'a' + i;
				string temporary = beginning + (char)letter;
				findSimilar(temporary, result);
			}

		}
	}
		
};
void sortStringByValue(vector<pair<string, int>>& input) {
	for (int i = 0; i < input.size() - 1; i++) {
		for (int j = 0; j < input.size() - i - 1; j++) {
			if (input[j].second < input[j + 1].second) {
				pair <string, int> temp(input[j]);
					input[j] = input[j + 1];
					input[j + 1] = temp;
			}
		}
	}
}
int main() {
	//zad2
	string txt;
	Trie sTree;
	while (cin >> txt) {
		sTree.addWord(txt);
	}
	/*
	sTree.addWord("ivan");
	sTree.addWord("ivan");
	sTree.addWord("gogo");
	sTree.addWord("gogo");
	sTree.addWord("gogo");
	sTree.addWord("misho");

	sTree.addWord("gogo");
	sTree.addWord("shefa");
	sTree.addWord("shefa");
	sTree.addWord("shefa");
	*/

	vector<string> words = sTree.getSuggestions("");
	vector<pair<string, int>> conc;
	for (int i = 0; i < words.size(); i++) {
		pair <string, int> temp(words[i], sTree.getValue(words[i]));
		conc.push_back(temp);
	}
	sortStringByValue(conc);

	cout << "insert how many words to output: " << endl;
	int n;
	cin >> n;
	for (int i = 0; i < n; i++) {
		cout << conc[i].first << endl;
	}

	
	system("pause");
	return 0;
}