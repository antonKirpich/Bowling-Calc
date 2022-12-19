#include <iostream>
#include <vector>
using namespace std;

class shot {
public:
    bool isStrike()
    {
        return ( firstShot == 10);  //Страйк, если первым ударом выбито 10 кеглей
    }
    bool isSpare()
    {
        return ((firstShot+secondShot == 10) & !isStrike());
        //Спаре, если выбито 10 кеглей и первый удар не страйк
    }
    bool isFinalizeFrame()    //открытый счет в раунде(т.е. можно точно вычислить) или нет
    {
        if ((firstShot+secondShot ) != 10) return true; else return false;
    }
    int getframeScore()       //возвращает очки фрейма
    {
        return frameScore;
    }
    void addFrameScore (int points)
    {
        frameScore += points;
    }
    int getTotalScoreAfterFrame()
    {
        return totalScoreAfterFrame;
    }
    int getFirstShot()          //кегли в первом броске
    {
        return firstShot;
    };
    int getSecondShot()         //кегли во втором броске
    {
        return secondShot;
    };
    shot(int firstShot, int secondShot, int frame)  //конструктор
    {
       this->firstShot  = firstShot;
       this->secondShot = secondShot;
       this->frameScore = firstShot + secondShot;
       this->totalScoreAfterFrame = firstShot + secondShot;
       if ((firstShot + secondShot) == 10)  notFinalizedFrame = true; //если страйк или спеар, то фрейм не финализирован
        else notFinalizedFrame = false;
    }
    shot()
    {
        firstShot = secondShot = totalScoreAfterFrame = frameScore = 0;
    }
    int totalScoreAfterFrame;   //очки общие
    int frameScore;             //очки во фрейме
    bool notFinalizedFrame;     //открытый фрейм или можно вычислить очки
private:
    int firstShot;
    int secondShot;
};

int main()
{
    cout << "Bowling calc" << endl;

    vector<shot> gameScore;     //массив-вектор объектов класса shot
    vector<shot>::iterator it;  //итератор

    for (int frame = 0; frame < 10; frame++)    //перебираем 10 фреймов
    {
        //Ввод кол-ва сбитых кеглей-----------------------------------------------------------------------
        int firstShot, secondShot = 0;
        do
        {
            cout << endl << "Make your " << frame + 1 << " throw..." << endl << " Enter first shot result(0...10): ";
            cin >> firstShot;
        }
        while ( (firstShot<0) || (firstShot>10) );

        if (firstShot < 10)     //если первый удар не страйк, то вводим сбитые кегли на 2м броске
        {
            do
            {
               cout << "Enter second shot result(0..." << (10-firstShot) << "): ";
               cin >> secondShot;
            }
            while ( (secondShot<0) || ( secondShot > (10-firstShot ) ));
        }

        shot *frameShot = new shot(firstShot, secondShot, frame+1);  //Новый объект класса бросок
        gameScore.push_back(*frameShot);                                   //добавляем в конец массива-вектора

        auto it = gameScore.end();      //итератор для перебора
        it--; //устанавливаем на последний фрейм

        if (frame != 0) //если это не первый раунд
        {
            it--;   //переход на предпоследний фрейм
            //можно добавлять только тогда, когда it указывает на финализир фрейм

            int prevTotalScore = it->totalScoreAfterFrame;
            it++; //переходим на последний фрейм
            it->totalScoreAfterFrame = it->frameScore + prevTotalScore; //добавляем очки с предыдущего раунда
            it--;

            for (auto iter = it; iter->notFinalizedFrame; --iter) //перебираем от конца к началу, пока есть флаг НЕфинализир
            {
                if (iter->isSpare()) //если предыдущий бросок - спар
                {
                    iter++;
                    int extraScore = iter->getFirstShot();
                    iter--;
                    iter->addFrameScore(extraScore);     //добавляем бонус очки за один след бросок
                    iter->notFinalizedFrame = false;           //фрейм финализируется
                    iter->totalScoreAfterFrame += extraScore;  //общие очки Total
                }

                if (iter->isStrike())   //если предыдущий бросок - страйк
                {
                    iter++;
                    int extraScore = (iter->getFirstShot()) + (iter->getSecondShot());
                    bool flag = !iter->isStrike();  //флаг разрешения фин, случай когда подряд несколько страйков
                    iter--;
                    iter->addFrameScore(extraScore);     //добавляем бонус очки за два след броска
                    if (flag) {
                        iter->notFinalizedFrame = false;  //фрейм финализируется
                        iter->totalScoreAfterFrame += extraScore;  //общие очки Total
                    }
                }

                int prevTotalScore = it->totalScoreAfterFrame;
                it++; //переходим на последний эл
                it->totalScoreAfterFrame = it->frameScore + prevTotalScore;
            }
        }

        //Вывод результатов на экран---------------------------------------------------------------------------
        cout << endl;
        cout << " Frame       "; for (int j=1; j<=frame+1; j++) { cout << "|" << j << "     "; } cout << endl;

        cout << " Result      ";
        for(it = gameScore.begin(); it != gameScore.end(); ++it)
        {
            cout << "|";
            if (it->isStrike()) { cout << "X     "; }
             else if (it->isSpare())  { cout << it->getFirstShot() << " S   "; }
               else {cout << it->getFirstShot() << " " << it->getSecondShot() << "   ";}
        }
        cout << endl;

        cout << " Frame Score ";
        for(it = gameScore.begin(); it != gameScore.end(); ++it)
        {
            cout << "|" << it->getframeScore();
            if (it->getframeScore() >= 10) cout << "    ";
            if (it->getframeScore() <  10) cout << "     ";        //выравнивание для табличного вывода
        }
        cout << endl;

        cout << " Total       ";
        for(auto iter = gameScore.begin(); iter != gameScore.end(); ++iter)
        {
            cout << "|" << iter->totalScoreAfterFrame;
            if (iter->totalScoreAfterFrame < 10)   {cout << "     "; continue;}     //Выравниваение для табличного вывода
            if (iter->totalScoreAfterFrame < 100)  {cout << "    ";  continue;}
            if (iter->totalScoreAfterFrame < 1000) {cout << "   ";   continue;}
        }
    }

    return 0;
}
