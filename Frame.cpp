#include "Frame.h"

    Frame::Frame(int firstShot, int secondShot)        //конструктор
    {
        this->firstShot  = firstShot;
        this->secondShot = secondShot;
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

