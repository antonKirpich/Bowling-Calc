#ifndef BOWLCALCVER2_FRAME_H
#define BOWLCALCVER2_FRAME_H

#include <vector>

class Frame
{
public:
    Frame(int firstShot, int secondShot);
    bool isStrike();
    bool isSpare();
    int getFirstShot();
    int getSecondShot();
    int CalcScore();
    void AddScore(int points);
    int getFrameScore();
    ~Frame();

private:
    int firstShot;
    int secondShot;
    int frameScore;
};

//функция подсчета общего кол-ва очков
int CalcTotalScore(std::vector<Frame>::iterator iter, int frame);

#endif //BOWLCALCVER2_FRAME_H
