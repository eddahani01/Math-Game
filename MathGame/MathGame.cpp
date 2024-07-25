using namespace std;

#include <iostream>

enum enQuestionsLevel{ Easy = 1, Med = 2, Hard = 3, Mix = 4 };

enum enOperationsType{ Add = 1, Sub = 2, Mul = 3, Div = 4, MixOps = 5 };

enum enAnswer{ Correct = 1, Incorrect = 2 };

string ShowOpType(enOperationsType OpType)
{
    string OperationTypes[5] = { "Add", "Sub" , "Mul", "Div", "Mix" };
    return OperationTypes[OpType - 1];
}

string ShowQuestLevel(enQuestionsLevel Level)
{
    string QuestionsLevel[4] = { "Easy", "Med" , "Hard", "Mix" };
    return QuestionsLevel[Level - 1];
}

int RandomNumber(int From, int To) {

    //Function to generate a random number

    int randNum = rand() % (To - From + 1) + From;

    return randNum;
}

struct stGameResults
{
    short NumberOfQuestions = 0;
    enQuestionsLevel QuestionsLevel;
    enOperationsType OperationType;
    short NumberOfRightAnswers = 0;
    short NumberOfWrongAnswers = 0;
};

struct stQuestionInfo
{
    short QuestionNumber = 0;
    enQuestionsLevel Level;
    short FirstNumber = 0;
    short SecondNumber = 0;
    enOperationsType OpType;
    short PlayerAnswer = 0;
    enAnswer IsAnswerCorrect;
    short CorrectAnswer = 0;

};

stQuestionInfo FillQuestionInfoWithNumbers(stQuestionInfo& QuestionInfo)
{
    switch (QuestionInfo.Level)
    {
    case Easy:
        QuestionInfo.FirstNumber = RandomNumber(1, 10);
        QuestionInfo.SecondNumber = RandomNumber(1, 10);
        break;
    case Med:
        QuestionInfo.FirstNumber = RandomNumber(10, 99);
        QuestionInfo.SecondNumber = RandomNumber(10, 99);
        break;
    case Hard:
        QuestionInfo.FirstNumber = RandomNumber(100, 1000);
        QuestionInfo.SecondNumber = RandomNumber(100, 1000);
        break;
    case Mix:
        QuestionInfo.FirstNumber = RandomNumber(1, 1000);
        QuestionInfo.SecondNumber = RandomNumber(1, 1000);
        break;
    default:
        break;
    }

    return QuestionInfo;
}

short ReadPlayerAnswer()
{
    short PlayerAnswer = 0;

    cin >> PlayerAnswer;

    return PlayerAnswer;
}

short HowManyQuestions()
{
    short NumQuest = 1;

    cout << "How Many Questions do you want to answer? ";
    cin >> NumQuest;

    return NumQuest;
}

short QuestionsLevel()
{
    short QuestLevel = 1;

    cout << "Enter Question Level [1] Easy, [2] Med, [3] Hard, [4] Mix ? ";
    cin >> QuestLevel;

    return QuestLevel;
}

short OperationType()
{
    short OpType = 1;

    cout << "Enter Operation Type [1] Add, [2] Sub, [3] Mul, [4] Div, [5] Mix ? ";
    cin >> OpType;

    return OpType;
}

string PrintOpType(enOperationsType OpType)
{
    switch (OpType)
    {
    case Add:
        return "+";
        break;
    case Sub:
        return "-";
        break;
    case Mul:
        return "*";
        break;
    case Div:
       return "/";
        break;
    
    default:
        break;
    }
}

void PrintQuestionInfo(stQuestionInfo QuestionInfo)
{
    cout << QuestionInfo.FirstNumber << endl;
    cout << QuestionInfo.SecondNumber << "  "<< PrintOpType(QuestionInfo.OpType) << endl;
    cout << "______________\n";

}

short GetCorrectAnswer(stQuestionInfo QuestionInfo)
{
    short FirstNumber = QuestionInfo.FirstNumber;
    short SecondNumber = QuestionInfo.SecondNumber;
    enOperationsType OpType = QuestionInfo.OpType;

    switch (OpType)
    {
    case Add:
        return FirstNumber + SecondNumber;
        break;
    case Sub:
        return FirstNumber - SecondNumber;
        break;
    case Mul:
        return FirstNumber * SecondNumber;
        break;
    case Div:
        return FirstNumber / SecondNumber;
        break;
    default:
        break;
    }

    return -1;
}

enAnswer CheckAnswer(stQuestionInfo QuestionInfo)
{
    if (QuestionInfo.PlayerAnswer == QuestionInfo.CorrectAnswer)
        return enAnswer::Correct;
    else
        return enAnswer::Incorrect;
}

void SetWinnerScreenColor(enAnswer Answer)
{
    switch (Answer)
    {
    case Correct:
        system("color 27"); //turn screen to Green
        break;
    case Incorrect:
        system("color 47"); //turn screen to Red
        cout << "\a";
        break;
    default:
        break;
    }

}

void PrintResult(stQuestionInfo QuestionInfo)
{
    if (QuestionInfo.IsAnswerCorrect == enAnswer::Incorrect)
    {
        cout << "\nWrong Answer :-(\n";
        cout << "The Right Answer is: " << QuestionInfo.CorrectAnswer << "\n\n";
    }
    else
        cout << "\nRight Answer :-)\n\n";

    SetWinnerScreenColor(QuestionInfo.IsAnswerCorrect);
}

stGameResults FillGameResult(short HowManyQuestions, enQuestionsLevel Level, enOperationsType OpType, short NumberOfRightAnswer, short NumberOfWrongAnswer)
{
    stGameResults GameResults;
    GameResults.NumberOfQuestions = HowManyQuestions;
    GameResults.OperationType = OpType;
    GameResults.QuestionsLevel = Level;
    GameResults.NumberOfRightAnswers = NumberOfRightAnswer;
    GameResults.NumberOfWrongAnswers = NumberOfWrongAnswer;

    return GameResults;
}

stGameResults PlayGame(short HowManyQuestions, short QuestionLevel, short OperationType)
{
    stQuestionInfo QuestionInfo;
    QuestionInfo.Level = (enQuestionsLevel)QuestionLevel;
    QuestionInfo.OpType = (enOperationsType)OperationType;

    short CountRightAnswer = 0, CountWrongAnswer = 0;

    for (short QuestionNumber = 1; QuestionNumber <= HowManyQuestions; QuestionNumber++)
    {
       
        cout << "\nQuestion [" << QuestionNumber << "/" << HowManyQuestions << "] \n\n";
        QuestionInfo.QuestionNumber = QuestionNumber;

        QuestionInfo = FillQuestionInfoWithNumbers(QuestionInfo);

        if (QuestionInfo.OpType == enOperationsType::MixOps)
        {
            QuestionInfo.OpType = (enOperationsType)RandomNumber(1,4);
        }
        PrintQuestionInfo(QuestionInfo);

        QuestionInfo.PlayerAnswer = ReadPlayerAnswer();
        QuestionInfo.CorrectAnswer = GetCorrectAnswer(QuestionInfo);
        QuestionInfo.IsAnswerCorrect = CheckAnswer(QuestionInfo);


        if (QuestionInfo.IsAnswerCorrect == enAnswer::Correct)
            CountRightAnswer++;
        else
            CountWrongAnswer++;

        PrintResult(QuestionInfo);
        QuestionInfo.OpType = (enOperationsType)OperationType;

    }

    return FillGameResult(HowManyQuestions,QuestionInfo.Level,QuestionInfo.OpType,CountRightAnswer,CountWrongAnswer);
}

void ShowFinalGameResult(stGameResults GameResults)
{
    string R = "";
    if (GameResults.NumberOfRightAnswers > GameResults.NumberOfWrongAnswers)
    {
        R = R + "PASS :-)";
        SetWinnerScreenColor(enAnswer::Correct);
    }
    else 
    {
        R = R + "FAIL :-(";
        SetWinnerScreenColor(enAnswer::Incorrect);
    }
        

    cout << "________________________________________\n\n";
    cout << "  Final Results is " << R << endl;
    cout << "\n______________________________________\n\n";

    cout << "Number Of Questions : " << GameResults.NumberOfQuestions << endl;
    cout << "Questions Level     : " << ShowQuestLevel(GameResults.QuestionsLevel) << endl;
    cout << "Operation Type      : " << ShowOpType(GameResults.OperationType) << endl;
    cout << "Number Of Right Answer: " << GameResults.NumberOfRightAnswers << endl;
    cout << "Number Of Wrong Answer: " << GameResults.NumberOfWrongAnswers << endl;
    cout << "_________________________________________\n\n";


}

void ResetScreen()
{
    system("cls");
    system("color 07");
}

void StartTheGame()
{
    char PlayAgain = 'Y';

    short NumQuestions = 0, QuestLevel = 0, OpType = 0;
   
    do
    {
        ResetScreen();
        NumQuestions = HowManyQuestions();
        QuestLevel = QuestionsLevel();
        OpType = OperationType();

        stGameResults GameResult = PlayGame(NumQuestions, QuestLevel, OpType);
        ShowFinalGameResult(GameResult);

        cout << endl << "Do you want to play again? Y/N? ";
        cin >> PlayAgain;
    } while (PlayAgain == 'Y' || PlayAgain == 'y');
}

int main()
{
    //Seeds the random number generator in C++, called only once
    srand((unsigned)time(NULL));

    StartTheGame();
}