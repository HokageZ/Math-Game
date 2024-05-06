#include <iostream>
using namespace std;

struct stGameInfo {
	string PassOrNot;
	int GameRounds;
	int Difficulty;
	int OperationType;
	int CorrectAnswers = 0;
	int WrongAnswers = 0;
};

enum enDifficulty {
	Easy = 1,
	Mid = 2,
	Hard = 3,
	Mix_Diff = 4
};

enum enOperationType {
	Addition = 1,
	Subtraction = 2,
	Multiplication = 3,
	Division = 4,
	Mix_OpT = 5
};

int ReadInt(string Message = "")
{
	int Num = 0;
	do {
		cout << Message;
		cin >> Num;
		if (cin.fail()) {
			cout << "Invalid input. Please enter a Number: ";
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
		else
			break;
	} while (!cin.fail());
	return Num;
}

int ReadPositiveOnly(string Message = "") {
	int Num = 0;
	do
	{
		cout << Message;
		Num = ReadInt();
	} while (Num <= 0);
	return Num;
}

int ReadIntWithin(int from, int to, string Message = "") {
	int Num = 0;
	do
	{
		cout << Message;
		Num = ReadInt();
	} while (Num < from || Num > to);
	return Num;
}

int Random(int from, int to) {
	return(rand() % (to - from + 1) + from);
}

string Tabs(int NumOfTabs) {
	string Tab = "";
	for (int i = 0; i < NumOfTabs; i++)
		Tab += "\t";
	return Tab;
}

void GameInfo_Reader(stGameInfo& GameInfo) {
	GameInfo.GameRounds = ReadPositiveOnly("How Many Rounds Do U Want 2 Play ? ");
	GameInfo.Difficulty = ReadIntWithin(1, 4, "Pls Choose The Difficulty ([1] Easy ,[2] Mid ,[3] Hard ,[4] Mix) : ");
	GameInfo.OperationType = ReadIntWithin(1, 5, "Pls Choose The Quiz Type ([1] Add ,[2] Sub ,[3] Multiply ,[4] Division ,[5] Mix) : ");
}

int QuestionGenerator_RT_Answer(stGameInfo GameInfo) {
	if (GameInfo.Difficulty == Mix_Diff)
		GameInfo.Difficulty = Random(Easy, Hard);
	if (GameInfo.OperationType == Mix_OpT)
		GameInfo.OperationType = Random(Addition, Division);

	int CorrectSolution = 0;
	int x, y;

	if (GameInfo.Difficulty == Easy) {
		x = Random(1, 10);
		y = Random(1, 10);
	}
	else if (GameInfo.Difficulty == Mid) {
		x = Random(10, 100);
		y = Random(10, 100);
	}
	else if (GameInfo.Difficulty == Hard) {
		x = Random(100, 1000);
		y = Random(100, 1000);
	}

	if (GameInfo.OperationType == Addition) {
		printf("\n%d + %d = ", x, y);
		CorrectSolution = x + y;
	}
	else if (GameInfo.OperationType == Subtraction) {
		printf("\n%d - %d = ", x, y);
		CorrectSolution = x - y;
	}
	else if (GameInfo.OperationType == Multiplication) {
		printf("\n%d X %d = ", x, y);
		CorrectSolution = x * y;
	}
	else if (GameInfo.OperationType == Division) {
		printf("\n%d / %d = ", x, y);
		CorrectSolution = x / y;
	}
	return CorrectSolution;
}

bool Answers_Reader_Validator(int CorrectAnswer) {
	int UserAnswer = ReadInt();
	if (UserAnswer == CorrectAnswer)
		return true;
	else
		return false;
}

void RoundOverScreen(stGameInfo& GameInfo, bool IsItCorrect, int CorrectAnswer) {
	if (IsItCorrect) {

		GameInfo.CorrectAnswers++;
		cout << "\nCorrect Answer (-:\n";
	}
	else {

		GameInfo.WrongAnswers++;
		cout << "\nWrong Answer )-: The Right Answer is " << CorrectAnswer << endl;
	}
}

void Print_Instructions() {
	cout << "\n\n" << "If there any fractions they are floored to Zero\n";
	cout << "Minus is also possible\n\n";
}

stGameInfo PlayGame() {
	stGameInfo GameInfo;
	GameInfo_Reader(GameInfo);
	Print_Instructions();
	for (int i = 0; i < GameInfo.GameRounds; i++) {
		int CorrectAnswer = QuestionGenerator_RT_Answer(GameInfo);
		bool IsItCorrect = Answers_Reader_Validator(CorrectAnswer);
		RoundOverScreen(GameInfo, IsItCorrect, CorrectAnswer);
	}
	return GameInfo;
}

void ShowGameOver() {
	cout << endl << "--------------------------------------------";
	cout << endl << "----------------[GAME OVER]-----------------";
	cout << endl << "--------------------------------------------\n";
}

void ShowFinalGameStats(stGameInfo GameInfo) {
	if (GameInfo.CorrectAnswers > GameInfo.WrongAnswers) {
		GameInfo.PassOrNot = "    PASS   ";

	}
	else {
		GameInfo.PassOrNot = " DIDN'T PASS";

	}
	string GameDifficulty;
	switch (GameInfo.Difficulty)
	{
	case Easy:
		GameDifficulty = "Easy";
		break;
	case Mid:
		GameDifficulty = "Medium";
		break;
	case Hard:
		GameDifficulty = "Hard";
		break;
	case Mix_Diff:
		GameDifficulty = "Mixed";
		break;
	}
	cout << endl << "---------------[" << GameInfo.PassOrNot << "]--------------";
	cout << endl << "Number of rounds : " << GameInfo.GameRounds;
	cout << endl << "Game Difficulty : " << GameDifficulty;
	cout << endl << "Number of correct answers : " << GameInfo.CorrectAnswers;
	cout << endl << "Number of wrong answers: " << GameInfo.WrongAnswers;
}

void AdditionalRound(stGameInfo& GameInfo) {
	cout << "\nSince it's a draw One more round was added";
	if (GameInfo.CorrectAnswers == GameInfo.WrongAnswers) {
		int CorrectAnswer = QuestionGenerator_RT_Answer(GameInfo);
		bool IsItTrue = Answers_Reader_Validator(CorrectAnswer);
		RoundOverScreen(GameInfo, IsItTrue, CorrectAnswer);
		GameInfo.GameRounds++;
	}
}

void START_GAME() {
	string AgainOrNot = "Y";
	do
	{
		stGameInfo GameInfo = PlayGame();
		if (GameInfo.CorrectAnswers == GameInfo.WrongAnswers)
			AdditionalRound(GameInfo);
		ShowGameOver();
		ShowFinalGameStats(GameInfo);
		cout << "\nDo U Want To Play Again ? (Y/N)";
		cin >> AgainOrNot;
	} while (AgainOrNot == "y" || AgainOrNot == "Y");
}

int main()
{
	srand((unsigned)time(NULL));
	START_GAME();
}