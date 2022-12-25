#include "Frame.h"

    Frame::Frame(int firstShot, int secondShot)        //конструктор
    {
        this->firstShot  = firstShot;
        this->secondShot = secondShot;
        frameScore = 0;
    }
    bool Frame::isStrike()
    {
        return ( firstShot == 10);  //Страйк, если первым ударом выбито 10 кеглей
    }
    bool Frame::isSpare()
    {
        return ((firstShot+secondShot == 10) & !isStrike());
        //Спаре, если выбито 10 кеглей и первый удар не страйк
    }
    int Frame::getFirstShot()          //кегли в первом броске
    {
        return firstShot;
    }
    int Frame::getSecondShot()         //кегли во втором броске
    {
        return secondShot;
    }
    int Frame::CalcScore()
    {
        frameScore = firstShot + secondShot;
        return frameScore;
    }
    void Frame::AddScore(int points)
    {
        frameScore += points;
    }
    int Frame::getFrameScore()
    {
        return  frameScore;
    }
    Frame::~Frame()
    { }


    //на входе функции имеем указатель на объект первого броска и число уже пройденных раундов
    int CalcTotalScore(std::vector<Frame>::iterator it, int frame)
    {
        int totalGameScore = 0;     //общий счет игры

        for (int i = 0; i <= frame; i++)
        {
            if (i == 9)     //если это последний раунд, то нет начисления бонусных очков
            {
                it[i].CalcScore();
                totalGameScore += it[i].getFrameScore();
                continue;
            }
            if (it[i].isStrike())         //если это страйк, то след два броска с бонусом (если они есть)
            {
                if (i != frame)             //если это не последний бросок
                {
                    if (it[i + 1].isStrike())    //если след удар опять Strike
                    {
                        it[i].CalcScore();
                        it[i].AddScore(10);   //бонус за следующий страйк

                        if ((frame - i) >=2 )       //если существует еще бросок (+2)
                        {
                            it[i].AddScore(it[i+2].getFirstShot());  //добавляем бонус через один бросок
                        }
                    }
                    else            //если след раунд регулар или спар
                    {
                        it[i].CalcScore();                //добавляем бонус очки со след 2х бросков
                        it[i].AddScore(it[i+1].getFirstShot());
                        it[i].AddScore(it[i+1].getSecondShot());
                    }
                }
                else        //если это крайний бросок
                {
                    it[i].CalcScore();
                }
            }

            if (it[i].isSpare())      //если это спар, то начисляем бонусы на след бросок (если он уже сделан)
            {
                if (i != frame)
                {
                    it[i].CalcScore();
                    it[i].AddScore(it[i+1].getFirstShot());
                }
                else  //если это крайний бросок
                {
                    it[i].CalcScore();
                }
            }

            if ((!it[i].isStrike()) && (!it[i].isSpare()))  //если это обычный бросок
            {
                it[i].CalcScore();
            }

            totalGameScore += it[i].getFrameScore();    //общий счет игры, делаем инкремент на очки последнего раунда

        }
        return totalGameScore;      //возращаем общий счет игры
    }

