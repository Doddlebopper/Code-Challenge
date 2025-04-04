#include <iostream>
#include <string>
#include <limits>
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>
#undef max
using json = nlohmann::json;

using namespace std;

const int MAXWRONG = 7;

string getWord() {
	auto response = cpr::Get(cpr::Url{"https://random-word-api.vercel.app/api?words=1&length=6"});

	if (response.status_code == 200) {
		json result = json::parse(response.text);
		return result[0];
	}
	else {
		return "Error";
	}
}

int gameStart(string name, int joke_counter) {
	string user_word = getWord();
	if (user_word == "error") {
		cout << "Couldn't get the word. Try again!" << endl;
		return 0;
	}

	transform(user_word.begin(), user_word.end(), user_word.begin(), ::tolower);

	string display(user_word.size(), '_');
	string user_guess;
	int wrong_guesses = 0;

	while (display != user_word && wrong_guesses < MAXWRONG) {
		cout << "Word: ";
		for (char c : display) cout << c << ' ';
		cout << "\nGuessed: { " << user_guess << " }\nWrong guesses: " << wrong_guesses << "/" << MAXWRONG << endl;

		cout << name << "'s letter: ";
		char guess;
		cin >> guess;
		guess = tolower(guess);

		if (user_guess.find(guess) != string::npos) {
			cout << "Letter already guessed.\n";
			continue;
		}

		user_guess += guess;

		bool correct = false;
		for (int i = 0; i < user_word.size(); ++i) {
			if (user_word[i] == guess) {
				display[i] = guess;
				correct = true;
			}
		}

		if (!correct) {
			wrong_guesses++;
			cout << "Incorrect guess!\n";
		}
	}

	if (display == user_word) {
		if (wrong_guesses == 0 && joke_counter == 1) {
			string user_joke_answer;
			cout << "You guessed the word without getting one wrong? You Deserve a joke!" << endl;
			cout << "What does the R in Recursion stand for?: ";
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			getline(cin, user_joke_answer);
			if (user_joke_answer == "Recursion" || user_joke_answer == "recursion") {
				cout << "\nHow did you do that? Im honestly impressed." << endl;
				cout << "True Ending (2/2)" << endl;
				return 1;
			}
			else {
				cout << "\nThe answer is: Recursion" << endl;
				return 0;
			}

		}
		else {
			cout << "Congrats, " << name << "! You guessed the word: " << user_word << endl;
			cout << "Bad Ending (1/2)" << endl;
			return 0;
		}
	}
	else {
		cout << "Sorry, you're out of guesses. The word was: " << user_word << endl;
		return 0;
	}
}

void startMenu(string name) {
	string user_input;
	int joke_counter = 0;
	cout << "Please select which option you would like to choose!" << endl;

	while (true) {
		string user_options = "1.) Start Game\n2.) Quit\n";
		cout << "What would you like to do?" << endl;
		cout << user_options;
		cout << name << "'s game: ";
		getline(cin, user_input);
		if (user_input == "start game" || user_input == "Start game" || user_input == "Start Game" || user_input == "start" || user_input == "Start" || user_input == "1") {
			int return_value = gameStart(name, joke_counter);
			if (return_value == 0) {
				continue;
			}
			else {
				cout << "Thank you for playing my game!" << endl;
				break;
			}
		}
		else if (user_input == "quit" || user_input == "Quit" || user_input == "2") {
			cout << "Thank you for playing my game!" << endl;
			break;
		}
		else if (user_input == "tell me a joke" || user_input == "Tell me a joke") {
			joke_counter = 1;
			cout << "You wanna hear joke? Ok I'll tell you a joke..." << endl;
			cout << "I would tell you a UDP joke, but you might not get it." << endl;
		}
		else {
			cout << "Input not understood. Please try again." << endl;
		}
	}
}

int main() {
	string user_name;
	cout << "Welcome to my Word Guessing Game!" << endl;
	cout << "What is your name?: ";
	cin >> user_name;

	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	startMenu(user_name);
}
