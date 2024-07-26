using namespace std;

#include <iostream>

enum enQuestionsLevel { EasyLevel = 1, MedLevel = 2, HardLevel = 3, Mix = 4 };

enum enOperationType { Add = 1, Sub = 2, Mult = 3, Div = 4, MixOp = 5 };

int RandomNumber(int From, int To) {

    //Function to generate a random number

    int randNum = rand() % (To - From + 1) + From;

    return randNum;
}

string GetQuestionLevelText(enQuestionsLevel Level)
{
    string QuestionsLevel[4] = { "Easy", "Med" , "Hard", "Mix" };
    return QuestionsLevel[Level - 1];
}

void SetScreenColor(bool Right)
{
    if (Right)
        system("color 2F"); //turn screen to Green
    else {
        system("color 4F"); //turn screen to Red
        cout << "\a";
    }
}

short ReadHowManyQuestions()
{
    short NumberOfQuestions;

    do
    {
        cout << "How Many Questions do you want to answer? ";
        cin >> NumberOfQuestions;

    } while (NumberOfQuestions < 1 || NumberOfQuestions >10);
    

    return NumberOfQuestions;
}

enQuestionsLevel ReadQuestionsLevel()
{
    short QuestionLevel = 0;

    do
    {
        cout << "Enter Question Level [1] Easy, [2] Med, [3] Hard, [4] Mix ? ";
        cin >> QuestionLevel;

    } while (QuestionLevel < 1 || QuestionLevel>4);
    
    return (enQuestionsLevel) QuestionLevel;
}

enOperationType ReadOperationType()
{
    short OpType;

    do
    {
        cout << "Enter Operation Type [1] Add, [2] Sub, [3] Mul, [4] Div, [5] Mix ? ";
        cin >> OpType;

    } while (OpType < 1 || OpType > 5);
    
    return (enOperationType) OpType;
}

string GetOpTypeSymbol(enOperationType OpType)
{
    switch (OpType) { 
     case enOperationType::Add:
        return"+";
     case enOperationType::Sub:
        return"-";
     case enOperationType::Mult:
        return"x";
    case enOperationType::Div:
        return"/";
    default:
        return"Mix";
    }
}

struct stQuestion
{
    int Number1 = 0;
    int Number2 = 0;
    enOperationType OperationType;
    enQuestionsLevel QuestionLevel;
    int CorrectAnswer = 0;
    int PlayerAnswer = 0;
    bool AnswerResult = false;

};

struct stQuizz
{
    stQuestion QuestionList[100];
    short NumberOfQuestions;
    enQuestionsLevel QuestionLevel;
    enOperationType Optype;
    short NumberOfRightAnswers = 0;
    short NumberOfWrongAnswers = 0;
    bool isPass = false;
};

int SimpleCalculator(int Number1, int Number2, enOperationType OpType)
{
    switch (OpType)
    {
    case Add:
        return Number1 + Number2;
    case Sub:
        return Number1 - Number2;
    case Mult:
        return Number1 * Number2;
    case Div:
        return Number1 / Number2;
    default:
        return Number1 + Number2;
    }
}

enOperationType GetRandomOperationType()
{
    int Op = RandomNumber(1, 4);
    return (enOperationType) Op;
}

stQuestion GenerateQuestion(enQuestionsLevel QuestionLevel, enOperationType OpType)
{
    stQuestion Question;

    if (QuestionLevel == enQuestionsLevel::Mix)
    {
        QuestionLevel = (enQuestionsLevel) RandomNumber(1,3);
    }
    if (OpType == enOperationType::MixOp)
    {
        OpType = GetRandomOperationType();
    }

    Question.OperationType = OpType;

    switch (QuestionLevel)
    {
    case EasyLevel:
        Question.Number1 = RandomNumber(1, 10);
        Question.Number2 = RandomNumber(1, 10);

        Question.CorrectAnswer = SimpleCalculator(Question.Number1,Question.Number2,Question.OperationType);
        Question.QuestionLevel = QuestionLevel;
        return Question;
    case MedLevel:
        Question.Number1 = RandomNumber(10, 50);
        Question.Number2 = RandomNumber(10, 50);

        Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, Question.OperationType);
        Question.QuestionLevel = QuestionLevel;
        return Question;
    case HardLevel:
        Question.Number1 = RandomNumber(50, 100);
        Question.Number2 = RandomNumber(50, 100);

        Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, Question.OperationType);
        Question.QuestionLevel = QuestionLevel;
        return Question;
    }

    return Question;
}

void GenerateQuizzQuestions(stQuizz& Quizz)
{
    for (short Question = 0; Question < Quizz.NumberOfQuestions; Question++)
    {
        Quizz.QuestionList[Question] = GenerateQuestion(Quizz.QuestionLevel,Quizz.Optype);
    }
}

int ReadQuestionAnswer()
{
    int Answer = 0;
    cin >> Answer;

    return Answer;
}

void PrintTheQuestion(stQuizz Quizz, short QuestionNumber)
{
    cout << "\n";
    cout << "Question [" << QuestionNumber + 1 << "/" << Quizz.NumberOfQuestions << "] \n\n";
    cout << Quizz.QuestionList[QuestionNumber].Number1 << endl;
    cout << Quizz.QuestionList[QuestionNumber].Number2 << " ";
    cout << GetOpTypeSymbol(Quizz.QuestionList[QuestionNumber].OperationType);
    cout << "\n____________" << endl;

}

void CorrectTheQuestionAnswer(stQuizz& Quizz, short QuestionNumber)
{
    if (Quizz.QuestionList[QuestionNumber].PlayerAnswer != Quizz.QuestionList[QuestionNumber].CorrectAnswer)
    {
        Quizz.QuestionList[QuestionNumber].AnswerResult = false;
        Quizz.NumberOfWrongAnswers++;

        cout << "Wrong Answer :-(\n";
        cout << "The Right Answer is: ";
        cout << Quizz.QuestionList[QuestionNumber].CorrectAnswer;
        cout << "\n";
    }
    else
    {
        Quizz.QuestionList[QuestionNumber].AnswerResult = true;
        Quizz.NumberOfRightAnswers++;

        cout << "Right Answer :-) \n";
    }

    cout << endl;

    SetScreenColor(Quizz.QuestionList[QuestionNumber].AnswerResult);
}

void AskAndCorrectQuestionListAnswers(stQuizz& Quizz)
{
    for (short QuestionNumber = 0; QuestionNumber < Quizz.NumberOfQuestions; QuestionNumber++)
    {
        PrintTheQuestion(Quizz, QuestionNumber);

        Quizz.QuestionList[QuestionNumber].PlayerAnswer = ReadQuestionAnswer();

        CorrectTheQuestionAnswer(Quizz, QuestionNumber);
    }

    Quizz.isPass = (Quizz.NumberOfRightAnswers >= Quizz.NumberOfWrongAnswers);

    /*if (Quizz.NumberOfRightAnswers >= Quizz.NumberOfWrongAnswers)
        Quizz.isPass = true;
    else
        Quizz.isPass = false;*/
}

string GetFinalResulText(bool Pass)
{
    if (Pass)
        return "PASS :-)";
    else
        return "FAIL :-(";
}

void PrintQuizzResults(stQuizz Quizz)
{
    cout << "\n______________________________\n\n";
    cout << "  Final Results is " << GetFinalResulText(Quizz.isPass) << endl;
    cout << "\n______________________________\n\n";

    cout << "Number Of Questions : " << Quizz.NumberOfQuestions << endl;
    cout << "Questions Level     : " << GetQuestionLevelText(Quizz.QuestionLevel) << endl;
    cout << "Operation Type      : " << GetOpTypeSymbol(Quizz.Optype) << endl;
    cout << "Number Of Right Answer: " << Quizz.NumberOfRightAnswers << endl;
    cout << "Number Of Wrong Answer: " << Quizz.NumberOfWrongAnswers << endl;
    cout << "________________________________\n\n";

    SetScreenColor(Quizz.isPass);
}

void PlayMathGame()
{
    stQuizz Quizz;
    Quizz.NumberOfQuestions = ReadHowManyQuestions();
    Quizz.QuestionLevel = ReadQuestionsLevel();
    Quizz.Optype = ReadOperationType();

    GenerateQuizzQuestions(Quizz);

    AskAndCorrectQuestionListAnswers(Quizz);

    PrintQuizzResults(Quizz);
}

void ResetScreen()
{
    system("cls");
    system("color 07");
}

void StartTheGame()
{
    char PlayAgain = 'Y';

    do
    {
        ResetScreen();
        PlayMathGame();

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