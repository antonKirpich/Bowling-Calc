#ifndef BOWLCALCVER2_FRAME_H
#define BOWLCALCVER2_FRAME_H

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



#endif //BOWLCALCVER2_FRAME_H
