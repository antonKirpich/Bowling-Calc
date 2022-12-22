#include <iostream>
#include <vector>
using namespace std;

class Frame
{
public:
    Frame(int firstShot, int secondShot)        //конструктор
    {
        this->firstShot  = firstShot;
        this->secondShot = secondShot;
    }
    bool isStrike()
    {
        return ( firstShot == 10);  //Страйк, если первым ударом выбито 10 кеглей
    }
    bool isSpare()
    {
        return ((firstShot+secondShot == 10) & !isStrike());
        //Спаре, если выбито 10 кеглей и первый удар не страйк
    }
    int getFirstShot()          //кегли в первом броске
    {
        return firstShot;
    }
    int getSecondShot()         //кегли во втором броске
    {
        return secondShot;
    }
    ~Frame()
    { }

    int frameScore;

private:
    int firstShot;
    int secondShot;
};

int main() {
    cout << "Bowling calc" << endl;

    vector<Frame> game;     //массив-вектор объектов класса Frame
    game.reserve(10);

    for (int frame = 0; frame < 10; frame++)    //перебираем 10 фреймов
    {
        //Ввод кол-ва сбитых кеглей-----------------------------------------------------------------------
        int firstShot, secondShot = 0;
        cout << endl << "Make your " << frame + 1 << " throw..." << endl;
        do {
             cout << " Enter first shot result(0...10): ";
             cin >> firstShot;
        } while ((firstShot < 0) || (firstShot > 10));

        if (firstShot < 10)     //если первый удар не страйк, то вводим сбитые кегли на 2м броске
        {
            do {
                cout << "Enter second shot result(0..." << (10 - firstShot) << "): ";
                cin >> secondShot;
            } while ((secondShot < 0) || (secondShot > (10 - firstShot)));
        }

        Frame *shot = new Frame(firstShot, secondShot);  //Новый объект класса бросок
        game.push_back(*shot);                           //добавляем в конец массива-вектора

        //подсчет frameScore-------------------------------------------------------------------------------
        for (int i = 0; i <= frame; i++)
        {
            if (game[i].isStrike())         //если это страйк, то след два броска с бонусом (если они есть)
            {
                if (i != frame)             //если это не последний бросок
                {
                    if (game[i + 1].isStrike())    //если след удар опять Strike
                    {
                        game[i].frameScore = game[i].getFirstShot() + game[i].getSecondShot();
                        game[i].frameScore += 10;   //бонус за следующий страйк

                        if ((frame - i) >=2 )       //если существует еще бросок (+2)
                        {
                            game[i].frameScore += game[i+2].getFirstShot();  //добавляем бонус через один бросок
                        }
                    }
                    else            //если след раунд регулар или спар
                    {
                        game[i].frameScore  = game[i].getFirstShot() + game[i].getSecondShot();      //добавляем бонус очки со след 2х бросков
                        game[i].frameScore += game[i+1].getFirstShot() + game[i+1].getSecondShot();
                    }
                }
                else        //если это крайний бросок
                {
                    game[i].frameScore = game[i].getFirstShot() + game[i].getSecondShot();
                }
            }

            if (game[i].isSpare())      //если это спар, то начисляем бонусы на след бросок (если он уже сделан)
            {
                if (i != frame)
                {
                    game[i].frameScore = game[i].getFirstShot() + game[i].getSecondShot();
                    game[i].frameScore += game[i+1].getFirstShot();
                }
                else
                {
                    game[i].frameScore = game[i].getFirstShot() + game[i].getSecondShot();
                }
            }

            if ((!game[i].isStrike()) && (!game[i].isSpare()))  //если это обычный бросок
            {
                game[i].frameScore = game[i].getFirstShot() + game[i].getSecondShot();
            }
        }

        //Вывод результатов на экран---------------------------------------------------------------------------
        cout << endl;
        cout << " Frame       "; for (int j=1; j<=frame+1; j++) { cout << "|" << j << "     "; } cout << endl;

        cout << " Result      ";
        for(auto it = game.begin(); it != game.end(); ++it)
        {
            cout << "|";
            if (it->isStrike()) { cout << "X     "; }
            else if (it->isSpare())  { cout << it->getFirstShot() << " S   "; }
            else {cout << it->getFirstShot() << " " << it->getSecondShot() << "   ";}
        }
        cout << endl;

        cout << " Frame Score ";
        for(auto it = game.begin(); it != game.end(); ++it)
        {
            cout << "|" << it->frameScore;
            if (it->frameScore >= 10) cout << "    ";
            if (it->frameScore <  10) cout << "     ";        //выравнивание для табличного вывода
        }
        cout << endl;

        int totalScore = game[0].frameScore;
        cout << " Total       |" << totalScore;
        if (totalScore < 10)   cout << "     ";
           else cout << "    ";
        for(auto it = game.begin() + 1; it != game.end(); ++it)
        {
            totalScore += it->frameScore;
            cout << "|" << totalScore;
            if (totalScore < 10)   {cout << "     "; continue;}     //Выравниваение для табличного вывода
            if (totalScore < 100)  {cout << "    ";  continue;}
            if (totalScore < 1000) {cout << "   ";   continue;}
        }

    }

    //удаляем все эл-ты вектора-массива
    //деструктор для каждого объекта вызовется автоматически
    game.clear();
    return 0;
}
